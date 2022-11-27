#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<ctype.h>
#include<math.h>

//int GCD(int a, int b);
//int differPrimes(int prime1);
//String AES(String input, long int key, int n);
void encrypt();
void decrpyt();
void generateRSA();
int coPrime(int x, int y);


int main(){	
	int choice;
	do {
	printf("\n----------AES CIPHER----------");
	printf("\nEncrypt_________1");
	printf("\nDecrypt_________2");
	printf("\nGenerate Key____3");
	printf("\nExit____________4");
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
		generateRSA(); break;
	case 4:
		break;
	default:
		printf("Wrong Input\n");
	}
  } while(choice != 4);
		
    return 0;	 	
}



void encrypt(){
	char plain[128], cipher[128], key[128], *header, *mod;
	char filename[32];
    int i, check;
    unsigned int e, n;
	FILE *fp;
	
    printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Public Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	 
	int size = strlen(plain);
	 
	header = strtok(key, "+");
    mod = strtok(NULL, "+");
    
    e = strtol(header, NULL, 16);
    n = strtol(mod, NULL, 16);
    
    long double x;
    long double z;
    for(i = 0; i < size; i++) {
        if(isalpha(plain[i])) {
            z = powl(plain[i]-'a',e);
            x = fmodl(z, n);
            cipher[i] = x + 'a';
        } else {
            cipher[i] = plain[i];
        }

    }
    cipher[i] = '\0';

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
	char plain[128], cipher[128], key[128], *header, *mod;
	char filename[32];
    int i, check, size;
    unsigned int e, n;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Public Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 128, fp) != NULL ) {
      		size = strlen(plain);
				header = strtok(key, "+");
    			mod = strtok(NULL, "+");
			    e = strtol(header, NULL, 16);
			    n = strtol(mod, NULL, 16);
			    
			    long double x;
			    long double z;
			    for(i = 0; i < size; i++) {
			        if(isalpha(plain[i])) {
			            z = powl(plain[i]-'a',e);
			            x = fmodl(z, n);
			            cipher[i] = x + 'a';
			        } else {
			            cipher[i] = plain[i];
			        }
			    }
   		}else{
   			printf("Something wrong inside the file");
		}
	}else{
		printf("Unable to open file");
	}
	cipher[i] = '\0';
	fclose(fp);
	printf("Before: %s\n", plain);
    printf("After: %s\n", cipher);
}

void generateRSA(){
	unsigned int prime1 = 2, prime2 = 13, n, totient, e, d, x = 1;
    char private_key[50], public_key[50], mod[50];
    
    n = prime1 * prime2;
    totient = (prime1 - 1)*(prime2 - 1);
    
     do {
        e = rand()%totient;
    } while(coPrime(e, totient) != 1);
    
    do {
        d = rand()%totient;
    } while((d*e)%totient != 1);
    
    itoa(n, mod, 16);
    itoa(e, private_key, 16);
    itoa(d, public_key, 16);
    sprintf(private_key, "%s+%s", private_key, mod);
    sprintf(public_key, "%s+%s", public_key, mod);

    printf("public key: %s\n", private_key);
    printf("private key: %s\n", public_key); 
}

int coPrime(int x, int y){
    int i, hcf;
    for(i = 1; i <= y; i++) {
	    if(y%i==0 && x%i==0) {
	        hcf = i;
	    }
    }
    return hcf;
}

