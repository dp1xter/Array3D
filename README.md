# Array3D

A class for storing a three-dimensional array of 17-bit positive integers.

# Features
* Accessing an array element in O(1) time and memory (the implementation can use a constant amount of additional memory, regardless of the size of the array)
input and output operators.  
* Multiplication by a number, where the result is a new array.
* Addition and subtraction of two arrays, where the result is also a new array (dimensions on all three axes must match, otherwise UB).
* A static method for creating an array that takes three positive numbers as its dimensions.

# Requirements
* According to the requirements of lab-work, the use of the STL is prohibited.
* The memory limit for the class is (x * y * z * 17) / 8 + const, where x, y, z is the size of the array, const is some constant.

# Tests
**Google-tests** are connected to the project.