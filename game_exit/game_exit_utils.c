/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:09:17 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:58:16 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_exit.h"

void		free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void		free_texture_path(t_config *config)
{
	if (config->textures.e_path)
	{
		free(config->textures.e_path);
		config->textures.e_path = NULL;
	}
	if (config->textures.i_path)
	{
		free(config->textures.i_path);
		config->textures.i_path = NULL;
	}
	if (config->textures.s_path)
	{
		free(config->textures.s_path);
		config->textures.s_path = NULL;
	}
	if (config->textures.w_path)
	{
		free(config->textures.w_path);
		config->textures.w_path = NULL;
	}
}
