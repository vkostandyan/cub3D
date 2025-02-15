/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:27:02 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/15 16:36:21 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_digit(char **split)
{
	int	i;

	i = 0;
	while (split[0][i])
	{
		if (!ft_isdigit(split[0][i]))
			return (0);
		i++;
	}
	i = 0;
	while (split[1][i])
	{
		if (!ft_isdigit(split[1][i]))
			return (0);
		i++;
	}
	i = 0;
	while (split[2][i] && split[2][i + 1])
	{
		if (!ft_isdigit(split[2][i]))
			return (0);
		i++;
	}
	return (1);
}

void	write_type(t_type type)
{
	if (type == NORTH)
		ft_putstr_fd("NO", STDERR_FILENO);
	else if (type == WEST)
		ft_putstr_fd("WE", STDERR_FILENO);
	else if (type == SOUTH)
		ft_putstr_fd("SO", STDERR_FILENO);
	else if (type == EAST)
		ft_putstr_fd("EA", STDERR_FILENO);
	else if (type == FLOOR)
		ft_putstr_fd("F", STDERR_FILENO);
	else if (type == CEILING)
		ft_putstr_fd("C", STDERR_FILENO);
}

void	write_key(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
}
