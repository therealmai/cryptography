#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>


void encrypt();
//void decrpyt();

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


