# import torch
# import torch.nn as nn


# # Define custom Conv3d layer with separate weights
# class CustomConv3d(nn.Module):
#     def __init__(self, in_channels, out_channels, kernel_size, stride=1, padding=0):
#         super(CustomConv3d, self).__init__()
#         self.in_channels = in_channels
#         self.out_channels = out_channels
#         self.kernel_size = kernel_size if isinstance(kernel_size, tuple) else (kernel_size, kernel_size, kernel_size)
#         self.stride = stride if isinstance(stride, tuple) else (stride, stride, stride)
#         self.padding = padding if isinstance(padding, tuple) else (padding, padding, padding)

#         self.filter = nn.Parameter(torch.Tensor(out_channels, in_channels, *self.kernel_size))
#         self.weights = nn.Parameter(torch.Tensor(out_channels, in_channels, *self.kernel_size))

#     def forward(self, x):
#         return nn.functional.conv3d(x, self.filter * self.weights, stride=self.stride, padding=self.padding)

# # Define the custom convolutional layer
# conv_layer = CustomConv3d(in_channels=128, out_channels=64, kernel_size=(1, 1, 1), stride=(1, 1, 1), padding=(0, 0, 0))

# # Initialize filter and weights to match the sequential values used in the C++ code
# with torch.no_grad():
#     conv_layer.filter.copy_(torch.arange(1, conv_layer.filter.numel() + 1, dtype=torch.float32).view_as(conv_layer.filter))
#     conv_layer.weights.copy_(torch.arange(1, conv_layer.weights.numel() + 1, dtype=torch.float32).view_as(conv_layer.weights))

# # Define input tensor dimensions
# batch_size = 1
# in_channels = 128
# in_depth = 1
# in_height = 1
# in_width = 1

# # Create input tensor with sequential values
# input_tensor = torch.arange(1, batch_size * in_channels * in_depth * in_height * in_width + 1, dtype=torch.float32).view(batch_size, in_channels, in_depth, in_height, in_width)


# output_tensor = conv_layer(input_tensor)


# # Print the dimensions
# print("Input dimensions:", input_tensor.shape)
# print("Filter dimensions:", conv_layer.filter.shape)
# print("Weights dimensions:", conv_layer.weights.shape)
# print("Output dimensions:", output_tensor.shape)



# # Print a few output values for verification
# print("First few output values:")
# output_tensor_flat = output_tensor.view(-1)
# print(" ".join(f"{val.item():.6f}" for val in output_tensor_flat[:5]))



import torch
import torch.nn as nn
import numpy as np

# Define custom Conv2d layer with separate weights
class CustomConv2d(nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size, stride=1, padding=0):
        super(CustomConv2d, self).__init__()
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size if isinstance(kernel_size, tuple) else (kernel_size, kernel_size)
        self.stride = stride if isinstance(stride, tuple) else (stride, stride)
        self.padding = padding if isinstance(padding, tuple) else (padding, padding)

        self.filter = nn.Parameter(torch.Tensor(out_channels, in_channels, *self.kernel_size))
        self.weights = nn.Parameter(torch.Tensor(out_channels, in_channels, *self.kernel_size))

    def forward(self, x):
        return nn.functional.conv2d(x, self.filter * self.weights, stride=self.stride, padding=self.padding)

# Define the custom convolutional layer
conv_layer = CustomConv2d(in_channels=128, out_channels=64, kernel_size=(1, 1), stride=(1, 1), padding=(0, 0))

# Initialize filter and weights to match the sequential values used in the C++ code
with torch.no_grad():
    conv_layer.filter.copy_(torch.arange(1, conv_layer.filter.numel() + 1, dtype=torch.float32).view_as(conv_layer.filter))
    conv_layer.weights.copy_(torch.arange(1, conv_layer.weights.numel() + 1, dtype=torch.float32).view_as(conv_layer.weights))

# Define input tensor dimensions
batch_size = 1
in_channels = 128
in_height = 1
in_width = 1

# Create input tensor with sequential values
input_tensor = torch.arange(1, batch_size * in_channels * in_height * in_width + 1, dtype=torch.float32).view(batch_size, in_channels, in_height, in_width)

# Perform convolution
output_tensor = conv_layer(input_tensor)

# Print the dimensions
print("Input dimensions:", input_tensor.shape)
print("Filter dimensions:", conv_layer.filter.shape)
print("Weights dimensions:", conv_layer.weights.shape)
print("Output dimensions:", output_tensor.shape)

# Print a few output values for verification
print("First few output values:")
output_tensor_flat = output_tensor.view(-1)
for i in range(min(5, output_tensor_flat.size(0))):
    print(output_tensor_flat[i].item(), end=" ")
print()

# Save the output to a .npy file
output_numpy = output_tensor.detach().cpu().numpy()
np.save("python_output.npy", output_numpy)
print("\nOutput saved to python_output.npy")