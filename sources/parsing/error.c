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

void	send_file_open_error(char *name)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Cannot open file ", 2);
	ft_putstr_fd(name, 2);
	system("leaks cub3D");
	exit(1);
}

void	decide_error2(int status)
{
	if (status == DOUBLE_COMMA)
		ft_putstr_fd("Invalid color separator: ',,'\n", STDERR_FILENO);
	else if (status == EDGE_COMMA)
		ft_putstr_fd(COLOR_COMMA_ERR, STDERR_FILENO);
	else if (status == INVALID_RANGE)
		ft_putstr_fd(COLOR_RANGE_ERR, STDERR_FILENO);
	else if (status == INVALID_COLOR_ARGUMENTS)
		ft_putstr_fd("Color values can only be numbers\n", STDERR_FILENO);
}

void	decide_error(char *str, t_type type, int status)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (status == MALLOC)
		ft_putstr_fd("Malloc error\n", STDERR_FILENO);
	else if (status == DOUBLICATE)
	{
		write_type(type);
		ft_putstr_fd(" is set more than once\n", STDERR_FILENO);
	}
	else if (status == INVALID_KEY)
	{
		ft_putstr_fd("Invalid key: ", STDERR_FILENO);
		write_key(str);
	}
	else if (status == TOO_FEW_VALUES || status == TOO_MANY_VALUES)
	{
		if (status == TOO_FEW_VALUES)
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
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	system("leaks cub3D");
	exit(1);
}
