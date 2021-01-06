# ALU-Simulator
This mini project implements a C-based simulator which simulates how arithmetic operations are implemented on hardware (logic gate) level. 
It includes four arithmetic operations (addition, subtraction, multiplication and division) for three data types (signed and unsigned int32, float32). 
Please refer to the documentation for more details on how each operation is implemented. 
Note that efficient implementations of arithemtic on hardware are very complicated and require many careful designs. This project is only a primary simulation of some basic ideas in this direction. 

## TODO
There are still some minor bugs remained to be fixed: 
1. For float32, computations involving 0 all fail because 0 requires some special encoding in IEEE 754, and the corresponding logics are not implemented in the current version yet. 
2. For float32, some tests fail due to a difference in the least significant bit, which is very likely caused by some difference in the detailed logics of the rounding process. 
