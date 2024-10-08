/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/06 15:07:26 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/09/06 15:21:46 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	int		*arg_array;
	t_data	data;

	i = 1;
	if (ac != 5 && ac != 6)
		return (1);
	while (av[i])
	{
		if (!input_check(av[i]))
			return (0);
		i++;
	}
	arg_array = turn_to_int(av);
	init_stuff(&data, arg_array, ac);
	init_philos(&data);
	create_threads(&data);
	cleanup_crew(&data, arg_array);
}
