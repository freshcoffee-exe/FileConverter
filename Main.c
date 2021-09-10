//============================================================================= 
// PROGRAMMER:    Eren Ozbay      
// PANTHER ID:    2452687
// CLASS:         COP4338, Online Section  
// SEMESTER:      Summer 2021 
// Project:       Assignment 5
// DUE:           07/09/2021
//=============================================================================

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ROW 1000 //input file will have less than or equal to 1000 lines
#define MAX_LEN 1000
#define MAX_TOKEN 100

char* trim(char* token) {
    if (!token)//error checking
        return NULL;
    int i = 0;
    while (*token == ' ')//remove leading spaces
        token++;
    for (i = strlen(token) - 1; i >= 0 && token[i] == ' '; i--); //remove trailing spaces
    token[i + 1] = '\0';
    return token;
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;
    int i;
    for (i = 0; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}
//Scanner s = new Scanner(new File("my table.csv"));
//s.useDelimiter(",");
//s.useDelimiter("[^a-zA-Z]");
//s.useDelimiter("^0-9a-zA-Z]");
//s.next() or s.nextLine()...
void handleConvert() {
    char* token1[MAX_TOKEN]; //token for the first input file
    char* token2[MAX_TOKEN]; //token for the second input file
    char* tl5 = ".tl5";
    char* csv = ".csv";
    char* tr9 = ".tr9";
    int i = 0, dataIndex = 0;

    if (getCommandWord(token1, MAX_TOKEN) == '\n') {
        printf("Too few arguments for the convert command! It must be in the formateconvert source.xxx destination.yyy \n");
        return;
    }
    if (getCommandWord(token2, MAX_TOKEN) != '\n') {
        printf("Too many arguments for the convert command! It must be in the formateconvert source.xxx destination.yyy \n");
        return;
    }       
        FILE* input = fopen(token1, "r");
        char* data[MAX_ROW];// array that will store the file content, line by line
        char* token;
        char line[MAX_LEN]; //temporary placeholder for a line input from the file
        //%d %ld %f %lf %c
        //for (; fscanf(input, "%[^\n]\n", line) != EOF; i++) {//
        for (;fgets(line, MAX_LEN, input) != NULL; i++) {
            line[strlen(line) - 1] = '\0'; //replace \n by \0
            data[dataIndex] = (char*)malloc(strlen(line) + 1); //+1 for \0
            strcpy(data[dataIndex++], line); //copying one string to another
        }

    if ((strstr(token2, tl5) != NULL) && (strstr(token1, csv) != NULL)) {   //if statement to convert .csv to tl5
        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], ",")); //tokenizes the ith row stored in the data array
            fprintf(output, "%-5.5s", token);
            while (token = trim(strtok(NULL, ",")))
                fprintf(output, "|%-5.5s", token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);

    }
    else if ((strstr(token2, csv) != NULL) && (strstr(token1, tl5) != NULL)) { //if statement to convert .tl5 to .csv
        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, ",%s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    } 
    else if ((strstr(token2, csv) != NULL) && (strstr(token1, tr9) != NULL)) { //if statement to convert .tr9 to .csv
        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, ",%s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    }
    else if ((strstr(token2, tr9) != NULL) && (strstr(token1, csv) != NULL)) {   //if statement to convert .csv to tr9
        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], ",")); //tokenizes the ith row stored in the data array
            fprintf(output, "%9.9s", token);
            while (token = trim(strtok(NULL, ",")))
                fprintf(output, "|%9.9s", token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);

    }
    else if ((strstr(token2, csv) != NULL) && (strstr(token1, csv) != NULL)) {   //if statement to convert .csv to .csv
        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], ",")); //tokenizes the ith row stored in the data array
            fprintf(output, token);
            while (token = trim(strtok(NULL, ",")))
                fprintf(output, ",%s", token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);

    }

    else if ((strstr(token2, tl5) != NULL) && (strstr(token1, tl5) != NULL)) { //if statement to convert .tl5 to .tl5

        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, "%-5.5s", token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, "|%-5.5s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    }
    else if ((strstr(token2, tl5) != NULL) && (strstr(token1, tr9) != NULL)) { //if statement to convert .tr9 to .tl5

        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, "%-5.5s", token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, "|%-5.5s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    }
    else if ((strstr(token2, tr9) != NULL) && (strstr(token1, tr9) != NULL)) { //if statement to convert .tr9 to .tr9

        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, "%9.9s", token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, "|%9.9s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    }

    else if ((strstr(token2, tr9) != NULL) && (strstr(token1, tl5) != NULL)) { //if statement to convert .tl5 to .tr9

        fclose(input);
        FILE* output = fopen(token2, "w");
        for (i = 0; i < dataIndex; i++) { //reading all of the lines of the input file
            token = trim(strtok(data[i], "|")); //tokenizes the ith row stored in the data array
            fprintf(output, "%9.9s", token);
            while (token = trim(strtok(NULL, "|")))
                fprintf(output, "|%9.9s", token);
            //fprintf(output, token);
            fprintf(output, i == dataIndex - 1 ? " " : "\n");
        }
        fclose(output);
    }
}


main()
{
    char command[MAX_TOKEN];
    char lastCharacter;

    while (1) {
        printf("Please enter a new command...\n");
        printf("Type Quit to exit, or 'convert source.xxx destination.yyy' to convert files \n");
        lastCharacter = getCommandWord(command, MAX_TOKEN);
        if (!strcmp(command, "quit"))
            break;
        else if (!strcmp(command, "convert")){
            handleConvert();
        }
        else {
            printf("Invalid Command, please try again");
        }
    }

}