/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 04:37:02 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/05 09:19:20 by asamir-k         ###   ########.fr       */
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
	while(++i < t)
	{
		if(map[i][1] == 'o')
			count++;
	}
	return(count);
}

void fill_sprite(char *str, t_object *sprite)
{
	int i;
	int flag;

	flag = 0;
	i = -1;
	while(str[++i])
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
	if (!(data->sprite[i].img = tga_load("ressources/enemies/toiletashkan.tga", &data->sprite[i].specs)))
		ft_error_exit("I couldnt load tga toiletashkan", data);
	if (!(data->sprite[i].dead_img = tga_load("ressources/enemies/dead.tga", &data->sprite[i].specs1)))
		ft_error_exit("I couldnt load tga +1", data);
		data->sprite[i].res_img = resize(data->sprite[i].dead_img, data->sprite[i].specs1, 1000);
	i++;
}
//	if (!(data->sprite[1].img = tga_load("ressources/enemies/dead.tga", &data->sprite[1].specs)))
//		ft_error_exit("I couldnt load tga toiletashkan", data);
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
	if ((data->sprite = (t_object *)malloc(sizeof(t_object) * data->sprite_nbr + 100)) == NULL)
		ft_error_exit("quand je essaye de mallocer les sprites car le putain de ashkan ne se rien faire ta mere", data);
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
