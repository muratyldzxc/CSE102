#include <stdio.h>
#include <math.h>
#include<time.h>
#include<stdlib.h>
#define SQUARE 1
#define RECTANGULAR 2
#define CIRCLE 3
#define PI 3
#define RED 0
#define YELLOW 1
#define BLUE 2
#define BLACK 3
#define WHITE 4

// creates a body for pokemon according to its shape
double CreateBody (int shape);
// sets pokemons's color 
int SetColor (int color);
//Pre condition: if shape is a rectangular , we assume its short edge length is 5
//Post condition: returns movement length
double LoadMoves(int shape, double body_size);
// it takes the difference of lower and upper, than provide a random number between 0-difference
int SetAttackPower(int lower_bound, int upper_bound);
// prints all features of a pokemon
void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power);

// Driver test program given by homework
int main(){
	
	int shape, color, attack_power;
	double size_of_body, move_length; 
	
	shape=CIRCLE;
	size_of_body = CreateBody (shape) ;
	
	color=798;
	color = SetColor(color) ;
	
	move_length = LoadMoves(shape, size_of_body);
	
	attack_power = SetAttackPower(0,150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);

	return 0;
}


double CreateBody (int shape){
	
	int edge,height,radius;
	double area;
	
	if(shape==SQUARE){		//if it is square,it takes the edge and multiple itself to find area
		
		printf("Please enter the edge of the SQUARE\n");
		scanf("%d",&edge);
		area=edge*edge;
	}
	if (shape==RECTANGULAR){	//if it is rectangular,it takes the edge and height ,multiple height*edge  to find area

		printf("Please enter the base of the RECTANGULAR\n");
		scanf("%d",&edge);
		printf("Please enter the base of the RECTANGULAR\n");
		scanf("%d",&height);
		area=edge*height;

	}
	if (shape==CIRCLE){		//if it is circle,it takes the radius,then multiple itself and PI to find area

		printf("Please enter the radius of the CIRCLE\n");
		scanf("%d",&radius);
		area=radius*radius*PI;
	}
	return area;
}

int SetColor (int color){

	if (0<=color && color<=1000){	//if the number between 0-1000 it  returns modulo five of the number
		
		color=(color % 5);
	}
	else{						//otherwise it returns 1
		color=1;
	}
	return color;
}

//Pre condition: if shape is a rectangular , we assume its short edge length is 5
double LoadMoves(int shape, double body_size){

	double move,edge;
	
	if (shape==SQUARE){		//if it is square ,it gets the root of the body_size to find edge,then multiple by 4 to find move length
		edge=sqrt(body_size);
		move=4*edge;
	}
	if(shape==RECTANGULAR){	//if it is rectangular ,it divides the  body_size by 5 to find long edge,then multiple addition of short and long edge by 2 to find move length
		edge=(body_size/5);
		move=2*(5+edge);
	}
	if (shape==CIRCLE){
		edge=sqrt((body_size/PI));	//if it is circle ,it gets the root of division the body_size by PI ,then multiple by 2 and PI to find move length
		move=2*PI*edge;
	}
	return move;
}

int SetAttackPower(int lower_bound, int upper_bound){	// it takes the difference of lower and upper, than provide a random number between 0-difference
	int power,difference;								//and add that number to lower_bound
	srand(time(NULL));
	difference=(lower_bound - upper_bound);
	power=(lower_bound+rand()%difference);

	return power;
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power){
	int i,j;
	char name[3][12]={"SQUARE","RECTANGULAR","CIRCLE"};
	char colour[5][7]={"RED","YELLOW","BLUE","BLACK","WHITE"};
	
	printf("\n\n"); //for good looking
	
	if (shape==SQUARE){		//if it is square ,it prints a square
		int edge;
		edge=sqrt(body_size);
		for ( i = 0; i < edge; ++i){

			for ( j = 0; j < edge; ++j){
				printf("X");
			}
			printf("\n");
		}	
	}
	if (shape==RECTANGULAR){	//if it is rectangular ,it prints a rectangular
		int edge;
		edge=(body_size/5);
		for ( i = 0; i < 5; ++i){

			for ( j = 0; j < edge; ++j){
				printf("X");
			}
			printf("\n");
		}	
	}

	if (shape==CIRCLE){				//if it is circle ,it prints a circle
		
		int radius,i,tab_number,ara_bosluk,bas_bosluk,Temp_ara_bosluk;
		radius=sqrt((body_size/PI));
		tab_number=radius-1;
		
		if((radius%2)==0){	//it checks radius is even or odd
			ara_bosluk=1;
		}
		else{
			ara_bosluk=2;
		}
		
		bas_bosluk=(tab_number-ara_bosluk)/2;	//it calculates the tab number at the beginning
		Temp_ara_bosluk=ara_bosluk;
		
		for(i=0; i<(tab_number/2); i++){		//for first line X
			printf("\t");
		}
		if((radius%2)==0){
			printf("    ");
		}
		printf("X\n");
		
		
		
		while(ara_bosluk<=tab_number){			//for middle rows
			
			for(i=0; i<bas_bosluk; i++){
				printf("\t");
			}
			printf("X");
			
			for(i=0; i<ara_bosluk; i++){
				printf("\t");
			}
			printf("X\n");
			
			ara_bosluk=ara_bosluk+2;
			bas_bosluk=bas_bosluk-1;
		}
		
		ara_bosluk=ara_bosluk-2;
		bas_bosluk=bas_bosluk+1;
		
		while(Temp_ara_bosluk<ara_bosluk){
			
			ara_bosluk=ara_bosluk-2;
			bas_bosluk=bas_bosluk+1;
		
			for(i=0; i<bas_bosluk; i++){
				printf("\t");
			}
			printf("X");
			
			for(i=0; i<ara_bosluk; i++){
				printf("\t");
			}
			printf("X\n");
			
		}
		for(i=0; i<(tab_number/2); i++){
			printf("\t");
		}
		if((radius%2)==0){
			printf("    ");
		}
		printf("X\n");
		}

	printf("\n\nName: %s Pokemon\n",name[(shape-1)]);	//it prints features of pokemon
	printf("Size: %lf\n",body_size);
	printf("Color: %s\n",colour[(color)]);
	printf("Move: %lf\n",move_length );
	printf("Attack Power: %d\n\n",attack_power );


}