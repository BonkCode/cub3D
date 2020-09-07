/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:25:36 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/06 17:25:48 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"

void			stop_casting(t_ray *ray, t_player player, int *dof)
{
	*dof = 32;
	ray->pos.x = player.pos.x;
	ray->pos.y = player.pos.y;
}
