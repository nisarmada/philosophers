#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sum;
	int	sign;

	i = 0;
	sign = 1;
	sum = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else
		if (nptr[i] == '+')
			i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	return (sum * sign);
}

int *turn_to_int(char **av)
{
    int i;
    int *array;
    int num_args;

    i = 1;
    while (av[i])
        i++;
    num_args = i - 1;
    array = malloc((num_args) * sizeof(int));
    if (!array)
        return (NULL);
    i = 0;
    while (i < num_args)
    {
        array[i] = ft_atoi(av[i + 1]);
        i++;
    }
   // print_array(array);
    return (array);
}
void print_array(int *array)
{
    int i = 0;

    while (array[i])
    {
        printf("array[%i] = %i\n", i, array[i]);
        i++;
    }
}

int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int input_check(char *av)
{
	int i;

	i = 0;
	if (av[i] == '\0')
		return (0);
	if (av[i] == '+')
		i++;
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}