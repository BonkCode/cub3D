/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:52:59 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/07 15:59:54 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		parse_resolution(char *line, t_config *config, int *i)
{
	if (config->win.x || config->win.y)
		config_exit(12, config);
	(*i)++;
	config->win.x = ft_atoi_cub3d(line, i);
	config->win.y = ft_atoi_cub3d(line, i);
	skip_spaces(line, i);
	if (config->win.x <= 0 || config->win.y <= 0 || line[*i] != '\0')
		config_exit(13, config);
}

void		texture_path(char *line, char **path, int *i, t_config *config)
{
	if (*path != NULL)
		config_exit(14, config);
	(*i) += 2;
	line = ft_strtrim(&line[*i], " ");
	if (check_extension(line, "xpm"))
		*path = ft_strdup(line);
	else
		config_exit(15, config);
	if (!(*path))
		config_exit(16, config);
	if (path == NULL)
		config_exit(17, config);
}

void		get_color(char *line, unsigned int *color, int *i, t_config *config)
{
	int r;
	int g;
	int b;

	(*i)++;
	if (*color != 0)
		config_exit(18, config);
	r = ft_atoi_cub3d(line, i);
	skip_spaces(line, i);
	(*i)++;
	g = ft_atoi_cub3d(line, i);
	skip_spaces(line, i);
	(*i)++;
	skip_spaces(line, i);
	b = ft_atoi_cub3d(line, i);
	skip_spaces(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		config_exit(19, config);
	*color = r * 65536 + g * 256 + b;
}
