#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

void encrypt();
void decrpyt();
int main(){	
int choice;
	do {
	printf("\n----------ATBASH CIPHER----------");
	printf("\nEncrypt____1");
	printf("\nDecrypt____2");
	printf("\nExit_______3");
	printf("\n\nEnter your choice: ");
	scanf("%d", &choice);
	printf("\n");
	(void) getchar(); //clean the input of newline

	switch (choice) {
	case 1: 
		encrypt(); break;
	case 2: 
		decrpyt(); break;
	case 3: 
		break;
	default:
		printf("Wrong Input\n");
	}
  } while(choice != 3);
    return 0;	 	
}

void encrypt(){
	char plain[32], cipher[32];
	char filename[32];
	int x, size, check;
	FILE *fp;
	
	printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	
	size = strlen(plain);
//	printf("size: %d", size);
	for(x = 0; x < size; x++) {
        if(isalpha(plain[x])) {
            cipher[x] = (isupper(plain[x]) ? 'Z'+'A' : 'z'+'a') - plain[x];
        } else {
            cipher[x] = plain[x];
        }
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
	char plain[32], cipher[32];
	char filename[32];
	int x, size;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 32, fp) !=NULL ) {
      			size = strlen(plain);
			for(x = 0; x < size; x++) {
        		if(isalpha(plain[x])) {
            		cipher[x] = (isupper(plain[x]) ? 'Z'+'A' : 'z'+'a') - plain[x];
        		} else {
            		cipher[x] = plain[x];
        		}    
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
