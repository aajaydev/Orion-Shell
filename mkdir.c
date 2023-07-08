#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>


int main(int NoArgs, char* CmdLine[]){
    int flagv=0;
    int flagp=0;
    int status;
    for(int i=1;i<NoArgs;i++){
        if(CmdLine[i][0]=='-'){
            if(strcmp(CmdLine[i],"-v")==0){
                flagv = 1;
            }
            else if(strcmp(CmdLine[i],"-p")==0){
                flagp = 1;
            }
            else{
                printf("mkdir: invalid option -- '%c'\n",CmdLine[i][1]);
                return 1;
            }
        }
        else{
            if(flagp==1){
                char* token = strtok(CmdLine[i],"/");
                char* path = (char*)malloc(100*sizeof(char));
                while(token!=NULL){
                    strcat(path,token);
                    status = mkdir(path,0777);
                    if(status==0 && flagv==1){
                        printf("mkdir: created directory '%s'\n",path);
                    }
                    else if(status==-1){
                        // printf("mkdir: cannot create directory '%s': File exists\n",path);
                    }
                    strcat(path,"/");
                    token = strtok(NULL,"/");
                }
            }
            else{
                status = mkdir(CmdLine[i],0777);
                if(status==0 && flagv==1){
                    printf("mkdir: created directory '%s'\n",CmdLine[i]);
                }
                else if(status==-1){
                    printf("mkdir: cannot create directory '%s': File exists\n",CmdLine[i]);
                }
            }
        }
    }
}