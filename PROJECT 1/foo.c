#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

void child(double a, double b);
double f(double x);

int main(int argc, char *argv[])
{
    int workers, tmp, i;
    double a = 1.0, b = 4.0, *start, *finish, tmp_start, tmp_finish, space;

    do
    {
        printf("number of processes: ");
        scanf("%d", &workers);
    } while (workers < 1);

    start = (double *)malloc(workers * sizeof(double));
    finish = (double *)malloc(workers * sizeof(double));
    if (!start || !finish)
    {
        fprintf(stderr, "Error Allocating memory!\n");
        exit(0);
    }

    space = (b - a) / workers;
    tmp_start = a;
    for (i = 0; i < workers; i++)
    {
        tmp_finish = tmp_start + space;
        start[i] = tmp_start;
        finish[i] = tmp_finish;
        if (finish[i] > b)
            finish[i] = b;
        tmp_start = tmp_finish;
    }

    for (i = 0; i < workers; i++)
    {
        if (fork() == 0)
        {
            child(start[i], finish[i]);
        }
    }

    printf("I'm the father [pid: %d, ppid: %d]\n", getpid(), getppid());
    for (i = 0; i < workers; i++)
        wait(&tmp);

    free(start); free(finish);

    return 0;
}

void child(double a, double b)
{
    unsigned long const n = 1e9;
    const double dx = (b - a) / n;

    double S = 0;

    for (unsigned long i = 0; i < n; i++)
    {
        S += f(a + (i + 0.5) * dx);
    }
    S *= dx;

    printf("I'm one of the children [S: %lf, pid: %d, ppid: %d]\n", S, getpid(), getppid());
    exit(1);
}

double f(double x)
{
    return log(x) * sqrt(x);
}
