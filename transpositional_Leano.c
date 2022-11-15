#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<math.h>


void encrypt();
int noSpaceLength(char plain[]);
void sort(char arr[], int size);
char ** matrixCipher(char plain[], char key[], char sortedKey[], int size, int keySize);
char ** matrixPlain(char plain[], char key[], char sortedKey[], int size, int keySize);
void decrpyt();

int main(){	

	int choice;
	do {
		printf("\n----------TRANSPOSITIONAL CIPHER----------");
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
	char plain[256], cipher[256], key[32], filename[32], sortedKey[32], **matrix;
	int x, y, z, l, size, check, keySize, maxRow;
	FILE *fp;
	
	printf("\nEnter Plain Text: ");		fflush(stdin);      scanf("%[^\n]",plain);
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	
	size = noSpaceLength(plain);
	keySize = noSpaceLength(key);
	strcpy(sortedKey, key);
	sort(sortedKey, keySize);
	
	matrix = matrixCipher(plain, key, sortedKey, size, keySize);
	maxRow = ceil(size/keySize) + 1;
	
	for(x = 0, z = 0, l = 0; l < keySize; x++) {
        if(matrix[0][x] == sortedKey[l]) {
            for(y = 1; y < maxRow && matrix[y][x] != 0; y++) {
                cipher[z++] = matrix[y][x];
            }
            cipher[z++] = ' ';
            matrix[0][x] = 0;
            l++;
            x = -1;
        }
    }
    cipher[z] = '\0';
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
	char plain[256], cipher[256], key[32], filename[32], sortedKey[32], **matrix;
	int x, y, z, l, size, check, keySize, maxRow;
	FILE *fp;
	
	printf("\nEnter Filename: ");		fflush(stdin);      scanf("%[^\n]",filename);
	printf("\nEnter Key: ");		fflush(stdin);      scanf("%[^\n]",key);
	
	
	
	fp = fopen(filename,"r");
	if(fp != NULL){
		
		if( fgets(plain, 256, fp) !=NULL ) {
			size = noSpaceLength(plain);
			keySize = noSpaceLength(key);
			strcpy(sortedKey, key);
			sort(sortedKey, keySize);
			
			matrix = matrixPlain(plain, key, sortedKey, size, keySize);
			maxRow = ceil(size/keySize) + 1;
			
			for(x = 1, z = 0; x < maxRow; x++) {
        		for(y = 0; y < keySize; y++, z++) {
        			
            		cipher[z] = matrix[x][y];
        		}
    		}
   		}else{
   			printf("Something wrong inside the file");
		}
	}else{
		printf("Unable to open file");
	}
	fclose(fp);
	cipher[z] = '\0';
	printf("Before: %s\n", plain);
    printf("After: %s\n", cipher);
}

int noSpaceLength(char plain[]){
	int x, retVal, size = strlen(plain);
    for(x = 0, retVal = 0; x < size; x++) {
        if(!isspace(plain[x])) {
            retVal++;
        }
    }
    return retVal;
}

void sort(char arr[], int size){ //bubbleSort
	int x, y, temp;
    for(x = 1; x < size; x++) {
        for(y = 0; y < size-x; y++) {
            if(arr[y] > arr[y+1]) {
                temp = arr[y];
                arr[y] = arr[y+1];
                arr[y+1] = temp;
            }
        }
    }
}

char ** matrixCipher(char plain[], char key[], char sortedKey[], int size, int keySize){
	int x, y, z, l, maxRow, sizeText;
	
	maxRow = ceil(size/keySize) + 1;
	sizeText = strlen(plain);
    char ** matrix = (char **)malloc(sizeof(char*) * maxRow);
    
    for(x = 0; x < maxRow; x++) {
        matrix[x] = (char *)malloc(sizeof(char) * keySize);
    }

    for(x = 0; x < keySize; x++) {
        matrix[0][x] = key[x];
    }
    
      for(x = 0, y = 1, z = 0; x < sizeText;) {
        if(z < keySize) {
            if(!isspace(plain[x])) {
                matrix[y][z++] = plain[x];
            }
            x++;
        } else {
            y++; z = 0;
        }
    }
    
    return matrix;
}


char ** matrixPlain(char plain[], char key[], char sortedKey[], int size, int keySize){
    int x, y, z, l, maxRow, sizeText;
    char ** matrix = (char **)calloc(sizeof(char*), maxRow);
    
    maxRow = ceil(size/keySize) + 1;
    sizeText = strlen(plain);
    
    for(x = 0; x < maxRow; x++) {
        matrix[x] = (char *)malloc(sizeof(char) * keySize);
    }

    for(x = 0; x < keySize; x++) {
        matrix[0][x] = key[x];
    }
    
    for(x = 0, z = 0, l = 0; l < keySize; x++) {
        if(matrix[0][x] == sortedKey[l]) {
            for(y = 1; y < maxRow && plain[z] != 0; z++) {
                if(!isspace(plain[z])) {
                    matrix[y++][x] = plain[z];
                }
            }
            matrix[0][x] = 0;
            l++;
            x = -1;
        }
    }

    return matrix;
}
