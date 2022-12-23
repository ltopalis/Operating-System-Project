#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct mesg_buffer
{
  long mesg_type;
  double mesg_data[3];
};

double f(double x)
{
  return log(x) * sqrt(x);
}

typedef struct mesg_buffer message;

double get_wtime(void)
{
  struct timeval t;

  gettimeofday(&t, NULL);

  return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}

void integral(int N)
{
  key_t key;
  int msgid;
  message distance;
  int i;
  double dx;
  double temp = 0.0;
  unsigned long const c = 1e9/N; 
  // ftok to generate unique key
  key = ftok("/temp", 65);
  // msgget creates a message queue
  // and returns identifier
  msgid = msgget(key, 0666);
  msgrcv(msgid, &distance, sizeof(distance), 1, 0);

  dx = (distance.mesg_data[1] - distance.mesg_data[0]) / c;

  for (i = 0; i < c; i++)

    temp += f(distance.mesg_data[0] + i*dx);

  distance.mesg_data[2] = temp * dx;
  distance.mesg_type = 2;
  msgsnd(msgid, &distance, sizeof(distance), 0);
  exit(1);
  // destroy message?
}

int main()
{
  int pid;
  int msgid;
  key_t key;
  message *result;
  double integral_result = 0.0;
  int i;
  float a = 1, b = 4, dy, dx;
  int N;

  printf("Give workers: ");
  scanf("%d", &N);
  result = (message*)malloc(N*(sizeof(message)));

  key = ftok("/temp", 65); // idio?
  msgid = msgget(key, 0666 | IPC_CREAT);

  double t0 = get_wtime();
  for (i = 0; i < N; i++)
    if (fork() == 0)
      integral(N);

  dy = (b - a) / N;
  for (i = 0; i < N; i++)
  {
    result[i].mesg_type = 1;
    result[i].mesg_data[0] = a + i * dy;
    result[i].mesg_data[1] = a + (i + 1) * dy;
    if (result[i].mesg_data[1] > b)
      result[i].mesg_data[1] = b;
    result[i].mesg_data[2] = 0.0;
  }

  for (i = 0; i < N; i++)
    msgsnd(msgid, &result[i], sizeof(result[i]), 0);

  for (i = 0; i < N; i++)
  {
    waitpid(-1, NULL, 0);
    msgrcv(msgid, &result[i], sizeof(result[i]), 2, 0);
  }

  for (i = 0; i < N; i++)
    integral_result += result[i].mesg_data[2];

  double t1 = get_wtime();

  printf("Result: %lf \t Time: %lf\n", integral_result, t1 - t0);
  free(result);
  exit(0);
}
