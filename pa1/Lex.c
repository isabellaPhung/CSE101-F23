#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"string.h"

int MAX_STRING_LENGTH = 255;

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Less than two command line arguments given! Please provide input file and output file.");
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if(input == NULL){
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 0;
    }
    if(output == NULL){
        fprintf(stderr, "Could not open %s.\n", argv[2]);
        return 0;
    }

    int lineCount = 0;
    for (char ch = getc(input); ch != EOF; ch = getc(input)){
        if(ch == '\n'){
            lineCount++;
        }
    }
    //printf("%d\n", lineCount); //lineCount test
    char **strArray = calloc(lineCount, sizeof(char *)); 
    for(int i = 0; i<lineCount; i++){
        strArray[i] = (char *)malloc(MAX_STRING_LENGTH); 
    }
    //string array prepared

    rewind(input);//resets input pointer
    for(int i = 0; i < lineCount; i++){
        fgets(strArray[i], MAX_STRING_LENGTH, input);
    }

    //testing string array
    /**
    for(int i = 0; i < lineCount; i++){
        printf("%s", strArray[i]);
    }
    **/
    fclose(input);

    
    return 0;
}
