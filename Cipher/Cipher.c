#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <errno.h> //This was in the example, so I'm going to include it.
#include <ctype.h> //This was mentioned in slack for the tolower() function




int main(){
    char result[10];
    char firstInput[10];
    char encrypt[] = "e\n";
    char mappingArray[104];
    char keyArray[104];
    int num = 0;
    char word[150];
    int index = 0;
    printf("Enter e for encrypt, or d for decrypt: \n");
    fgets(firstInput,10,stdin);
    int compare = strcmp(firstInput,encrypt);
    if(compare==0){
        printf("Enter key text file to use: \n");
        char file_path[260];
        char* status = fgets(file_path,260,stdin);
        printf("Enter a word to encrypt: \n");
        scanf("%s",word);
        int length = strlen(word);
        printf("\n");
        if(status==NULL){
            printf("Error reading the file\n");
        }
        else{
            char* newLine = strchr(file_path, '\n');
            if(newLine){
                *newLine = '\0';
            }
            //Read entire contents of file_path into mappingArray and keyArray
            FILE* file_pointer;
            errno = 0;
            file_pointer = fopen(file_path, "r");
            if(file_pointer==NULL){
                printf("Error opening file %s with error %d\n",file_path,errno);
            }
            else{
                char buffer[10];
                while(fgets(buffer,10,file_pointer)!=NULL){
                    newLine = strchr(buffer,'\n');
                    if(newLine){
                        *newLine = '\0';
                    }




                    //THIS IS THE SPOT WHERE I TEST FOR | X,() |, ERROR NUMBER 4
                    if(buffer[2] == '\0'){
                        printf("Error: One of the lines in the key is not complete.\n\n");
                        return 0;
                    }
                    mappingArray[index]=toupper(buffer[0]);
                    keyArray[index]=toupper(buffer[2]);
                    index++;


                    if(index>1){
                        for(int i = 1; i < index; i++){
                            if(toupper(buffer[0]) == (mappingArray[i-1])){
                                printf("Error: There is a duplicate letter on the left side of the key\n\n");
                                return 0;
                            }
                            if(toupper(buffer[2]) == (keyArray[i-1])){
                                printf("Error: There is a duplicate letter on the right side of the key\n\n");
                                return 0;
                            }
                        }
                    }
                }


                for(int i = 0; i<length;i++){
                    char *store;
                    store = strchr(mappingArray,toupper(word[i]));
                   
                    int numb = strlen(store);
                    int number = 26-numb;
                    result[i] = (keyArray[number]);
                }
            }
            result[length] = '\0';
        }
        /*TESTS FOR ENCRYPTION
        hello = oyddh
        goodbye = ihhteny
        short = mohlw
        */
    }
    else{
        printf("Enter key text file to use: \n");
        char file_path[260];
        char* status = fgets(file_path,260,stdin);
        printf("Enter a word to decrypt: \n");
        scanf("%s",word);
        int length = strlen(word);
        printf("\n");
        if(status==NULL){
            printf("Error getting user input\n");
        }
        else{
            char* newLine = strchr(file_path, '\n');
            if(newLine){
                *newLine = '\0';
            }
            FILE* file_pointer;
            errno = 0;
            file_pointer = fopen(file_path, "r");
                if(file_pointer==NULL){
                    printf("Error opening file %s with error %d\n",file_path,errno);
                }
            else{
                char buffer[10];
                while(fgets(buffer,10,file_pointer)!=NULL){
                    newLine = strchr(buffer,'\n');
                    if(newLine){
                        *newLine = '\0';
                    }




                    //THIS IS THE SPOT WHERE I TEST FOR | X,() |, ERROR NUMBER 4
                    if(buffer[2] == '\0'){
                        printf("Error: One of the lines in the key is not complete.\n\n");
                        return 0;
                    }


                    mappingArray[index]=toupper(buffer[2]);
                    keyArray[index]=toupper(buffer[0]);
                    index++;


                    if(index>1){
                        for(int i = 1; i < index; i++){
                            if(toupper(buffer[0]) == (keyArray[i-1])){
                                printf("Error: There is a duplicate letter on the left side of the key\n\n");
                                return 0;
                            }
                            if(toupper(buffer[2]) == (mappingArray[i-1])){
                                printf("Error: There is a duplicate letter on the right side of the key\n\n");
                                return 0;
                            }
                        }
                    }
                }


                for(int i = 0; i<length;i++){
                    char *store;
                    store = strchr(mappingArray,toupper(word[i]));
                   
                    int numb = strlen(store);
                    int number = 26-numb;


                    result[i] = (keyArray[number]);
                   
                }
            }
           
            result[length] = '\0';
        }
        /*TESTS FOR DECRYPTION
        oyddh = hello
        ihhteny = goodbye
        mohlw = short
        */
    }
    for(int i = 0; i < strlen(result);i++){
        if(result[i]>='a'&&result[i]<='z'){
        result[i] = result[i] - 32;
        }
    }
    printf("%s\n",result);
    return 0;
}



