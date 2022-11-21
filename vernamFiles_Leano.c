#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>


void encrypt();
void decrpyt();

int main(){	
    srand(time(NULL));
	int choice;
	do {
	printf("\n----------VERNAM CIPHER----------");
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
	char plain[32], cipher[32], otp[32];
	char filename[32], otp_filename[32];
    int x, check;
	FILE *fp;
	
	printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
    printf("\nEnter OTP Filename: ");	fflush(stdin);      scanf("%[^\n]",otp_filename);
	
    for(x = 0; x < strlen(plain); x++) {
        otp[x] = rand()%127+1;
    }

    fp = fopen(otp_filename,"w");
	 if(fp != NULL){
	 	check = fputs(otp, fp);
	 	if(check == EOF) {
	 		printf("Failed writing to one-time pad file");
	 	}
	 }else{
	 	printf("Unable to open one-time pad file");
	 }
    fclose(fp);
	
	for(x = 0; x < strlen(plain); x++) {
        cipher[x] = plain[x]^(otp[x]-1);
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
	char plain[32], cipher[32], otp[32];
	char filename[32], otp_filename[32];
    int x, check;
	FILE *fp, *otp_fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
    printf("\nEnter OTP Filename: ");	fflush(stdin);      scanf("%[^\n]",otp_filename);
	
	fp = fopen(filename,"r");
	if(fp != NULL){
		if( fgets(plain, 32, fp) !=NULL ) {
			otp_fp = fopen(otp_filename,"r");
            if(fp != NULL){
                if( fgets(otp, 32, otp_fp) !=NULL ) {
                    for(x = 0; x < strlen(plain); x++) {
                        cipher[x] = plain[x]^(otp[x]-1);
                    }
                    cipher[x] = '\0';
                }else{
                    printf("Something wrong inside the one-time pad file");
                }
            }else{
                printf("Unable to open one-time pad file");
            }
            fclose(otp_fp);
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
