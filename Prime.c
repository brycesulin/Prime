#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <pthread.h>

void *runner(void *param);

int main(int argc, char *argv[]) {

    //Verify two args were passed in
    if (argc < 2) {
        printf("Please pass in 2 arguments!\n");
        exit(1);
    } else if (argc == 2) {

        //verify the input is greater than or equal to two
        if (atoi(argv[1]) < 2) {
            printf("Input values must be greater than or equal to 2!\n");
            exit(1);
        } else if (atoi(argv[1]) >= 2) {

            pthread_t tid;       //Thread ID
            pthread_attr_t attr; //Set of thread attributes

            printf("The prime numbers of a given number %d are: ", atoi(argv[1]));

            //Get the default attributes
            pthread_attr_init(&attr);
            //Create the thread
            pthread_create(&tid, &attr, runner, argv[1]);
            //Wait for the thread to exit
            pthread_join(tid, NULL);
        }
    }
}

//The thread will begin control in this function
void *runner(void *param) {
    int i, j, upper = atoi(param);
    /* Check to see if a number is prime */
    for (i = 2; i < upper; i++) {
        int trap = 0;
        /* Check each number for divisibility */
        for (j = 2; j < i; j++) {
            int result = i % j;
            /* If any of the numbers divide cleanly
                then this number is not prime. So
                stop checking. */
            if (result == 0) {
                trap = 1;
                break;
            }
        }
        //No numbers divided cleanly so this number must be prime
        if (trap == 0) {
            printf("%d ", i);
        }
    }
    //Exit the thread
    printf("\n");
    pthread_exit(0);
}
