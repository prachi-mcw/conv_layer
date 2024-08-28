# import numpy as np
# import sys

# def compare_npy_files(file1, file2, tolerance=1e-5):
#     # Load the .npy files
#     data1 = np.load(file1)
#     data2 = np.load(file2)

#     # Check if the shapes are the same
#     if data1.shape != data2.shape:
#         print(f"Shapes do not match: {data1.shape} vs {data2.shape}")
#         return False

#     # Compare the data
#     if np.allclose(data1, data2, atol=tolerance):
#         print("Arrays are equal within the specified tolerance.")
#         return True
#     else:
#         # Find the differences
#         diff = np.abs(data1 - data2)
#         max_diff = np.max(diff)
#         max_diff_index = np.unravel_index(np.argmax(diff), diff.shape)
        
#         print(f"Arrays are not equal. Maximum difference: {max_diff}")
#         print(f"Location of maximum difference: {max_diff_index}")
#         print(f"Value in first array: {data1[max_diff_index]}")
#         print(f"Value in second array: {data2[max_diff_index]}")
        
#         return False

# if __name__ == "__main__":
#     if len(sys.argv) != 3:
#         print("Usage: python compare_npy.py <file1.npy> <file2.npy>")
#         sys.exit(1)

#     file1 = sys.argv[1]
#     file2 = sys.argv[2]
    
#     compare_npy_files(file1, file2)

import numpy as np

cpp_output = np.load("cpp_output.npy")
python_output = np.load("python_output.npy")
print("Outputs are equal:", np.allclose(cpp_output, python_output, rtol=1e-5, atol=1e-5))

print("C++ output shape:", cpp_output.shape)
print("C++ output dtype:", cpp_output.dtype)
print("Python output shape:", python_output.shape)
print("Python output dtype:", python_output.dtype)
print("First few elements of C++ output:", cpp_output.flatten()[:10])
print("First few elements of Python output:", python_output.flatten()[:10])

print("C++ output range:", np.min(cpp_output), np.max(cpp_output))
print("Python output range:", np.min(python_output), np.max(python_output))