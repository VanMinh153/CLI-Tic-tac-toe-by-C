#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int size;
char board[50][50];
const char PLAYER = 'X';
const char COMPUTER = 'O';
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
int main() {
	char winner = ' ';
	do{
		printf("Which size of game u want #(3-50) ? : ");
		scanf("%d", &size);
		if(size < 3 || size > 50) printf("Invalid size !\n");
	} while(size < 3 || size > 50);
	resetBoard();
	while(winner == ' ' && checkFreeSpaces() != 0){
		printBoard();
		
		playerMove();
		winner = checkWinner();
		if(winner != ' ' || checkFreeSpaces() == 0){
			break;
		}
		computerMove();
		winner = checkWinner();
		if(winner != ' ' || checkFreeSpaces() == 0){
			break;
		}
	}
	
	printBoard();
	printWinner(winner);
	return 0;
}
void resetBoard(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			board[i][j] = ' ';
		}
	}
}
void printBoard(){
	for(int i = 1; i <= size; i++){
		if(i == 1) printf("%6d", i);
		else printf("%3d", i);
	}
	printf("\n");
	for(int i = 0; i < size; i++){
		//printf("%d ", i + 1);
		for(int j = 0; j < size; j++){
			if(j == size - 1) printf("%3c", board[i][j]);
			else if(j == 0) printf("%6c|", board[i][j]);
			else printf("%3c|", board[i][j]);
		}
		printf("\n");
		if(i != size - 1){
			for(int j = 0; j < size; j++){
				if(j == size - 1) printf("---");
				else printf("---|");
			}
			printf("\n");
		}
	}
}
int checkFreeSpaces(){
	int freeSpaces = size * size;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(board[i][j] != ' ') freeSpaces--;
		}
	}
	return freeSpaces;
}
void playerMove(){
	int x;
	int y;
	do{
		printf("Enter row #(1 - %d): ", size);
		scanf("%d", &x);
		x--;
		printf("Enter column #(1 - %d): ", size);
		scanf("%d", &y);
		y--;
		if(board[x][y] != ' '){
			printf("Invalid move!\n");
		}
		else{
			board[x][y] = PLAYER;
			break;
		}
	} while(board[x][y] != ' ');	
}
void computerMove(){
	//creates a seed based on current time
	srand(time(0));
	int x;
	int y;
	if(checkFreeSpaces() > 0){
		do{
			x = rand() % 100;
			y = rand() % 100;
		} while(board[x][y] != ' ');
		board[x][y] = COMPUTER;
	}
	else{
		printWinner(' ');
	}
}
char checkWinner(){
	//check rows
	for(int i = 0; i < size; i++){
		int check = 1;
		for(int j = 1; j < size; j++){
			if(board[i][j] != board[i][0]) check = 0;
		}
		if(check) return board[i][0];
	}
	//check columns
	for(int i = 0; i < size; i++){
		int check = 1;
		for(int j = 1; j < size; j++){
			if(board[j][i] != board[j][0]) check = 0;
		}
		if(check) return board[0][i];
	}
	//check diagonals
	int check = 1;
	for(int i = 0; i < size; i++){
		if(board[i][i] != board[0][0]) check = 0;
	}
	if(check) return board[0][0];
	
	int check1 = 1;
	for(int i = 0; i < size; i++){
		if(board[i][size - 1 - i] != board[0][size - 1]) check1 = 0;
	}
	if(check1) return board[0][size - 1];
	
	return ' ';
}
void printWinner(char winner){
	if(winner == PLAYER){
		printf("YOU WIN!");
	}
	else if(winner == COMPUTER){
		printf("YOU LOSE!");
	}
	else printf("IT'S A TIE!");
}

