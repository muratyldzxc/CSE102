#include <stdio.h>
#include <string.h>

//beginning of the first part functions


// it take two number, add them and return the result
int add(int number1,int number2);
// it take two number, subract second number from first number and return the result
int sub(int number1, int number2);
// it take two number, multiple them and return the result
int mult(int number1, int number2);
// it take two number, add them and return the result
int div(int number1,int number2); 
// it take two number, it calculates number1 modulo according to number 2 , and return the result
int modulo(int number1,int number2);
// it take two number, multiple number2 times number1 and return the result
int power(int number1,int number2);
//it is a function that take the operation and two number
int doit (int (*ptrFunction)(int number1,int number2), int first_number, int second_number);

// end of the first part funcitons

//beginning of the second part functions

// it takes a ten size array and fill it numbers which is taken by user (for labs and homeworks)
void take_grades(int Temp[10] );
// it takes a two size array and fill it numbers which is taken by user (for midterm and final exam)
void take_exam_grades(int Temp[2]);
// it takes a ten size array and calculate average of it ,return average( for homeworks)
double calculate_homework(int Temp[10]);
// it takes a ten size array and calculate average of it,return average ( for labs)
double calculate_lab(int Temp[10]);	
// it takes average of homeworks,two size array(for exams),average of labs
//and it calculates the last grade according to given percents
// return last grade
double calculate_all(int homework_average ,int Temp[],int lab_average);

// end of the second part funcitons

// driver test program for part1
void Run_Part1();
// driver test program for part2
void Run_Part2();
// driver test program for part3
void Run_Part3();
// driver test program for whole program
void Menu();

//helper functions

// it prints whitespaces number of whitespace times
void print_whitespaces(int whitespace);
// it prints stars number of stars times
void print_stars(int stars); 

int main(int argc, char const *argv[]){
	
	Menu();

	return 0;
}

//beginning of the first part functions

int add(int number1,int number2){ // it take two number, add them and return the result

	return number1+number2;
}

int sub(int number1, int number2){ // it take two number, subract second number from first number and return the result

	return number1-number2;
}
int mult(int number1, int number2){ // it take two number, multiple them and return the result

	return number1*number2;
}

int div(int number1,int number2){ // it take two number, add them and return the result

	if(number2==0){
		printf("result is infinitive\n");
		return 0;
	}
	else{
		return number1/number2;
	}
	
}
int modulo(int number1,int number2){ // it take two number, it calculates number1 modulo according to number 2 , and return the result

	return number1%number2;
}
int power(int number1,int number2){ // it take two number, multiple number2 times number1 and return the result
	int i,result=1;
	for ( i = 0; i < number2; ++i){
		result=result*number1;
	}
	return result;
}
int doit (int (*ptrFunction)(int number1,int number2), int first_number, int second_number){ //it is a function that take the operation and two number,
	int result;																				 // according to operation it calls another function and send two numbers to that funciton
	result=ptrFunction(first_number,second_number);											 // return the result of that operation of two numbers
	return result;
}
// end of the first part funcitons

//beginning of the second part functions

void take_grades(int Temp[10] ){ // it takes a ten size array and fill it numbers which is taken by user (for labs and homeworks)
	int i;
	
	for ( i = 0; i <10 ; ++i){
		printf("Please give %d.grade\n",i+1);
		scanf("%d",&Temp[i]);
	}
}
void take_exam_grades(int Temp[2]){	// it takes a two size array and fill it numbers which is taken by user (for midterm and final exam)
	int i;
	
	for ( i = 0; i < 2; ++i){
		if (i==0){
			printf("Please give midterm grade\n");
		}
		else{
			printf("Please give final grade\n");
		}
		scanf("%d",&Temp[i]);
	}
}
double calculate_homework(int Temp[10]){ // it takes a ten size array and calculate average of it ,return average( for homeworks)
	int i;
	double result=0;
	
	for ( i = 0; i < 10; ++i){
		
		result=result+Temp[i];
	}
	return result/10;
}
double calculate_lab(int Temp[10]){ 	// it takes a ten size array and calculate average of it,return average ( for labs)
	int i;
	double result=0;
	
	for ( i = 0; i < 10; ++i){
		
		result=result+Temp[i];
	}
	return result/10;

}
// it takes average of homeworks,two size array(for exams),average of labs
//and it calculates the last grade according to given percents
// return last grade

double calculate_all(int homework_average ,int Temp[],int lab_average){

	double result;
	result=((double)homework_average/10)+((double)lab_average/5)+(3*(double)Temp[0]/10)+(4*(double)Temp[1]/10);

	return result;

}
void Run_Part1(){
	char process[100],operation[3];
	int number1,number2,previous=0,i=0;
	memset(operation,0,3);
	memset(process,0,100);
	fgets(process, 100, stdin);
	
	do{	
		
		i=0;
		memset(operation,0,3); //it resets the string with zeros
		memset(process,0,100); //it resets the string with zeros
		fgets(process, 100, stdin);

		if( !(strcmp(process,"ESC\n")==0 || strcmp(process,"esc\n")==0) ){ //if user doesn't give ESC or esc
			
			while(process[i]!=' '){ //it reads one by one untill space
			
				operation[i]=process[i]; //it gets operation
				
				i++;
				
			}
			i++; //increasing i to pass space
			number1=0;
			while(process[i]!=' ' && process[i]!='\0' && process[i]!='\n' ){ //it reads one by one untill space,\0 or \n
			
				number1=(int)process[i]-48+number1*10; // it takes number
				i++;
				
			}
		
			if(process[i]=='\n' || process[i]=='\0'){ //for one input, it takes previous as number 1
				number2=number1;
				number1=previous;					
			}
			else{
				i++; //increasing i to pass space
				number2=0;
				
				while(process[i]!=' ' && process[i]!='\0' && process[i]!='\n'){//it reads one by one untill space,\0 or \n
					
					number2=(int)process[i]-48+number2*10; // it takes number
					
					i++;
				}
				
			}
			
			if (strcmp(operation,"+")==0){ // if operation +,send add to doit function
				previous=doit(add,number1,number2);
			}
			else if (strcmp(operation,"-")==0){// if operation +,send sub to doit function
				previous=doit(sub,number1,number2);
			}
			else if (strcmp(operation,"*")==0){// if operation +,send mult to doit function
				previous=doit(mult,number1,number2);
			}
			else if (strcmp(operation,"/")==0){// if operation +,send div to doit function
				previous=doit(div,number1,number2);
			}
			else if (strcmp(operation,"**")==0){// if operation +,send power to doit function	
				previous=doit(power,number1,number2);
			}
			else if (strcmp(operation,"%")==0){// if operation +,send modulo to doit function
				previous=doit(modulo,number1,number2);
			}
			printf("result is : %d\n",previous);//print the result
		}
		
	
	}while(!(strcmp(process,"ESC\n")==0 || strcmp(process,"esc\n")==0)); //if user doesn't give ESC or esc


}
void Run_Part2(){
	int homework[10],lab[10],exams[2];
	double homework_average,lab_average,final_grade;
	printf("HOMEWORK GRADES:\n\n");
	take_grades(homework); //takes homework grades
	printf("LAB GRADES:\n\n");
	take_grades(lab);		//takes lab grades
	printf("EXAM GRADES:\n\n");
	take_exam_grades(exams); //takes exam grades
	homework_average=calculate_homework(homework); //calculates homework average
	lab_average=calculate_lab(lab);					//calculates lab average
	final_grade=calculate_all(homework_average,exams,lab_average);//calculates last grade
	printf("final_grade: %lf\n",final_grade ); //prints last grade

}
void print_whitespaces(int whitespace){
	int j;
	for (j = 0; j<whitespace ; ++j){ // it prints whitespaces number of whitespace times
		printf(" ");
	}
}
void print_stars(int stars){ // it prints stars number of stars times
	int j;
	for (j = 0; j<stars ; ++j){
		printf("*");
	}
}
void Run_Part3(){
	int height,i,j,k,star_number=0,whitespace;
	printf("Please give the height: ");
	scanf("%d",&height); //takes height

	whitespace=height-1; // arrange whitespace
	
	for (i = 0; i < height; ++i){ // do it height times
		
		print_whitespaces(whitespace);
		printf("/");
		print_stars(star_number);	
		printf("\\");
		whitespace--;
		star_number=star_number+2;
		printf("\n");

	}
	
	whitespace=0;
	star_number=star_number-2;
	
	for (i = 0; i < height; ++i){ // do it height times
		
		print_whitespaces(whitespace);

		printf("\\");
		
		print_stars(star_number);
		
		printf("/");
		whitespace++;
		star_number=star_number-2;
		printf("\n");

	}


}

void Menu(){

	int choice;
	
	do{
		printf("\n");// it displays menu
		printf("***** MENU *****\n");
		printf("1.Run_Part1\n");
		printf("2.Run_Part2\n");
		printf("3.Run_Part3\n");
		printf("4. Exit\n");

		scanf("%d",&choice); //it takes choice
		switch(choice){

			case 1:
				printf("\nWelcome to calculator\n");
				printf("for addition '+'\n");
				printf("for subtraction '-'\n");
				printf("for multiplication '*'\n");
				printf("for division '/'\n");
				printf("for power '**'\n");
				printf("for modulo '%%'\n");
				printf("\nyou can enter process like: + 10 2 or for one input / 5 \n"); // yanyana girilmelidir.
				printf("to get back to the menu, please write 'ESC' or 'esc' and enter it\n");
				Run_Part1();

				break;

			case 2:
				
				Run_Part2();
				
				
				
				break;
			
			case 3:
				
				Run_Part3();
				
				break;

			case 4:
				printf("\nThank you for playing this .\n");	// it will shut down the program after that
				break;

			default:
				printf("You entered an invalid number, please enter a valid number\n");	 // it conrols choice about menu options
		}
	}while(choice!=4);// it keeps going until choice is 4
}