/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:44:35 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/06 17:33:28 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			skip_spaces(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int			ft_atoi_cub3d(char *line, int *i)
{
	int		num;

	num = 0;
	skip_spaces(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

char		*ft_strdup_cub3d(char *str)
{
	char			*dest;
	char			*temp;

	temp = (char *)malloc(sizeof(*dest) * (ft_strlen_gnl(str) + 1));
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str && *str != ' ')
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}

int			check_extension(char *filename, char *extension)
{
	int		i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if ((i > 4 && filename[i - 1] == extension[2]\
		&& filename[i - 2] == extension[1])
		&& (filename[i - 3] == extension[0])\
		&& filename[i - 4] == '.')
		return (1);
	return (0);
}

int			is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}
