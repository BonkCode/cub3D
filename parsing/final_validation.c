/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:36:39 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/07 15:57:57 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	final_validation(t_config *c)
{
	if (!c->win.x || !c->win.y)
		config_exit(5, c);
	if (!c->textures.e_path || !c->textures.i_path
		|| !c->textures.n_path || !c->textures.s_path || !c->textures.w_path)
		config_exit(6, c);
	if (!*c->map.map || !c->map.map)
		config_exit(7, c);
	if (!c->player.x)
		config_exit(8, c);
	if (!c->floor)
		config_exit(9, c);
	if (!c->ceiling)
		config_exit(10, c);
	check_file(c->textures.e_path, c);
	check_file(c->textures.i_path, c);
	check_file(c->textures.n_path, c);
	check_file(c->textures.s_path, c);
	check_file(c->textures.w_path, c);
}
