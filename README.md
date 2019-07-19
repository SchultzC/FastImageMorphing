# FastImageMorphing


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
- Default CMakeLists.txt is for a specific Virtual Environment using g++
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

