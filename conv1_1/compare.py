import numpy as np

cpp_output = np.load("output.npy")
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