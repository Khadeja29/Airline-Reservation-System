# Airline-Reservation-System
## 1 Introduction
This project involoved simulation of a simple Airline Reservation System which will involve
accessing shared resources. In real life, there are travel agencies who try to reserve seats for
their customers. When a customer asks for a seat from a specific flight, the agency checks if
there is an empty seat in the aircraft and reserves it immediately (if there is any). Only one
reservations can be made on a seat, so there will be no overbooking. There will be one thread
per agency simulating the activities of that agency. When an agency thread is booking a seat,
the other agency will do busy waiting.
It is implemented using POSIX threads.

## 2 Program Flow and Explanation 
#### 1- Global Initializations: 
All the global variable initializations are made in this section for the two
child threads and main to be able to access them including the matrix M, turn variable for busy waiting
for the travel agent threads, seats_left as a counter to be changed when a seat is booked by the child
threads and for the main thread to check and change the availability of seats through capacity_full
variable.
####2- Travel Agency Functions: 
Two different functions for each Travel Agent threads. Each takes
the pointer to id (TAI) for the main as a parameter and converts it to a local pointer int variable. Then
the function keeps checking capacity_full, if it is false which means that at least one seat is empty , the
thread enters a non-critical(because it is not affected by other thread as each has unique variables to
generate random numbers) area and generates a random index for the row and column. The thread
then enters looping and busy waiting depending on the turn variable it either keeps looping so that the
other thread can alter its critical region or enters the critical region and gives an output to show so. Then
it checks if the randomly generated coordinate of M is not occupied (that is its value is zero).If it is not
occupied, the coordinate is assigned the value of TAI of that thread, seats_left is decremented and the
seat_No/seat is calculated from the coordinates and a statement is printed showing successful
registration. Afterwards turn is changed to indicate a change in thread turn in registered and if
otherwise.
#### 3- Main thread: Parent thread initialization
#### 4- Initializations, Thread Creation & Function calls: 
srand(time(NULL)); is implemented to
make sure distinct number is generated every time. Then the 2D array/matrix M if filled using a loop
before threads are created so it doesn’t affect the global variable M. The threads and TAI ids are also
initialized.
#### 5- Main Thread task to check if capacity is full: 
Two threads are created and the pointer to
TAI is passed as a parameter. After the thread creation the main continuously checks if the capacity_fill
is changed to true using the seats_left counter because looping over the global M wouldn’t be feasible
once threads are created.
#### 6- Joining threads after capacity is filled and indication/Printing the Seating
Plan: 
After the capacity_full is true, child threads are joined to stop their implementation and
whatever tasks that follow are only implemented by the main/parent thread. The statements which are
given indicated that no seats are left, and M is looped over to print out the seating plan because loop
won’t affect the global variable as only one thread is working.


## 3 Note:

The program was implemented as a part of coursework CS307: Operating Systems.For more details about the implementation refer to the pdf about the project implementation from the project folder.The comments in the code are numbered according to the section 2 above which aims to make following the code easier.

