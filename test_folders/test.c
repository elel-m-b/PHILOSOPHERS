#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>


void        *routine(void *arg)
{
    char *s = (char *)(arg);
    printf ("%s\n", s);
    return (NULL);
}

int main()
{
    pthread_t       t1;
    pthread_t       t2;
    
    pthread_create(&t1, NULL, routine, "Hello");
    pthread_create(&t2, NULL, routine, "world");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

}