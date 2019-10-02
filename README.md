# assignment2
Arshia Behzad
2320643
behzad@chapman.edu
CPSC 230-06
Assignment 2

Source Files: main.cpp, board.h, board.cpp, cell.h, cell.cpp

#Any issues
#Who you calibrated with, if any


Game of Life

Stephen helped me with the deconstructor 
I went to stackoverflow to see how to append to a file, debuging and how to
use system.pause()

I made my array 2 rows and 2 columns larger than the actual board. This forms a sort
of border (which I have patened as the BehzadBorder™) in which it makes it easier 
(at least for me conceptually) to both check neighbors and work the other modes. 

In classic mode this border is filled with completely dead cells. This border allows 
for not needing many more if statements when checking neighbors on corners of the 
array 

In donut mode the border is filled with the oppoiste end. For example the top border
is filled with last row of the array. This allows for the code to work without any
further changes 

In mirror mode the border is filled with the same end. For example the top border
is filled with first row of the array. This allows for the code to work without any
further changes 

stoping alternating series of generations is not functional right now


