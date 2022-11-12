    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>

    char* decipherText(char plain[], char cipher[], int shift);
    char* cipherText(char plain[], char cipher[], int shift);

    int main(){
        char plain[32], *cipher;
        int shift, choice;

        printf("Enter text: ");
        fgets(plain, sizeof(plain), stdin);
        printf("Cipher: Press 0 || Decipher: Press 1 ");
        scanf("%d", &choice);
        printf("How many shifts: ");
        scanf("%d", &shift);
      
        
        cipher = (choice == 0) ? cipherText(plain, cipher, shift) : decipherText(plain, cipher, shift);
        
        printf("Plain Text: %s\n", plain);
        printf("Cipher Text: %s", cipher);
    }

    char* decipherText(char plain[], char cipher[], int shift){
        int x, size = strlen(plain);
        cipher = (char*) malloc(sizeof(char)*size+1);

        for(x=0; x< size; x++){
            if(isalpha(plain[x])){
                //(ch - 'a' + key) % 26 + 'a'
                cipher[x] = (isupper(plain[x])) ? (plain[x] - 'A' + shift) % 26 + 'A' : (plain[x] - 'a' + shift) % 26 + 'a';
            }else{
                cipher[x] = plain[x];
            }
        }
        cipher[size] = '\0';
        return cipher;
    }


    char* cipherText(char plain[], char cipher[], int shift){
        int x, size = strlen(plain);
        cipher = (char*) malloc(sizeof(char)*size+1);

        for(x=0; x< size; x++){
            if(isalpha(plain[x])){
                // (ch - 'a' - key + 26) % 26 + 'a'
                cipher[x] = (isupper(plain[x])) ? (plain[x] - 'A' - shift + 26) % 26 + 'A' : (plain[x] - 'a' - shift + 26) % 26 + 'a';
            }else{
                cipher[x] = plain[x];
            }
        }
        cipher[size] = '\0';
        return cipher;
    }