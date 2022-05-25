#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Your functions here
void encrypt(char str[]) {
	int i, j; //declaration of variables i and j for further loops
	int N = 0; //declaration and initialization of the variable N which will represent the number of characters in the string without spaces
	int R, C; //declaration of the variables R and C that will represent the number of rows and columns respectively
	int length = 0; //declaration and initialization of the variable that will represent the length of the string, which is the total number of characters in the string
	int indexarr = 0; //declaration and initialization of the variable that will represent the index of the array str[]

	for (i = 0; i < 500; i++) { //using for loop to calculate the number of characters in the string without spaces
		if ((str[i] != ' ') && (str[i] != '\n') && (str[i] != '\0')) { //because the array contains 500 places, I also put the end of string and tab to the condition of if statement
			N++;
		}
	}

	for (i = 0; i < 500; i++) { //using for loop to calculate the length of the string
		if ((str[i] != '\0')) { //because the array contains 500 places, I used the end of string to calculate the length
			length++;
		}
	}

	R = floor(sqrt(N)); //this function returns the largest integer that is smaller than or equal to the square root of N
	C = ceil(sqrt(N)); //this function returns the smallest integer that is greater than or equal to the square root of N

	if (((R * C) >= N)) { //using if statements to make sure that R and C satisfies the requirements written in the instruction, if no increment R
	} else if (R <= C) {
		if ((R - sqrt(N)) < 0) {
			R++;
		}
	}

	char arr[R][C]; //declaration of the 2d array

	for (i = 0; i < R; i++) { //using nested for loops to fill 2d array with characters from the string str[], here i is representing rows
		for (j = 0; j < C; j++) { //here j is representing columns
			while (((str[indexarr] == ' ') || (str[indexarr] == '\n')
					|| (str[indexarr] == '\0')) && (indexarr < length)) { //using while loop to make sure that the character from the string is not space, tab or end of string
				indexarr++;
			}
			arr[i][j] = str[indexarr]; //equate the character from the string to the position in 2d array
			indexarr++; //increment the index of an array to continue filling 2d array, until index of an array will be more than the length of the string
		}
	}
	for (j = 0; j < C; j++) { //switching columns and rows of the 2d array, and printing it's content as one string, using for loops
		for (i = 0; i < R; i++) {
			printf("%c", arr[i][j]);
		}
		printf(" "); // printing blank space between every column
	}
}

typedef struct { //declaring struct Date, which members are day, month, and year of type int
	int day;
	int month;
	int year;
} Date;

typedef struct { //declaring struct Member, which members are firstname, secondname, and result of type string, id of type int, and dt of type Date
	int id;
	char firstname[20];
	char lastname[20];
	char result[9];
	Date dt;
} Member;

void encryptintofile(char str[]) { //declaring new function that will encrypt the input of the file line-by-line and rewrite it to the new file
	int i, j; //declaration of variables i and j for further loops
	int N = 0; //declaration and initialization of the variable N which will represent the number of characters in the string without spaces
	int R, C; //declaration of the variables R and C that will represent the number of rows and columns respectively
	int length = 0; //declaration and initialization of the variable that will represent the length of the string, which is the number of characters in the string
	int indexarr = 0; //declaration and initialization of the variable that will represent the index of the array str[]

	for (i = 0; i < 500; i++) { //using for loop to calculate the number of characters in the string without spaces

		if ((str[i] != ' ') && (str[i] != '\n') && (str[i] != '\0')) { //because the array contains 500 places, I also put the end of string and tab to the condition of if statement
			N++;
		}
		if (str[i] == '\0') { //and also break the loop when the character reaches end of string
			break;
		}
	}

	for (i = 0; i < 500; i++) { //using for loop to calculate the length of the string
		if ((str[i] != '\0')) { //because the array contains 500 places, I used the end of string to calculate the length
			length++;
		}
		if (str[i] == '\0') { //and also break the loop when the character reaches end of string
			break;
		}
	}

	R = floor(sqrt(N)); //this function returns the largest integer that is smaller than or equal to the square root of N
	C = ceil(sqrt(N)); //this function returns the smallest integer that is greater than or equal to the square root of N

	if (((R * C) >= N)) { //using if statements to make sure that R and C satisfies the requirements written in instruction, if no increment R
	} else if (R <= C) {
		if ((R - sqrt(N)) < 0) {
			R++;
		}
	}

	char arr[R][C]; //declaration of the 2d array

	for (i = 0; i < R; i++) { //using nested for loops to fill 2d array with characters from the string str[], here i is representing rows
		for (j = 0; j < C; j++) { //here j is representing columns
			if (indexarr >= length) { //filling unused spaces in array with blankspace, so that there will not be trash characters in the result
				arr[i][j] = ' ';
				continue;
			}
			while (((str[indexarr] == ' ') || (str[indexarr] == '\n')
					|| (str[indexarr] == '\0')) && (indexarr < length)) { //using while loop to make sure that the character from the string is not space, tab or end of string
				indexarr++;
			}
			arr[i][j] = str[indexarr]; //equate the character from the string to the position in 2d array
			indexarr++; //increment the index of an array to continue filling 2d array
		}
	}
	FILE *outfile; // declaring a new output file
	outfile = fopen("encrypted_results.txt", "a"); //opening the output file for appending
	for (j = 0; j < C; j++) { //switching columns and rows of the 2d array, and printing it's content as one string, using for loops in the output file
		for (i = 0; i < R; i++) {
			fprintf(outfile, "%c", arr[i][j]);
		}
		fprintf(outfile, " "); // printing blank space between every column in the output file
	}
	fprintf(outfile, "\n"); // printing new line character between every row in the output file
	fclose(outfile); //closing output file
}

int readresults(Member members[100]) { //declaring function that will read the file line by line and send every line to the above function, and counting the number of lines, which will be returned to the main function
	int i; //declaring variable i for further loops
	char ch; //declaring character ch that will be used to count the number of line
	int line_num = 0; ///declaration and initialization of the variable that will represent the number of lines in the file
	char line[500]; //declaration of the array line, that will contain the strings from the file
	FILE *infile; //declaration of the new input file
	infile = fopen("pcr_results.txt", "r"); //opening the file for reading to count the number of line

	if (infile == NULL) { //checking whether the file is opened successfully or not, if not printing error message
		printf("problem opening file!");
		return 1;
	}

	do { //using do-while loop to count the number of lines in the file
		ch = fgetc(infile);
		if ((ch == '\n') || (ch == EOF)) {
			line_num++;
		}
	} while (ch != EOF);

	fclose(infile); // closing the file, after successfully counting the number of lines

	infile = fopen("pcr_results.txt", "r"); //opening the file for reading

	for (i = 0; i < 100; i++) { //using for loop to get the strings from the file line-by-line and send them to the previous function for encrypting
		if (i >= line_num) { //making sure that there are not additional lines
			break;
		}
		fgets(line, 500, infile); //getting the string from the file, and transferring it to array line
		encryptintofile(line); //sending array line to the previous function
	}
	fclose(infile); //closing file after successfully encrypting the file

	infile = fopen("pcr_results.txt", "r"); //opening file for reading the information from the file and storing it to the members array

	for (i = 0; i < 100; i++) { //using for loop for reading the information from the file and storing it to the members array , which will be used in the next task
		if (i >= line_num) { //making sure that there are not additional lines
			break;
		}
		fscanf(infile, "%d %s %s %s %d-%d-%d", &members[i].id,
				members[i].firstname, members[i].lastname, members[i].result,
				&members[i].dt.day, &members[i].dt.month, &members[i].dt.year);
	}
	fclose(infile); //closing the file after successfully transferring the information to the members array

	return line_num; //returning the number of lines in the file to the main function
}

Member updateRecord(Member members[100], int pos, char newresult[], int day,
		int month, int year) { //declaring new function of type member
	int i; //declaring variable i for further loop
	for (i = 0; i <= 9; i++) { //using for loop to transfer and update the information from newresult[9] to members[pos].result[9] character by character
		members[pos].result[i] = newresult[i];
	}
	members[pos].dt.day = day; //updating the date in members array
	members[pos].dt.month = month;
	members[pos].dt.year = year;
	char line[500]; //declaring new string for encrypting
	sprintf(line, "%.4d %s %s %s %.2d-%.2d-%.4d", members[pos].id,
			members[pos].firstname, members[pos].lastname, members[pos].result,
			members[pos].dt.day, members[pos].dt.month, members[pos].dt.year); //Transfer the information from member array to line string
	encryptintofile(line); //sending line string to the encryptintofile function for encrypting
	printf("A new record has been added!\n"); //printing the message about successfully updating the file
	return (members[pos]); //returning members[pos] to the main function
}

int main(void) {
	printf("Yerzhan Yerbatyr\n\n");

	setvbuf(stdout, NULL, _IONBF, 0);

	printf("------\n");
	printf("TASK 1\n");
	printf("------\n");
	char S[500] = "N A Z A R B A Y E V  university, 11-10-2021."; // you can change this
	encrypt(S);

	printf("\n\n\n------\n");
	printf("TASK 2\n");
	printf("------\n");
	Member members[100];
	int num_lines;
	num_lines = readresults(members);
	printf("The number of lines %i\n", num_lines);

	printf("\n\n\n------\n");
	printf("TASK 3\n");
	printf("------\n");

	int ID, pos, day, year, month; //declaring new variables for representing ID, position in the array, day, year, and month respectively
	int i; //declaring new variable for using it in loop
	char newresult[9]; //declaring new string that will store the information about PCR result
	do { //using do-while loop to make infinite loop
		pos = -1; //Initializing position variable to -1, to use it in if statements. Since position can be only positive, if the ID is not found in the members array, it will be equal to -1
		printf("Please give an ID: "); //Prompting the user to enter in an id
		scanf("%d", &ID); //reading ID
		if (ID == 0) { //if ID is 0, break the loop
			break;
		}
		for (i = 0; i < 100; i++) { //Checking whether the ID is present in the members array or not, if it found the pos variable is changed to the current index 'i' of the array in the for loop
			if (ID == members[i].id) {
				pos = i;
			}
		}
		if (pos < 0) { //if the ID is not found in the members array, pos = -1 (was initialized previously, and was not changed), so it gives the error message and returns to the start of do-while loop
			printf("This ID does not exist\n");
		}
		if (pos >= 0 && pos < 100) { //in contrast, if the ID is found, pos will be between 0 and 99, since array starts from 0.
			printf("Please give a new result: "); //Prompting the user to enter in a new result
			scanf("%s", newresult); //reading new result
			printf("Please give a new date (dd-mm-yyyy): "); //Prompting the user to enter in a new date
			scanf("%d-%d-%d", &day, &month, &year); //reading new date
			updateRecord(members, pos, newresult, day, month, year); //Sending array, the position, new result, day, month and year to the updateRecord function
		}
	} while (1);

	// DO NOT WRITE ANYTHING BELOW THIS LINE!
	// DO NOT REMOVE OR CHANGE THIS LINE, IT IS USED FOR AUTOMATIC PROCESSING.
	return 0;
}
