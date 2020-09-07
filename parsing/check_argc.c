/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:20:24 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/07 15:58:44 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_args(int argc, char **argv, t_config *config)
{
	if (argc < 2 || argc > 3)
		config_exit(1, config);
	else if ((argc == 2 && (!(check_extension(argv[1], "cub") \
			|| (argc == 3 && (!(check_extension(argv[2], "cub"))))))))
		config_exit(2, config);
	else if (argc == 3)
	{
		if ((ft_strncmp(argv[1], "--save", ft_strlen(argv[2])) != 0))
			config_exit(3, config);
		else
			config->save = 1;
	}
}

int		check_file(char *filename, t_config *config)
{
	int fd;
	int res;

	res = 1;
	fd = open(filename, O_RDONLY);
	if (fd < 1)
		config_exit(4, config);
	close(fd);
	return (res);
}
