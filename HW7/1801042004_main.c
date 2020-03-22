#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum { noone, cap, car }player_type;

typedef enum { start, property, tax, punish }block_type;

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

	player owner ;
	block_type type;

}block;

void wait_punish( block * current_block, player * current_player ); // for wait punish
void pay_tax( block * current_block, player * current_player );	// for pay tax
int pay_rent( block * current_block, player * current_player ); // for pay rent
void set_array(int *arr,int size,int value); // set an array number of size times with value
void print_whitespaces(int whitespace);		// it prints whitespace
void print_dash(int dash);					// it prints dash
int find_digit_number(int number);			// finds digit number
int find_free_space( int * owned_block_ids ); // find the first free space in array and return index
int verify_property( int id, int owned_block_ids[] ); // it checks the given id is in the array or not, if it is return index, if it is not return -1
void show_my_account( player * current_player ); 		// show current player account
void slide_myProperties( int *my_properties);			// slides my properties for good looking
void represent_the_board( block board [20], int * arr ); // it turns board to an int array to print the screen as wanted
void show_my_properties( block board [20], int owned_block_ids[] ); // shows current player properties
void buy_house( block * current_block,  player * current_player ); // buy house


void init_the_board( block board[20]);	// init the board
void init_the_player( player * init_player ); // init the players
void show_board( block board[20], player player_one,  player player_two ); // show board as wanted
void show_properties( block board[20] );	// show all properties and their features							
void buy_property( block* current_block,  player* current_player); // buy a property
void sell_property( block board[20], player* current_player);		// sell a property
void gameplay ( block board[20],  player player_one,  player player_two ); // it runs the game

int main(){
	srand(time(NULL));
	block board[20] ;
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
void show_my_account( player * current_player ){

	printf("\nYour account : %d$\n", current_player->account );
}
void slide_myProperties( int *my_properties){
	int i=0;

	for ( i = 0; i < 11; ++i){
		
		if ( *(my_properties+i) == 0 ){
			*(my_properties+i)=*(my_properties+i+1);
			*(my_properties+i+1) = 0;
		}
	}
}
void represent_the_board( block board [20], int * arr ){

	arr[0] = board[0].block_id;
	arr[1] = board[1].block_id;
	arr[2] = board[2].block_id;
	arr[3] = board[3].block_id;
	arr[4] = board[4].block_id;
	arr[5] = board[5].block_id;

	arr[6] = board[19].block_id;
	arr[7] = board[6].block_id;
	arr[8] = board[18].block_id;
	arr[9] = board[7].block_id;
	arr[10] = board[17].block_id;
	arr[11] = board[8].block_id;
	arr[12] = board[16].block_id;
	arr[13] = board[9].block_id;

	arr[14] = board[15].block_id;
	arr[15] = board[14].block_id;
	arr[16] = board[13].block_id;
	arr[17] = board[12].block_id;
	arr[18] = board[11].block_id;
	arr[19] = board[10].block_id;

}
void init_the_board( block board [20] ){

	int i;
	
	char name[20][15]  = { "Start","Esenyurt","Car Park","Tuzla","Arnavutkoy","Wait 2 Turn","Catalca","Beykoz","Car Fix","Maltepe","Bills","Sisli","Oil","Atasehir","Sariyer","Wait 1 Turn","Kadikoy","Besiktas","Vocation","Bebek" };
	int price[20] = { 0,16000,1500,16500,17000,2,20000,23000,1750,30000,2000,33000,2250,35000,40000,1,43000,60000,5000,70000 };
	int rent[20] = { 0,800,0,850,875,0,1000,1100,0,1350,0,1500,0,1600,1750,0,1900,2500,0,3500 };
	int rent_1[20] = { 0,4000,0,4250,4500,0,5000,5500,0,7000,0,8000,0,8500,9500,0,11000,15000,0,20000 };
	int rent_2[20] = { 0,9000,0,9500,10000,0,12000,12500,0,15000,0,16000,0,17000,19000,0,21500,28000,0,35500 };
	int rent_3[20] = { 0,25000,0,26000,28000,0,30000,33000,0,40000,0,42000,0,45000,48000,0,55000,60000,0,65000 };
	int house_price[20] = { 0,10000,0,12000,12000,0,13000,13000,0,15000,0,16000,0,17000,19000,0,23000,30000,0,35000 };
	block_type type[20] = { start,property,tax,property,property,punish,property,property,tax,property,tax,property,tax,property,property,punish,property,property,tax,property };
	
	for ( i = 0; i < 20; ++i){	
		board[i].block_id = i ;
		board[i].name = ( char * )malloc( sizeof( name[i] ) );
		strcpy(board[i].name , name[i]);

		board[i].price = price[i] ;
		board[i].rent = rent[i] ;
		board[i].rent_1 = rent_1[i] ;
		board[i].rent_2 = rent_2[i] ;
		board[i].rent_3 = rent_3[i] ;
		board[i].house_price = house_price[i] ;
		board[i].house_count = 0 ;
		board[i].owner.type = noone ;
		board[i].type = type[i] ;	
	}
}

void init_the_player( player * init_player ){

	init_player->type = noone ;
	init_player->current_block_id = 0 ;
	set_array( init_player->owned_block_ids, 12, 0 );
	init_player->account = 100000 ;
	init_player->turn_to_wait = 0 ;
	init_player->name = NULL ;
}

void show_board( block board[20], player player_one,  player player_two){
	
	int row, column, current_block_id=0, reached_block_id=0, i=0, digit_number  ;
	int represent_arr [20];

	represent_the_board( board, represent_arr );

  	print_dash(175);
  	printf("\n");
	for ( row = 0; row < 6 ; ++row){
		
		/* printing block name */
		current_block_id = reached_block_id;
	
		for ( column = 0; column < 6; ++column){
			
			if ( !( ( 0 < row && row < 5) &&  ( 0 < column && column < 5) ) ){
				
				printf("|");
				print_whitespaces(8); //tab		
				printf("%-20s", board[ represent_arr[ current_block_id ] ].name);
				current_block_id ++;

				if ( !( row == 0 || row == 5 ) ){
					printf("|");
					print_whitespaces(3);
				}
			}
			else{
				print_whitespaces(8); //tab	
				print_whitespaces(20); //text
			}
		}

		if ( ( row == 0 || row == 5 ) ){
			printf("|");

		}
		
		printf("\n");

		/* printing block price */
		current_block_id = reached_block_id;
	
		
		for ( column = 0; column < 6; ++column){
			
			if ( !( ( 0 < row && row < 5) &&  ( 0 < column && column < 5) ) ){
				printf("|");
				print_whitespaces(8); //tab	
				if ( board[ represent_arr[ current_block_id ] ].type == property || board[ represent_arr[ current_block_id ] ].type == tax ){
					printf("%d$", board[ represent_arr[ current_block_id ] ].price);
					digit_number = find_digit_number( board[ represent_arr[ current_block_id ] ].price );

					print_whitespaces( 20 - digit_number - 1);

				}
				else{
					print_whitespaces(20);
				}
				
				current_block_id ++;

				if ( !( row == 0 || row == 5 ) ){
					printf("|");
					print_whitespaces(3);
				}

			}
			else{
				print_whitespaces(8); //tab	
				print_whitespaces(20);//text
			}
		}
		
		if ( ( row == 0 || row == 5 ) ){
			printf("|");
			

		}

		printf("\n");

		/* printing user */
		current_block_id = reached_block_id;
	
		for ( column = 0; column < 6; ++column){
			
			if ( !( ( 0 < row && row < 5) &&  ( 0 < column && column < 5) ) ){
				
				

				if ( ( player_one.current_block_id == represent_arr[ current_block_id ] ) && ( player_two.current_block_id == represent_arr[ current_block_id ] ) ){
					
					printf("|");
					print_whitespaces(8); //tab	
					printf("%-10s", player_one.name );
					printf("  %-8s", player_two.name );

				}
				else if( player_one.current_block_id == represent_arr[ current_block_id ] ){
					
					printf("|");
					print_whitespaces(8); //tab	
					printf("%-20s", player_one.name );
				}

					
				else if ( player_two.current_block_id == represent_arr[ current_block_id ] ){
						
					printf("|");
					print_whitespaces(8); //tab		
					printf("%-20s", player_two.name );

				}
				else{
					printf("|");
					print_whitespaces(8); //tab	
					print_whitespaces(20); // text

				}

				if ( !( row == 0 || row == 5 ) ){
					printf("|");
					print_whitespaces(3);
				}
			
				current_block_id ++;		
			}
			else{
				print_whitespaces(8); //tab	
				print_whitespaces(20); // text
			}
		}
		if ( ( row == 0 || row == 5 ) ){
			printf("|");
		}

		printf("\n");
		reached_block_id = current_block_id ;

		if (  ( 0 < row && row < 4)  ){
			print_dash(30);
			print_whitespaces(115);
			print_dash(30);

			
		}
		else{
			print_dash(175);
		}
		printf("\n");

	}

	
}

void show_properties( block board[20] ){

	int  i, choice, digit_number;
	printf("\nPlease select a property to see details\n");

	for ( i = 0; i < 20; ++i){

		if ( board[ i ].type == property ){
			
			printf("%d -\t %s \n",i ,board[ i ].name );
		}		
	}
	printf("0 -\t exit \n");

	printf("\nSelected  choice: ");
	scanf("%d",&choice);
	printf("\n");
	
	do{

		if ( 0 <= choice  && choice <= 19 ){
			print_dash(28);
			printf("\n|");
			print_whitespaces(8);
			printf("%-10s", board[choice].name );
			print_whitespaces(8);
			printf("|\n");

			print_dash(28);
			printf("\n|");
			print_whitespaces(4);
			printf("Rent");
			print_whitespaces(8);
			printf("%d$", board[choice].rent );
			digit_number = find_digit_number( board[choice].rent );
			print_whitespaces( 10 - digit_number - 1);
			printf("|");


			printf("\n|");
			print_whitespaces(4);
			printf("Rent 1 H" );
			print_whitespaces(4);
			printf("%d$", board[choice].rent_1 );
			digit_number = find_digit_number( board[choice].rent_1 );
			print_whitespaces( 10 - digit_number - 1);
			printf("|");

			printf("\n|");
			print_whitespaces(4);
			printf("Rent 2 H" );
			print_whitespaces(4);
			printf("%d$", board[choice].rent_2 );
			digit_number = find_digit_number( board[choice].rent_2 );
			print_whitespaces( 10 - digit_number - 1);
			printf("|");

			printf("\n|");
			print_whitespaces(4);
			printf("Rent 3 H" );
			print_whitespaces(4);
			printf("%d$", board[choice].rent_3 );
			digit_number = find_digit_number( board[choice].rent_3 );
			print_whitespaces( 10 - digit_number - 1);
			printf("|\n");

			print_dash(28);

			printf("\n|");
			print_whitespaces(4);
			printf("House Price" );
			print_whitespaces(1);
			printf("%d$", board[choice].house_price );
			digit_number = find_digit_number( board[choice].house_price );
			print_whitespaces( 10 - digit_number - 1);
			printf("|\n");

			print_dash(28);
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

void show_my_properties( block board [20], int owned_block_ids[] ){

	int i = 0, none = 0;
	printf("\nYour properties\n");

	while( owned_block_ids[ i ] != 0 ){		

		printf("%d -  %s \n", owned_block_ids[ i ] , board[ owned_block_ids[ i ] ].name );	
		none = 1;
		i++;			
	}
	if ( none == 0)
	printf("\nNONE\n");
}

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
			printf("\nHouse is bought\n");
			printf("\nPrice of building a house in this property : %d$\n", current_block->house_price );
			printf("\nHouse number that was built in this property is : %d\n",current_block->house_count );
			show_my_account( current_player );
			printf("\nDo you want to build a house (Y:1 N:0)\n");
			scanf("%d",&buy);
		}	

	}while( buy == 1 );
}

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
	printf("\n\nThe property is bought\n");
	show_my_account( current_player );
	buy_house( current_block, current_player );

}

void sell_property( block board[20], player * current_player ){
	int id, index = 0, no_property, sold_price, i;
	show_my_properties( board, current_player->owned_block_ids );

	no_property = find_free_space( current_player->owned_block_ids );
	if ( no_property == 0){
		printf("\nSorry , you have no property to sell\n");
		return;
	}

	printf("\nPlease give an id to sell a property (to exit enter 0)\n");
	scanf("%d",&id);

	while( !( id == 0 || no_property == 0 ) ){

		if ( board[id].type != property ){
			printf("\nThe id that you give is not a property\n");
		}
		else{
			index = verify_property( id, current_player->owned_block_ids );
		}
		if ( index != -1 ){
			sold_price = ( board[ id ].price + ( board[ id ].house_count * board[ id ].house_price ) ) / 2 ;
			printf("\n %d- %s  is sold, Sold for %d\n", id, board[id].name, sold_price);
			current_player->account += ( board[ id ].price + ( board[ id ].house_count * board[ id ].house_price ) ) / 2 ;
			current_player->owned_block_ids[ index ] = 0;
			board[id].owner.type = noone ;		
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
void gameplay ( block board[20],  player player_one,  player player_two ){

	block  * current_block ;
	player * current_player, * other_player;
	int dice, choice, choice_two, pay ;
	player_type turn ;

	init_the_board( board );
	init_the_player( &player_one );
	init_the_player( &player_two );

	player_one.name = "cap" ;
	player_two.name = "car" ;
	printf("\n\n\nWelcome to game\n\n");
	printf("First player is %s \n", player_one.name );
	printf("Second player is %s \n", player_two.name );
	player_one.type = cap ;
	player_two.type = car ;
	
	printf("\n\n");
	show_board( board, player_one, player_two);
	printf("\n");
	current_player = &player_one;
	other_player = &player_two;
	turn = player_one.type;
	do{
		do{
			if ( current_player->turn_to_wait == 0 ){
				current_block = & board [ current_player->current_block_id ];

				printf("\nTurn : %s\n",current_player->name);
				printf("\n1 - Roll the dice\n");
				printf("2 - Show my account\n");
				printf("3 - Show my properties\n");
				printf("4 - Show property deeds\n");
				printf("5 - Buy property\n");
				printf("6 - Buy house\n");
				printf("7 - Sell property\n");
				printf("\nPlease select an option to continue : ");
				scanf("%d", &choice);
				printf("\n");
				switch( choice ){

					case 1:
						dice = (rand() % 6) + 1 ;
						printf("dice: %d\n",dice );
						if ( current_player->current_block_id + dice >=20){
							current_player->account += 10000;
						}
						current_player->current_block_id = ( current_player->current_block_id + dice ) % 20;
						current_block = & board [ current_player->current_block_id ];
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
						else if ( current_block->type == punish && current_player->turn_to_wait == 0){
							show_board( board, player_one, player_two);
							printf("\nTurn : %s\n",current_player->name);
							wait_punish( current_block, current_player );
						}
						else if( current_block->type == property && current_block->owner.type == noone ){
							printf("\nTurn : %s\n",current_player->name);
							printf("Do you want to buy this property. (Y:1 N:0)\n");
							scanf("%d",&choice_two);
							if ( choice_two == 1 && (current_block->price > current_player->account) ){
								printf("\nYou do not have enough money to buy this property.You can sell your properties to gain money\n");
								sell_property( board , current_player );
							}
							if ( choice_two == 1){
								//system("clear");
								show_board( board, player_one, player_two);
								printf("\nTurn : %s\n",current_player->name);
								buy_property( current_block , current_player );
							}
							else{
								show_board( board, player_one, player_two);
							}						
						}
						else if ( current_block->type == property && current_block->owner.type == current_player->type ){
							buy_house( current_block, current_player  );
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

			
		}while( choice != 1 && current_player->turn_to_wait == 0 );
		
		
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
	if ( player_one.account < 0 ){
		printf("Car player won the game\n");
	}
	else if ( player_two.account < 0 ){
		printf("Cap player won the game\n\n");
	}

}