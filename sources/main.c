/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:43:38 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/25 21:28:29 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycasting/cub3D.h"

int main(int argc, char **argv)
{
    parse(argc, argv);
	game(argv[1]);
    system("leaks cub3D");
    return (0);
}
