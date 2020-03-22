#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person{ 
    char name[20]  ; 
    char surname[20] ; 
    char musical_Work[20] ; 
    int age; 
    struct person * next; 
} *top; 

// find the node number in stack
int find_node_number ( );
// swap data between  nodes
void swap (struct person * current );
// print the data in the stack
void print_stack ( );
// add a node into stack, add it at the top
void addNode( char name[], char surname [], char creation [], int age );
// delete a node, delete it at the top
void deleteNode( );
// sort stack according to age
void Sort_Increasingly( );
// sort stack according to name
void Sort_Alphabetically( );
// it shows menu
void menu ();

int main(int argc, char const *argv[])
{
	menu();	
	return 0;
}

// find the node number in stack
int find_node_number ( ){
	int i=0;
	struct person * temp = top ;
	
	while( temp != NULL ){
		temp= temp->next;
		i++;	
	}
	return i;
}

// swap data between  nodes
void swap (struct person * current ){ 	
	// copy the current node
    struct person * temp = ( struct person * )malloc( sizeof( struct person ) ) ;
	strcpy( temp->name, current->name ) ;
	strcpy( temp->surname, current->surname ) ;
	strcpy( temp->musical_Work, current->musical_Work ) ;
	temp->age = current->age;
	// copy current->next node to current node
	strcpy( current->name, current->next->name ) ;
	strcpy( current->surname, current->next->surname ) ;
	strcpy( current->musical_Work, current->next->musical_Work ) ;
	current->age = current->next->age;
	// copy current node to  current->next node
	strcpy( current->next->name, temp->name ) ;
	strcpy( current->next->surname, temp->surname ) ;
	strcpy( current->next->musical_Work, temp->musical_Work ) ;
	current->next->age = temp->age;

} 

// print the data in the stack
void print_stack ( ){
	int i = 1;
	struct person * temp ;
	temp = top ;
	printf("\n\nStack : \n");
	while( temp != NULL ){
		printf("************* \n");
		printf("%d)\n", i );
		printf("Name: %s\n", temp->name );
		printf("Surname: %s\n", temp->surname );
		printf("Creation: %s\n", temp->musical_Work );
		printf("Age: %d\n", temp->age );
		i++;
		temp = temp->next ;
	}
}
// add a node into stack, add it at the top
void addNode( char name[], char surname [], char creation [], int age ){
	struct person * Temp = ( struct person * )malloc( sizeof( struct person ) );
	strcpy( Temp->name, name ) ;
	strcpy( Temp->surname, surname ) ;
	strcpy( Temp->musical_Work, creation ) ;
	Temp->age = age ;
	
	Temp->next = top ;
	top = Temp ;
}

// delete a node, delete it at the top
void deleteNode( ){
	if ( top != NULL )
	{
		struct person * temp ;
		temp = top->next ;
		free( top );
		top = top->next ;
	}
	else
		printf("\nYou have nothing to delete in the stack\n");
	
}
// sort stack according to age
void Sort_Increasingly( ){	
	int node_number, i = 0 ;
	struct person * temp = top ;
	node_number = find_node_number();

	while( i < node_number ){
		temp = top ;
		while( temp->next != NULL ){
			if( temp->age > temp->next->age ){ 
				swap( temp ) ;	
			}
			temp = temp->next ;
		}
		i++;
	}
	printf(" i :  %d \n",i);	
}
// sort stack according to name
void Sort_Alphabetically( ){
	int node_number, k, i = 0 ;
	struct person * temp = top ;
	node_number = find_node_number();
	
	while( i < node_number ){
		temp = top ;
		while( temp->next != NULL ){
			if( strcmp( temp->name, temp->next->name ) > 0 ){
				swap( temp );
			}
			temp = temp->next ;
		}
		i++;
	}
}
// it shows menu
void menu (){
	int choice, age ;
	char name[20], surname [20],  creation [20] ; 

	printf("\n****MENU**** \n");
	printf("   1- Add a Person to the Stack \n");
	printf("   2- Pop a Person from the Stack \n");
	printf("   3- Sort Alphabetical Order \n");
	printf("   4- Sort Age in Increasing Order \n");
	printf("   5- Exit menu \n");
	printf("************* \n");
	printf("Select your choice: ");

	scanf("%d", &choice );
	while( choice != 5 )
	{
		switch( choice )
		{
			case 1:
				printf("Name: ");
				scanf(" %[^\n]",name);
				printf("Surname: ");
				scanf(" %[^\n]",surname );
				printf("Creation: ");
				scanf(" %[^\n]",creation );
				printf("Age: ");
				scanf("%d",&age );
				addNode( name, surname, creation, age );
				print_stack();
				break;
			case 2:
				deleteNode();
				print_stack();
				break;
			case 3:
				Sort_Alphabetically( );
				print_stack();
				break;
			case 4:
				Sort_Increasingly( );
				print_stack();
				break;
			case 5:
				printf("Closing the program...\n");
				break;
			default:
				printf("You entered an invalid number , Please give a number which is in the MENU\n");
		}
		
		printf("\n****MENU**** \n");
		printf("   1- Add a Person to the Stack \n");
		printf("   2- Pop a Person from the Stack \n");
		printf("   3- Sort Alphabetical Order \n");
		printf("   4- Sort Age in Increasing Order \n");
		printf("   5- Exit menu \n");
		printf("************* \n");
		printf("Select your choice: ");

		scanf("%d", &choice );
	}
	printf("\nClosing the program...\n");

}
