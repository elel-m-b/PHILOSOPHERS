#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
int     ft_strlen(char *s)
{
    int     i;
    i = 0;
    while (s[i])
        i++;
    return (i);
}

void        put_errro(char *err)
{
    write (2, err, ft_strlen(err));
}

int     check_args(int ac)
{
    if (ac != 6 && ac != 5)
    {
        put_errro("Invalid number of argument\n");
        return (1);
    }
    return (0);
}

int main(int        ac, char **av)
{
    if (check_args(ac))
        return (1);
    return (0);
}