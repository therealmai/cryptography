#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char* abash(char plain[], char cipher[]);
int main(){
    int x;
    char *plain, *cipher;
    printf("Enter text: ");
    gets(plain);

    cipher = abash(plain, cipher);
    
    printf("Before: %s\n", plain);
    printf("After: %s", cipher);

    return 0;
}

char* abash(char plain[], char cipher[]){
 int x, size = strlen(plain);
 cipher = (char*) malloc(sizeof(char)*size+1);
    for(x = 0; x < size; x++) {
        if(isalpha(plain[x])) {
            cipher[x] = (isupper(plain[x]) ? 'Z'+'A' : 'z'+'a') - plain[x];
        } else {
            cipher[x] = plain[x];
        }
    }
    cipher[size] = '\0';
    return cipher;
}