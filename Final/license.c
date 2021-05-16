#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

void *sortFunc(void *vargp) {
    pid_t pid=fork();
    if (pid==0) {
        char * args[] = {"./mergeSort",NULL};
        execv(args[0], args);
        exit(127);
    }
    else {
        waitpid(pid,0,0);
    }
}
int exists(){
    const char *fname = "license.txt";
    FILE *file;
    if( access( fname, F_OK ) != -1 ) {
        return 0;
    } else {
        return -1;
    }
}

int main(){
    printf("\n\t\t***************************************************************\t\t\n");
    printf("\n\t\t**********************License Simulator************************\t\t\n");
    pthread_t ptid;
    int checkLicence = exists();
    if (checkLicence == 0){
        int choice=0;
        printf("\n\t\tLicense Loaded Successfully\n\n");
        do{
            pthread_create(&ptid, NULL, &sortFunc, NULL);
            pthread_join(ptid, NULL);
            printf("\nDo u wish to continue?");
            printf("Press 1 for yes or 0 for no");
            scanf("%d", &choice);
        }while(choice != 0);
    }
    else{
        printf("\n\tNo License found\n\tMaximum 5 uses allowed \n");
        int choice=0;
        for(int i=0; i< 5 ; i++){
            pthread_create(&ptid, NULL, &sortFunc, NULL);
            pthread_join(ptid, NULL);
            printf("\nDo u wish to continue?");
            printf("Press 1 for yes or 0 for no");
            scanf("%d", &choice);
            if(i == 5 && choice ==1){
                printf("Max No of uses Passed\n Please Purchase license to continue");
            }
        }
    }
    printf("\n\t\t*********************All Rights Reserved***********************\t\t\n");
    printf("\n\t\t***************************************************************\t\t\n");
    return 0;
}