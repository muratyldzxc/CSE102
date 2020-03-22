#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 20

// Queue structure
typedef struct queue {
	int data ;
	struct queue * next_q ;
}queue;
//Stack structure
typedef struct stack {
	int data ;
	struct stack * next_s ;
}stack;
// Binary tree structure
typedef struct bst {
	int data ;
	struct bst * left_b ;
	struct bst * right_b ;
}bst;
// create a new node and add it to the stack
void add_to_s ( stack ** sp, int data ){
	stack * newp = ( stack * )malloc( sizeof( stack ) ) ;
	newp->data = data ;
	newp->next_s = *sp ;
	*sp = newp ;	
}
// create a new node and add it to the queue
void add_to_q( queue ** head ,int data){
	queue * new_q = ( queue * )malloc( sizeof( queue ) ) ;

	new_q->data = data;
 	new_q->next_q = NULL;
 
	if( *head == NULL){
		*head = new_q;	
	}else{
		queue *temp_q = *head ;
		while( temp_q->next_q != NULL ){
			temp_q = temp_q->next_q ;
		}
		temp_q->next_q = new_q;
	}
}
// create a new node and add it to the binary tree
void add_to_bst( bst ** root, int data ){

	if( *root == NULL ){
		( *root) = ( bst * )malloc( sizeof( bst ) ) ;
		( *root )->data = data ;
		( *root )->left_b = NULL ;
		( *root )->right_b = NULL ;
	}
	else{
		if( data == ( *root )->data ){
			return ;
		}
		else if( data > ( *root )->data ){
			add_to_bst( &( ( *root)->right_b ) , data ) ;
		}
		else if( data < ( *root )->data ){
			add_to_bst( &( ( *root)->left_b ) , data ) ;
		}
	}
}
// print data in the stack
void print_stack( stack * temp_s ){

	while( temp_s != NULL ){
		printf(" %d,",temp_s->data );
		temp_s = temp_s->next_s ;
	}
}
// print data in the queue
void print_queue( queue * temp_q ){
	
 	while( temp_q != NULL ){
	 	printf(" %d,",temp_q->data );
	 	temp_q = temp_q->next_q ;
 	}
}

void fill_structures( stack ** stack_, queue ** queue_, bst ** bst_, int data[ ] ){
	int i ;
	double start_t[3], end_t[3], total_t[3] ; // for three struct execution time
	
	// STACK
	start_t[0] = clock();				// it holds start time
	for ( i = 0; i < SIZE ; ++i){		// it fill the stack with given data
		add_to_s( stack_, data[ i ] );
	}
	end_t[0] = clock();					// it holds end time
	total_t[0] = ( end_t[0] - start_t[0] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[0] *= 1000 ;									  // converting seconds to milliseconds
	
	// QUEUE
	start_t[1] = clock();				// it holds start time
	for ( i = 0; i < SIZE ; ++i){
		add_to_q( queue_, data[ i ] );	// it fill the queue with given data
	}
	end_t[1] = clock();					// it holds end time
	total_t[1] = ( end_t[1] - start_t[1] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[1] *= 1000 ;									  // converting seconds to milliseconds

	// BST
	start_t[2] = clock();				// it holds start time
	for ( i = 0; i < SIZE ; ++i){	
		add_to_bst( bst_, data[ i ] );	// it fill the bst with given data
	}
	end_t[2] = clock();					// it holds end time
	total_t[2] = ( end_t[1] - start_t[1] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[2] *= 1000 ;									  // converting seconds to milliseconds

	printf("\n\n***** fill_structures() *****\n\n");		// print the report to the console
	printf("\nStructures\tStack\t\tQueue\t\tBST\n");	
	printf("Exec. time(ms)\t%lf\t%lf\t%lf\n", total_t[0], total_t[1], total_t[2] );
	
}
// it orders data in the stack
void order_stack ( stack * stack_ ){
	int i = 0, temp ;
	stack * cursor = stack_ ;

	while( i < SIZE ){
		cursor = stack_ ;

		while( cursor->next_s != NULL ){

			if( cursor->data < cursor->next_s->data ){ // if next data is bigger than the previous, swap them
				temp = cursor->data ;
				cursor->data = cursor->next_s->data ;
				cursor->next_s->data = temp ;
			}
			cursor = cursor->next_s ;
		}
		i++;
	}
}
// it orders data in the queue
void order_queue ( queue * queue_ ){
	int i = 0, temp ;
	queue * cursor = queue_ ;

	while( i < SIZE ){
		cursor = queue_ ;

		while( cursor->next_q != NULL ){

			if( cursor->data < cursor->next_q->data ){ // if next data is bigger than the previous, swap them
				temp = cursor->data ;
				cursor->data = cursor->next_q->data ;
				cursor->next_q->data = temp ;
			}
			cursor = cursor->next_q ;
		}
		i++;
	}
}
// it prints data in bst with decreasing order
// it goes to right until get null then print the value , go back adn do the same for left
void ordered_print_bst ( bst * root ){

	if( root == NULL ){
		return ;
	}
	else{
		ordered_print_bst( root->right_b ) ;
		printf(" %d,", root->data ) ;
		ordered_print_bst( root->left_b ) ;
	}
}
void ordered_print( stack * stack_, queue * queue_, bst * bst_ ){
	double start_t[3], end_t[3], total_t[3] ;	// for three struct execution time

	printf("\n\n***** ordered_print() *****\n\n");

	printf("\nSTACK:");
	start_t[0] = clock(); // it holds start time
	order_stack( stack_ ) ;
	print_stack( stack_ ) ;
	end_t[0] = clock();	  // it holds end time
	total_t[0] = ( end_t[0] - start_t[0] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[0] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	printf("\nQUEUE:");
	start_t[1] = clock(); // it holds start time
	order_queue( queue_ ) ;
	print_queue( queue_ ) ;
	end_t[1] = clock();	   // it holds end time
	total_t[1] = ( end_t[1] - start_t[1] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[1] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	printf("\nBST:");
	start_t[2] = clock();  // it holds start time
	ordered_print_bst( bst_ ) ;
	end_t[2] = clock();    // it holds end time
	total_t[2] = ( end_t[2] - start_t[2] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[2] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	printf("\nStructures\tStack\t\tQueue\t\tBST\n");		  // print the report to the console
	printf("Exec. time(ms)\t%lf\t%lf\t%lf\n", total_t[0], total_t[1], total_t[2] );

}
// it search the value if find any print the value and the step and returns 1, if dont find any returns -1
int search_in_stack( stack * stack_, int val_to_search){
	int i = 0 ,none = -1 ;
	stack *temp = stack_ ;

	while( temp != NULL ){
		i++;
		if( temp->data == val_to_search ){
			printf("The value \"%d\" founded on %d.step\n", val_to_search, i );
			none = 1 ;
		}
		temp = temp->next_s ;
	}
	return none ;
}
// it search the value if find any print the value and the step and returns 1, if dont find any returns -1
int search_in_queue( queue * queue_, int val_to_search ){
	int i = 0 ,none = -1 ;
	queue *temp = queue_ ;

	while( temp != NULL ){
		i++;
		if( temp->data == val_to_search ){
			printf("The value \"%d\" founded on %d.step\n", val_to_search, i );
			none = 1 ;
		}
		temp = temp->next_q ;
	}
	
	return none ;
}
// it search the value if find any print the value and the step and returns 1, if dont find any returns -1
int search_in_bst( bst * root, int val_to_search, int * step ){
	int none = -1 ;
	if( root != NULL ){
		if( root->data == val_to_search ){
		printf("The value \"%d\" founded on %d.step\n", val_to_search, *step );
		return 1 ;
		}
		else if( root->data > val_to_search ){
			( *step )++ ;
			none = search_in_bst( root->left_b, val_to_search, step ) ;
		}
		else if( root->data < val_to_search ){
			( *step )++ ;
			none = search_in_bst( root->right_b, val_to_search, step );
		}
	}

	return none ;
}
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search){
	int none , step = 1 ;
	double start_t[3], end_t[3], total_t[3] ;	// for three struct execution time

	printf("\n\n***** search() *****\n\n");

	printf("In Stack:\n\n");
	start_t[0] = clock(); // it holds start time
	none = search_in_stack( stack_, val_to_search ) ;
	end_t[0] = clock();    // it holds end time
	total_t[0] = ( end_t[0] - start_t[0] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[0] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	if( none == -1 ){
		printf("No result found in Stack\n");
	}

	printf("\nIn Queue:\n\n");
	start_t[1] = clock(); // it holds start time
	none = search_in_queue( queue_, val_to_search ) ;
	end_t[1] = clock();    // it holds end time
	total_t[1] = ( end_t[1] - start_t[1] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[1] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	if( none == -1 ){
		printf("No result found in Queue\n");
	}

	printf("\nIn BST:\n\n");
	start_t[2] = clock(); // it holds start time
	none = search_in_bst( bst_, val_to_search, &step ) ;
	end_t[2] = clock();    // it holds end time
	total_t[2] = ( end_t[2] - start_t[2] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[2] *= 1000 ;									  // converting seconds to milliseconds
	printf("\n");

	if( none == -1 ){
		printf("No result found in BST\n");
		printf("none %d\n",none);
	}

	printf("\nStructures\tStack\t\tQueue\t\tBST\n");		  // print the report to the console
	printf("Exec. time(ms)\t%lf\t%lf\t%lf\n", total_t[0], total_t[1], total_t[2] );
}
// it find max and min node and swap it with first two nodes, after that move top foward  2 node
void special_traverse_stack( stack * stack_ ){
	stack *cursor, *top, *min_s, *max_s ;
	int temp_max, temp_min ;
	top = stack_ ;
	while( top != NULL && top->next_s != NULL ){
		cursor = top ;
		max_s = cursor ;
		min_s = cursor ;

		while( cursor->next_s != NULL ){
			if( cursor->next_s->data > max_s->data ){
				
				max_s = cursor->next_s ;
			}
			if( cursor->next_s->data < min_s->data ){
				min_s = cursor->next_s ;
			}
			cursor = cursor->next_s ;
		}

		temp_max = max_s->data ;
		temp_min = min_s->data ;

		max_s->data = top->data ;
		min_s->data = top->next_s->data ;

		top->data = temp_max ;
		top->next_s->data = temp_min ;
		top = top->next_s->next_s ;
	}
}
// it find max and min node and swap it with first two nodes, after that move top foward  2 node
void special_traverse_queue( queue * queue_ ){
	queue *cursor, *top, *min_q, *max_q ;
	int temp_max, temp_min ;
	top = queue_ ;
	while( top != NULL && top->next_q != NULL ){
		cursor = top ;
		max_q = cursor ;
		min_q = cursor ;

		while( cursor->next_q != NULL ){
			if( cursor->next_q->data > max_q->data ){
				
				max_q = cursor->next_q ;
			}
			if( cursor->next_q->data < min_q->data ){
				min_q = cursor->next_q ;
			}
			cursor = cursor->next_q ;
		}

		temp_max = max_q->data ;
		temp_min = min_q->data ;

		max_q->data = top->data ;
		min_q->data = top->next_q->data ;
		
		top->data = temp_max ;
		top->next_q->data = temp_min ;
		top = top->next_q->next_q ;
	}
}
void special_traverse(stack * stack_, queue * queue_, bst * bst_){
	double start_t[3], end_t[3], total_t[3] ; // for three struct execution time
	printf("\n\n***** special_traverse() *****\n\n");
	
	printf("\nFOR Stack:");
	start_t[0] = clock();	// it holds start time
	special_traverse_stack( stack_ ) ;
	end_t[0] = clock();		// it holds end time
	total_t[0] = ( end_t[0] - start_t[0] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[0] *= 1000 ;									  // converting seconds to milliseconds
	print_stack( stack_ ) ;
	
	printf("\n\nFOR Queue:");
	start_t[1] = clock();	// it holds start time
	special_traverse_queue( queue_ ) ;
	end_t[1] = clock();		// it holds end time
	total_t[1] = ( end_t[1] - start_t[1] ) / CLOCKS_PER_SEC ; // it holds execution time as seconds
	total_t[1] *= 1000 ;
	print_queue( queue_ ) ;


	printf("\n\nStructures\tStack\t\tQueue\t\tBST\n");	
	printf("Exec. time(ms)\t%lf\t%lf\n\n", total_t[0], total_t[1]);
}

int main() { 

 int data[20]={ 5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4 }; 
 
 	bst * bst_     = NULL; 
 	queue * queue_ = NULL; 
 	stack * stack_ = NULL; 

	fill_structures( &stack_, &queue_, &bst_, data); 



 	ordered_print( stack_, queue_, bst_ ) ; 
 	search( stack_, queue_, bst_, 7 ) ; 
 	special_traverse( stack_, queue_, bst_ ) ; 

 return 0; 
}
