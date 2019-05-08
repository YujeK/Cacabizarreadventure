/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 02:48:39 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:49:02 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

char		**read_lines(int fd)
{
	char	*buf;
	int		ret;
	char	**txt;
	char	*str;

	str = ft_strnew(1);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((txt = ft_strsplit(str, '|')) == NULL || ret == -1)
		exit_on_error();
	free(str);
	return (txt);
}

t_map		read_vertex(t_map map, char **txt)
{
	int			save;
	static int	count = -1;

	while (map.j < ft_strlen(txt[map.i]) - 2 && (txt[map.i][map.j] < '0' ||
				txt[map.i][map.j] > '9'))
		map.j++;
	save = ft_iatoi(txt[map.i], map.j);
	while (map.j < ft_strlen(txt[map.i]) - 2 && txt[map.i][map.j] >= '0' &&
			txt[map.i][map.j] <= '9')
		map.j++;
	while (++map.j < ft_strlen(txt[map.i]) - 2)
	{
		count++;
		map.vertex_length++;
		map.vertex[count].x = ft_iatoi(txt[map.i], map.j);
		while (map.j < ft_strlen(txt[map.i]) - 2 && txt[map.i][map.j] >= '0' &&
				txt[map.i][map.j] <= '9')
			map.j++;
		map.vertex[count].y = save;
	}
	return (map);
}

t_map		read_edges(t_map map, char **txt, int save, int flag)
{
	while (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] != 'c')
	{
		map.edges[map.edges_length].x = ft_iatoi(txt[map.i], map.j);
		map.sector[map.sector_length]
		.edges[map.sector[map.sector_length].edges_length] = map.edges_length;
		if (flag == 0)
			save = map.edges[map.edges_length].x;
		flag = 1;
		while (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] >= '0' &&
				txt[map.i][map.j] <= '9')
			map.j++;
		map.j++;
		if (map.j < ft_strlen(txt[map.i]) - 3 && txt[map.i][map.j] == 'c')
			map.edges[map.edges_length].y = save;
		else
			map.edges[map.edges_length].y = ft_iatoi(txt[map.i], map.j);
		map.sector[map.sector_length].edges_length++;
		map.edges_length++;
	}
	map.sector_length++;
	return (map);
}

t_map		read_sector(t_map map, char **txt)
{
	int		flag;
	int		save;

	save = 0;
	flag = 0;
	map.sector[map.sector_length].edges_length = 0;
	if ((map.sector[map.sector_length].edges =
				(int*)malloc(sizeof(t_coord) * (500))) == NULL)
		exit_on_error();
	map.sector[map.sector_length].num = map.sector_length;
	while (map.j < ft_strlen(txt[map.i]) - 3 &&
			(txt[map.i][map.j] < '0' || txt[map.i][map.j] > '9'))
		map.sector[map.sector_length].floor_height =
			ft_iatoi(txt[map.i], ++map.j);
	while (map.j < ft_strlen(txt[map.i]) - 3 &&
			txt[map.i][map.j] >= '0' && txt[map.i][map.j] <= '9')
		map.j++;
	map.sector[map.sector_length].ceil_height = ft_iatoi(txt[map.i], ++map.j);
	while (map.j < ft_strlen(txt[map.i]) - 3 &&
			txt[map.i][map.j] >= '0' && txt[map.i][map.j] <= '9')
		map.j++;
	map.j++;
	map = read_edges(map, txt, save, flag);
	return (map);
}

t_map		read_map(void)
{
	t_map	map;
	char	**txt;
	int		fd;
	size_t	strlen;

	fd = open("map.txt", O_RDONLY);
	txt = read_lines(fd);
	close(fd);
	map = init_map();
	while (txt[++map.i])
	{
		strlen = ft_strlen(txt[map.i]) - 2;
		map.j = 0;
		if (txt[map.i][map.j])
		{
			if (txt[map.i][map.j] == '\n')
				continue;
			map = make_read_decision(map, txt, strlen);
		}
	}
	map.i = -1;
	while (++map.i < ft_tablen(txt))
		free(txt[map.i]);
	free(txt);
	return (map);
}
