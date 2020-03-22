#include<stdio.h>
#include<stdlib.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

//BEGIN OF THE GIVEN CODE
int get_line_size(char *line);
void copy_string(char *source, char *destination);
void remove_newline(char *line);
void print_dictionary(char *dict[]);
void print_coord(int coord[DICT_SIZE][4]);
//END OF THE GIVEN CODE

//BEGIN OF MY CODE

// set an array with size time by value
void set_array(int *arr,int size,int value);
//compare 2 string, if they are equal returns 0,otherwise returns 1
int str_cmp(char *str1, char *str2);
// return size of the given string
int str_len( char *str);
// reverse the given string and return it as a char pointer
char * reverse_string(char *word);
//print a 15*15 matris
void print_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],int row,int column);
//fill 15*15 matris with random charecters
void fill_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],int row,int column);
// place the given word to 15*15 matris with given cordinates 
void place_words_to_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],char *word,int begin_x,int begin_y,int end_x,int end_y);
// match the given word to 15*15 matris characters with given cordinates, if they match  returns 1 ,otherwise returns 0
int match_words(char Puzzle_Map[][DICT_SIZE],char *user_word , int x_cordinate,int y_cordinate,int do_x,int do_y);
// it makes the given word characters uppercase
void make_uppercase(char Puzzle_Map[][DICT_SIZE],char *user_word,int x_cordinate,int y_cordinate,int do_x,int do_y);
// it checks which word is founded,and return its index
int check_words(char **dict_words,char *user_word);
// it checks how many words are founded,and return the number
int check_founded_words(int * founded_words);


int main(){
	// BEGIN OF THE GIVEN CODE
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	//print_dictionary(dict);
	//print_coord(coord);
	// END OF THE GIVEN CODE

	// BEGIN OF THE MY CODE
	time_t t;
	srand((unsigned) time(&t));
	char Puzzle_Map[15][15], user_word[WORD_LEN];
	int i=0,j,c,founded_words[DICT_SIZE],x_cordinate,y_cordinate,carry,number_of_founded_words=0;

	set_array(founded_words,15,0);//it zeroes the given array

	fill_Puzzle_Map(Puzzle_Map,15,15);// it fills the puzzle map with random characters

	// it place words on the puzzle map with their given cordinates
	for ( i = 0; i <DICT_SIZE; ++i){
		place_words_to_Puzzle_Map(Puzzle_Map,dict[i],coord[i][0],coord[i][1],coord[i][2],coord[i][3]);
		
	}

	printf("\nWELCOME TO PUZZLE MAP GAME\n");
	printf("\n\tPUZZLE MAP\n");
	print_Puzzle_Map(Puzzle_Map,15,15); //print puzzle map
	char *reverse;	
	do{
		printf("\nPlease give the word: ");
		scanf("%s",user_word);
		reverse=(char*) malloc(sizeof(char) * (str_len(user_word)+1));
		reverse=reverse_string(user_word);

		// if the given word is not exit or EXIT 
		if ((str_cmp(user_word,"exit")!=0 && str_cmp(user_word,"EXIT")!=0)){
			
			printf("\nPlease give x cordinate: ");
			scanf("%d",&x_cordinate);
			printf("\nPlease give y cordinate: ");
			scanf("%d",&y_cordinate);
			/*
				i:1 j:1 sag asagi
				i:1 j:0 asagi
				i:1 j:-1 sol asagi
				
				i:0 j:1 sag 
				i:0 j:0 nothing
				i:0 j:-1 sol 
			
				i:-1 j:1 sag yukari
				i:-1 j:0 yukari
				i:-1 j:-1 sol yukari
			*/	
			carry=0;// to understand the word is match or not
			for ( i = 1; -2<i; --i){	
				for (j = 1; -2<j; --j){
				
					carry=match_words(Puzzle_Map,user_word,x_cordinate,y_cordinate,i,j);
					
					if(carry!=1){ //if word is not match, then use reverse of it to check again
						carry=match_words(Puzzle_Map,reverse,x_cordinate,y_cordinate,i,j);
					}
					// if word is match
					if (carry==1){
						make_uppercase(Puzzle_Map,user_word,x_cordinate,y_cordinate,i,j); // make uppercase of characters of the string
						founded_words[check_words(dict,user_word)]=1; // it records matched  words 
						number_of_founded_words=check_founded_words(founded_words); //it holds number of founded words
						printf("\n%d.kelime: %s bulundu\n",check_words(dict,user_word)+1,user_word); //it says whats the number of the word you found
					}			
				}
				
			}
			printf("\n\tPUZZLE MAP\n");
			print_Puzzle_Map(Puzzle_Map,15,15); // prints puzzle map
			printf("\nnumber of words you found: %d \n",number_of_founded_words);	//it prints number of founded words
			
			
		
		}
		
	}while((str_cmp(user_word,"exit")!=0 && str_cmp(user_word,"EXIT")!=0) && number_of_founded_words<DICT_SIZE); //if given word is exit or EXIT or all words founded ,it breaks the loop
	
	if (number_of_founded_words==15){ // if you foun all words
		printf("\nYou found all words.Thank you for playing.\n");
	}
	else{ // if you want to exit
		printf("\nClosing the game...\n");
	}
	
	

	
	// WRITE HERE...
		
	return 0;
}


//BEGIN OF THE GIVEN CODE
int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n' && *ch_iter != 13) {
		ch_iter++; // next char

	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}
//END OF THE GIVEN CODE

//BEGIN OF MY CODE

// set an array with size time by value
void set_array(int *arr,int size,int value){
	int i;
	for (i = 0; i < size ; i++){ 
        *(arr+i) = value; 
    } 
}

 //compare 2 string, if they are equal returns 0,otherwise returns 1
int str_cmp(char *str1, char *str2){

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

// return size of the given string
int str_len( char *str){
	int i=0;
	while(*(str+i)!='\0' ){
		i++;
	}

	return i;
}

// reverse the given string and return it as a char pointer
char * reverse_string(char *word){
	int length,i=0,max;
	char *reverse=(char*) malloc(sizeof(char) * (str_len(word)+1));
	max=str_len(word);
	while(*(word+i)!='\0'){
		*(reverse+max-i-1)=*(word+i);
		i++;
	}
	
	*(reverse+i)='\0';
	
	return reverse;
}

//print a 15*15 matris
void print_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],int row,int column){
	int i,j;
	for ( i = 0; i < row; ++i){
		for (j = 0; j < column; ++j){
			
			printf("%c ",Puzzle_Map[i][j]);
		}
		printf("\n");
	}
}

//fill 15*15 matris with random charecters
void fill_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],int row,int column){
	int i,j;
	for ( i = 0; i < row; ++i){
		for (j = 0; j < column; ++j){
			Puzzle_Map[i][j]=(rand()%26)+97;
		}
	}
}

// place the given word to 15*15 matris with given cordinates 
void place_words_to_Puzzle_Map(char Puzzle_Map[][DICT_SIZE],char *word,int begin_x,int begin_y,int end_x,int end_y){
	int i=0,length;


	length=str_len(word);
	while(i<length){
		
		if (begin_x<end_x && begin_y<end_y){ //sağ aşağı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y++;
			begin_x++;
		}
		else if (begin_x<end_x && begin_y>end_y){ //sol aşağı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y--;
			begin_x++;
		}
		else if (begin_x>end_x && begin_y<end_y){ //sağ yukarı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y++;
			begin_x--;
		}
		else if (begin_x>end_x && begin_y>end_y){ //sol yukarı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y--;
			begin_x--;
		}
		else if (begin_y<end_y){ //sağ
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y++;
		}
		else if (begin_y>end_y){ //sol
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_y--;
		}
		else if (begin_x<end_x){ //aşağı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_x++;
		}
		else if (begin_x>end_x){ //yukarı
			Puzzle_Map[begin_x][begin_y]=*(word+i);
			begin_x--;
		}
		else if (begin_x==end_x && begin_y==end_y){
			Puzzle_Map[begin_x][begin_y]=*(word+i);
		}
		i++;
	}

}
// match the given word to 15*15 matris characters with given cordinates, if they match  returns 1 ,otherwise returns 0
int match_words(char Puzzle_Map[][DICT_SIZE],char *user_word , int x_cordinate,int y_cordinate,int do_x,int do_y){
	
	int i=0,length,same=1;

	length=str_len(user_word);

	while(i<length){
		// if the given word characters not match with characters given by cordinates,it does same=0  and break the loop
		if ( !( *(user_word+i) == Puzzle_Map[x_cordinate][y_cordinate] || ( *(user_word+i)-32) == Puzzle_Map[x_cordinate][y_cordinate]) ){
			same=0;
			
			i=length;

		}
		
		x_cordinate+=do_x; //it says increase,decrease or do nothing , depend on the given parameter
		y_cordinate+=do_y; //it says increase,decrease or do nothing , depend on the given parameter
		
		if (x_cordinate>14 && x_cordinate<0 && y_cordinate>14 && y_cordinate<0){
			i=length;
		}
		i++;
	}
	return same; // return same
}

// it makes the given word characters uppercase
void make_uppercase(char Puzzle_Map[][DICT_SIZE],char *user_word,int x_cordinate,int y_cordinate,int do_x,int do_y){
	int i=0,length;
	length=str_len(user_word);

	while(i<length){
		// if it is not uppercase already, it makes the character uppercase
		if (Puzzle_Map[x_cordinate][y_cordinate]>91){
			Puzzle_Map[x_cordinate][y_cordinate]-=32;
		}

		x_cordinate+=do_x; //it says increase,decrease or do nothing , depend on the given parameter
		y_cordinate+=do_y; //it says increase,decrease or do nothing , depend on the given parameter
		i++;
	}
	
}

// it checks which word is founded,and return its index
int check_words(char **dict_words,char *user_word){
	int i=0;
	while(str_cmp(dict_words[i],user_word)!=0 && i<15){
		i++;
	}
	return i;
}

// it checks how many words are founded,and return the number
int check_founded_words(int * founded_words){
	int i=0,count=0;
	while(i<15){

		if (*(founded_words+i)==1){
			count++;
		}
		i++;
	}
	return count;
}