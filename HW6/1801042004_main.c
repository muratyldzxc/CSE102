#include <stdio.h>
#include <stdlib.h>

// it finds GCD
int common(int number1, int number2);
// it gets power of a number
int get_power(int  base, int power);
// it fills array with numbers that user entered
void Take_arr_elements(int arr [],int size);
//it prints given array
void Print_Array(int arr[], int size);
// In part 2, benefit from internet for helping homework done
// it sorts arrays
void Merge(int arr[], int left, int middle, int right);
// Function has to divide the list into two lists recursively until it can no more be divided  
// left is for left index beginning and right is for right index beginning 
void MergeSort(int arr[], int left, int right);
// it does the formula
void Part_3(int number);
// perform part 4 operation
int Part_4(int number,int digit);
//  looks all characters of given string,searching capital letter,untill find one or come to \0 character
void Part_5(char *str);
// test for whole program
void Menu();

int main(){
	
	Menu();

	return 0;
}

// it finds GCD
int common(int number1, int number2){
   
    if (number2 != 0){

       return common(number2, number1%number2);
    }

    else{

    	return number1;
    }      
}
// it gets power of a number
int get_power(int  base, int power){
	
	int i=0,result=1;
	
	while(i<power){
		result= result * base;
		i++;
	}

	return result;
}
// it fills array with numbers that user entered
void Take_arr_elements(int arr [],int size){
	int i;
	
	for ( i = 0; i < size; ++i){
		
		printf("\n%d.element: ",i+1 );
		scanf("%d",&arr[i]);
	}
}
//it prints given array
void Print_Array(int arr[], int size) { 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d, ", arr[i]); 
    printf("\n"); 
} 
// In part 2, benefit from internet for helping homework done
// it sorts arrays
void Merge(int arr[], int left, int middle, int right) { 
    int i, j, k; 
    int n1 = middle - left + 1; //it is max index of left part
    int n2 =  right - middle; 	//it is max index of right part
    
    int Left[n1], Right[n2]; 
  
    // copy data to temp arrays 
    for (i = 0; i < n1; i++) {
    	Left[i] = arr[left + i]; 
    }

    for (j = 0; j < n2; j++) {   
    	Right[j] = arr[middle + 1+ j]; 
    }
  
    
    i = 0; // left array index
    j = 0; // right array index
    k = left; // arr array index(begin)
    
    // sort  temp arrays 

    while (i < n1 && j < n2) { 

        if (Left[i] <= Right[j]) { 

            arr[k] = Left[i]; 
            i++; 
        } 
        else{

            arr[k] = Right[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // Copy the remaining elements of Left array
    while (i < n1) { 

        arr[k] = Left[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of Right array
    while (j < n2) { 
        
        arr[k] = Right[j]; 
        j++; 
        k++; 
    } 
} 
// Function has to divide the list into two lists recursively until it can no more be divided  
// left is for left index beginning and right is for right index beginning 
void MergeSort(int arr[], int left, int right) { 
    if (left < right) { 
        
        int middle = (left+right)/2; 
  
        MergeSort(arr, left, middle); // for Left array
        MergeSort(arr, middle+1, right);   // for Right array
  
        Merge(arr, left, middle, right); // for sorting
    } 
} 
// it does the formula
void Part_3(int number){

	printf("%d ",number);
	if (number==1){
		printf("\n");
		return;	
	}

	else{
		
		if ( (number%2)==0 ){
			
			Part_3(number/2);
		}
		else if( (number%2)==1 ){
			Part_3(3*number + 1);
		}
	}
}

int Part_4(int number,int digit){
	
	int digit_number=1,sum;
	//find digit number of given number
	while( ( number / (get_power(10,digit_number)) ) > 0){
		
		digit_number++;
		
	}
	// if digit number bigger than or equal immediate digit
	// it takes immediate digit and 3 power of immediate number
	if (digit<=digit_number){
		
		sum= get_power( ( (number/get_power(10,digit-1)) % 10) , digit_number) + Part_4(number,digit+1);
	}
	else{
	
		return 0;
	}
	
	if (sum==number && digit==1){
		printf("EQUAL\n");
	}
	else if (sum != number && digit==1){
		printf("NOT EQUAL\n");
	}
	return sum;

}
//  looks all characters of given string,searching capital letter,untill find one or come to \0 character
void Part_5(char *str){
	
	//finish condition
	if (*str=='\0'){ 
		return;
	}
	else{
		// capital letter condition
		if ('A' <= *str  && *str <='Z'){
			printf("First capital letter is : %c\n",*str);
			return;
		}
		else{
			Part_5(&str[1]);
		}
	}
}

void Menu(){
	int choice, number1, number2, size, i, *arr;
	char str[100];

	
	
	do{
		printf("\nWelcome to Program\n\n");
		for ( i = 0; i < 5; ++i){
			printf("%d) Run Part %d\n",i+1,i+1);
		}
		printf("\nPlease give the choice: ");
		scanf("%d",&choice);
		printf("\n");	
		switch( choice ){
			// Run Part1
			case 1:
				printf("\nPlease give first number: ");
				scanf("%d",&number1);
				printf("Please give second number: ");
				scanf("%d",&number2);
				printf("\n");	
				printf("GCD of these two number: %d \n",common(number1,number2));

				break;
			// Run Part2	
			case 2:
				printf("please give the size of array: ");
				scanf("%d",&size);	
				arr=(int *)malloc( sizeof(int) * size );

				Take_arr_elements(arr,size);
				MergeSort(arr,0,size-1);
				printf("\n");	
				printf("Sorted array elements: ");
				Print_Array(arr,size);	

				break;
			// Run Part3
			case 3:
				printf("Please give the number: ");	
				scanf("%d",&number1);
				printf("\n");	
				Part_3(number1);
				break;
			// Run Part4
			case 4:
				printf("Please give the number: " );
				scanf("%d",&number1);
				printf("\n");	
				Part_4(number1,0);
				break;
			// Run Part5
			case 5:
				printf("Please give the sentence: " );
				scanf("%s",str);
				printf("\n");	
				Part_5(str);
				break;
			// closing program
			case 6:
				printf("\nClosing the program...\n");
				break;
			// invalid choice
			default:
				printf("\nYou entered an invalid number.\n");
				

		}

	}while(choice!=6);
	
}
