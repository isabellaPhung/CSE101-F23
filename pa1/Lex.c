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

    List sorted = newList();
    append(sorted, 0);
    moveFront(sorted);
    //printf("line count: %d\n", lineCount);
    //perform insertion sort
    //printf("test: %d\n", get(sorted));
    int testiterator = 0;
    for(int i = 1; i < lineCount; i++){
        //printf("i: %d\n", i);
        while(1){
            //printf("cursor index: %d\n", index(sorted));
            if(index(sorted) == -1){
                append(sorted, i);
                break;
            }
            testiterator++;
            //printf("iterator: %d\n", testiterator);
            int compare = strcmp(strArray[get(sorted)], strArray[i]);
            if( compare >= 0 ){//if belongs left or equivalent
                insertBefore(sorted, i);
                break;
            }
            
            moveNext(sorted);
        }
        testiterator = 0;
        moveFront(sorted);
    }
    //printList(stdout, sorted); 

    moveFront(sorted);
    for(int i = 0; i < lineCount; i++){
        fprintf(stdout, "%s", strArray[get(sorted)]);
        moveNext(sorted);
    }
    return 0;
}
