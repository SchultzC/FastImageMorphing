# FastImageMorphing


## Project Option # 1
### A C++ implementation of image morphing (Beier and Neely '92)
https://www.cs.princeton.edu/courses/archive/fall00/cs426/papers/beier92.pdf

- This repository contains a C++ implementation of Beier and Neely image morphing.  It leverages opencv GUI functionality to provide the user with the ability to change the position of the control vectors.  As noted in the paper it is possible to get some bad looking results when the control vectors cross ("don't cross the streams").


- Two border modes are possible "copy" and "wrap".  Default will build with "copy".  This controls the edge behavior of the image.



## Required Libraries:
- OpenCV 4.1

### To build and run
From within project directory
```
cmake .
```
```
make
```
```
./SpeedMorphing
```

### Build notes
- Default CMakeLists.txt is for the provided Udacity Virtual Environment using g++
- A separate CMakeList_myMAC.txt is provided for clang++


### Code Description
- **CapStone_SpeedMorphing.cpp** : main function which initialized the Morph class with the input image and a holder for the result image.  Displays the output via opencv GUI functionality.

- **Morph.h and Morph.cpp** : Contains the core of the morphing logic detailed in paper (mentioned above) as well as some intermediate calculations.

- **Point2d.h and Point2d.cpp** : Contains an implementation of a 2D point class used by the Morph class. Has methods specific to point arithmetic including overloads to both the + and - operators.

### Expected Operation
When:
```
./SpeedMorphing
```
is run the user should see and opencv GUI with 8 sliders that relate to 2 control vecotors.  The sliders are:
- **Line1 Xstart** : The x component of the control 1 vector starting point 
- **Line1 Ystart** : The y component of the control 1 vector starting point 
- **Line1 Xend** : The x component of the control 1 vector ending point 
- **Line1 Yend** : The y component of the control 1 vector ending point 

- **Line2 Xstart** : The x component of the control 2 vector starting point 
- **Line2 Ystart** : The y component of the control 2 vector starting point 
- **Line2 Xend** : The x component of the control 2 vector ending point 
- **Line2 Yend** : The y component of the control 2 vector ending point 

#### Recommended Use:
As mentioned some of the results can be crazy looking.  To get a feel for things, I recommend starting by moving the **Line2 Yend** slider first as this shows intuitive behavior that will not cross the control vectors.



### Rubric Points
- **README** (all)

- **Compiling and Testing** (all)

- **Loops, Functions, I/O**:
  - An understanding of C++ functions and control structures. (See Morph.h, Point2d.h)
  - Project reads data from a file and process the data, or the program writes data to a file. (See CapStone_SpeedMorphing.cpp  line10 reading image from disk)
  - Project accepts user input and processes the input. (See CapStone_SpeedMorphing.cpp  Set up opencv GUI to take user input via sliders)
  
- **Object Oriented Programming**:
  - Project uses Object Oriented Programming techniques. (See Morph.h, Point2d.h, CapStone_SpeedMorphing.cpp)
  - Classes use appropriate access specifiers for class members. (See Morph.h, Point2d.h for public and private methods and data)
  - Class constructors utilize member initialization lists (See Morph.h line16, Point2d.h line14)
  - Classes abstract implementation details from their interfaces. (See Morph.h, Point2d.h)
  - Classes encapsulate behavior. (See Morph.h, Point2d.h)
  - Classes follow an appropriate inheritance hierarchy (Morph inherits Point2D so that it can perform the required calculations).
  - Overloaded functions allow the same function to operate on different parameters. (See Point2d.h  both the + and - operators have been overloaded)
  
- **Memory Management**:
  - Project uses move semantics to move data, instead of copying it, where possible. (see CapStone_SpeedMorphing.cpp line13 and line14)
  - Project uses smart pointers instead of raw pointers. shared_ptr was used for the image Mats this was an in an effort to make concurrency possible/efficient later, though it was not actually implemented here. (see CapStone_SpeedMorphing.cpp line13 and line14)
