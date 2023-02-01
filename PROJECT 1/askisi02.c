/*
 * ΣΑΜΑΡΑ ΧΡΙΣΤΙΝΑ-ΕΛΕΑΝΝΑ 1084622
 * ΤΟΠΑΛΗΣ ΛΑΖΑΡΟΣ         1088101
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>

struct mesg_buffer
{
    long mesg_type;
    double mesg_data[3]; // [0] -> start, [1] -> finish, [2] -> result
};

typedef struct mesg_buffer mesg;

void child(int workers);
double f(double x);
double get_wtime(void);

int main(int argc, char *argv[])
{
    int workers, tmp, i, msgid;
    double a = 1.0, b = 4.0, space, sum = 0;
    key_t key;
    mesg *message_to_ch;

    do
    {
        printf("number of processes: ");
        scanf("%d", &workers);
    } while (workers < 1);

    message_to_ch = (mesg *)malloc(workers * sizeof(mesg));
    if (!message_to_ch)
    {
        fprintf(stderr, "Error Allocating memory!\n");
        exit(0);
    }

    system("touch .tempfile");
    key = ftok("./.tempfile", 45);

    msgid = msgget(key, 0666 | IPC_CREAT);

    double t0 = get_wtime();
    for (i = 0; i < workers; i++)
        if (fork() == 0)
            child(workers);

    space = (b - a) / workers;
    for (i = 0; i < workers; i++)
    {
        message_to_ch[i].mesg_type = 1;
        message_to_ch[i].mesg_data[0] = a + i * space;
        message_to_ch[i].mesg_data[1] = a + (i + 1) * space;
        message_to_ch[i].mesg_data[2] = 0;
        if (message_to_ch[i].mesg_data[1] > b)
            message_to_ch[i].mesg_data[1] = b;
    }

    for (i = 0; i < workers; i++)
        msgsnd(msgid, &message_to_ch[i], sizeof(message_to_ch[i]), 0);

    for (i = 0; i < workers; i++)
    {
        waitpid(-1, NULL, 0);
        msgrcv(msgid, &message_to_ch[i], sizeof(message_to_ch[i]), 2, 0);
    }

    for (i = 0; i < workers; i++)
        sum += message_to_ch[i].mesg_data[2];

    double t1 = get_wtime();

    printf("Time=%lf, Result=%lf\n", t1 - t0, sum);

    free(message_to_ch);

    system("rm .tempfile");

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

void child(int workers)
{
    unsigned long const n = (unsigned long)1e9 / workers;
    key_t key;
    int msgid;
    mesg message_from_par;

    key = ftok("./.tempfile", 45);
    msgid = msgget(key, 0666);
    msgrcv(msgid, &message_from_par, sizeof(message_from_par), 1, 0);

    const double dx = (message_from_par.mesg_data[1] - message_from_par.mesg_data[0]) / n;
    message_from_par.mesg_data[2] = 0;

    for (unsigned long i = 0; i < n; i++)
        message_from_par.mesg_data[2] += f(message_from_par.mesg_data[0] + i * dx);
    message_from_par.mesg_data[2] *= dx;

    message_from_par.mesg_type = 2;
    message_from_par.mesg_data[0] = 0;
    message_from_par.mesg_data[1] = 0;
    msgsnd(msgid, &message_from_par, sizeof(message_from_par), 0);

    exit(1);
}

double f(double x)
{
    return log(x) * sqrt(x);
}

double get_wtime(void)
{
    struct timeval t;

    gettimeofday(&t, NULL);

    return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}
