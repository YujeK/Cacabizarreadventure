/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:58:43 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:10 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		ft_iatoi(char *wall, int index)
{
	int number;
	int i;
	int	negative;

	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
}

t_map	init_map(void)
{
	t_map map;

	map.i = -1;
	map.sector_length = 0;
	map.edges_length = 0;
	map.vertex_length = 0;
	map.sprite_g_len = 0;
	if ((map.vertex = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.edges = (t_coord*)malloc(sizeof(t_coord) * (1000))) == NULL)
		exit_on_error();
	if ((map.sector = (t_sector*)malloc(sizeof(t_sector) * (200))) == NULL)
		exit_on_error();
	if ((map.g_sprite = (t_sprite_g*)malloc(sizeof(t_sprite_g) * 200)) == NULL)
		exit_on_error();
	return (map);
}

t_map	read_player(t_map map, char **txt)
{
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.player.pos.x = ft_iatoi(txt[map.i], map.j);
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.j++;
	map.player.pos.y = ft_iatoi(txt[map.i], map.j);
	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	map.j = map.j + 3;
	map.player.sector_num = ft_iatoi(txt[map.i], map.j);
	return (map);
}

t_map	make_read_decision(t_map map, char **txt, size_t strlen)
{
	if (txt[map.i][map.j] == 'v')
		map = read_vertex(map, txt);
	if (txt[map.i][map.j] == 's')
		map = read_sector(map, txt);
	else if (txt[map.i][map.j] == 'p')
	{
		while (map.j < strlen && (txt[map.i][map.j] < '0' ||
					txt[map.i][map.j] > '9'))
			map.j++;
		map.player.pos.x = ft_iatoi(txt[map.i], map.j);
		while (map.j < strlen && !(txt[map.i][map.j] < '0' ||
					txt[map.i][map.j] > '9'))
			map.j++;
		map.j++;
		map.player.pos.y = ft_iatoi(txt[map.i], map.j);
		while (map.j < strlen && !(txt[map.i][map.j] < '0' ||
					txt[map.i][map.j] > '9'))
			map.j++;
		map.j = map.j + 3;
		map.player.sector_num = ft_iatoi(txt[map.i], map.j);
	}
	return (map);
}
