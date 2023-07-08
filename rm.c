#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int NoArgs , char* CmdLine[]){
    int flagi=0;
    int flagv=0;
    int flagd=0;
    int status;
    for(int i=1;i<NoArgs;i++){
        if(CmdLine[i][0]=='-'){
            if(strcmp(CmdLine[i],"-i")==0){
                flagi = 1;
            }
            else if(strcmp(CmdLine[i],"-v")==0){
                flagv = 1;
            }
            else if(strcmp(CmdLine[i],"-d")==0){
                flagd = 1;
            }
            else{
                printf("rm: invalid option -- '%c'\n",CmdLine[i][1]);
                return 1;
            }
        }
        else{
            struct stat st;
            stat(CmdLine[i],&st);
            if(S_ISDIR(st.st_mode)){
                if(flagd==1){
                    if(flagi==1){
                        printf("rm: remove directory '%s'? ",CmdLine[i]);
                        char c;
                        scanf("%c",&c);
                        if(c=='y'){
                            status = rmdir(CmdLine[i]);
                            if(flagv==1 && status==0){
                                printf("rm: removed directory '%s'\n",CmdLine[i]);
                            }
                            else if(status==-1){
                                printf("rm: cannot remove '%s': Directory not empty\n",CmdLine[i]);
                            }
                        }
                    }
                    else{
                        status = rmdir(CmdLine[i]);
                        if(flagv==1 && status==0){
                            printf("rm: removed directory '%s'\n",CmdLine[i]);
                        }
                        else if(status==-1){
                            printf("rm: cannot remove '%s': Directory not empty\n",CmdLine[i]);
                        }
                    }
                }
                else{
                    printf("rm: cannot remove '%s': Is a directory\n",CmdLine[i]);
                }
            }
            else{
                if(access(CmdLine[i],F_OK)==0){
                    if(flagi==1){
                        printf("rm: remove regular file '%s'? ",CmdLine[i]);
                        char c;
                        scanf("%c",&c);
                        if(c=='y'){
                            status = remove(CmdLine[i]);
                            if(status==0 && flagv==1){
                                printf("rm: removed '%s'\n",CmdLine[i]);
                            }
                        }
                    }
                    else{
                        status = remove(CmdLine[i]);
                        if(status==0 && flagv==1){
                            printf("rm: removed '%s'\n",CmdLine[i]);
                        }
                    }
                }
                else{
                    printf("rm: cannot remove '%s': No such file or directory\n",CmdLine[i]);
                }
            
            }
        }
    }

    return 0;
}