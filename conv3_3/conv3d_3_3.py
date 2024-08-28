import torch
import torch.nn as nn
import numpy as np

def print_dimensions(batch_size, channels, depth, height, width, name):
    print(f"{name} dimensions: {batch_size}x{channels}x{depth}x{height}x{width}")

# Define dimensions (same as in C++ code)
batch_size = 1
in_channels = 64
in_depth = 16
in_height = 32
in_width = 32
out_channels = 64
filter_depth = 3
filter_height = 3
filter_width = 3
stride_d = 1
stride_h = 1
stride_w = 1
pad_d = 1
pad_h = 1
pad_w = 1

# Calculate output dimensions
out_depth = (in_depth + 2 * pad_d - filter_depth) // stride_d + 1
out_height = (in_height + 2 * pad_h - filter_height) // stride_h + 1
out_width = (in_width + 2 * pad_w - filter_width) // stride_w + 1

# Print dimensions
print_dimensions(batch_size, in_channels, in_depth, in_height, in_width, "Input")
print_dimensions(out_channels, in_channels, filter_depth, filter_height, filter_width, "Filter")
print_dimensions(batch_size, out_channels, out_depth, out_height, out_width, "Output")

# Create input and filter tensors
input_tensor = torch.arange(1, batch_size * in_channels * in_depth * in_height * in_width + 1, dtype=torch.float32).reshape(batch_size, in_channels, in_depth, in_height, in_width)
filter_tensor = torch.arange(1, out_channels * in_channels * filter_depth * filter_height * filter_width + 1, dtype=torch.float32).reshape(out_channels, in_channels, filter_depth, filter_height, filter_width)

# Create Conv3d layer
conv3d = nn.Conv3d(in_channels, out_channels, kernel_size=(filter_depth, filter_height, filter_width),
                   stride=(stride_d, stride_h, stride_w), padding=(pad_d, pad_h, pad_w), bias=False)

# Set the weights of the Conv3d layer to our filter tensor
with torch.no_grad():
    conv3d.weight = nn.Parameter(filter_tensor)

# Perform convolution
output = conv3d(input_tensor)

# Print a few input, filter, and output values for verification
print("\nFirst few input values:")
print(input_tensor.flatten()[:10])

print("\nFirst few filter values:")
print(filter_tensor.flatten()[:10])

print("\nFirst few output values:")
print(output.flatten()[:10])

# Save the output to a .npy file
output_numpy = output.detach().cpu().numpy()
np.save("python_output.npy", output_numpy)
print("\nOutput saved to python_output.npy")