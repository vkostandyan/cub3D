/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:43:38 by vkostand          #+#    #+#             */
/*   Updated: 2025/02/19 17:44:21 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_parse	pars_data;

	pars_data = parse(argc, argv);
	game(*argv, &pars_data);
	(void)argc;
	(void)argv;
	return (0);
}
