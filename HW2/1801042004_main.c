#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// it prints whitespaces number of length times
void Print_Whitespace( int length);
// it calculates the difference between LN and guess
void show_distance(int guess ,int LN );
//it just prints the scores which given as parameters
void show_scores(int score_human, int score_program);
// it prints  trial,min and max value, take the guess from user and return it
int make_a_guess (int trial, int min, int max);
int Play_Lucky_Number();
void draw_hourglass (int height);
void draw_mountain_road (int length, int max_radius);
// test program for all functions
void Menu();

int main(int argc, char const *argv[]){
	
	srand(time(NULL)); //for creating random numbers
	Menu();// it holds the hole menu activities

	return 0;
}


void Print_Whitespace( int length){ // it prints whitespaces number of length times
	int i;
	for ( i = 0; i< length; ++i){
		printf(" ");
	}
}
void show_distance(int guess ,int LN ){	// it calculates the difference between LN and guess
	int difference,i;
	difference=LN-guess;
	
	if (difference<0){
		difference= difference*(-1);
	}
	for (i = 0; i <10 ; ++i){			//if difference between in i power of 2 and i+1 power of 2, then distance is i+1				
		
		if ((pow(2,i)<=difference) && difference< pow(2,i+1)){

			printf("Distance : %d\n",i+1);

			i=10;
		}
		else if(difference==0){
			printf("Distance : 0. You win!\n");
			i=10;
		}
	}

}
void show_scores(int score_human, int score_program){ //it just prints the scores which given as parameters
	printf("\n");
	printf("Your Score: %d Program Score: %d\n",score_human,score_program);
}
int make_a_guess (int trial, int min, int max){	// it prints  trial,min and max value, take the guess from user and return it
	int guess;
	printf("(Trial: %d) Make a guess between %d and %d: ",trial,min,max);
	scanf("%d",&guess);
	printf("\n");
	return guess;
}
int Play_Lucky_Number(){

	int guess,trial=1,min=1,max=1024,LN;
	

	LN=rand()%1024 + 1; //it creates random number between 0-1025
	
	do{
	
		guess=make_a_guess(trial,min,max);	//it prints trial,min,max value and take guess from user
		
		if (min<=LN && LN<guess){	//if LN between min and guess,it makes max=guess
			max=guess;
		}
		else if(guess<LN && LN<=max){ //if LN between guess and max,it makes min=guess
			min=guess;
		}
		show_distance(guess,LN);//it calculates distance and print it

		trial++;
	}while(guess!=LN  &&  trial<=10); //user has 10 trial,if user right guess the LN and if trial is not higher then 10 loop is stop,if trial is higher than 10 it stop too

	if (guess==LN){
		return 1;	//if user win
	}
	else{
		return 0; //if program win
	}
}
void draw_hourglass (int height){
	
	int i,j,white_space=0;
	
	printf("\n");
	for ( i = 1; i < height; i=i+2){

		Print_Whitespace(white_space); //it prints whitespaces

		for ( j = 0; j< (height-i+1); ++j){//it prints * as much as height but i is increasing ,so it will print * as much as two less  each time.
										   //when it comes 1 , it is not printing
			printf("*");
		}
		white_space++;//to center the shape as wanted ,whitespace increasing 
		printf("\n");
	}

	for ( i = 1; i <=height; i=i+2){// it prints a pyramid 

		Print_Whitespace(white_space);

		for ( j = 0; j< i; ++j){
			printf("*");
		}
		white_space--;
		printf("\n");
	}

}
void draw_mountain_road (int length, int max_radius){
	
	int Temp_r,white_space=0,i,j,edge_number=0,direction=0;
	
	printf("\n");

	

	while(length!=edge_number){ // it keeps going until length = edge_number
		
		Temp_r = rand()%(max_radius+1); //it creates random number between 0-max_radius(R) inclusively
		
		if (edge_number==0){//it just  works once , to avoid overflow  it prints whitespaces max_radius times

			white_space=Temp_r+max_radius;
		}
	
		if (direction==0){ //temp_r is temporary radius, it prints the half circle ,if direction is = 0 it draws first / , then \
			
			for ( i = 0; i < Temp_r; ++i){	 
				
				
				Print_Whitespace(white_space);
				printf("/");
				printf("\n");
				white_space--;

			}
			
			Print_Whitespace(white_space);	//it center the edge ,int this case whitespace=max_radius
		
			printf("|");
			printf("\n");
			
			for ( i = 0; i < Temp_r; ++i){	
			
				
				Print_Whitespace(white_space+1);
				printf("\\");
				printf("\n");
				white_space++;

			}
			direction=1;
			white_space++;
		}

		else if (direction==1){//temp_r is temporary radius, it prints the half circle ,if direction is =1 it draws first \ then /
			
			for ( i = 0; i < Temp_r; ++i){	
			
				
				Print_Whitespace(white_space);
				printf("\\");
				printf("\n");
				white_space++;

			}

	
			Print_Whitespace(white_space);
			printf("|");
			printf("\n");

			for ( i = 0; i < Temp_r; ++i){	
				
				
				Print_Whitespace(white_space-1);
				printf("/");
				printf("\n");
				white_space--;

			}
			direction=0;
			white_space--;	
			
		}
		edge_number++; //it increasing edge number for each half circle

	}

}

void Menu(){

	int choice, N,R, height,score_program=0,score_human=0,win;
	
	do{
		printf("\n");// it displays menu
		printf("***** MENU *****\n");
		printf("1.Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");

		scanf("%d",&choice); //it takes choice
		switch(choice){

			case 1:

				win=Play_Lucky_Number(); //user play the game, it returns who win the game
				
				if (win==1){//if value is 1 then human win the game
					score_human++;	
				}
				else{//if value is 0 then program win the game
					score_program++;
				}
				show_scores(score_human,score_program); //it just show scores


				break;

			case 2:

				printf("Please enter the height: \n");
				scanf("%d",&height);
							
				while((height%2)==0){// it controls the height , is it odd or not
					printf("You entered en even number, please enter an odd number\n");
					scanf("%d",&height);
				}
				
				draw_hourglass(height); //drawing hourglass

				printf("\n");
				break;
			
			case 3:
	
				printf("Please give the length\n");//it takes N and R
				scanf("%d",&N);
				printf("Please give the max radius\n");
				scanf("%d",&R);

				draw_mountain_road(N,R); //it draws mountain road

				printf("\n");
				break;

			case 4:
				printf("\nThank you for playing this .\n");	// it will shut down the program after that
				break;

			default:
				printf("You entered an invalid number, please enter a valid number\n");	 // it conrols choice about menu options
		}
	}while(choice!=4);// it keeps going until choice is 4
}