/*
 * Description:
 * Author: Andre Barata
 * Date: 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LOTTO_NUMBERS 6
#define MAX_LOTTO_RANGE 42
#define MIN_LOTTO_RANGE 1
#define REC_NUMS_INCREMENT 10

typedef struct statRec {
	int * numbersUsed;
	int * numberRepeats;
	int length;
	int maxNums;
} stat;

void addGuessStats(stat *, int *);
void newLottoGuess(int *, stat *);
void displayLottoGuest(int *);
void bubbleSort(int *);

int inArray(int, int *, int);

main() {
	stat guessStatistics;
	char choice = 0;

	int lottoGuess[LOTTO_NUMBERS] = {0};

	//Initializing the statistics struct
	guessStatistics.length = 0;
		
	
	//Loops the menu while 6 is not inputed
	do {
		printf("%d", guessStatistics.length);
		printf(
			"Welcome to the lotto program\n"
			"\tChoose one of the options bellow:\n"
			"------------------------------------\n"
			"\t1 - Enter lotto guess\n"
		);
		
		if (guessStatistics.length != 0) {
			printf(
				"\t2 - Display last guessed lotto numbers\n"
				"\t3 - Sort the last guessed numbers\n"
				"\t4 - See winnings\n"
				"\t5 - See guess statistics\n"
			);
		}
		
		printf("\t6 - Exit\n");
		
		scanf("%1s", &choice);
		
		if (choice == '1') {
			newLottoGuess(lottoGuess, &guessStatistics);
		}
		else if (guessStatistics.length != 0 && choice == '2') {
			printf("The last guessed lotto numbers are: ");
			displayLottoGuest(lottoGuess);
		}
		else if (guessStatistics.length != 0 && choice == '3') {
		
		}
		else if (guessStatistics.length != 0 && choice == '4') {
			
		}
		else if (guessStatistics.length != 0 && choice == '5') {

		}
		else if (choice == '6') {
			if (guessStatistics.length != 0) {
				free(guessStatistics.numbersUsed);
				free(guessStatistics.numberRepeats);
			}
			printf("Bye\n\n");
		}
		else {
			printf("Invalid option entered\n");
		}
	}
	while (choice != '6');
}

void addGuessStats(stat * stats, int * guess) {
	
	//If statistics struct is not initialized
	if (stats->length == 0) {
		//Getting Space to store statistics
		stats->numbersUsed = calloc(
			sizeof(stat), REC_NUMS_INCREMENT
		);
		
		stats->numberRepeats = calloc(
			sizeof(stat), REC_NUMS_INCREMENT
		);
		
		if (stats->numberRepeats == NULL && stats->numberRepeats == NULL) {
			printf("Error allocating memory\n");
			return;
		}
		
		stats->maxNums = REC_NUMS_INCREMENT;
		stats->length = LOTTO_NUMBERS;
		
		for (int i = 0; i < LOTTO_NUMBERS; i++) {
			*(stats->numbersUsed + i) = *(guess + i);
			printf("%d", *(stats->numbersUsed + i));
			*(stats->numberRepeats + i) = 1;
		}
	}
}

void newLottoGuess(int * lotoGuess, stat * guessStatistics) {
	printf(
		"Enter the %d lotto numbers\n"
		"(numbers must be unique and between %d and %d):\n",
		LOTTO_NUMBERS,
		MIN_LOTTO_RANGE,
		MAX_LOTTO_RANGE
	);
	
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		char numberStr[2];
		int number;
		
		int valid;
		
		//While input incorrect
		do {
			printf(" - ");

			scanf("%s", numberStr);
			
			number = atoi(numberStr);
			
			//Parameters for input validity
			valid = (
				number != 0 &&
				(number <= MAX_LOTTO_RANGE && number >= MIN_LOTTO_RANGE) &&
				inArray(number, lotoGuess, LOTTO_NUMBERS) == -1
			);
			
			//Error checking
			if (!valid) {
				if (number > MAX_LOTTO_RANGE || number < MIN_LOTTO_RANGE) {
					printf(
						"Input is not a number between %d and %d\n",
						MIN_LOTTO_RANGE,
						MAX_LOTTO_RANGE
					);
				}
				else {
					printf("You can't use repeated numbers\n");
				}
				
			}
			else {
				*(lotoGuess + i) = number;
			}
		}
		while (!valid);
	}
	
	addGuessStats(guessStatistics, lotoGuess);
}

void displayLottoGuest(int * lotoGuess) {
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		printf("%d ", *(lotoGuess + i));
	}
	
	printf("\n");
}

/*
 * Implements a modified version
 * of the bubble sort algorithm
*/
void bubbleSort(int * array) {
	int j = 0;
	int temp = 0;
	int sorted = 0;
	
	do { 
		sorted = 0;
		for (j = 0; j < LOTTO_NUMBERS - 1; j++) {
	
			if (*(array + j) > *(array + (j+1))) {
				temp = *(array + j);
				*(array + j) = *(array + (j+1));
				*(array + (j+1)) = temp;
				
				sorted++;
			}
		}
	}
	while (sorted != 0);
}

int inArray(int number, int * list, int size) {
	//Passes throght the list until the right string is found
	for (int i = 0; i < size; i++) {
		//Compares the given string with a string in the list
		if (number == *(list + i)) {
			
			return i;
		}
	}
	
	return -1;
}
