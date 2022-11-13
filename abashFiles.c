#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void displayText(char plain[]);
int main(){
    int num;
    FILE *fptr;
    char filename[32], plain[32];

    printf("Filename: ");
    fgets(filename, sizeof(filename), stdin);

    fptr = fopen(filename, "rb+");

    if(fptr != NULL){
        printf("Success");

        while(fread(&plain, sizeof(plain), 1, fptr) !=0 ){
            displayText(plain);
        }
    }


    return 0;
}

void displayText(char plain[]){
    printf("%s", plain);
}