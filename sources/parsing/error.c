/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:19:44 by marvin            #+#    #+#             */
/*   Updated: 2024/12/28 23:19:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	write_type(t_type type)
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

static void write_key(char *str)
{
	int i;

	i = 0;
	if(!str)
		return ;
	while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while(str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
}

void decide_error2(int status)
{
	if(status == DOUBLE_COMMA)
		ft_putstr_fd("Invalid color separator: ',,'\n", STDERR_FILENO);
	else if(status == EDGE_COMMA)
		ft_putstr_fd("Color values cannot start or end with ','\n", STDERR_FILENO);
	else if(status == INVALID_RANGE)
		ft_putstr_fd("Color values should be in a range of 0-255\n", STDERR_FILENO);
	else if(status == INVALID_COLOR_ARGUMENTS)
		ft_putstr_fd("Color values can only be numbers\n", STDERR_FILENO);
}

void	decide_error(char *str, t_type type, int status)
{
	ft_putstr_fd("\033[1;31mError\033[0m\n", STDERR_FILENO);
	if(status == MALLOC)
		ft_putstr_fd("Malloc error\n", STDERR_FILENO);
	else if (status == DOUBLICATE)
	{
		write_type(type);
		ft_putstr_fd(" is set more than once\n", STDERR_FILENO);
	}
	else if(status == INVALID_KEY)
	{
		ft_putstr_fd("Invalid key: ", STDERR_FILENO);
		write_key(str);
	}
	else if(status == TOO_FEW_VALUES || status == TOO_MANY_VALUES)
	{
		if(status == TOO_FEW_VALUES)
			ft_putstr_fd("too few arguments for: ", STDERR_FILENO);
		else
			ft_putstr_fd("too many arguments for: ", STDERR_FILENO);
		write_type(type);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		decide_error2(status);
}

void	send_error(char *str)
{
	if (!str)
		return ;
	ft_putstr_fd(str, 2);
    system("leaks cub3D");
	exit(1);
}
