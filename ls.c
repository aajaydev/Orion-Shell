#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(int NoArgs , char* CmdLine[]){
    struct dirent *d;
	DIR *dh = opendir(".");
    int flagi=0;
    int flaga=0;
    if(NoArgs>4){
        printf("ls: invalid number of arguments, command should be of the form 'ls [-i] [-a] [directory]'\n");
        return 1;
    }
    for(int i=1;i<NoArgs;i++){
        if(CmdLine[i][0]=='-'){
            if(strcmp(CmdLine[i],"-i")==0){
                flagi = 1;
                continue;
            }
            else if(strcmp(CmdLine[i],"-a")==0){
                flaga = 1;
                continue;
            }
            else{
                printf("ls: invalid option -- '%c'\n",CmdLine[i][1]);
                return 1;
            }
        }
        else{
            dh = opendir(CmdLine[i]);
            if(dh==NULL){
                printf("ls: cannot access '%s': No such file or directory\n",CmdLine[i]);
                return 1;
            }
        }
    }
    while ((d = readdir(dh)) != NULL)
	{
        if(d->d_name[0]!='.' || flaga==1){
            if(flagi==1){
                printf("%llu ",d->d_ino);
            }
            printf("%s  ",d->d_name);
        }else if(d->d_name[0]=='.'){
            if(flaga==1){
                if(flagi==1){
                    printf("%llu ",d->d_ino);
                }
                printf("%s  ",d->d_name);
            }
        }
        else{
            if(flagi==1){
                printf("%llu ",d->d_ino);
            }
            printf("%s  ",d->d_name);
        }

	}
    printf("\n");
}