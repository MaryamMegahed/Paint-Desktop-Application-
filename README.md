# Paint-Desktop-Application-
Paint Desktop Application Using Qt C++

![uml diagram](https://i.imgur.com/Q4MiPy3.png)


In this project we have 5 classes:
        ->Zoom class:
This class responsible for zooming the program main window 
          ->Re-Size class:
This class responsible for resize the program window 
            ->Main Window:
The main class in the program because it includes functions 
- draw shapes (square-circle-line)
-  functions (fill the shape – color pen -color size)
-  functions(undo-redo)
- functions (search-sort) that we can search for specific shape by its name and sort the shapes by its dimeter
- function (eraser) to clear the wrong shapes
- functions(cut-paste) to make the program easier 
- The main function (open – new – save) to open a picture in the program, save to save the images that drawn by the user and new that open a new window to create new project.
->About class:
The class that includes the main information about the program
->Draw panel class:
- It is the class responsible for mouse action and function starting from pressing the left button and ending with the releasing of the button.
- Mouse event: is responsible for drawing shapes, getting location, and information about the drawn shapes.
- Clear: responsible for clearing the main window of the program.
- Undo/redo: getting the previous drawn shapes of the program.
- Setting the brush size, pen width, shapes color, pen color, and the style of drawing 

