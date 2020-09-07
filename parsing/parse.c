/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:28:01 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/07 14:15:52 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	parse_line(char *line, t_config *config)
{
	int i;

	i = 0;
	skip_spaces(line, &i);
	if (line[i] == '1')
		get_map(config, line);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		parse_resolution(line, config, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		texture_path(line, &config->textures.n_path, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		texture_path(line, &config->textures.s_path, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		texture_path(line, &config->textures.w_path, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		texture_path(line, &config->textures.e_path, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		texture_path(line, &config->textures.i_path, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		get_color(line, &config->ceiling, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		get_color(line, &config->floor, &i);
	else if (line[i] != '\0')
		config_error("Error\nInvalid map configuration.\n");
	return (0);
}

int			parse_file(char *filename, t_config *config)
{
	int		fd;
	int		r;
	char	*line;

	r = 1;
	if (!(check_file(filename)))
		exit(0);
	fd = open(filename, O_RDONLY);
	while ((r = get_next_line(fd, &line)) > 0)
	{
		if (parse_line(line, config) == -1)
			r = -1;
		free(line);
	}
	if (parse_line(line, config) == -1)
		r = -1;
	free(line);
	close(fd);
	if (r < 0)
		config_error("Error\nParsing Error\n");
	return (1);
}
