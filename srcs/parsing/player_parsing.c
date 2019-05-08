/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:46:50 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:15:09 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		get_string(char **map)
{
	int i;
	int line;
	int t;

	line = 0;
	t = ft_tablen(map);
	i = -1;
	while (++i < t)
	{
		if (map[i][1] == 'p')
		{
			line = i;
			break ;
		}
	}
	if (line == 0)
		exit(EXIT_FAILURE);
	return (line);
}

void	get_p_coords(char *str, t_plyr *player, int i, int f)
{
	while (str[++i])
	{
		if (f == 0 && str[i] >= '0' && str[i] <= '9'
			&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player->where.x = ft_iatof(str, i) / 10;
			f++;
		}
		else if (f == 1 && str[i] >= '0' && str[i] <= '9'
			&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player->where.y = ft_iatof(str, i) / 10;
			f++;
		}
		else if (f == 2 && str[i] >= '0' && str[i] <= '9'
			&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			player->angle = ft_iatof(str, i);
			f++;
		}
		else if (f == 3 && str[i] >= '0' && str[i] <= '9'
		&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
			player->sector = (unsigned int)ft_iatof(str, i);
	}
}

t_plyr	load_player(t_sector *sectors, char **map)
{
	t_plyr	player;
	char	*str;
	int		f;
	int		i;

	str = NULL;
	i = -1;
	f = 0;
	player.velocity.x = 0;
	player.velocity.y = 0;
	player.velocity.z = 0;
	player.anglecos = 0;
	player.anglesin = 0;
	player.yaw = 0;
	if (map[get_string(map)])
		str = map[get_string(map)];
	get_p_coords(str, &player, i, f);
	player.where.z = sectors[player.sector].floor + EYEHEIGHT;
	return (player);
}
