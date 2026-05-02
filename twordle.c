//Author: Modi McCracken
//PA 10

#include <stdio.h>
#include <stdbool.h>

#define wordSize 5
#define maxGuesses 6
#define stringSize 6
#define FILENAME "mystery.txt"

void getKeyWord(char word[]);
void getGuess(char guessArray[], int guessNumber);
bool isValidGuess(char guessArray[]);
void convertLowercase(char string[]);
void giveGuessResponse(char guess[], char word[], char displayGuess[], char hintArrows[]);
bool correctGuess(char guess[], char word[]);

int main() {
	char word[stringSize];
	char guess[stringSize];
	char guessCollection[maxGuesses][stringSize];
	char hintArrows[maxGuesses][stringSize];
	
	int index;
	int guessCount = 0;
	
	getKeyWord(word);
	convertLowercase(word);
	
	while (guessCount < maxGuesses -1) {
		getGuess(guess, guessCount + 1);
		giveGuessResponse(guess, word, guessCollection[guessCount], hintArrows[guessCount]);
		
		printf("================================\n");
		
		for (index = 0; index <= guessCount; index++) {
			printf("%s\n", guessCollection[index]);
			
			if (hintArrows[index][0] != ' ' || hintArrows[index][1] != ' '
			 || hintArrows[index][2] != ' ' || hintArrows[index][3] != ' ' 
			 || hintArrows[index][4] != ' ') {
			 	printf("%s\n", hintArrows[index]);
			}
			
		printf("\n");
		}
		
		if (correctGuess(guess, word)) {
			printf("You won!\n");
			return 0;
		}
		
		guessCount++;
	}
	
	printf("Final Guess: ");
	scanf("%s", guess);
	convertLowercase(guess);
	while (!isValidGuess(guess)) {
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
		scanf("%s", guess);
		convertLowercase(guess);
	}
	
	giveGuessResponse(guess, word, guessCollection[guessCount], hintArrows[guessCount]);
	
	printf("================================\n");
	
	for(index = 0; index <= guessCount; index++) {
		printf("%s\n", guessCollection[index]);
		
		if (hintArrows[index][0] != ' ' || hintArrows[index][1] != ' '
		 || hintArrows[index][2] != ' ' || hintArrows[index][3] != ' ' 
		 || hintArrows[index][4] != ' ') {  
			 printf("%s\n", hintArrows[index]);
		}
		printf("\n");
	}	 
			 
	if(correctGuess(guess, word)) {
		printf("You won!\n");
	}
	else {
	printf("You lost, better luck next time!\n");
	}			 
			 
	return 0;
}


void getKeyWord(char word[]) {
	FILE *file = fopen(FILENAME, "r");
	
	if (file == NULL) {
		printf("could not open word.txt\n");
		word[0] = '\0';
		return;
	}
	
	fscanf(file, "%s", word);
	fclose(file);
}

void getGuess(char guess[], int guessNumber) {
	printf("Guess %d! Enter your guess: ", guessNumber);
	scanf("%s", guess);
	convertLowercase(guess);
	
	while (!isValidGuess(guess)) {
		printf("Your guess must be 5 letters long.\n");
		printf("please try again: ");
		scanf("%s", guess);
		convertLowercase(guess);
	}
}

void convertLowercase(char string[]) {
	int i = 0;
	
	while (string[i] != '\0') {
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = string[i] +32;
		}
		i++;
	}
}

bool isValidGuess(char guess[]) {
	int j = 0;
	
	while (guess[j] != '\0') {
		if (!((guess[j] >= 'a' && guess[j] <= 'z') ||
		(guess[j] >= 'A' && guess[j] <= 'Z'))) {
			return false;
		}
		j++;
	}
	return j == wordSize;
}

void giveGuessResponse(char guess[], char word[], char displayGuesses[], char hintArrows[]) {
	int k, l;
	bool found;
	
	for (k = 0; k < wordSize; k++) {
		displayGuesses[k] = guess[k];
		hintArrows[k] = ' ';
	}
	
	displayGuesses[wordSize] = '\0';
	hintArrows[wordSize] = '\0';
	
	for (k = 0; k < wordSize; k++) {
		if (guess[k] == word[k]) {
		displayGuesses[k] = displayGuesses[k] - 32;
		}
		else {
			found = false;
		
			for (l = 0; l < wordSize; l++) {
				if (guess[k] == word[l] && guess[l] != word[l]) {
					found = true;
				}
			}
			if (found) {
				hintArrows[k] = '^';
			}
		}
	}
}

bool correctGuess(char guess[], char word[]) {
	int m;
	
	for (m = 0; m < wordSize; m++) {
		if (guess[m] != word[m]) {
			return false;
		}
	}
	return true;
}
