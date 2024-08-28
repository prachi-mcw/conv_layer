# Convolution Implementation in C++ for 1x1 and 3x3 kernels
The repo contains kernel implementation for 1x1 and 3x3 convolution in C++. The python script is used for validation
# Prequisites 
- g++
- python3
# How to run 
Note: make sure to enable python environment in the terminal before running
```
    cd conv1_1
    g++ -std=c++11 -O3 conv3d_1_1.cpp -o conv3d
    ./conv3d
    python conv3d_1_1.py
    python compare.py
    
```
```
    cd conv3_3
    g++ -std=c++11 -O3 conv3d_3_3.cpp -o conv3d
    ./conv3d
    python conv3d_3_3.py
    python compare.py
```
