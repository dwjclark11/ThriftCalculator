# ThriftCalculator
Fun little calculator that uses Thrift, Imgui, Glad, and SDL. 
This is basically an extended version of the [C++ Thrift Calculator tutorial](https://thrift.apache.org/tutorial/cpp.html) to gain a better understanding of how to use thrift with a GUI appilication.

![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/8f741709-a87b-47e3-8a2f-b68e7fc4d843)



The client in this case is the Calculator, using ImGui, GLAD, and SDL to create the required buttons, window, etc. The server side does all the calculations. 
When the ```=``` is pushed, a call is made to the server to calculate the chosen numbers. The ```Server``` and ```Client``` are their own separate programs. 
The server must be running in order to get the client to work. 

The calculator is only a simple calculator and is only to demonstrate the client-server relationship using thrift. It can definitely be extended to add more functionalities, etc.


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

![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/150fd1f0-0202-429b-bfc0-20cbf4a1c305)


* If the path is not set, in Visual Studio the ```Custom Build Tool``` for the thrift files will have to be changed to accommodate where your thrift compiler is located.
* Go to the properties of the ```calculator.thrift``` file and adjust the command line arguments to use the path where your thrift compiler is located

![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/906e6a09-3e7b-402a-bbe3-13aff9ff2e54)
![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/31f9bd97-c728-45ac-86f8-9ec81238ba5c)
![image](https://github.com/dwjclark11/ThriftCalculator/assets/63356975/cec38033-ba82-47fa-9eba-634f3499dfff)


You can change the CMD Line arguments to something like below:
```C:\thrift\thrift.exe -gen cpp -o .  $(ProjectDir)thrift\%(Filename)%(Extension)``` -- Use your filepath for thrift.

### Build
* Once the above requirements have been set, you should be able to build the VS sln.
* If everything builds successfully, go to the build folder and run the ```Server.exe```. If the server is not running when trying to run the Client Calculator, the client will fail to run.
* Once the server is running, you can now locally run the visual studio solution and use the calculator.
