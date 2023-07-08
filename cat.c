#include <stdio.h>
#include <string.h>

int main(int NoArgs , char* CmdLine[]){
    FILE* filePointer;
    char element;
    int flagE = 0;
    int flagn = 0;
    for(int i=1;i<NoArgs;i++){
        if(CmdLine[i][0]=='-'){
            if(strcmp(CmdLine[i],"-E")==0){
                flagE = 1;
            }
            else if(strcmp(CmdLine[i],"-n")==0){
                flagn = 1;
            }
            else{
                printf("echo: invalid option -- '%c'\n",CmdLine[i][1]);
                return 1;
            }
        }
        else{
            filePointer = fopen(CmdLine[i],"r");
            if(filePointer==NULL){
                printf("cat: %s: No such file or directory\n",CmdLine[i]);
                return 1;
        }
    }
    }
    int LineCount = 1;
    if(flagn==1){
        printf("%d\t",LineCount);
    }
    while((element = fgetc(filePointer)) != EOF){
        if(flagE==1){
            if(element=='\n'){
                printf("$");
            }
        }
        if(flagn==1){
            if(element=='\n'){
                LineCount++;
                printf("%c",element);
                printf("%d\t",LineCount);
            }
            else{
                printf("%c",element);
            }
        }
        else{
            printf("%c",element);
        }

    }
    if(flagE==1){
        printf("$");
    }
    printf("\n");
    fclose(filePointer);
    return 0;
}