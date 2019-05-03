/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:46:50 by asamir-k          #+#    #+#             */
/*   Updated: 2019/04/30 02:17:11 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_plyr Load_Player(t_sector *sectors, char *str)
{
	t_plyr player;
	int i;
	int f;

	i = 0;
	f = 0;
	player.velocity.x = 0;
	player.velocity.y = 0;
	player.velocity.z = 0;
	player.anglecos = 0;
	player.anglesin = 0;
	player.yaw = 0;
	while (str[i])
	{
		if(f == 0 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player.where.x = ft_iatof(str, i);
			f++;
		}
		else if (f == 1 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player.where.y = ft_iatof(str, i);
			f++;
		}
		else if (f == 2 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player.angle = ft_iatof(str, i);
			f++;
		}
		else if (f == 3 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player.sector = (unsigned int)ft_iatof(str, i);
		}
		i++;
	}

	player.where.z = sectors[player.sector].floor + Eyeheight;
	return (player);
}
