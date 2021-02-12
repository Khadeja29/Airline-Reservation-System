#include <iostream>
#include <pthread.h> // to use pthreads
#include <stdio.h>    //printf library
#include <stdlib.h> // random number choosing library   

using namespace std;

// 1- Gloabal Intializations:

int M[2][50]; //Gloabal Declaration and intialization to zero of the 2D array M representing seats
bool capacity_full =false; //keeping a check for capacity
int seats_left =100; //To change if capacity_full to true if seats left are 0
int turn=0; //For busy waiting

// 2- TravelAgency Functions:

void * booking_1(void *trav) //TravelAgency1 thread
{
	int * id_1 = (int*) trav; //ID of thread
	while(capacity_full== false ) //Capcity is not full/seats left
	{
		//Non-critical Region
		//Create a random seat number
		int row_1= rand ()%2;//geneates number 0-1 value for row
		int col_1= rand ()% 50; //geneates number 0-49 value for col
		
		//Loop and Busy waiting
		while (turn!=0 ) 
		{ }
		
		//Critical Region
		printf("Agency %d Entered Critical Region \n",*id_1); //indicate Critical region
		if (M[row_1][col_1]== 0) //The seat is not occupied
		{
			M[row_1][col_1] = *id_1; //Mark the seat as 1
			seats_left--; //reduced seat capacity 
			int seat_No;//Calculate seat number
			if (row_1 ==0) 
			{
				seat_No = col_1+1;
			}
			else{
				seat_No = (2*col_1)+1;
			}
			printf("Seat Number %d is reserved by Agency %d \n",seat_No,*id_1);//indicate seat alloaction
				
		}
		
		//Change Turn to TravelAgency2
		turn= 1;
		printf("Agency %d Exit Critical Region \n\n",*id_1); //indicate turn change
		
	}
	
}

void * booking_2(void * trv) //TravelAgency2 thread
{
	int * id_2 = (int*) trv; 
	while(capacity_full == false) //Capcity is not full/seats left
	{
		//Non-critical region
		//Create a random seat number
		int row_2= rand ()%2;//geneates number 0-1 value for row
		int col_2= rand ()% 50; //geneates number 0-49 value for col
		
		//looping and busy waiting
		while (turn!=1) 
		{  }
		printf("Agency %d Entered Critical Region \n",*id_2); //indicate critical region
		if (M[row_2][col_2]== 0) //The seat is not occupied
	    {
			//Critical Region	
			M[row_2][col_2] = *id_2; //Mark the seat as 2
			seats_left--; //reduced seat capacity 
			int seat;
			if (row_2 ==0) 
			{
				seat= col_2+1;
			}
			else{
				seat = (2*col_2)+1;
			}//Calculate seat number
			printf("Seat Number %d is reserved by Agency %d \n",seat,*id_2); //indicate seat alloaction
				 
		}
		
        //Change turn to TravelAgency1		
		turn= 0;
		printf("Agency %d Exit Critical Region \n\n",*id_2); //indicate turn change
	
	}
}

// 3- Main thread
int main()
{
	//4- Intializations,Thread Creation & Function calls
	srand(time(NULL)); //To makes sure seat value choosen is random
	
	//Intializating all seats to zero
	for(int i=0;i < 2; i++)
    {
        for(int j=0;j < 50; j++)
        {
			M[i][j]=0;
        }
    }
	
	//Intializations to create Travel Agency threads
	pthread_t TravelAgency1,TravelAgency2; 
	int TAI_1 = 1;
	int TAI_2 = 2;
	
	//Agency thread creation and function calls
	pthread_create(&TravelAgency1,NULL,booking_1,(void*) &TAI_1);
	pthread_create(&TravelAgency2,NULL,booking_2,(void*) &TAI_2);
	
	//5- Main Thread task to check if capacity is full
	bool check =true;
	while ( check)
    {
		if ( seats_left !=0) //Checks if number of seats is greater than zero
		{
			capacity_full = false;
		}
		else
		{
			capacity_full = true;
			check = false;
			
		}
	}

	
	//6- Joining threads/ Printing the Seating Plan
    pthread_join(TravelAgency1,NULL);
    pthread_join(TravelAgency2,NULL);
	
	
	printf("No Seats Left \n\n");
	
	
	printf("Plane is full:\n\n");
	
	//print out the matrix
	for(int i=0;i < 2; i++)
    {
        for(int j=0;j < 50; j++)
        {
			int ans= M[i][j];
			printf("%d",ans);
            
        }
        printf("\n");
    }
	

	return 0;
}