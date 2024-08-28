// #include <iostream>
// #include <vector>
// #include <chrono>
// #include <fstream>
// #include <string>
// #include <cstring>



// void write_npy_header(std::ofstream& file, const std::vector<int>& shape, int word_size) {
//     std::string magic_string = "\x93NUMPY";
//     char version[2] = {1, 0};
//     file.write(magic_string.c_str(), magic_string.size());
//     file.write(version, 2);

//     std::string header = "{'descr': '<f4', 'fortran_order': False, 'shape': (";
//     for (size_t i = 0; i < shape.size(); ++i) {
//         header += std::to_string(shape[i]);
//         if (i < shape.size() - 1) header += ", ";
//     }
//     header += "), }";
    
//     int header_len = header.size() + 1;  // +1 for the newline
//     int padding = 64 - (magic_string.size() + 2 + 2 + header_len) % 64;
//     header.append(padding, ' ');
//     header += '\n';

//     uint16_t header_len_le = header.size();
//     file.write(reinterpret_cast<char*>(&header_len_le), 2);
//     file.write(header.c_str(), header.size());
// }
// // Function to perform 3D convolution with weights
// void conv3d(const float* input, const float* filter, const float* weights, float* output,
//             int batch_size, int in_channels, int in_depth, int in_height, int in_width,
//             int out_channels, int filter_depth, int filter_height, int filter_width,
//             int stride_d, int stride_h, int stride_w, int pad_d, int pad_h, int pad_w) {
//     int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
//     int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
//     int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int oc = 0; oc < out_channels; ++oc) {
//             for (int od = 0; od < out_depth; ++od) {
//                 for (int oh = 0; oh < out_height; ++oh) {
//                     for (int ow = 0; ow < out_width; ++ow) {
//                         float sum = 0.0f;
//                         for (int ic = 0; ic < in_channels; ++ic) {
//                             for (int fd = 0; fd < filter_depth; ++fd) {
//                                 for (int fh = 0; fh < filter_height; ++fh) {
//                                     for (int fw = 0; fw < filter_width; ++fw) {
//                                         int id = od * stride_d + fd - pad_d;
//                                         int ih = oh * stride_h + fh - pad_h;
//                                         int iw = ow * stride_w + fw - pad_w;
//                                         if (id >= 0 && id < in_depth && ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
//                                             int input_idx = ((((n * in_channels + ic) * in_depth + id) * in_height + ih) * in_width + iw);
//                                             int filter_idx = ((((oc * in_channels + ic) * filter_depth + fd) * filter_height + fh) * filter_width + fw);
//                                             sum += input[input_idx] * filter[filter_idx] * weights[filter_idx];
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                         int output_idx = ((((n * out_channels + oc) * out_depth + od) * out_height + oh) * out_width + ow);
//                         output[output_idx] = sum;
//                     }
//                 }
//             }
//         }
//     }
// }

// int main() {
//     // Define dimensions
//     const int batch_size = 1;
//     const int in_channels = 128;
//     const int in_depth = 1;
//     const int in_height = 1;
//     const int in_width = 1;
//     const int out_channels = 64;
//     const int filter_depth = 1;
//     const int filter_height = 1;
//     const int filter_width = 1;
//     const int stride_d = 1;
//     const int stride_h = 1;
//     const int stride_w = 1;
//     const int pad_d = 0;
//     const int pad_h = 0;
//     const int pad_w = 0;

//     // Calculate output dimensions
//     int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
//     int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
//     int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

//     // Print dimensions
//     std::cout << "Input dimensions: " << batch_size << "x" << in_channels << "x" << in_depth << "x" << in_height << "x" << in_width << std::endl;
//     std::cout << "Filter dimensions: " << out_channels << "x" << in_channels << "x" << filter_depth << "x" << filter_height << "x" << filter_width << std::endl;
//     std::cout << "Output dimensions: " << batch_size << "x" << out_channels << "x" << out_depth << "x" << out_height << "x" << out_width << std::endl;

//     // Allocate memory for input, filter, weights, and output
//     std::vector<float> input(batch_size * in_channels * in_depth * in_height * in_width);
//     std::vector<float> filter(out_channels * in_channels * filter_depth * filter_height * filter_width);
//     std::vector<float> weights(out_channels * in_channels * filter_depth * filter_height * filter_width);
//     std::vector<float> output(batch_size * out_channels * out_depth * out_height * out_width);

//     // Initialize input, filter, and weights with sequential values
//     for (size_t i = 0; i < input.size(); ++i) {
//         input[i] = static_cast<float>(i + 1);
//     }
//     for (size_t i = 0; i < filter.size(); ++i) {
//         filter[i] = static_cast<float>(i + 1);
//     }
//     for (size_t i = 0; i < weights.size(); ++i) {
//         weights[i] = static_cast<float>(i + 1);
//     }

//     conv3d(input.data(), filter.data(), weights.data(), output.data(),
//            batch_size, in_channels, in_depth, in_height, in_width,
//            out_channels, filter_depth, filter_height, filter_width,
//            stride_d, stride_h, stride_w, pad_d, pad_h, pad_w);
  

 

//     // Print a few output values for verification
//     std::cout << "First few output values:" << std::endl;
//     for (int i = 0; i < 5 && i < output.size(); ++i) {
//         std::cout << output[i] << " ";
//     }
//     std::cout << std::endl;


//     // Save output as .npy file
// std::string filename = "output.npy";
// std::ofstream file(filename, std::ios::binary);
// std::vector<int> shape = {batch_size, out_channels, out_depth, out_height, out_width};
// write_npy_header(file, shape, sizeof(float));
// file.write(reinterpret_cast<char*>(output.data()), output.size() * sizeof(float));
// file.close();

// std::cout << "Output saved as " << filename << std::endl;

//     return 0;
// }








// #include <iostream>
// #include <vector>
// #include <chrono>

// // Function to perform 3D convolution with weights
// void conv3d(const float* input, const float* filter, const float* weights, float* output,
//             int batch_size, int in_channels, int in_depth, int in_height, int in_width,
//             int out_channels, int filter_depth, int filter_height, int filter_width,
//             int stride_d, int stride_h, int stride_w, int pad_d, int pad_h, int pad_w) {
//     int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
//     int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
//     int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

//     for (int n = 0; n < batch_size; ++n) {
//         for (int oc = 0; oc < out_channels; ++oc) {
//             for (int od = 0; od < out_depth; ++od) {
//                 for (int oh = 0; oh < out_height; ++oh) {
//                     for (int ow = 0; ow < out_width; ++ow) {
//                         float sum = 0.0f;
//                         for (int ic = 0; ic < in_channels; ++ic) {
//                             for (int fd = 0; fd < filter_depth; ++fd) {
//                                 for (int fh = 0; fh < filter_height; ++fh) {
//                                     for (int fw = 0; fw < filter_width; ++fw) {
//                                         int id = od * stride_d + fd - pad_d;
//                                         int ih = oh * stride_h + fh - pad_h;
//                                         int iw = ow * stride_w + fw - pad_w;
//                                         if (id >= 0 && id < in_depth && ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
//                                             int input_idx = ((((n * in_channels + ic) * in_depth + id) * in_height + ih) * in_width + iw);
//                                             int filter_idx = ((((oc * in_channels + ic) * filter_depth + fd) * filter_height + fh) * filter_width + fw);
//                                             sum += input[input_idx] * filter[filter_idx] * weights[filter_idx];
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                         int output_idx = ((((n * out_channels + oc) * out_depth + od) * out_height + oh) * out_width + ow);
//                         output[output_idx] = sum;
//                     }
//                 }
//             }
//         }
//     }
// }

// int main() {
//     // Define dimensions
//     const int batch_size = 1;
//     const int in_channels = 128;
//     const int in_depth = 1;
//     const int in_height = 1;
//     const int in_width = 1;
//     const int out_channels = 64;
//     const int filter_depth = 1;
//     const int filter_height = 1;
//     const int filter_width = 1;
//     const int stride_d = 1;
//     const int stride_h = 1;
//     const int stride_w = 1;
//     const int pad_d = 0;
//     const int pad_h = 0;
//     const int pad_w = 0;

//     // Calculate output dimensions
//     int out_depth = (in_depth + 2 * pad_d - filter_depth) / stride_d + 1;
//     int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
//     int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

//     // Print dimensions
//     std::cout << "Input dimensions: " << batch_size << "x" << in_channels << "x" << in_depth << "x" << in_height << "x" << in_width << std::endl;
//     std::cout << "Filter dimensions: " << out_channels << "x" << in_channels << "x" << filter_depth << "x" << filter_height << "x" << filter_width << std::endl;
//     std::cout << "Output dimensions: " << batch_size << "x" << out_channels << "x" << out_depth << "x" << out_height << "x" << out_width << std::endl;

//     // Allocate memory for input, filter, weights, and output
//     std::vector<float> input(batch_size * in_channels * in_depth * in_height * in_width);
//     std::vector<float> filter(out_channels * in_channels * filter_depth * filter_height * filter_width);
//     std::vector<float> weights(out_channels * in_channels * filter_depth * filter_height * filter_width);
//     std::vector<float> output(batch_size * out_channels * out_depth * out_height * out_width);

//     // Initialize input, filter, and weights with sequential values
//     for (size_t i = 0; i < input.size(); ++i) {
//         input[i] = static_cast<float>(i + 1);
//     }
//     for (size_t i = 0; i < filter.size(); ++i) {
//         filter[i] = static_cast<float>(i + 1);
//     }
//     for (size_t i = 0; i < weights.size(); ++i) {
//         weights[i] = static_cast<float>(i + 1);
//     }

//     // Perform convolution and measure time
//     auto start = std::chrono::high_resolution_clock::now();
//     conv3d(input.data(), filter.data(), weights.data(), output.data(),
//            batch_size, in_channels, in_depth, in_height, in_width,
//            out_channels, filter_depth, filter_height, filter_width,
//            stride_d, stride_h, stride_w, pad_d, pad_h, pad_w);
//     auto end = std::chrono::high_resolution_clock::now();

//     std::chrono::duration<double, std::milli> duration = end - start;
//     std::cout << "Convolution time: " << duration.count() << " ms" << std::endl;

//     // Print a few output values for verification
//     std::cout << "First few output values:" << std::endl;
//     for (int i = 0; i < 5 && i < output.size(); ++i) {
//         std::cout << output[i] << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }





#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

void write_npy_header(std::ofstream& ofs, int batch_size, int out_channels, int out_height, int out_width) {
    // Define .npy header information
    std::string header = "{'descr': '<f4', 'fortran_order': False, 'shape': (";
    header += std::to_string(batch_size) + ", " + std::to_string(out_channels) + ", " +
              std::to_string(out_height) + ", " + std::to_string(out_width) + "), }";

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
void save_output_to_npy(const std::string& filename, const std::vector<float>& output, int batch_size, int out_channels, int out_height, int out_width) {
    std::ofstream ofs(filename, std::ios::binary);

    // Write .npy header
    write_npy_header(ofs, batch_size, out_channels, out_height, out_width);

    // Write the output data
    ofs.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));

    ofs.close();
}

// Function to perform  convolution with weights
void conv(const float* input, const float* filter, const float* weights, float* output,
            int batch_size, int in_channels, int in_height, int in_width,
            int out_channels, int filter_height, int filter_width,
            int stride_h, int stride_w, int pad_h, int pad_w) {
    int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
    int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

    for (int n = 0; n < batch_size; ++n) {
        for (int oc = 0; oc < out_channels; ++oc) {
            for (int oh = 0; oh < out_height; ++oh) {
                for (int ow = 0; ow < out_width; ++ow) {
                    float sum = 0.0f;
                    for (int ic = 0; ic < in_channels; ++ic) {
                        for (int fh = 0; fh < filter_height; ++fh) {
                            for (int fw = 0; fw < filter_width; ++fw) {
                                int ih = oh * stride_h + fh - pad_h;
                                int iw = ow * stride_w + fw - pad_w;
                                if (ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
                                    int input_idx = ((n * in_channels + ic) * in_height + ih) * in_width + iw;
                                    int filter_idx = (((oc * in_channels + ic) * filter_height + fh) * filter_width + fw);
                                    sum += input[input_idx] * filter[filter_idx] * weights[filter_idx];
                                }
                            }
                        }
                    }
                    int output_idx = ((n * out_channels + oc) * out_height + oh) * out_width + ow;
                    output[output_idx] = sum;
                }
            }
        }
    }
}

int main() {
    // Define dimensions
    const int batch_size = 1;
    const int in_channels = 128;
    const int in_height = 1;
    const int in_width = 1;
    const int out_channels = 64;
    const int filter_height = 1;
    const int filter_width = 1;
    const int stride_h = 1;
    const int stride_w = 1;
    const int pad_h = 0;
    const int pad_w = 0;

    // Calculate output dimensions
    int out_height = (in_height + 2 * pad_h - filter_height) / stride_h + 1;
    int out_width = (in_width + 2 * pad_w - filter_width) / stride_w + 1;

    // Print dimensions
    std::cout << "Input dimensions: " << batch_size << "x" << in_channels << "x" << in_height << "x" << in_width << std::endl;
    std::cout << "Filter dimensions: " << out_channels << "x" << in_channels << "x" << filter_height << "x" << filter_width << std::endl;
    std::cout << "Output dimensions: " << batch_size << "x" << out_channels << "x" << out_height << "x" << out_width << std::endl;

    // Allocate memory for input, filter, weights, and output
    std::vector<float> input(batch_size * in_channels * in_height * in_width);
    std::vector<float> filter(out_channels * in_channels * filter_height * filter_width);
    std::vector<float> weights(out_channels * in_channels * filter_height * filter_width);
    std::vector<float> output(batch_size * out_channels * out_height * out_width);

    // Initialize input, filter, and weights with sequential values
    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = static_cast<float>(i + 1);
    }
    for (size_t i = 0; i < filter.size(); ++i) {
        filter[i] = static_cast<float>(i + 1);
    }
    for (size_t i = 0; i < weights.size(); ++i) {
        weights[i] = static_cast<float>(i + 1);
    }

    // Perform convolution and measure time
    auto start = std::chrono::high_resolution_clock::now();
    conv(input.data(), filter.data(), weights.data(), output.data(),
           batch_size, in_channels, in_height, in_width,
           out_channels, filter_height, filter_width,
           stride_h, stride_w, pad_h, pad_w);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Convolution time: " << duration.count() << " ms" << std::endl;

    // Print a few output values for verification
    std::cout << "First few output values:" << std::endl;
    for (int i = 0; i < 5 && i < output.size(); ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;
save_output_to_npy("output.npy", output, batch_size, out_channels, out_height, out_width);
    std::cout << "Output saved to output.npy" << std::endl;

    return 0;
}
