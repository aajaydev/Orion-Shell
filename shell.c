#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
char* shelldir;
char* homedir;


int cd(char **cmd_split){
    char dir[1000];
    int i=0;
    int flagL=0;
    // printf("%s\n",getcwd(dir,1000));
    for(i=1;cmd_split[i]!=NULL;i++){
        if(cmd_split[i][0]=='-'){
            if(strcmp(cmd_split[i],"-L")==0){
                flagL=1;
                continue;
            }
            else if(strcmp(cmd_split[i],"-P")==0){
                flagL=0;
                continue;
            }
            else if(strcmp(cmd_split[i],"-")==0){
                chdir("..");
                printf("%s\n",getcwd(dir,1000));
                return 0;
            }
            else{
                printf("cd: invalid option -- '%s'\n",cmd_split[i]);
                return 1;
            }
        }
        if(strcmp(cmd_split[i],"~")==0){
            chdir(getenv("HOME"));
            printf("%s\n",getcwd(dir,1000));
        }
        else{
            int successful = chdir(cmd_split[i]);
            if(successful!=0){
                printf("cd: %s: No such file or directory\n",cmd_split[i]);
                return 1;
            }
            printf("%s\n",getcwd(dir,1000));
        }
    }
    if(i==1){
        chdir(getenv("HOME"));
        printf("%s\n",getcwd(dir,1000));
    }
    return 0;
}

int echo(char **cmd_split){
    int flagn=0;
    int flage=0;

    for(int i=1;cmd_split[i]!=NULL;i++){
        if(cmd_split[i][0]=='-'){
            if(strcmp(cmd_split[i],"-n")==0){
                flagn=1;
                continue;
            }
            else if(strcmp(cmd_split[i],"-e")==0){
                flage=1;
                continue;
            }
            else{
                printf("echo: invalid option -- '%s'\n",cmd_split[i]);
                return 1;
            }
        }
        else{
            if(flage==1){
                for(int j=0;cmd_split[i][j]!='\0';j++){
                    if(cmd_split[i][j]=='\\'){
                        if(cmd_split[i][j+1]=='n'){
                            printf("\n");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='t'){
                            printf("\t");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='a'){
                            printf("\a");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='b'){
                            printf("\b");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='v'){
                            printf("\v");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='f'){
                            printf("\f");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='r'){
                            printf("\r");
                            j++;
                        }
                        else if(cmd_split[i][j+1]=='\\'){
                            printf("\\");
                            j++;
                        }
                        else{
                            printf("\\");
                        }
                    }
                    else{
                        if(cmd_split[i][j]!='\"'){
                            printf("%c",cmd_split[i][j]);
                        }
                    }
                }
            }
            else{
                for(int j=0;cmd_split[i][j]!='\0';j++){
                    if(cmd_split[i][j]=='\"'){
                        continue;
                    }
                    printf("%c",cmd_split[i][j]);
                }
            }
            if(cmd_split[i+1]!=NULL){
                printf(" ");
            }
        }
    }
    if(flagn==0){
        printf("\n");
    }
    return 0;
    
}

int pwd(char **cmd_split){
    int flagL=0;
    int flagP=0;
    for(int i=1;cmd_split[i]!=NULL;i++){
        if(cmd_split[i][0]=='-'){
            if(strcmp(cmd_split[i],"-L")==0){
                flagL=1;
                continue;
            }
            else if(strcmp(cmd_split[i],"-P")==0){
                flagP=1;
                continue;
            }
            else{
                printf("pwd: invalid option -- '%s'\n",cmd_split[i]);
                return 1;
            }
        }
    }
    if(flagL==1 && flagP==1){
        printf("pwd: options -L and -P are mutually exclusive\n");
        return 1;
    }
    if(flagL==1){
        printf("%s\n",getenv("PWD"));
        return 0;
    }
    char direc[1000];
    printf("%s\n",getcwd(direc,1000));
    return 0;
}
//________________________________________________________________________________
void *thread_Cmd(void *arg){
    // printf("Thread created\n");
    char **cmd_split = (char **)arg;
    char pathToShell[1000];
    strcpy(pathToShell,shelldir);
    strcat(pathToShell,"/");
    for(int i=0;cmd_split[i]!=NULL;i++){
        strcat(pathToShell,cmd_split[i]);
        strcat(pathToShell," ");
    }
    const char *execute = pathToShell;
    system(execute);
    return NULL;
}
//________________________________________________________________________________
int main(){
    char *cmd;
    char path[1000];
    shelldir=getcwd(path,1000);
    char **cmd_split;
    int usePthread;
    while(1){
        printf("orion>");
        cmd = (char *)malloc(1000*sizeof(char));
        cmd_split = (char **)malloc(1000*sizeof(char *));
        size_t len = 1000;
        getline(&cmd,&len,stdin);
        if(strlen(cmd)==1){
            continue;
        }
        char *iter = strtok(cmd, " \n");
        int i =0;
        while(iter != NULL){
            if(strcmp(iter,"&t")==0){
                usePthread=1;
                break;
            }
            cmd_split[i] = iter; 
            iter = strtok(NULL, " \n");
            i++;
        }
        cmd_split[i] = NULL;

        if(strcmp(cmd_split[0],"cd")==0){
            cd(cmd_split);
        }
        else if(strcmp(cmd_split[0],"echo")==0){
            echo(cmd_split);
        }
        else if(strcmp(cmd_split[0],"pwd")==0){
            pwd(cmd_split);
        }
        else if(strcmp(cmd_split[0],"exit")==0){
            exit(0);
        }
        else{
            if(usePthread==1){
                pthread_t thread;
                pthread_create(&thread,NULL,thread_Cmd,cmd_split);
                pthread_join(thread,NULL);
                usePthread=0;
            }

            else{

                char commandPath[1000];
                pid_t pid = fork();

                if(pid==0){
                    strcpy(commandPath,shelldir);
                    strcat(commandPath,"/");
                    strcat(commandPath,cmd_split[0]);
                    int status = execv(commandPath,cmd_split);
                    if(status==-1){
                        printf("orion: %s: command not found\n",cmd_split[0]);
                        exit(0);
                    }
                    exit(0);
                }
                else{
                    wait(NULL);
                }
            }
        }
    }
    return 0;
}


