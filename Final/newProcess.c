#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int play = 0;

struct keyvalue{
    int key;
    int value;
};

int fib(int n){
    if(n==0 || n==1)
    return n;
    else
    return fib(n-1)+fib(n-2);
}

void *runner(void *param){
    struct keyvalue *temporary = (struct keyvalue*)param;
    temporary->value = fib(temporary->key);
    pthread_exit(NULL);
}

// Defining process details 
struct process { 
	char name; 
	int at, bt, ct, wt, tt; 
	int completed; 
	float ntt; 
} p[10]; 

int n; 

// Sorting Processes by Arrival Time 
void sortByArrival() {
	struct process temp; 
	int i, j; 

	// Selection Sort applied 
	for (i = 0; i < n - 1; i++) { 
		for (j = i + 1; j < n; j++) { 
			// Check for lesser arrival time 
			if (p[i].at > p[j].at) {
				// Swap earlier process to front 
				temp = p[i]; 
				p[i] = p[j]; 
				p[j] = temp; 
			} 
		} 
	} 
}

void *sortFunc(void *vargp) {
    // sleep(1);
    // printf("Printing GeeksQuiz from Thread \n");
    // return NULL;
    pid_t pid=fork();
    if (pid==0) { /* child process */
        // static char *argv[]={"echo","Foo is my name.",NULL};
        // execv("/bin/echo",argv);
        system("./mergeSort");
        printf("this is a new process");
        exit(127);
    }
    else {
        waitpid(pid,0,0);
    }
}
int checkPrime(int num){
	int i;
	int flg=0;
	/*if number (num) is divisble by any number from 2 to num/2
	  number will not be prime.*/
	for(i=2;i<(num-1);i++)
	{
		if(num%i==0){
			flg=1;
			break;
		}
	}
	if(flg) return 0;
	else return 1;
}

void *primeFunc(void * vargp) {
    int i,n;

	n = 100;

	printf("All prime numbers are from 1 to %d:\n",n);
	for(i=1;i<=n;i++){
		if(checkPrime(i))
			printf("%d,",i);
	}
	return 0;
}

void *schedulerFunc(void *vargp) {
    int i, j, t, sum_bt = 0; 
	char c; 
	float avgwt = 0, avgtt = 0; 
	n = 3; 

	// predefined arrival times 
	int arriv[] = { 0, 2, 4}; 

	// predefined burst times 
	int burst[] = { 3, 6, 4}; 

	// Initializing the structure variables 
	for (i = 0, c = 'A'; i < n; i++, c++) { 
		p[i].name = c; 
		p[i].at = arriv[i]; 
		p[i].bt = burst[i]; 
		// Variable for Completion status Pending = 0 Completed = 1 
		p[i].completed = 0; 
		// Variable for sum of all Burst Times 
		sum_bt += p[i].bt; 
	} 

	sortByArrival(); 
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time"); 
	printf("\tTurnAround Time\t Normalized TT"); 
	for (t = p[0].at; t < sum_bt;) { 

		float hrr = -9999; 

		float temp; 

		int loc; 
		for (i = 0; i < n; i++) { 

			if (p[i].at <= t && p[i].completed != 1) { 

				temp = (p[i].bt + (t - p[i].at)) / p[i].bt; 

				if (hrr < temp) { 

					hrr = temp; 

					loc = i; 
				} 
			} 
		} 

		t += p[loc].bt; 

		p[loc].wt = t - p[loc].at - p[loc].bt; 

		p[loc].tt = t - p[loc].at; 

		avgtt += p[loc].tt; 

		p[loc].ntt = ((float)p[loc].tt / p[loc].bt); 

		p[loc].completed = 1; 

		avgwt += p[loc].wt; 
		printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at); 
		printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt); 
		printf("%d\t\t%f", p[loc].tt, p[loc].ntt); 
	} 
	printf("\nAverage waiting time:%f\n", avgwt / n); 
	printf("Average Turn Around time:%f\n", avgtt / n); 
}
void *fibo(void *vargp) {
    int range;
    int i, n, t1 = 0, t2 = 1, nextTerm;
    n= 15;
    printf("\n\nfirst 15 terms of Fibonacci Series: ");

    for (i = 1; i <= n; ++i) {
        printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    return 0;
}

int main(){
    pthread_t id1, id2, id3, id4 ;
    printf("\nBefore Thread\n");
    pthread_create(&id1, NULL, schedulerFunc, NULL);
    printf("\n");
    printf("\n");
    pthread_create(&id2, NULL, fibo, NULL);
    printf("\n");
    printf("\n");
    pthread_create(&id3,NULL, sortFunc, NULL);
    printf("\n");
    printf("\n");
    pthread_create(&id4,NULL, primeFunc, NULL);
    printf("\n");
    printf("\n");
    pthread_join(id1,NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4,NULL);
    printf("\n");
    printf("\nAfter Thread\n");
    printf("\n");
    return 0;
}