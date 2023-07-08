#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int NoArgs , char* CmdLine[]){
    time_t t = time(NULL);
    char buffer[100];
    int flagu = 0;
    int flagR = 0;
    if(NoArgs>3){
        printf("date: invalid number of arguments, command should be of the form 'date [-u] [-R]'\n");
        return 1;
    }
    for(int i=0;i<NoArgs;i++){
        if(CmdLine[i][0]=='-'){
            if(strcmp(CmdLine[i],"-u")==0){
                flagu = 1;
            }
            else if(strcmp(CmdLine[i],"-R")==0){
                flagR = 1;
            }
            else{
                printf("date: invalid option -- '%c'\n",CmdLine[i][1]);
                return 1;
            }
        }
    }
    if(NoArgs==1){
        struct tm tm = *localtime(&t);
        strftime(buffer, sizeof(buffer), "%A %d %B %Y %I:%M:%S %p %Z \n", &tm);
        printf("%s",buffer);
        }
    if(flagu==1 && NoArgs==2){
        struct tm tm = *gmtime(&t);
        strftime(buffer, sizeof(buffer), "%A %d %B %Y %I:%M:%S %p %Z \n", &tm);
        printf("%s",buffer);
    }
    if(flagR==1 && NoArgs==2){
        struct tm tm = *localtime(&t);
        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z \n", &tm);
        printf("%s",buffer);
    }
    if(flagR==1 && flagu==1){
        struct tm tm = *gmtime(&t);
        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z \n", &tm);
        printf("%s",buffer);
    }

    return 0;
    }