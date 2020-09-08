/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:10:04 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 14:02:10 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_EXIT_H
# define GAME_EXIT_H

# include "cub.h"

# define OK_EXIT     	 "Hope you enjoy the game.\nSEE YOU LATER COWPOKE\n"
# define ARGS_NUM    	 "Error\nWrong amount of args\n"
# define WRONG_EXT   	 "Error\nWrong extenstion\n"
# define WRONG_OPT   	 "Error\nOnly --save option is available\n"
# define MAP_404     	 "Error\nMap or texture file doesn't exists\n"
# define RES_NOT_SPEC	 "Error\nResolution is not specified\n"
# define TEXT_NOT_SPEC   "Error\nOne of the textures wasn't specified\n"
# define MAP_NOT_SPEC 	 "Error\nMap wasn't specified\n"
# define PLAYER_NOT_SPEC "Error\nPlayer wasn't specified\n"
# define FLOOR_NOT_SPEC  "Error\nFloor wasn't specified\n"
# define CEIL_NOT_SPEC   "Error\nCeiling wasn't specified\n"
# define MLX_INIT_ERR    "Error\nFailed to init mlx\n"
# define MULT_RES		 "Error\nPlease, choose one resolution\n"
# define BAD_RES		 "Error\nPlease, configure resolution properly\n"
# define MULT_TEXT		 "Error\nYou need to configure textures only once\n"
# define WRONG_TEXT_F    "Error\nTexture format corrupted\n"
# define PATH_ERROR		 "Error\nCheck texture path. Empty or too long\n"
# define BAD_TEXT		 "Error\nPlease, configure textures properly\n"
# define MULT_COLORS	 "Error\nYou specified floor or ceiling color twice"
# define BAD_COLOR		 "Error\nPlease configure color properly\n"
# define MALLOC_ERR 	 "Error\nMalloc error."
# define INVALID_MAP	 "Error\nInvalid map\n"
# define PARSE_ERROR	 "Error\nParsing Error\n"
# define MULT_PLAYER	 "Error\n2 players on map\n"

void		free_texture_path(t_config *config);
void		free_map(char **map);

#endif
