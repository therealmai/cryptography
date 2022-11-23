#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<ctype.h>
#include<math.h>

void encrypt(long int e, int n);
void decrpyt(long int e, int n);
int GCD(int a, int b);
char* AES(char* input, long int key, int n);

int main(){	
	int p = 13, q = 2; // two prime numbers
	
	long int n = p * q;
    long int totient = (p - 1) * (q - 1);
	
	long int e = 0, count;
    for(e = 2; e < totient && (GCD(e, totient) != 1 || GCD(e, n) != 1); e++){}
    
    long int d = 0;
    for(d = 1; fmod((e * d), totient) != 1; d++){}
    
	int choice;
	do {
	printf("\n----------SHIFTING CIPHER----------");
	printf("\nEncrypt____1");
	printf("\nDecrypt____2");
	printf("\nExit_______3");
	printf("\n\nEnter your choice: ");
	scanf("%d", &choice);
	printf("\n");
	(void) getchar(); //clean the input of newline

	switch (choice) {
	case 1: 
		encrypt(e,n); break;
	case 2: 
		decrpyt(d,n); break;
	case 3: 
		break;
	default:
		printf("Wrong Input\n");
	}
  } while(choice != 3);
		
    return 0;	 	
}

int GCD(int a, int b){
    int temp;
    while (1) {
        temp = a % b;
        if (temp == 0)
            return b;
        a = b;
        b = temp;
    }
}


void encrypt(long int e, int n){
	char plain[128], *cipher;
	char filename[32];
    int x, check, prime1=0, prime2=0;
	FILE *fp;
	
     printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	 printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	 cipher = AES(plain, e, n);
	 
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


void decrpyt(long int e, int n){
	char plain[128], *cipher;
	char filename[32];
    int x, check, prime1=0, prime2=0;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	 
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 128, fp) != NULL ) {
			cipher = AES(plain, e, n);
   		}else{
   			printf("Something wrong inside the file");
		}
	}else{
		printf("Unable to open file");
	}
	cipher[x] = '\0';
	
	printf("Before: %s\n", plain);
    printf("After: %s\n", cipher);
}

char* AES(char* input, long int key, int n){
	int x;
    char* output = (char*)calloc(strlen(input) + 1, sizeof(char));

    for( x = 0; x < strlen(input); x++){
        if(isalpha(input[x])){
            int letter = input[x] - ('a');
            double power = pow(letter, key);
            double modulo = fmod(fmod(power, n), 26);
            output[x] = modulo + ('a');
            printf("%c : %c\n", input[x], output[x]);
        }else{
            output[x] = input[x];
        }
    }
    return output;
}


