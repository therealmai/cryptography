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
	printf("\n----------VIGENERE CIPHER----------");
	printf("\nEncrypt____1");
	printf("\nDecrypt____2");
	printf("\nExit_______3");
	printf("\n\nEnter your choice: ");
	scanf("%d", &choice);
	printf("\n");
	(void) getchar();

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
	char plain[32], cipher[32], key[32];
	char filename[32];
	int x, y, size, check, keySize;
	FILE *fp;
	
	printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	size = strlen(plain);
	keySize = strlen(key);
	
	
	 for(x = 0, y = 0; x < size; x++) {
        if(isalpha(plain[x])) {
        	if(isupper(plain[x])){
        		cipher[x] = (toupper(plain[x]) + toupper(key[(y++)%keySize]) - ('A' * 2)) % 26 + 'A';
			}else{
				cipher[x] = (toupper(plain[x])+toupper(key[(y++)%keySize]) - ('A' * 2 )) % 26 + 'a' ;
			}
        } else {
            cipher[x] = plain[x];
        }
    }
    cipher[x] = '\0';

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
	char plain[32], cipher[32], key[32];
	char filename[32];
	int x, y, size, check, keySize;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Key: ");		fflush(stdin);      scanf("%[^\n]",key);

	keySize = strlen(key);
	
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 32, fp) !=NULL ) {
			size = strlen(plain);
			 for(x = 0, y = 0; x < size; x++) {
                if(isalpha(plain[x])) {
                    if(isupper(plain[x])){
                        cipher[x] = (toupper(plain[x]) - toupper(key[(y++)%keySize]) + 26 ) % 26 + 'A';
                    }else{
                        cipher[x] = (toupper(plain[x]) - toupper(key[(y++)%keySize]) + 26 ) % 26 + 'a';
                    }
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
	cipher[x] = '\0';
	printf("Before: %s\n", plain);
    printf("After: %s\n", cipher);
}



