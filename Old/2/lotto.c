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

typedef struct statRec {
	int numbersUsed[MAX_LOTTO_RANGE];
	int numberRepeats[MAX_LOTTO_RANGE];
	int length;
} stat;

void addGuessStats(stat *, int *);
void displayGuessStats(stat *);
void newLottoGuess(int *, stat *);
void displayLottoGuest(int *);
void seeWinnings(int *);
void bubbleSort(int *);

int inArray(int, int *, int);

main() {
	stat stats;
	char choice = '0';

	int lottoGuess[LOTTO_NUMBERS] = {0};

	//Initializing the statistics struct
	stats.length = 0;
	
	//Loops the menu while 6 is not inputed
	do {
		printf(
			"Welcome to the lotto program\n"
			"\tChoose one of the options bellow:\n"
			"------------------------------------\n"
			"\t1 - Enter lotto guess\n"
		);
		
		if (stats.length != 0) {
			printf(
				"\t2 - Display last guessed lotto numbers\n"
				"\t3 - Sort the last guessed numbers\n"
				"\t4 - See winnings\n"
				"\t5 - See guess statistics\n"
			);
		}
		
		printf("\t6 - Exit\n");
		
		//Loop while input is whitespace
		do {
			scanf("%c", &choice);
		}
		while (choice == '\n' || choice ==' ');

		//Menu options
		if (choice == '1') {
			newLottoGuess(lottoGuess, &stats);
		}
		else if (stats.length != 0 && choice == '2') {
			printf("The last guessed lotto numbers are: ");
			displayLottoGuest(lottoGuess);
		}
		else if (stats.length != 0 && choice == '3') {
			bubbleSort(lottoGuess);
			printf("The last guessed lotto numbers after sorting are: ");
			displayLottoGuest(lottoGuess);
		}
		else if (stats.length != 0 && choice == '4') {
			seeWinnings(lottoGuess);
		}
		else if (stats.length != 0 && choice == '5') {
			displayGuessStats(&stats);
		}
		else if (choice == '6') {
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
		stats->length = LOTTO_NUMBERS;
		
		for (int i = 0; i < LOTTO_NUMBERS; i++) {
			*(stats->numbersUsed + i) = *(guess + i);
			*(stats->numberRepeats + i) = 1;
		}

	}
	else {
		for (int i = 0; i < LOTTO_NUMBERS; i++) {
			int index = inArray(
				*(guess + i),
				stats->numbersUsed,
				stats->length
			);
			
			if (index == -1) {
				*(stats->numbersUsed + (stats->length)) = *(guess + i);
				*(stats->numberRepeats + (stats->length)) = 1;
				stats->length++;
			}
			else {
				(*(stats->numberRepeats + index))++;
			}
		}
	}
}

void displayGuessStats(stat * stats) {
	for (int i = 0; i < stats->length; i++) {
		printf(
			"The number %d was repeated %d times\n",
			*(stats->numbersUsed + i),
			*(stats->numberRepeats + i)
		);
	}
}

void newLottoGuess(int * lottoGuess, stat * stats) {
	printf(
		"Enter the %d lotto numbers\n"
		"(numbers must be unique and between %d and %d):\n",
		LOTTO_NUMBERS,
		MIN_LOTTO_RANGE,
		MAX_LOTTO_RANGE
	);
	
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		*(lottoGuess + i) = 0;
	}
	
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		char numberStr[2];
		int number;
		
		int valid;
		
		//While input incorrect
		do {
			printf(" - ");

			scanf("%s", numberStr);
			
			//Converting input to number
			number = atoi(numberStr);
			
			//Parameters for input validity
			valid = (
				(number <= MAX_LOTTO_RANGE && number >= MIN_LOTTO_RANGE) &&
				inArray(number, lottoGuess, LOTTO_NUMBERS) == -1
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
				//If value valid insert in array
				*(lottoGuess + i) = number;
			}
		}
		while (!valid);
	}
	 
	addGuessStats(stats, lottoGuess);
	
}

/*
 * Displays a lotto guess
*/
void displayLottoGuest(int * lottoGuess) {
	
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		printf("%d ", *(lottoGuess + i));
	}
	
	printf("\n");
}

void seeWinnings(int * lottoGuess) {
	int winningNumbers[] = {1,3,5,7,9,11};
	int bonus = 42;
	
	int matches = 0;
	int bonusMatches = 0;
	
	for (int i = 0; i < LOTTO_NUMBERS; i++) {
		if (inArray(*(lottoGuess + i), winningNumbers, LOTTO_NUMBERS) != -1) {
			matches++;
		}
	}
	printf("%d\n", matches);
	bonusMatches = (
		inArray(bonus, lottoGuess, LOTTO_NUMBERS) != -1
	);
	
	if (matches == 6) {
		printf("Jackpot!!!\n");
	}
	else if (matches == 5) {
		if (bonusMatches) {
			printf("Congratulations, you won a new car!!!\n");
		}
		else {
			printf("Congratulations, you won a holiday!!!\n");
		}
	}
	else if (matches == 4) {
		if (bonusMatches) {
			printf("Congratulations, you won a weekend away!!!\n");
		}
		else {
			printf("Congratulations, you won a night out!!!\n");
		}
	}
	else if (matches == 3 && bonusMatches) {
		printf("Congratulations, you won a cinema ticket!!!\n");
	}
	else {
		printf("Sorry, you didn't win a prize\n");
	}
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
		for (j = 0; j < LOTTO_NUMBERS; j++) {
	
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
