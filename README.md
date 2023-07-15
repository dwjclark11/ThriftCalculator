# ThriftCalculator
Fun little calculator that uses Thrift, Imgui, Glad, and SDL. 
This is basically an extended version of the [C++ Thrift Calculator tutorial][https://thrift.apache.org/tutorial/cpp.html] to gain a better understanding of how to 
use thrift with a GUI appilication.

The client in this case is the Calculator, using ImGui, GLAD, and SDL to create the required buttons, window, etc. The server side does all the calculations. 
When the ```=``` is pushed, a call is made to the server to calculate the chosen numbers. The ```Server``` and ```Client``` are their own separate programs. 
The server must be running in order to get the client to work. 

## Requirements
* GLAD
* ImGui
* SDL
* Thrift Libraries and Compiler

### VCPKG
If you have vcpkg you can install the required thirft libraries with the following from the CMD LINE:

* ```vcpkg install thrift:x64-windows```

Or you can build them from source: [Thrift Source][https://github.com/apache/thrift/releases]

### Thrift Compiler
* You can get the thrift compiler from here: [Thrift Download][https://thrift.apache.org/download]

