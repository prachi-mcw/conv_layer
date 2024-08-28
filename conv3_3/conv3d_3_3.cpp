#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdint>


// Function to write .npy file header
void write_npy_header(std::ofstream& ofs, int batch_size, int out_channels, int out_depth, int out_height, int out_width) {
    // Define .npy header information
    std::string header = "{'descr': '<f4', 'fortran_order': False, 'shape': (";
    header += std::to_string(batch_size) + ", " + std::to_string(out_channels) + ", " +
              std::to_string(out_depth) + ", " + std::to_string(out_height) + ", " +
              std::to_string(out_width) + "), }";

    // Padding to align header to 16 bytes
    while ((header.size() + 10) % 16 != 0) {
        header += ' ';
    }

    // Write the magic string and version number
    ofs.write("\x93NUMPY", 6);
    uint8_t version[2] = {1, 0};
    ofs.write(reinterpret_cast<char*>(version), 2);

    // Write the header length and header itself
    uint16_t header_len = static_cast<uint16_t>(header.size());
    ofs.write(reinterpret_cast<char*>(&header_len), sizeof(header_len));
    ofs.write(header.c_str(), header.size());
}

// Function to save output to .npy file
void save_output_to_npy(const std::string& filename, const std::vector<float>& output, int batch_size, int out_channels, int out_depth, int out_height, int out_width) {
    std::ofstream ofs(filename, std::ios::binary);

    // Write .npy header
    write_npy_header(ofs, batch_size, out_channels, out_depth, out_height, out_width);

    // Write the output data
    ofs.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));

    ofs.close();
}
void conv3d(const float* input, const float* filter, float* output,
            int batch_size, int in_channels, int in_depth, int in_height, int in_width,
            int out_channels, int filter_depth, int filter_height, int filter_width,
            int stride_d, int stride_h, int stride_w, int pad_d, int pad_h, int pad_w) {

    int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
    int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
    int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

    for (int n = 0; n < batch_size; ++n) {
        for (int oc = 0; oc < out_channels; ++oc) {
            for (int od = 0; od < out_depth; ++od) {
                for (int oh = 0; oh < out_height; ++oh) {
                    for (int ow = 0; ow < out_width; ++ow) {
                        float sum = 0.0f;
                        for (int ic = 0; ic < in_channels; ++ic) {
                            for (int fd = 0; fd < filter_depth; ++fd) {
                                for (int fh = 0; fh < filter_height; ++fh) {
                                    for (int fw = 0; fw < filter_width; ++fw) {
                                        int id = od * stride_d + fd - pad_d;
                                        int ih = oh * stride_h + fh - pad_h;
                                        int iw = ow * stride_w + fw - pad_w;
                                        if (id >= 0 && id < in_depth && ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
                                            int input_idx = ((((n * in_channels + ic) * in_depth + id) * in_height + ih) * in_width + iw);
                                            int filter_idx = (((((oc * in_channels + ic) * filter_depth + fd) * filter_height + fh) * filter_width + fw));
                                            sum += input[input_idx] * filter[filter_idx];
                                        }
                                    }
                                }
                            }
                        }
                        int output_idx = ((((n * out_channels + oc) * out_depth + od) * out_height + oh) * out_width + ow);
                        output[output_idx] = sum;
                    }
                }
            }
        }
    }
}

void print_dimensions(int batch_size, int channels, int depth, int height, int width, const std::string& name) {
    std::cout << name << " dimensions: " << batch_size << "x" << channels << "x" << depth << "x" << height << "x" << width << std::endl;
}

int main() {
    // Define dimensions
    const int batch_size = 1;
    const int in_channels = 64;
    const int in_depth = 16;  // Added depth dimension
    const int in_height = 32;
    const int in_width = 32;
    const int out_channels = 64;
    const int filter_depth = 3;  // 3x3x3 filter
    const int filter_height = 3;
    const int filter_width = 3;
    const int stride_d = 1;
    const int stride_h = 1;
    const int stride_w = 1;
    const int pad_d = 1;
    const int pad_h = 1;
    const int pad_w = 1;

    // Calculate output dimensions
    int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
    int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
    int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

    // Print dimensions
    print_dimensions(batch_size, in_channels, in_depth, in_height, in_width, "Input");
    print_dimensions(out_channels, in_channels, filter_depth, filter_height, filter_width, "Filter");
    print_dimensions(batch_size, out_channels, out_depth, out_height, out_width, "Output");

    std::vector<float> input(batch_size * in_channels * in_depth * in_height * in_width);
    std::vector<float> filter(out_channels * in_channels * filter_depth * filter_height * filter_width);
    std::vector<float> output(batch_size * out_channels * out_depth * out_height * out_width);

    // Initialize input and filter with sequential values
    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = static_cast<float>(i + 1);
    }
    for (size_t i = 0; i < filter.size(); ++i) {
        filter[i] = static_cast<float>(i + 1);
    }

    // Perform convolution and measure time
    auto start = std::chrono::high_resolution_clock::now();
    conv3d(input.data(), filter.data(), output.data(),
           batch_size, in_channels, in_depth, in_height, in_width,
           out_channels, filter_depth, filter_height, filter_width,
           stride_d, stride_h, stride_w, pad_d, pad_h, pad_w);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Convolution time: " << duration.count() << " ms" << std::endl;

    // Print a few input, filter, and output values for verification
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nFirst few input values:" << std::endl;
    for (int i = 0; i < 10 && i < input.size(); ++i) {
        std::cout << input[i] << " ";
    }
    std::cout << "\n\nFirst few filter values:" << std::endl;
    for (int i = 0; i < 10 && i < filter.size(); ++i) {
        std::cout << filter[i] << " ";
    }
    std::cout << "\n\nFirst few output values:" << std::endl;
    for (int i = 0; i < 10 && i < output.size(); ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    // Save output to .npy file
    save_output_to_npy("cpp_output.npy", output, batch_size, out_channels, out_depth, out_height, out_width);

    return 0;
}