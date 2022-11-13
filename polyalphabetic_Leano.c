#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>


void encrypt();
char* getKey(int size);
void decrpyt();

int main(){	

	int choice;
	
	printf("Press 0 Encryption || Press 1 for Decryption: ");    
	scanf("%d", &choice);   
	
	
	switch(choice){
		case 0 : encrypt(); break;
		case 1 : decrpyt(); break;
		default : printf("Incorrect input");
	}
		
    return 0;	 	
}


void encrypt(){
	char plain[32], cipher[32], *key;
	char filename[32];
	int x, size, check;
	FILE *fp;
	
	printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	size = strlen(plain);
	key = getKey(size);
	
	 //encryption
    for(x = 0; x < size; x++){
    	cipher[x] = ((plain[x] + key[x]) % 26) + 'A';
	}
	
    fp = fopen(filename,"w");
	if(fp != NULL){
		check = fputs(cipher, fp);
		if(check != EOF){
			printf("Before: %s\n", plain);
    		printf("After: %s\n", cipher);
		}else{
			printf("Failed writing to file");
		}
	}else{
		printf("Unable to open file");
	}
	fclose(fp);
}


void decrpyt(){
	char plain[32], cipher[32], *key;
	char filename[32];
	int x, size, check;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
		
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 32, fp) !=NULL ) {
			size = strlen(plain);
			key = getKey(size);
			 for(x = 0; x < size; x++){
			 	 cipher[x] = (((plain[x] - key[x]) + 26) % 26) + 'A';
			 }
   		}else{
   			printf("Something wrong inside the file");
		}
	}else{
		printf("Unable to open file");
	}
	fclose(fp);
	printf("Before: %s\n", plain);

    printf("After: %s\n", cipher);
}


char* getKey(int size){
	char *retKey, key[32];
	int keylen,x,y;
	
	printf("\nEnter Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	keylen = strlen(key);
	retKey = (char*) malloc(sizeof(char)*1);
	for(x = 0, y = 0; x < size; x++, y++){
        if(y == keylen)
            y = 0;
 
        retKey[x] = key[y];
    }
    retKey[x] = '\0';
    return retKey;
}



