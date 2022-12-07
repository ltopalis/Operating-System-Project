#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/ipc.h>


double get_wtime(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec*1.0e-6;
}

double f(double x)
{
    return log(x)*sqrt(x);
}

int main(int argc, char *argv[]) {
    int workers;

    do{
        printf("number of workers: ");
        scanf("%d", &workers);
    }while(workers < 1);


    return 0;

}