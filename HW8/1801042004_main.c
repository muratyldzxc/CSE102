#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum { noone, cap, car }player_type;

typedef enum { start, property, tax, punish, fortune }block_type;

typedef struct {
	
	player_type type ;

	int current_block_id ;
	int owned_block_ids[12] ;
	int account ;
	int turn_to_wait ;
	char * name ;

}player;

typedef struct {
	
	int block_id ;
	char * name ;
	int price ;
	int rent ;
	int rent_1 ;
	int rent_2 ;
	int rent_3 ;
	int house_price ;
	int house_count ;

	block_type type;
	player owner ;
	struct block * next_b;

}block;

typedef struct {
	int card_id ;
	char * name ;
	int amount ;

}fortune_card;

void wait_punish( block * current_block, player * current_player );
void pay_tax( block * current_block, player * current_player );
int pay_rent( block * current_block, player * current_player );
// set an array with size time by value
void set_array(int *arr,int size,int value);
// it prints whitespace
void print_whitespaces(int whitespace);
// it prints dash
void print_dash(int dash);
// it calculates digit number, for good looking
int find_digit_number(int number);
// it returns the empty index number
int find_free_space( int * owned_block_ids );
// it check the selected property if the user has that property or not
int verify_property( int id, int owned_block_ids[] );
// print current player account
void show_my_account( player * current_player );
// slides current player owned properties for good looking
void slide_myProperties( int *my_properties);
// find the block which is given with number and return it
block * find_node ( block * head, int number );
// for printing board to the console , design arr 
void represent_the_board( block * board , int * arr );
// init the board
void init_the_board( block * board  );
// init the fortune  deck
void init_the_deck( fortune_card * deck );
// print the board on  the console
void show_board( block * board, player player_one,  player player_two);
// show selected property and its details
void show_properties( block * board );
// show current player owned properties
void show_my_properties( block * board , int owned_block_ids[] );
// built a house
void buy_house( block * current_block,  player * current_player );
// buy  a property
void buy_property( block * current_block,  player * current_player);
// find max cost property in the owned properties for to sell
int find_max_cost_property( block * board, int * owned );
//sell property
void sell_property( block * board, player * current_player );
// find average price of all properties
int find_average_cost( block * board );
// to perform fortune card block process
void play_fortune_card( fortune_card * deck , block * board, player * current_player, player * other_player );
// it is for computer , to know what to do
void cap_plays( block * board, player * current_player, player * other_player );
// it runs the game
void gameplay ( block * board,  player player_one,  player player_two );



int main(){
	srand(time(NULL));
	block * board = ( block * )malloc( sizeof( block ) );
	player player_one, player_two ;
	gameplay( board , player_one, player_two );


	return 0;
}


void wait_punish( block * current_block, player * current_player ){
	//printf("%s player got %d tour punishment\n", current_player->name, current_block->price );
	current_player->turn_to_wait = current_block->price + 1 ;
}
void pay_tax( block * current_block, player * current_player ){
	printf("\n%s player paid a tax %d$\n", current_player->name, current_block->price );
	current_player->account -= current_block->price ; 
}
int pay_rent( block * current_block, player * current_player ){

	if ( current_block->house_count == 0 ){
		return current_block->rent;
	}
	else if ( current_block->house_count == 1 ){
		return current_block->rent_1;
	}
	else if ( current_block->house_count == 2 ){
		return current_block->rent_2;
	}
	else if ( current_block->house_count == 3 ){
		return current_block->rent_3;
	}

}
// set an array with size time by value
void set_array(int *arr,int size,int value){
	int i;
	for (i = 0; i < size ; i++){ 
        *(arr+i) = value; 
    } 
}

// it prints whitespace
void print_whitespaces(int whitespace){
	int j;
	for (j = 0; j<whitespace ; ++j){ // it prints whitespaces number of whitespace times
		printf(" ");
	}
}

// it prints dash
void print_dash(int dash){
	int j;
	for (j = 0; j<dash; ++j){ // it prints dash number of dash times
		printf("-");
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
// it returns the empty index number
int find_free_space( int * owned_block_ids ){
	
	int i, free_space;
	for ( i = 0; i < 12; ++i){
		
		if ( owned_block_ids[i] == 0 ){
			
			free_space = i ;
			i = 12 ; // break the loop
		}
	}
	return free_space;
}
// it check the selected property if the user has that property or not
int verify_property( int id, int owned_block_ids[] ){

	int i, verify = -1;
	for ( i = 0; i < 12; ++i){
		
		if ( owned_block_ids[i] == id ){
			
			verify = i ;
			i = 12 ; // break the loop
		}
	}
	return verify;

}
// print current player account
void show_my_account( player * current_player ){

	printf("\nYour account : %d$\n", current_player->account );
}
// slides current player owned properties for good looking
void slide_myProperties( int *my_properties){
	int i=0;

	for ( i = 0; i < 11; ++i){
		
		if ( *(my_properties+i) == 0 ){
			*(my_properties+i)=*(my_properties+i+1);
			*(my_properties+i+1) = 0;
		}
	}
}
// find the block which is given with number and return it
block * find_node ( block * head, int number ){
	int i=0;
	while( i< number ){
		
		head= head->next_b;
		i++;
		
	}
	return head;
}
// for printing board to the console , design arr 
void represent_the_board( block * board , int * arr ){

	arr[0] = ( find_node( board, 0 ) )->block_id;
	arr[1] = ( find_node( board, 1 ) )->block_id;
	arr[2] = ( find_node( board, 2 ) )->block_id;
	arr[3] = ( find_node( board, 3 ) )->block_id;
	arr[4] = ( find_node( board, 4 ) )->block_id;
	arr[5] = ( find_node( board, 5 ) )->block_id;
	arr[6] = ( find_node( board, 6 ) )->block_id;
	
	arr[7] = ( find_node( board, 23 ) )->block_id;
	arr[8] = ( find_node( board, 7 ) )->block_id;
	arr[9] = ( find_node( board, 22 ) )->block_id;
	arr[10] = ( find_node( board, 8 ) )->block_id;
	arr[11] = ( find_node( board, 21 ) )->block_id;
	arr[12] = ( find_node( board, 9 ) )->block_id;
	arr[13] = ( find_node( board, 20 ) )->block_id;
	arr[14] = ( find_node( board, 10 ) )->block_id;
	arr[15] = ( find_node( board, 19 ) )->block_id;
	arr[16] = ( find_node( board, 11 ) )->block_id;
	
	arr[17] = ( find_node( board, 18 ) )->block_id;
	arr[18] = ( find_node( board, 17 ) )->block_id;
	arr[19] = ( find_node( board, 16 ) )->block_id;
	arr[20] = ( find_node( board, 15 ) )->block_id;
	arr[21] = ( find_node( board, 14 ) )->block_id;
	arr[22] = ( find_node( board, 13 ) )->block_id;
	arr[23] = ( find_node( board, 12 ) )->block_id;

}
// init the board
void init_the_board( block * board  ){

	int i;
	block * temp;
	temp = board ;
	block Temp_board[24] = {	
								{ 0  ,"Start"	    ,     0,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,start    , noone  },
								{ 1  ,"Esenyurt"	, 16000,  800 , 4000 , 9000 ,25000 ,10000 ,0 ,property , noone  },
								{ 2  ,"Car Park"    ,  1500,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,tax	   , noone  },
								{ 3  ,"Fortune Card",	  0,    0 ,    0 ,	  0 ,	 0 ,    0 ,0 ,fortune  , noone  },
								{ 4  ,"Tuzla"	    , 16500,  850 , 4250 , 9500 ,26000 ,12000 ,0 ,property , noone  },
								{ 5  ,"Arnavutkoy"  , 17000,  875 , 4500 ,10000 ,28000 ,12000 ,0 ,property , noone  },
								{ 6  ,"Wait 2 Turn" ,     2,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,punish   , noone  },
								{ 7  ,"Catalca"	    , 20000, 1000 , 5000 ,12000 ,30000 ,13000 ,0 ,property , noone  },
								{ 8  ,"Beykoz"	    , 23000, 1100 , 5500 ,12500 ,33000 ,13000 ,0 ,property , noone  },
								{ 9  ,"Fortune Card",	  0,    0 ,    0 ,	  0 ,	 0 ,    0 ,0 ,fortune  , noone  },
								{ 10 ,"Car Fix"	    ,  1750,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,tax 	   , noone  },
								{ 11 ,"Maltepe"	    , 30000, 1350 , 7000 ,15000 ,40000 ,15000 ,0 ,property , noone  },
								{ 12 ,"Bills"	    ,  2250,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,tax 	   , noone  },
								{ 13 ,"Sisli"	    , 33000, 1500 , 8000 ,16000 ,42000 ,16000 ,0 ,property , noone  },
								{ 14 ,"Oil"		    ,  2250,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,tax 	   , noone  },
								{ 15 ,"Atasehir"    , 35000, 1600 , 8500 ,17000 ,45000 ,17000 ,0 ,property , noone  },
								{ 16 ,"Sariyer"	    , 40000, 1750 , 9500 ,19000 ,48000 ,19000 ,0 ,property , noone  },
								{ 17 ,"Fortune Card",	  0,    0 ,    0 ,	 0  ,	 0 ,    0 ,0 ,fortune  , noone  },
								{ 18 ,"Wait 1 Turn" ,     1,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,punish   , noone  },
								{ 19 ,"Kadikoy"	    , 43000, 1900 ,11000 ,21500 ,55000 ,23000 ,0 ,property , noone  },
								{ 20 ,"Besiktas"    , 60000, 2500 ,15000 ,28000 ,60000 ,30000 ,0 ,property , noone  },
								{ 21 ,"Fortune Card",	  0,    0 ,    0 ,	  0 ,	 0 ,    0 ,0 ,fortune  , noone  },
								{ 22 ,"Vocation"    ,  5000,    0 ,    0 ,    0 ,    0 ,    0 ,0 ,tax 	   , noone  },
								{ 23 ,"Bebek"	    , 70000, 3500 ,20000 ,35500 ,65000 ,35000 ,0 ,property , noone  }
							};
		
		board->block_id = 0 ;	
		board->name = (char*)malloc(20);
		strcpy( (board->name) ,Temp_board[0].name );
		board->price = Temp_board[0].price ;
		board->rent = Temp_board[0].rent ;
		board->rent_1 = Temp_board[0].rent_1 ;
		board->rent_2 = Temp_board[0].rent_2 ;
		board->rent_3 = Temp_board[0].rent_3 ;
		board->house_price = Temp_board[0].house_price ;
		board->house_count = Temp_board[0].house_count ;
		board->owner.type = Temp_board[0].owner.type ;
		board->type = Temp_board[0].type ;						

	for ( i = 1; i < 24; ++i){	

		block * Temp_block = ( block * )malloc( sizeof( block ) );
		Temp_block->block_id = i ;	
		Temp_block->name = (char*)malloc(20);
		strcpy( (Temp_block->name) ,Temp_board[i].name );
		Temp_block->price = Temp_board[i].price ;
		Temp_block->rent = Temp_board[i].rent ;
		Temp_block->rent_1 = Temp_board[i].rent_1 ;
		Temp_block->rent_2 = Temp_board[i].rent_2 ;
		Temp_block->rent_3 = Temp_board[i].rent_3 ;
		Temp_block->house_price = Temp_board[i].house_price ;
		Temp_block->house_count = Temp_board[i].house_count ;
		Temp_block->owner.type = Temp_board[i].owner.type ;
		Temp_block->type = Temp_board[i].type ;
		
		Temp_block->next_b = NULL ; 
		board->next_b = Temp_block ;
		board = board->next_b ;

	}

}
// init the player
void init_the_player( player * init_player ){

	init_player->type = noone ;
	init_player->current_block_id = 0 ;
	set_array( init_player->owned_block_ids, 12, 0 );
	init_player->account = 100000 ;
	init_player->turn_to_wait = 0 ;
	init_player->name = NULL ;
}
// init the fortune  deck
void init_the_deck( fortune_card * deck ){
	int i;
	fortune_card Temp_deck [5] = { 
								{  1,  "Free House"     ,   1     },
								{  2,  "Time Travel"    ,   2     },
								{  3,  "Garnishment"    ,   5000  },
								{  4,  "Generosity"     ,   10000 },
								{  5,  "Treasure Hunter",   20000 }
							 };
	for(  i = 0; i < 5; ++i){
		deck[i].card_id = Temp_deck[i].card_id ;
		deck[i].name = (char*)malloc(20) ;
		strcpy( (deck[i].name) ,Temp_deck[i].name );
		deck[i].amount = Temp_deck[i].amount ;
	}
}
// print the board on  the console
void show_board( block * board, player player_one,  player player_two){
	
	int row, column, current_block_id=0, reached_block_id=0, i=0, digit_number  ;
	int represent_arr [23];

	represent_the_board( board, represent_arr );

  	print_dash(169);
  	printf("\n");
	for ( row = 0; row < 7 ; ++row){
		
		/* printing block name */
		current_block_id = reached_block_id;
	
		for ( column = 0; column < 7; ++column){
			
			if ( !( ( 0 < row && row < 6) &&  ( 0 < column && column < 6) ) ){
				
				printf("|");
				print_whitespaces(8); //tab		
				printf("%-15s", find_node( board, represent_arr[ current_block_id ])->name);
				current_block_id ++;

				if ( !( row == 0 || row == 6 ) ){
					printf("|");
					print_whitespaces(4);
				}
			}
			else{
				print_whitespaces(23); //text
			}
		}

		if ( ( row == 0 || row == 6 ) ){
			printf("|");

		}
		printf("\n");
		

		/* printing block price */
		current_block_id = reached_block_id;
	
		
		for ( column = 0; column < 7; ++column){
			
			if ( !( ( 0 < row && row < 6) &&  ( 0 < column && column < 6) ) ){
				printf("|");
				print_whitespaces(8); //tab	
				if ( find_node( board, represent_arr[ current_block_id ])->type == property || find_node( board, represent_arr[ current_block_id ])->type == tax ){
					printf("%d$", find_node( board, represent_arr[ current_block_id ])->price);
					digit_number = find_digit_number( find_node( board, represent_arr[ current_block_id ])->price );

					print_whitespaces( 15 - digit_number - 1);

				}
				else{
					print_whitespaces(15);
				}
				
				current_block_id ++;

				if ( !( row == 0 || row == 6 ) ){
					printf("|");
					print_whitespaces(4);
				}

			}
			else{
				print_whitespaces(8); //tab	
				print_whitespaces(15);//text
			}
		}
		
		if ( ( row == 0 || row == 6 ) ){
			printf("|");
		}

		printf("\n");

		/* printing user */
		current_block_id = reached_block_id;
	
		for ( column = 0; column < 7; ++column){
			
			if ( !( ( 0 < row && row < 6) &&  ( 0 < column && column < 6) ) ){
				
				

				if ( ( player_one.current_block_id == represent_arr[ current_block_id ] ) && ( player_two.current_block_id == represent_arr[ current_block_id ] ) ){
					
					printf("|");
					print_whitespaces(8); //tab	
					printf("%-5s", player_one.name );
					printf("  %-8s", player_two.name );

				}
				else if( player_one.current_block_id == represent_arr[ current_block_id ] ){
					
					printf("|");
					print_whitespaces(8); //tab	
					printf("%-15s", player_one.name );
				}

					
				else if ( player_two.current_block_id == represent_arr[ current_block_id ] ){
						
					printf("|");
					print_whitespaces(8); //tab		
					printf("%-15s", player_two.name );

				}
				else{
					printf("|");
					print_whitespaces(8); //tab	
					print_whitespaces(15); // text

				}

				if ( !( row == 0 || row == 6 ) ){
					printf("|");
					print_whitespaces(4);
				}
			
				current_block_id ++;		
			}
			else{
				print_whitespaces(8); //tab	
				print_whitespaces(15); // text
			}
		}
		if ( ( row == 0 || row == 6 ) ){
			printf("|");
		}

		printf("\n");

		reached_block_id = current_block_id ;

		if (  ( 0 < row && row < 5)  ){
			print_dash(25);
			print_whitespaces(119);
			print_dash(25);	
		}
		else{
			print_dash(169);
		}
		printf("\n");

	}	
}
// show selected property and its details
void show_properties( block * board ){

	int  i, choice ;
	printf("\nPlease select a property to see details\n");

	for ( i = 0; i < 24; ++i){

		if ( find_node( board, i)->type == property ){
			
			printf("%d -\t %s \n", i, find_node( board, i)->name );
		}		
	}
	printf("0 -\t exit \n");

	printf("\nSelected  choice: ");
	scanf("%d",&choice);
	printf("\n");
	
	do{

		if ( 0 <= choice  && choice <= 19 ){

			print_dash(33);
			printf("\n|");
			printf("\t\t%-10s\t", find_node( board, choice )->name );
			printf("|\n");

			print_dash(33);
			printf("\n|");
			printf("\tRent");
			printf("\t\t%d$\t", find_node( board, choice )->rent );
			printf("|");

			printf("\n|");
			printf("\tRent 1 H" );
			printf("\t%d$\t", find_node( board, choice )->rent_1 );
			printf("|");

			printf("\n|");
			printf("\tRent 2 H" );
			printf("\t%d$\t", find_node( board, choice )->rent_2 );
			printf("|");

			printf("\n|");
			printf("\tRent 3 H" );
			printf("\t%d$\t", find_node( board, choice )->rent_3 );
			printf("|\n");

			print_dash(33);

			printf("\n|");
			printf("\tHouse Price" );
			printf("\t%d$\t", find_node( board, choice )->house_price );
			printf("|\n");

			print_dash(33);
			printf("\n");

		}
		else{
			printf("You entered an invalid  number, Please try again \n");
		}
		printf("\nSelected choice: ");
		scanf("%d",&choice);
		printf("\n");
	}while( choice != 0 );

}
// show current player owned properties
void show_my_properties( block * board , int owned_block_ids[] ){

	int i = 0, none = 0;
	printf("\nYour properties\n");

	while( owned_block_ids[ i ] != 0 ){		

		printf("%d -  %s \n", owned_block_ids[ i ] , find_node( board, owned_block_ids[ i ])-> name );	
		none = 1;
		i++;			
	}
	if ( none == 0)
	printf("\nNONE\n");
}
// built a house
void buy_house( block * current_block,  player * current_player ){
	int buy=0;
	if ( current_block->type != property ){
		printf("\nSorry , it is not a property\n");
		return;
	}
	else if ( current_block->owner.type != current_player->type ){
		printf("\nYou cant built house before buy that property\n");
		return;
	}
	if ( current_player->type == car){
		printf("\nPrice of building a house in this property : %d$\n", current_block->house_price );
		printf("\nHouse number that was built in this property is : %d\n",current_block->house_count );
		printf("\nDo you want to build a house (Y:1 N:0)\n");
		scanf("%d",&buy);

		do{
			if ( buy != 0){

				if ( current_block->house_price > current_player->account ){
					printf("\nYou have not enough money to build a house\n");
					return;
				}
				else if ( current_block->house_count >= 3 ){
					printf("\nYou can not build a house cause house number on this property is 3\n");
					return;
				}
				else if ( buy == 1 ){
					current_block->house_count++ ;
					current_player->account -= current_block->house_price;
				}
				printf("\nHouse is built\n");
				printf("\nPrice of building a house in this property : %d$\n", current_block->house_price );
				printf("\nHouse number that was built in this property is : %d\n",current_block->house_count );
				show_my_account( current_player );
				printf("\nDo you want to build a house (Y:1 N:0)\n");
				scanf("%d",&buy);
			}	

		}while( buy == 1 );
	}
	else{
		if ( current_block->house_price > current_player->account ){
			printf("\nYou have not enough money to build a house\n");
			return;
		}
		else if ( current_block->house_count >= 3 ){
			printf("\nYou can not build a house cause house number on this property is 3\n");
			return;
		}
		else if ( buy == 1 ){
			current_block->house_count++ ;
			current_player->account -= current_block->house_price;
		}
		printf("\nHouse is built\n");
	}
	
}
// buy  a property
void buy_property( block * current_block,  player * current_player){
	
	int free_space ;
	if ( current_block->type != property ){
		printf("\nSorry , it is not a property\n");
		return;
	}
	else if ( current_block->owner.type != noone){
		printf("\nSorry ,this property is already sold\n");
		return;
	}
	else if ( current_block->block_id != current_player->current_block_id ){
		printf("\nYou are not on this property, you can buy a property if you are on that propety\n");
		return;
	}
	else if( current_player->account < current_block->price ){
		show_my_account( current_player );
		printf("\nSorry ,you have not enough money to buy this property\n");
		return;
	}
	
	current_block->owner = *current_player ;	// bought property

	free_space = find_free_space( current_player->owned_block_ids );
	current_player->owned_block_ids[ free_space ] = current_block->block_id;	//adding property to user
	current_player->account -= current_block->price;
	printf("\n\n%s is bought\n", current_block->name);
	show_my_account( current_player );
	if ( current_player->type == car ){
		buy_house( current_block, current_player );
	}
	
}
// find max cost property in the owned properties for to sell
int find_max_cost_property( block * board, int * owned ){
	int max , i=1, max_id=0 ;
	max = find_node( board , owned[0] )->price;

	while( owned[i] != 0 ){
		if ( max < find_node( board , owned[i] )->price ){
			
			max = find_node( board , owned[i] )->price ;
			max_id = owned[i] ;
		}
		i++;
	}
	return max_id;
}
//sell property
void sell_property( block * board, player * current_player ){
	int id, index = 0, no_property, sold_price, i;

	no_property = find_free_space( current_player->owned_block_ids );
	if ( no_property == 0){
		printf("\nSorry , you have no property to sell\n");
		return;
	}
	else if( current_player->type != cap ){
		show_my_properties( board, current_player->owned_block_ids );
		printf("\nPlease give an id to sell a property (to exit enter 0)\n");
		scanf("%d",&id);
		while( !( id == 0 || no_property == 0 ) ){

			if ( find_node( board, id )->type != property ){
				printf("\nThe id that you give is not a property\n");
			}
			else{
				index = verify_property( id, current_player->owned_block_ids );
			}
			if ( index != -1 ){
				sold_price = ( find_node( board, id )->price + ( find_node( board, id )->house_count * find_node( board, id )->house_price ) ) / 2 ;
				printf("\n %d- %s  is sold, Sold for %d\n", id, find_node( board, id )->name, sold_price);
				current_player->account += ( find_node( board, id )->price + ( find_node( board, id )->house_count * find_node( board, id )->house_price ) ) / 2 ;
				current_player->owned_block_ids[ index ] = 0;
				find_node( board, id )->owner.type = noone ;		
				slide_myProperties( current_player->owned_block_ids );	
				show_my_account( current_player );	
			}	
			else{
				printf("\nThe id you entered is not your property\n");
			}

			no_property = find_free_space( current_player->owned_block_ids );
			if ( no_property != 0){
				show_my_properties( board, current_player->owned_block_ids );
				printf("\nPlease give an id to sell a property (to exit enter 0)\n");
				scanf("%d",&id);
			}
		}
		if ( no_property == 0){
			printf("\nSorry , you have no other property to sell\n");
		}
	}	
	else if( current_player->type == cap ){
		show_my_properties( board, current_player->owned_block_ids );
		id = find_max_cost_property( board, current_player->owned_block_ids );
		printf("\nid: %d\n",id );
		sold_price = ( find_node( board, id )->price + ( find_node( board, id )->house_count * find_node( board, id )->house_price ) ) / 2 ;
		printf("\n %d- %s  is sold, Sold for %d\n", id, find_node( board, id )->name, sold_price);
		current_player->account += ( find_node( board, id )->price + ( find_node( board, id )->house_count * find_node( board, id )->house_price ) ) / 2 ;
		current_player->owned_block_ids[ index ] = 0;
		find_node( board, id )->owner.type = noone ;		
		slide_myProperties( current_player->owned_block_ids );	
		show_my_account( current_player );	
	}
	
}
// find average price of all properties
int find_average_cost( block * board ){
	int sum = 0, i=0 ;
	while( board != NULL ){
		if ( board->type == property){
			sum += board->price ;
			i++;
		}
		board = board->next_b ;
	}
	return sum/(i);
}
// to perform fortune card block process
void play_fortune_card( fortune_card * deck , block * board, player * current_player, player * other_player ){
	int pick, dice, number_of_property;
	pick = rand() % 5 ;
	printf("pick = %d\n",pick + 1);
	number_of_property = find_free_space( current_player->owned_block_ids );
	printf("Your picked fortune card is %s\n", deck[pick].name );
	
	if ( deck[pick].card_id == 1 && number_of_property != 0 ){
		if( number_of_property == 1 ){
			find_node( board, current_player->owned_block_ids[ 0 ] )->house_count ++ ;
			printf("You built a house  on  %s for free\n",find_node( board, current_player->owned_block_ids[ 0 ] )->name );
		}
		else{
			dice = rand() % number_of_property ;
			find_node( board, current_player->owned_block_ids[ dice ] )->house_count ++ ;
			printf("You built a house  on  %s for free\n",find_node( board, current_player->owned_block_ids[ dice ] )->name );
		}
	}
	else if( deck[pick].card_id == 2 ){
		dice = (rand() % 6) + 1;
		printf("dice = %d", dice);
		if( dice >= 4 ){
			current_player->current_block_id -= deck[pick].amount ;
			printf("You moved backward 2 block\n");
		}
		else{
			current_player->current_block_id += deck[pick].amount ;
			printf("You moved forward 2 block\n");
		}
	}
	else if( deck[pick].card_id == 3 ){
		current_player->account -= deck[pick].amount ;
		printf("You paid 5000 to the bank\n");
	}
	else if( deck[pick].card_id == 4 ){
		current_player->account -= deck[pick].amount ;
		other_player->account += deck[pick].amount ;
		printf("You paid 10000 to the opponent\n");
	}
	else if( deck[pick].card_id == 5 ){
		current_player->account += deck[pick].amount ;
		printf("You took 20000 from the bank\n");
	}
}
// it is for computer , to know what to do
void cap_plays( block * board, player * current_player, player * other_player ){
	int dice, pay ;
	block * current_block ;
	fortune_card deck[4];
	init_the_deck( deck );

	current_block = current_player->current_block_id ;
	printf("\nTurn : cap \n");
	
	dice = (rand() % 6) + 1 ;
	printf("dice: %d\n",dice );
	//move
	if ( current_player->current_block_id + dice >=24){
		current_player->account += 10000;
	}
	current_player->current_block_id = ( current_player->current_block_id + dice ) % 24;
	current_block = find_node( board ,current_player->current_block_id ) ;

	if( current_block->type == fortune ){		// if it is a fortune block , calls play fortune card function
		show_board( board, * current_player, * other_player );
		play_fortune_card( deck, board, current_player, other_player );
		current_block = find_node( board ,current_player->current_block_id ) ;
	}
	
	if ( current_block->type == property && current_block->owner.type == noone ){ //if it is an unknowed property
		if( current_block->price < find_average_cost(board) ){
			buy_property( current_block, current_player );
		}
		else{
			dice = (rand() % 6) + 1 ;
			printf("dice: %d\n",dice );
			if( dice < 4 ){
				buy_property( current_block, current_player );
			}

		}
	}
	else if( current_block->type == property && current_block->owner.type == current_player->type ){ // if it is an owned property and yours,then built house with the rule
		
		if( find_free_space( current_player->owned_block_ids ) >= 4 ){ // if computer has more than 1/3 property of all properties
			dice = (rand() % 6) + 1 ;
			printf("dice: %d\n",dice );
			if( dice < 4 ){
				buy_house( current_block, current_player );
			}
		}
	}
	//pay tax			
	if ( current_block->type  == tax ){
		
		while ( current_block->price > current_player->account && current_player->owned_block_ids[0] != 0 ){
			printf("\nYou have not enough money to pay tax\n");
			sell_property( board , current_player );
		}							
		pay_tax( current_block, current_player );
		show_my_account( current_player );
	} 
	//pay rent
	else if ( current_block->type == property && current_block->owner.type != current_player->type && current_block->owner.type != noone ){
		pay = pay_rent( current_block, current_player );
		while ( pay > current_player->account && current_player->owned_block_ids[0] != 0 ){
			printf("\nYou have not enough money to pay rent\n");
			sell_property( board , current_player );
		}
		current_player->account -= pay;	
		current_block->owner.account += pay;
		printf("\n%d$ from %s paid to %s  \n", pay, current_player->name, current_block->owner.name );
		show_my_account( current_player );			
	} 
	// get punished
	else if ( current_block->type == punish && current_player->turn_to_wait == 0){
		wait_punish( current_block, current_player );
	}
	
}
// it runs the game
void gameplay ( block * board,  player player_one,  player player_two ){

	block  * current_block ;
	player * current_player, * other_player;
	int dice, choice, choice_two, pay, roll = 0 ;
	player_type turn ;
	fortune_card deck[4];

	init_the_board( board );
	init_the_player( &player_one );
	init_the_player( &player_two );
	init_the_deck( deck );

	player_one.name = "car" ;
	player_two.name = "cap" ;
	printf("\n\n\nWelcome to game\n\n");
	printf("User is %s \n", player_one.name );
	printf("Computer is %s \n\n", player_two.name );
	player_one.type = car ;
	player_two.type = cap ;
	show_board( board, player_one, player_two);

	current_player = &player_one;
	other_player = &player_two;
	turn = player_one.type;
	do{
		roll = 0;
		do{
			if ( current_player->turn_to_wait == 0 && current_player->type == car ){
				current_block = find_node( board ,current_player->current_block_id );

				printf("\nTurn : %s\n",current_player->name);
				if ( roll == 0) printf("\n1 - Roll the dice\n");
				else if( roll == 1 ) printf("\n1 - Switch the turn\n");
				printf("2 - Show my account\n");
				printf("3 - Show my properties\n");
				printf("4 - Show property deeds\n");
				printf("5 - Buy property\n");
				printf("6 - Buy house\n");
				printf("7 - Sell property\n");
				printf("\nPlease select an option to continue : ");
				scanf("%d", &choice);
				printf("\n");
				if ( choice == 1 ) roll++;
				if (  roll != 2 ){
					switch( choice ){

						case 1:
							dice = (rand() % 6) + 1 ;
							printf("dice: %d\n",dice );
							if ( current_player->current_block_id + dice >=24){
								current_player->account += 10000;
							}
							current_player->current_block_id = ( current_player->current_block_id + dice ) % 24;
							current_block = find_node( board ,current_player->current_block_id ) ;
							show_board( board, player_one, player_two);
							if( current_block->type == fortune ){ // if it is a fortune block , calls play fortune card function
								show_board( board, player_one, player_two);
								play_fortune_card( deck, board, current_player, other_player );
								current_block = find_node( board ,current_player->current_block_id ) ;
							}
							// pay tax
							if ( current_block->type  == tax ){ 
								show_board( board, player_one, player_two);
								printf("\nTurn : %s\n",current_player->name);
								if ( current_block->price > current_player->account ){
									printf("\nYou do not have enough money to pay tax.You must sell your properties to gain money,otherwise you will bankrupt and lose the game\n");
									sell_property( board , current_player );
								}
								pay_tax( current_block, current_player );
								show_my_account( current_player );
							}
							// pay rent
							else if ( current_block->type == property && current_block->owner.type != current_player->type && current_block->owner.type != noone ){
								show_board( board, player_one, player_two);
								printf("\nTurn : %s\n",current_player->name);
								pay = pay_rent( current_block, current_player );
								if ( pay > current_player->account ){
									printf("\nYou do not have enough money to pay tax.You must sell your properties to gain money,otherwise you will bankrupt and lose the game\n");
									sell_property( board , current_player );
								}
								current_player->account -= pay;	
								other_player->account += pay;
								printf("\n%d$ from %s paid to %s  \n", pay, current_player->name, current_block->owner.name );
								show_my_account( current_player );			
							}
							// get punished
							else if ( current_block->type == punish && current_player->turn_to_wait == 0){
								show_board( board, player_one, player_two);
								wait_punish( current_block, current_player );
							}
							break;
						case 2:	
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							show_my_account( current_player );
							break;
						case 3:			
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							show_my_properties( board, current_player->owned_block_ids );
							break;
						case 4:
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							show_properties( board );
							break;
						case 5:
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							show_my_account( current_player );
							buy_property( current_block , current_player );	
							break;
						case 6:	
							show_board( board, player_one, player_two);	
							printf("\nTurn : %s\n",current_player->name);
							buy_house( current_block, current_player );		
							break;
						case 7:
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							sell_property( board, current_player );
							break;
						default :
							show_board( board, player_one, player_two);
							printf("\nYou entered an invalid choice");
					}
				}
					
			}
			else if ( current_player->turn_to_wait == 0 && current_player->type == cap ){
				show_board( board, player_one, player_two);
				cap_plays( board, current_player, other_player );
				roll = 2 ;
			}		
		}while( roll != 2 && current_player->turn_to_wait == 0 );
		show_board( board, player_one, player_two);
		if ( current_player->turn_to_wait != 0 ){
			printf("%s player has %d turn punishment\n", current_player->name, current_player->turn_to_wait - 1 );
			current_player->turn_to_wait --;
		}
		if ( current_player->turn_to_wait != 0 && other_player->turn_to_wait !=0 ){
			if ( current_player->turn_to_wait > other_player->turn_to_wait ){
				current_player->turn_to_wait -= other_player->turn_to_wait;
				other_player->turn_to_wait = 0;
			}
			else if (  current_player->turn_to_wait < other_player->turn_to_wait ){
				other_player->turn_to_wait -= current_player->turn_to_wait;				
				current_player->turn_to_wait = 0;
			}
			else{
				current_player->turn_to_wait = 0;
				other_player->turn_to_wait = 0;
			}
		}
		if ( player_one.type == turn ){
			turn = player_two.type;
			current_player = &player_two;
			other_player = &player_one;
		}
		else{
			turn = player_one.type;
			current_player = &player_one;
			other_player = &player_two;
		}
		printf("\n");


	}while( player_one.account > 0  && player_two.account > 0);
	printf("\n\n");
	show_board( board, player_one, player_two);
	if ( player_one.account < 0 ){
		printf("Cap player won the game\n");
	}
	else if ( player_two.account < 0 ){
		printf("Car player won the game\n\n");
	}

}