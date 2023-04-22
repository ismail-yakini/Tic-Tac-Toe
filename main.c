#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


#define user 0
#define computer 1


void interface(char *);
void user_play(char *T);
void computer_play(char *T);
bool choice(char *T, char n);
int check(char *T);
void message(int result, bool player);
bool play_again();


void interface(char *T){
	system("clear");
	printf("\n\n");
	printf("\t\t\t\t +++++++++++++++ \n");
	printf("\t\t\t\t +  %c | %c | %c  + \n", T[0], T[1], T[2]);
	printf("\t\t\t\t + ----------- + \n");
	printf("\t\t\t\t +  %c | %c | %c  + \n", T[3], T[4], T[5]);
	printf("\t\t\t\t + ----------- + \n");
	printf("\t\t\t\t +  %c | %c | %c  + \n", T[6], T[7], T[8]);
	printf("\t\t\t\t +++++++++++++++ \n");
}


void user_play(char *T){
	char n;
	do{
		interface(T);
		printf("\n\n\t\t\t\t    Play Now !\n");
		printf("\t\t\t\t        ");
		scanf("%c", &n);
		while(!getchar()); //to avoid printting the last line twice
		printf("\n");
	}while(!choice(T, n));
	T[n-49] = 'X';
}


void computer_play(char *T){
	int n;
	time_t time1, time2;
	interface(T);
	printf("\n\n\t\t\t\t      ");
	printf("Wait ...\n");
	time1 = time(NULL);
	do{
    	srand(time(0)) ;  // Seed the random number generator
    	n = 0 + rand() % (9 - 0 + 1);
		n+=49;
	}while(!choice(T, n));
	time2 = time(NULL);
	if(difftime(time2, time1) < 1.5){
		sleep(1.5);
	}
	T[n-49] = 'O';
}


bool choice(char *T, char n){
	if(n<'1' || n>'9'){
		return 0;
	}else if(T[n-49]=='X' || T[n-49]=='O'){
		return 0;
	}else{
		return 1;
	}
}


int check(char *T){
	int no_winner = 2;
	for(int i=0; i<=6; i+=6){
		if(T[i] == T[i+1] && T[i] == T[i+2]){
			return 1;
		}
	}
	for(int i=0; i<=2; i+=2){
		if(T[i] == T[i+3] && T[i] == T[i+6]){
			return 1;
		}
	}
	for(int i=1; i<5; i++){
		if(T[4] == T[4+i] && T[4] == T[4-i]){
			return 1;
		}	
	}
	for(int i=0; i<9; i++){
		if(T[i] != 'X' && T[i] != 'O'){
			no_winner = 0;
			break;
		}
	}
	return no_winner;
}


void message(int result, bool player){
	if(result == 2){
		printf("\n\n\t\t\t\t    ");
		printf("NO Winner\n");
	}else if(result == 1 && player == user){
		printf("\n\n\t\t\t\t ");
		printf("Congratulation !\n");
		printf("\n\t\t\t\t ");
		printf("   You Win !\n");
	}else{
		printf("\n\n\t\t\t\t    ");
		printf("You Lose !\n");
	}
	sleep(1.5);
}


bool play_again(){
	char n;
	printf("\n\n");
	do{
		printf("Do you want to play again [Y/N] : ");
		scanf("%c", &n);
		while(!getchar()); //to avoid printting the last line twice
	}while(n != 'Y' && n != 'y' && n != 'N' && n != 'n');
	if(n == 'Y' || n == 'y'){
		return 1;
	}else{
		return 0;
	}
}


int main(){
	char *T = malloc(9 * sizeof(char));
	char n;
	bool player ;
	int result;
	repeat:
	player = computer;
	for(int i=0; i<9; i++){
		T[i] = 49 + i;
	}
	do{
		player = !player;
		if(player == user){
			user_play(T);
		}else{
			computer_play(T);
		}
	}while((result = check(T)) == 0);
	interface(T);
	message(result, player);
	if(play_again()){
		goto repeat;
	}else{
		system("clear");
		exit(1);
	}
	return 0;
}