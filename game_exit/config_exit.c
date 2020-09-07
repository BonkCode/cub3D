/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:26:51 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/07 15:55:52 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"
#include "cub.h"
#include "game_exit.h"

static void		clean_garbage_config(t_config *config)
{
	free_texture_path(config);
	free_map(config->map.map);
}

static void		print_message(int exit_code)
{
	(exit_code == 0) ? ft_putstr_fd(OK_EXIT, 2) : 0;
	(exit_code == 1) ? ft_putstr_fd(ARGS_NUM, 2) : 0;
	(exit_code == 2) ? ft_putstr_fd(WRONG_EXT, 2) : 0;
	(exit_code == 3) ? ft_putstr_fd(WRONG_OPT, 2) : 0;
	(exit_code == 4) ? ft_putstr_fd(MAP_404, 2) : 0;
	(exit_code == 5) ? ft_putstr_fd(RES_NOT_SPEC, 2) : 0;
	(exit_code == 6) ? ft_putstr_fd(TEXT_NOT_SPEC, 2) : 0;
	(exit_code == 7) ? ft_putstr_fd(MAP_NOT_SPEC, 2) : 0;
	(exit_code == 8) ? ft_putstr_fd(PLAYER_NOT_SPEC, 2) : 0;
	(exit_code == 9) ? ft_putstr_fd(FLOOR_NOT_SPEC, 2) : 0;
	(exit_code == 10) ? ft_putstr_fd(CEIL_NOT_SPEC, 2) : 0;
	(exit_code == 11) ? ft_putstr_fd(MLX_INIT_ERR, 2) : 0;
	(exit_code == 12) ? ft_putstr_fd(MULT_RES, 2) : 0;
	(exit_code == 13) ? ft_putstr_fd(BAD_RES, 2) : 0;
	(exit_code == 14) ? ft_putstr_fd(MULT_TEXT, 2) : 0;
	(exit_code == 15) ? ft_putstr_fd(WRONG_TEXT_F, 2) : 0;
	(exit_code == 16) ? ft_putstr_fd(PATH_ERROR	, 2) : 0;
	(exit_code == 17) ? ft_putstr_fd(BAD_TEXT, 2) : 0;
	(exit_code == 18) ? ft_putstr_fd(MULT_COLORS, 2) : 0;
	(exit_code == 19) ? ft_putstr_fd(BAD_COLOR, 2) : 0;
	(exit_code == 20) ? ft_putstr_fd(MALLOC_ERR, 2) : 0;
	(exit_code == 21) ? ft_putstr_fd(INVALID_MAP, 2) : 0;
	(exit_code == 22) ? ft_putstr_fd(PARSE_ERROR, 2) : 0;
	(exit_code == 23) ? ft_putstr_fd(MULT_PLAYER, 2) : 0;
}

void			config_exit(int exit_code, t_config *config)
{
	clean_garbage_config(config);
	print_message(exit_code);
	exit(exit_code);
}
