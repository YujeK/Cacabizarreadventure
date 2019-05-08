/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 01:11:05 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:46:12 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		player_outside(t_map map)
{
	if (in_sector_full(map, map.player.pos) == -1)
		return (1);
	return (0);
}
