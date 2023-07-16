# ThriftCalculator
Fun little calculator that uses Thrift, Imgui, Glad, and SDL. 
This is basically an extended version of the [C++ Thrift Calculator tutorial](https://thrift.apache.org/tutorial/cpp.html) to gain a better understanding of how to 
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

Or you can build them from source: [Thrift Source](https://github.com/apache/thrift/releases)

### Thrift Compiler
* You can get the thrift compiler from here: [Thrift Download](https://thrift.apache.org/download)
* The thrift compiler will have the version in the name, I recommend renaming the file to ```thrift.exe``` for simplicity.
* Once you have the ```thrift.exe```, put in in a good location like ```C:\thrift\thrift.exe```
* Then you are going to want to set the path as a system variable so you can call thrift from any CMD Line

![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/aada7099-5103-43ab-b726-a30cf15f02fc)
![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/a681cf0f-1b82-4c84-9e24-d3ad1710de43)
![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/b2db280c-d32c-4d1b-bc44-ea72e255ce05)

* If the path is not set, in Visual Studio the ```Custom Build Tool``` for the thrift files will have to be changed to accommodate where your thrift compiler is located.
* Go to the properties of the ```calculator.thrift``` file and adjust the command line arguments to use the path where your thrift compiler is located

![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/30633bc2-0b1e-4c58-8ddd-9bba7966d05d)

You can change the CMD Line arguments to something like below:
```C:\thrift\thrift.exe -gen cpp -o .  $(ProjectDir)thrift\%(Filename)%(Extension)``` -- Use your filepath for thrift.
