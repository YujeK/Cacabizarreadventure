/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 04:37:02 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:39:59 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		count_sprites(char **map)
{
	int i;
	int t;
	int count;

	count = 0;
	i = -1;
	t = ft_tablen(map);
	while (++i < t)
	{
		if (map[i][1] == 'o')
			count++;
	}
	return (count);
}

void	fill_sprite(char *str, t_object *sprite)
{
	int i;
	int flag;

	flag = 0;
	i = -1;
	while (str[++i])
	{
		if (flag == 0 && str[i] >= '0' && str[i] <= '9'
		&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sprite->where.x = ft_iatof(str, i) / 10;
			flag++;
		}
		else if (flag == 1 && str[i] >= '0' && str[i] <= '9'
		&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sprite->where.y = ft_iatof(str, i) / 10;
			flag++;
		}
		else if (flag == 2 && str[i] >= '0' && str[i] <= '9'
		&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sprite->sectorno = (int)ft_iatof(str, i);
		}
	}
}

void	load_sprites(t_data *data)
{
	int i;

	i = 0;
	while (i < data->sprite_nbr)
	{
		if (!(data->sprite[i].img = tga_load(
			"ressources/enemies/targuet.tga", &data->sprite[i].specs)))
			ft_error_exit("I couldnt load tga toiletashkan");
		if (!(data->sprite[i].dead_img = tga_load(
			"ressources/enemies/1score.tga", &data->sprite[i].specs1)))
			ft_error_exit("I couldnt load tga +1");
		data->sprite[i].res_img = resize(data->sprite[i].dead_img
		, data->sprite[i].specs1, 600);
		i++;
	}
}

void	init_sprites(t_data *data, char **map)
{
	int i;
	int j;
	int t;

	j = 0;
	t = ft_tablen(map);
	i = 0;
	data->sprite_nbr = count_sprites(map);
	if ((data->sprite = (t_object *)malloc(sizeof(t_object)
	* data->sprite_nbr + 100)) == NULL)
		ft_error_exit("Fail malloc sprites");
	while (i < data->sprite_nbr)
	{
		if (map[j][1] == 'o')
		{
			fill_sprite(map[j], &data->sprite[i]);
			data->sprite[i].i = i;
			data->sprite[i].status = 0;
			i++;
		}
		j++;
	}
	load_sprites(data);
}
