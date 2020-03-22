#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby}pokemon;
typedef enum {linear,quadratic}attack_type;

//compare 2 string, if they are equal returns 0,otherwise returns 1
int str_cmp(char *str1, char *str2);
//it takes a string(a pokemon name) inside the fucntion,and prints features of the pokemon
void pokedex(char Pokemon_name[][11], int range[],attack_type type[],int attack_power[], int stamina[]);
// it prints pokemons according to given  parameters
void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[],int pokemon_count);
// user select  a pokemon and add it to his/her pocket
void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_pocket);
// user select  a pokemon and subract it from his/her pocket
void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_Pokemons);
// it moves pokemons after release_a_pokemon , for good looking
void Slide_myPokemons(pokemon *my_Pokemons);
// show pokemons in labaraatory
void oaks_laboratory(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_pocket);
// it prints the area
void show_area (char Pokemon_name[][11],int area[8][8],int pokemon_staminas[8][8]);
// it calculates distance between x's and y's 
int calculate_distance(int x_cordinate,int y_cordinate,int new_x_cordinate,int new_y_cordinate);
void attack_to_pokemon(int rule_x_cordinate,int rule_y_cordinate,attack_type type,int range,int attack_power,pokemon rival_pokemons[4],int rival_Pokemons_cordinate[4][2],int area[8][8],int pokemon_staminas[8][8]);
// it switchs the old location with new location and empties the old location
void switch_location(int x_cordinate,int y_cordinate,int rule_x_cordinate,int rule_y_cordinate,int area [8][8],int pokemon_staminas[8][8]);
//perform battle
void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]);
// plays the game
void menu();


// HELPER FUNCTIONS

// it prints whitespace
void print_whitespaces(int whitespace);
// it prints underscores
void print_underscores(int underscores);
// set an array with size time by value
void set_array(int *arr,int size,int value);
// it calculates digit number, for good looking
int find_digit_number(int number);
// finding min value in array
int find_min_value(int arr[],int size,pokemon rival_pokemons[]);
// it checks user or AI pocket, if it is fully empty then returns 1
int control_pockets(pokemon Pokemons[],int pokemon_count);

int main(int argc, char const *argv[]){
 	srand(time(NULL));
	menu();
	
	
	return 0;
}


int str_cmp(char *str1, char *str2){ //compare 2 string, if they are equal returns 0,otherwise returns 1

	char c1,c2,i=0;
	do{
      c1 =*(str1+i);
      c2 =*(str2+i);
      i++;
      if (c1 == '\0')
        return 0;
    }
	while (c1 == c2);

	return 1;
}


//it takes a string(a pokemon name) inside the fucntion,and prints features of the pokemon
void pokedex(char Pokemon_name[][11], int range[],attack_type type[],int attack_power[], int stamina[]){ 
	char pokemon_name[11];
	int i,pokemon_number=-1;
	
	do{
		printf("\nPlease give the name of the pokemon,first letter must be upper case like: Pikachu\n");
		scanf("%s",pokemon_name);
		
		for ( i = 0; i < 10; ++i){
			
			// try to find which pokemon is  given by user
			if (str_cmp(pokemon_name,Pokemon_name[i])==0){
				pokemon_number=i;
				i=10;
			}
		}
		if (pokemon_number==-1){
			printf("\nIts an invalid name, Please give a valid name\n");
		}
	}while(pokemon_number==-1);
	
	// prints features of the pokemon
	printf("\nName : %s\n",Pokemon_name[pokemon_number]);
	
	if (type[pokemon_number]==0){
		printf("A. Type : Linear \n");
	}
	else{
		printf("A. Type : Quadratic \n");
	}

	printf("Range : %d block\n",range[pokemon_number]);
	printf("A. Power : %d\n",attack_power[pokemon_number]);
	printf("Stamina : %d\n",stamina[pokemon_number]);


}
// it prints pokemons according to given  parameters
void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[],int pokemon_count) {
	int i=0;
	printf("\nPOKEMONS\n");
	while(i!=pokemon_count){

		
		if (Pokemons[i]==-1){
			printf("%d - \n",i );
		}
		else{
			printf("%d - %s\n",i,Pokemon_name[Pokemons[i]]);
		}
		i++;
	}

}
// user select  a pokemon and add it to his/her pocket
void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_pocket){
	int choice,i=0,same=1;

	show_Pokemons(Pokemon_name,Pokemons,10); //it prints all pokemons in the pokedex
	printf("\nPlease give the pokemon number of you want to catch: ");
	scanf("%d",&choice);

	// it checks that is choice in pokedex and it is not in the pocket
	while(same){
		same=0;
		i=0;
		while((*(my_pocket+i)!=-1 && i!=4) ){
			
			if ( (str_cmp(Pokemon_name[*(my_pocket+i)],Pokemon_name[choice])==0) || choice<0 || choice>10){
				same=1;
			}
			i++;			
		}
		if (choice<0 || choice>10){
			printf("\nYou entered an invalid number.Please give a valid number: ");
			scanf("%d",&choice);
		}
		else if (same==1){
			printf("\nYou already have pick that pokemon.You can't pick twice,Please pick another one: ");
			scanf("%d",&choice);	
		}
	}
	// giving information to the user about pokemon he/she select
	if (i<4){
		printf("\nSelected Pokemon: %d - %s\n",Pokemons[choice],Pokemon_name[choice]);
		*(my_pocket+i)=choice;
	}
	else if(i==4){ //it checks that is pocket full or not
		printf("\nYour pocket is full.Please release one pokemon to catch one \n");
	}
	
}
// user select  a pokemon and subract it from his/her pocket
void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_Pokemons){
	int choice;
	show_Pokemons(Pokemon_name,my_Pokemons,4); //shows all pokemons in the pocket
	
	printf("Please give the pokemon number of you want to release\n");
	scanf("%d",&choice);
	// it checks that is choice  between 0-4
	while(choice<0 || choice>4){ 
		printf("\nYou entered an invalid number.Please give a valid number\n");
		scanf("%d",&choice);
	}

	printf("\nSelected Pokemon: %d - %s\n",choice,Pokemon_name[*(my_Pokemons+choice)]);
	
	*(my_Pokemons+choice)=-1; // it releases the selected pokemon
}
// it moves pokemons after release_a_pokemon , for good looking
void Slide_myPokemons(pokemon *my_Pokemons){
	int i=0;

	for ( i = 0; i < 3; ++i){
		
		if (*(my_Pokemons+i)==-1){
			*(my_Pokemons+i)=*(my_Pokemons+i+1);
			*(my_Pokemons+i+1)=-1;
		}
	}
}

void oaks_laboratory(char Pokemon_name[][11], pokemon Pokemons[],pokemon *my_pocket){
	
	int choice;
	
	
	
	do{
		printf("\n Welcome to Laboratory of Professor Oak. How can I help you?\n");
		printf("1) Show Pokemons \n");
		printf("2) Catch a Pokemon \n");
		printf("3) Release a Pokemon\n");
		printf("4) Show my pocket\n");
		printf("5) Back \n");
		scanf("%d",&choice);

		switch (choice){

			case 1:
				show_Pokemons(Pokemon_name,Pokemons,10); //shows all pokemon in the pokedex
				break;
			case 2:										
				catch_a_pokemon(Pokemon_name,Pokemons,my_pocket); // user select  a pokemon and add it to his/her pocket
				break;
			case 3:
				release_a_pokemon(Pokemon_name,Pokemons,my_pocket); // user select  a pokemon and subract it from his/her pocket
				Slide_myPokemons(my_pocket); // it moves pokemons after release_a_pokemon , for good looking
				break;
			case 4:
				show_Pokemons(Pokemon_name,my_pocket,4); //shows all pokemons in the pocket
				break;
			case 5:
				printf("Closing oaks laboratory...\n");
				break;
			default:
				printf("\nYou entered an invalid number.Please give a valid number\n");	
				break;
		}
	}while(choice!=5);
}

// it prints whitespace
void print_whitespaces(int whitespace){
	int j;
	for (j = 0; j<whitespace ; ++j){ // it prints whitespaces number of whitespace times
		printf(" ");
	}
}
// it prints underscores
void print_underscores(int underscores){
	int j;
	for (j = 0; j<underscores; ++j){ // it prints whitespaces number of whitespace times
		printf("_");
	}
}

// set an array with size time by value
void set_array(int *arr,int size,int value){
	int i;
	for (i = 0; i < size ; i++){ 
        *(arr+i) = value; 
    } 
}
// it calculates digit number, for good looking
int find_digit_number(int number){
	int digit_number=0;
	while(number>0){
		number=number/10;
		digit_number++;
	}
	return  digit_number;
}
// it prints the area
void show_area (char Pokemon_name[][11],int area[8][8],int pokemon_staminas[8][8]){
 	int x_cordinate=0,y_cordinate=0,coloumn=0,digit_number=0,i;
 	printf("\n");
 	print_underscores(73);
 	printf("\n");
 	for (x_cordinate = 0; x_cordinate < 8; ++x_cordinate){
 		
 		printf("\n");
 		printf("|");
	 	
	 	for ( y_cordinate = 0; y_cordinate < 8; ++y_cordinate){
	 		
	 		
			print_whitespaces(2);
			
			if (area[x_cordinate][y_cordinate]!=-1){
				
				for ( i = 0; i < 3; ++i){
					printf("%c",Pokemon_name[ (area[x_cordinate][y_cordinate]) ] [i]);
				}
				print_whitespaces(3);	
			}
			else{ print_whitespaces(6); }
		
			printf("|");
	 	}
		printf("\n");
		printf("|");
		for ( y_cordinate = 0; y_cordinate < 8; ++y_cordinate){
	 		
	 		
			print_whitespaces(1);
			
			if (pokemon_staminas[x_cordinate][y_cordinate]!=-1){
				
				printf("(%d)",pokemon_staminas[x_cordinate][y_cordinate]);
				digit_number=find_digit_number(pokemon_staminas[x_cordinate][y_cordinate]);
				print_whitespaces(1+(4-digit_number));	
			}
			else{ print_whitespaces(7); }
		
			printf("|");
	 	}
	 	printf("\n");
	 	print_underscores(73);
 	}
 		
	printf("\n");
}
// it calculates distance between x's and y's 
int calculate_distance(int x_cordinate,int y_cordinate,int new_x_cordinate,int new_y_cordinate){
	int difference_x,difference_y,distance;
	difference_x=(x_cordinate - new_x_cordinate);
	difference_y=(y_cordinate - new_y_cordinate);
	if (difference_x<0){
		difference_x=difference_x*(-1);
	}
	if (difference_y<0){
		difference_y=difference_y*(-1);
	}
	distance=difference_x + difference_y;
	return distance;
}
// finding min value in array
int find_min_value(int arr[],int size,pokemon rival_pokemons[]){
	int i,min=arr[0];
	for ( i = 1; i < size; ++i){
		
		if (arr[i]<min && (rival_pokemons[i]!=-1) ){
			min=arr[i];
		}
	}
	return min;

}
// it checks user or AI pocket, if it is fully empty then returns 1
int control_pockets(pokemon Pokemons[],int pokemon_count){
	int i,control=1;
	for ( i = 0; i < pokemon_count; ++i){
		if (Pokemons[i]!=-1 ){
			control=0;
		}
	}
	return control;
}
// it performs an attack
void attack_to_pokemon(int rule_x_cordinate,int rule_y_cordinate,attack_type type,int range,int attack_power,pokemon rival_pokemons[4],int rival_Pokemons_cordinate[4][2],int area[8][8],int pokemon_staminas[8][8]){
	int x_cordinate,y_cordinate,i,min_value,space[4];
	
	for ( i = 0; i < 4; ++i){
		x_cordinate=rival_Pokemons_cordinate[i][0];
		y_cordinate=rival_Pokemons_cordinate[i][1];
		
		if ((rival_pokemons[i]!=-1)){
			space[i]=calculate_distance(x_cordinate,y_cordinate,rule_x_cordinate,rule_y_cordinate);	
		}		
	}
	
	
	if (type==0){

		min_value=find_min_value(space,4,rival_pokemons);

		for ( i = 0; i < 4; ++i){
				
			if ((min_value<=range) && (min_value==space[i]) && (rival_pokemons[i]!=-1) ){
			
				x_cordinate=rival_Pokemons_cordinate[i][0];
				y_cordinate=rival_Pokemons_cordinate[i][1];
				pokemon_staminas[x_cordinate][y_cordinate]-= attack_power;
		
				if (pokemon_staminas[x_cordinate][y_cordinate]<=0){
					area[x_cordinate][y_cordinate]=-1;
					pokemon_staminas[x_cordinate][y_cordinate]=-1;
					rival_pokemons[i]=-1;
					rival_Pokemons_cordinate[i][0]=-1;
					rival_Pokemons_cordinate[i][1]=-1;
				}

			}
		}
	}
	else if (type==1){
		for ( i = 0; i < 4; ++i){
			if ((space[i]<=range) && (rival_pokemons[i]!=-1)  ){
				
				x_cordinate=rival_Pokemons_cordinate[i][0];
				y_cordinate=rival_Pokemons_cordinate[i][1];
				pokemon_staminas[x_cordinate][y_cordinate]-= attack_power;
			}
				
			if (pokemon_staminas[x_cordinate][y_cordinate]<=0){
				area[x_cordinate][y_cordinate]=-1;
				pokemon_staminas[x_cordinate][y_cordinate]=-1;
				rival_pokemons[i]=-1;
				rival_Pokemons_cordinate[i][0]=-1;
				rival_Pokemons_cordinate[i][1]=-1;
			}

		}
		
	}

}
// it switchs the old location with new location and empties the old location
void switch_location(int x_cordinate,int y_cordinate,int rule_x_cordinate,int rule_y_cordinate,int area [8][8],int pokemon_staminas[8][8]){
	if (area[rule_x_cordinate][rule_y_cordinate]!=area[x_cordinate][y_cordinate]){
		area[rule_x_cordinate][rule_y_cordinate]=area[x_cordinate][y_cordinate];
		pokemon_staminas[rule_x_cordinate][rule_y_cordinate]=pokemon_staminas[x_cordinate][y_cordinate];
		area[x_cordinate][y_cordinate]=-1;
		pokemon_staminas[x_cordinate][y_cordinate]=-1;
	}
	
	
}
//perform battle
void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]){
	int area[8][8],pokemon_staminas[8][8],space[4];
	
	set_array(pokemon_staminas[0],64,-1);
	set_array(area[0],64,-1);
	int x_cordinate,y_cordinate,rule_x_cordinate, rule_y_cordinate, i=0,j,same=1,distance,min_value,AI_win=0,user_win=0;
	pokemon AI_Pokemons[4]={-1,-1,-1,-1},temp_pokemon,rule_pokemon;
	int user_Pokemons_cordinate[4][2],AI_Pokemons_cordinate[4][2];
	
	// it takes x and y cordinates for user pokemons
	while(user_Pokemons[i]!=-1 && i<4){

		printf("\nPlease give %s x_cordinate: ",Pokemon_name[(user_Pokemons[i])]);
		scanf("%d",&x_cordinate);
		printf("\nPlease give %s y_cordinate: ",Pokemon_name[(user_Pokemons[i])]);
		scanf("%d",&y_cordinate);
		
		//error messages
		if( area[x_cordinate][y_cordinate]!=-1  ){
			printf("\nThere is a pokemon in the place which you want to move.Please try another location.\n");
		}
		else if (x_cordinate <=1 && x_cordinate>=0 && y_cordinate>=0 && y_cordinate<=7){
			area[x_cordinate][y_cordinate]=user_Pokemons[i];
			pokemon_staminas[x_cordinate][y_cordinate]=stamina[user_Pokemons[i]];
			user_Pokemons_cordinate[i][0]=x_cordinate;
			user_Pokemons_cordinate[i][1]=y_cordinate;
			i++;
		}
		if (!(x_cordinate <=1 && x_cordinate>=0)){
			printf("\nAt the beginning ,you can replace your pokemons in first two rows.Please try again.\n");
		}
		else if (!(y_cordinate>=0 && y_cordinate<=7)){
			printf("\nThe bounderies 0 and 7 ,please do not give higher cordinate then 7 or less cordinate then 0.Please try again.\n");
		}
	}
	
	i=0;
	// it assignes x and y cordinates for AI pokemons
	while( i<4){
		x_cordinate=rand()%2;
		y_cordinate=rand()%8;
		same=1;
		// it checks that is the place is empty
		if (area[6+x_cordinate][y_cordinate]==-1){
			
			while(same){
				same=0;
				j=0;
				temp_pokemon=rand()%10;
				
				// it checks that has the pokemon selected already by AI
				while(j<4){
					
					if ((AI_Pokemons[j]==temp_pokemon)){
						same=1;
					}
					
					j++;
				}
				// if it  hasn't chosen by  AI ,it assignes
				if (same==0){
					AI_Pokemons[i]=temp_pokemon;
					area[6+x_cordinate][y_cordinate]=temp_pokemon;
					pokemon_staminas[6+x_cordinate][y_cordinate]=stamina[AI_Pokemons[i]];
					AI_Pokemons_cordinate[i][0]=6+x_cordinate;
					AI_Pokemons_cordinate[i][1]=y_cordinate;
				}							
			}	
			
			i++;		
		}
	}

	printf("\nWELCOME THE TOURNAMENT\n");
	show_area(Pokemon_name,area,pokemon_staminas);
	printf("\n");
	// it repeats untill AI or user win
	while((user_win==0 && AI_win==0 )){
		
		if (AI_win==0){
			show_Pokemons(Pokemon_name,user_Pokemons,4);
			printf("\nPlease select the pokemon you want to rule: ");
			scanf("%d",&rule_pokemon);
			printf("\nYou can give cordinates between [0-7] for x and y.\n");
			// it repeats untill all condition is okay
			do{
				//it takes new cordinates of the pokemon which rule
				printf("\nPlease give %s new x_cordinate: ",Pokemon_name[(user_Pokemons[rule_pokemon])]);
				scanf("%d",&rule_x_cordinate);
				printf("\nPlease give %s new y_cordinate: ",Pokemon_name[(user_Pokemons[rule_pokemon])]);
				scanf("%d",&rule_y_cordinate);
				
				// it takes rule pokemon old cordinates
				x_cordinate=user_Pokemons_cordinate[rule_pokemon][0];
				y_cordinate=user_Pokemons_cordinate[rule_pokemon][1];
				
				// it calculates distance between x's and y's 
				distance=calculate_distance(x_cordinate,y_cordinate,rule_x_cordinate,rule_y_cordinate);
				
				//error messages
				if (distance>2){
					printf("\nYou can move 1 or 2 block.Please try again.\n");
				}
				if( !( ( !(area[rule_x_cordinate][rule_y_cordinate]!=-1) ) || ( (area[rule_x_cordinate][rule_y_cordinate]!=-1) && (area[rule_x_cordinate][rule_y_cordinate]==area[x_cordinate][y_cordinate]) ) ) ){
					printf("\nThere is a pokemon in the place which you want to move.Please try another location.\n");
				}
				if( rule_x_cordinate>7 || rule_x_cordinate<0 || rule_y_cordinate>7 || rule_y_cordinate<0 ){
					printf("\nThe bounderies 0 and 7 ,please do not give higher cordinate then 7 or less cordinate then 0.Please try again.\n");
				}
			}while(distance>2 || !( ( !(area[rule_x_cordinate][rule_y_cordinate]!=-1) ) || ( (area[rule_x_cordinate][rule_y_cordinate]!=-1) && (area[rule_x_cordinate][rule_y_cordinate]==area[x_cordinate][y_cordinate]) ) ) );

			// it switchs the old location with new location and empties the old location
			switch_location(x_cordinate,y_cordinate,rule_x_cordinate,rule_y_cordinate,area,pokemon_staminas);

			// it switchs the old cordinates with new cordinates
			user_Pokemons_cordinate[rule_pokemon][0]=rule_x_cordinate;
			user_Pokemons_cordinate[rule_pokemon][1]=rule_y_cordinate;

			printf("\nUSER PLAYED\n");
			attack_to_pokemon( rule_x_cordinate,rule_y_cordinate,type[user_Pokemons[rule_pokemon]],range[user_Pokemons[rule_pokemon]],attack_power[(user_Pokemons[rule_pokemon])],AI_Pokemons,AI_Pokemons_cordinate, area, pokemon_staminas);
			show_area(Pokemon_name,area,pokemon_staminas);
			
			// it checks the AI pocket 
			user_win=control_pockets(AI_Pokemons,4);
		}
		
		printf("\n\n");
		
		if ((user_win==0)){


			// it checks that is the place is empty
			do{
				rule_pokemon=rand()%4;
			}while((AI_Pokemons[rule_pokemon])==-1);

			//it takes new cordinates of the pokemon which rule
			x_cordinate=AI_Pokemons_cordinate[rule_pokemon][0];
			y_cordinate=AI_Pokemons_cordinate[rule_pokemon][1];

			same=1;
			// it repeats untill all condition is okay
			// avoiding errors
			while(same){
				same=0;
				rule_x_cordinate=rand()%3;
				if (rule_x_cordinate==2){
					rule_y_cordinate=0;
				}
				else if(rule_x_cordinate==1){		
					rule_y_cordinate=rand()%2;
				}
				else if(rule_x_cordinate==0){
					rule_y_cordinate=rand()%3;
				}
			
				if (x_cordinate>=4 && x_cordinate<=7){
					rule_x_cordinate=x_cordinate - rule_x_cordinate;
				}
				else if(x_cordinate>=0 && x_cordinate<4){
					rule_x_cordinate=x_cordinate + rule_x_cordinate;
				}

				if (y_cordinate>4 && y_cordinate<=7){
					rule_y_cordinate=y_cordinate - rule_y_cordinate;
				}
				else if (y_cordinate>=0 && y_cordinate<=4){
					rule_y_cordinate=y_cordinate + rule_y_cordinate;
				}
			
				if (rule_x_cordinate>7 || rule_x_cordinate<0 || rule_y_cordinate>7 || rule_y_cordinate<0){
					
					same=1;
				}
				if ( !( ( !(area[rule_x_cordinate][rule_y_cordinate]!=-1) ) || ( (area[rule_x_cordinate][rule_y_cordinate]!=-1) && (area[rule_x_cordinate][rule_y_cordinate]==area[x_cordinate][y_cordinate]) ) ) ){
					same=1;
				}
			}

			// it switchs the old location with new location and empties the old location
			switch_location(x_cordinate,y_cordinate,rule_x_cordinate,rule_y_cordinate,area,pokemon_staminas);
			// it switchs the old cordinates with new cordinates		
			AI_Pokemons_cordinate[rule_pokemon][0]=rule_x_cordinate;
			AI_Pokemons_cordinate[rule_pokemon][1]=rule_y_cordinate;
			printf("\nAI PLAYED\n");
			attack_to_pokemon( rule_x_cordinate,rule_y_cordinate,type[AI_Pokemons[rule_pokemon]],range[AI_Pokemons[rule_pokemon]],attack_power[(AI_Pokemons[rule_pokemon])],user_Pokemons,user_Pokemons_cordinate, area, pokemon_staminas);
			show_area(Pokemon_name,area,pokemon_staminas);
			
			// it checks the user pocket 
			AI_win=control_pockets(user_Pokemons,4);


		}
		if (user_win==1){
			printf("USER WIN THE GAME\n");
		}
		else if (AI_win==1){
			printf("AI WIN THE GAME\n");
		}
	}
		
	
}

void menu(){

	int choice;
	char Pokemon_name[10][11]={"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};
	int range[10]={1,3,4,3,2,2,1,2,3,2};
	attack_type type[10]={quadratic,linear,linear,linear,quadratic,linear,quadratic,quadratic,linear,linear};
	int attack_power[10]={ 500,350,300,400,250,250,350,200,350,300} ;
	int stamina[10]={2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
	int area[8][8];
	int pokemon_staminas[8][8];
	
	pokemon Pokemons[10]={Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby};
	pokemon my_Pokemons[4]={-1,-1,-1,-1};
	
	set_array(pokemon_staminas[0],64,-1);
	set_array(area[0],64,-1);

	
	
	do{
		printf("\n Please select an option to continue: \n");
		printf("1) Open Pokedex  \n");
		printf("2) Go to Oak’s Laboratory  \n");
		printf("3) Enter the tournament\n");
		printf("4) Exit\n");
		scanf("%d",&choice);

		switch (choice){

			case 1: // runs pokedex
				pokedex(Pokemon_name,range,type,attack_power,stamina); 
				break;
			case 2:	// runs oaks_laboratory									
				oaks_laboratory(Pokemon_name,Pokemons,my_Pokemons);
				break;
			case 3: //runs battle
				battle(Pokemon_name,range,type,attack_power,stamina,my_Pokemons);
				break;
			case 4:
				printf("Closing Menu...\n");
				break;
			default:
				printf("\nYou entered an invalid number.Please give a valid number\n");	
				break;
		}
	}while(choice!=4);



}