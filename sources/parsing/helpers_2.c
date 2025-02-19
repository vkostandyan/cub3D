/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:27:02 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:34:25 by vkostand         ###   ########.fr       */
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

void	check_empty_lines(t_parse *data, char *map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		flag = 0;
		if (map[i] == '\n')
			i++;
		while (map[i] && map[i] != '\n')
		{
			if (map[i] == '1' || map[i] == '0' || map[i] == 'N' || map[i] == 'S'
				|| map[i] == 'E' || map[i] == 'W')
				flag = 1;
			i++;
		}
		if (flag == 0)
		{
			free_and_set_null(map);
			clean_parsing_data(data);
			send_error("Empty line in the map\n");
		}
	}
}
