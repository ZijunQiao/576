HW1

- A program to display a 1920x1080 image. This has been given as Microsoft Visual C++ .dsp and .dsw project files along with the accompanying code in the .cpp and .h files

The project includes the following important files.
1. Image.h	- header file for MyImage class
2. Image.cpp	- defines operations on an image such as read, write, modify
3. Main.cpp	- entry point of the application, takes care of the GUI, the 
		  image display operations, and the initialization of the RGB image.

The current setting is tested by `Visual Studio Community 2019` , version `16.2.4`.

- Compile the program to produce a an executable Image.exe
- To run the program you need to provide the program with command line arguments as below, they can be passed in Visual C++ using Project > Settings or just launch a .exe file from the command prompt

```
$ Image.exe ./miamibeach.rgb ModeNumber Ratio anti-alising
```
Mode 1 for resizing only.
Mode 2 for magnifier.
Mode 3/other for HW1Q3.
If the forth argument set as 1,then use anti-alising function.