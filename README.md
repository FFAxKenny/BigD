# PG: BigD
### Ejay Tumacder; Joshua Rivera

Landing BigD in the C and back out.

This project is the software that'll drive the uMouse hardware from the 
starting cell to the destination. We've decided to divide the project into 
two sub-projects: low and high.

## HIGH
Contains code that'll make navigate around the maze in hopes to map and
get to the center.  After getting to the center, the mouse should go back
to the starting cell and attempt a faster time.

The key functions for basic mouse functionality that link high and low are:

1. moveForwardOneCell
2. faceLeft
3. faceRight
4. faceBack

-Most of the meat is in moveForwardOneCell as it needs error correction 
-Error Correction is implemented with control algorithms such as 
 Proportional, Integral, and  Differential control.
-Functions 2-4 are easily achievable with basic motor functionality.

## LOW
A lot like how are own bodies work automatically to keep ourselves oriented.
This part of the code implements a way we can achieve the four functions
with great precision and accuracy.  With that being said, there is a lot of
emphasis here in error correction.

This is where we breakdown the sensor reading information into useful
data for the mouse so that it makes the correct decisions with the
two motors.
