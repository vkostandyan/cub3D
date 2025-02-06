/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:43:38 by vkostand          #+#    #+#             */
/*   Updated: 2025/01/24 16:39:42 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3D.h"
int main(int argc, char **argv)
{
	t_parse pars_data;
    pars_data = parse(argc, argv);
	game(*argv, &pars_data);
    // system("leaks cub3D");
    (void)argc;
    (void)argv;
    return (0);
}
