/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:08:57 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:47:23 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		recursive(t_map map, int i, int current_y)
{
	if (i == 0)
		return (1);
	if (map.vertex[i].y != current_y && i < map.vertex_length)
		return (recursive(map, i - 1, current_y));
	if (map.vertex[i].y == current_y)
		return (2);
	return (0);
}

void	write_vertex(t_map map, int fd)
{
	int i;
	int j;

	i = -1;
	while (++i < map.vertex_length)
	{
		if (i == 1 && map.vertex[i].y == map.vertex[i - 1].y)
			continue;
		if (i > 1 && recursive(map, i - 1, map.vertex[i].y) == 2)
			continue;
		ft_putstr_fd("vertex ", fd);
		ft_putnbr_fd(map.vertex[i].y, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.vertex[i].x, fd);
		j = i;
		while (++j < map.vertex_length)
		{
			if (map.vertex[i].y == map.vertex[j].y)
			{
				ft_putchar_fd(' ', fd);
				ft_putnbr_fd(map.vertex[j].x, fd);
			}
		}
		ft_putstr_fd(" z\n", fd);
	}
}

void	write_edges(t_map map, int s_num, int fd)
{
	int		i;
	int		fd_index;
	t_wall	edge_to_find;

	i = -1;
	while (++i < map.sector[s_num].edges_length)
	{
		edge_to_find = get_line_coordinates(map, map.sector[s_num].edges[i]);
		fd_index = get_fd_index(map, edge_to_find.start);
		ft_putnbr_fd(fd_index, fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd("c  ", fd);
}

void	write_sectors(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sector_length)
	{
		ft_putstr_fd("sector ", fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.sector[i].floor_height, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.sector[i].ceil_height, fd);
		ft_putchar_fd(' ', fd);
		write_edges(map, i, fd);
		write_neighbours(map, i, fd);
		ft_putstr_fd(" z", fd);
		ft_putchar_fd('\n', fd);
	}
}

void	write_fd(t_map map)
{
	int fd;

	fd = open("map.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	truncate("map.txt", 0);
	write_vertex(map, fd);
	ft_putstr_fd("z\n", fd);
	write_sectors(map, fd);
	ft_putstr_fd("z\n", fd);
	write_player(map, fd);
	ft_putstr_fd("z\n", fd);
	write_sprites_globales(map, fd);
	close(fd);
}
