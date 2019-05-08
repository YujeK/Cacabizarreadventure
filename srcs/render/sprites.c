/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:57:44 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 22:59:00 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			render_sprite(t_plyr player,
t_object *sprite, t_sector *sectors, t_bas *bas)
{
	bas->yc = sectors[sprite->sectorno].ceil - player.where.z;
	bas->yf = sectors[sprite->sectorno].floor - player.where.z;
	bas->sp.x = sprite->where.x - player.where.x;
	bas->sp.y = sprite->where.y - player.where.y;
	bas->t1.x = bas->sp.x * player.anglesin - bas->sp.y * player.anglecos;
	bas->t1.y = bas->sp.x * player.anglecos + bas->sp.y * player.anglesin;
	if (bas->t1.y <= 0)
		return (-1);
	bas->xscale = HFOV / bas->t1.y;
	bas->yscale = VFOV / bas->t1.y;
	bas->xt = SCREEN_WIDTH / 2 - (int)(bas->t1.x * bas->xscale);
	bas->y1 = SH / 2 - (int)
	(yaw(bas->yf, bas->t1.y, player.yaw) * bas->yscale);
	bas->y2 = SH / 2 - (int)
	(yaw(bas->yc, bas->t1.y, player.yaw) * bas->yscale);
	sprite->x = bas->xt;
	sprite->y1 = bas->y1 - sprite->size;
	return (sprite->x);
}

t_object	*sort_sprites(t_object *sprite, t_data data)
{
	int i;
	int temp;

	i = -1;
	while (++i < data.sprite_nbr - 1)
	{
		if (sprite[i].i > sprite[i + 1].i)
		{
			temp = sprite[i].i;
			sprite[i].i = sprite[i + 1].i;
			sprite[i + 1].i = temp;
			i = -1;
		}
	}
	return (sprite);
}

t_object	*sprite_size(t_object *sprite, t_plyr player, t_data data, t_b *b)
{
	int	i;

	i = -1;
	while (++i < data.sprite_nbr - 1)
	{
		sprite[i].dist = sqrt(pow(sprite[i].where.x
		- player.where.x, 2) + pow(sprite[i].where.y - player.where.y, 2));
		b->temp = sprite[i].dist / 10;
		sprite[i].size = 250 / b->temp;
		sprite[i].x = 0;
		sprite[i].x_count = 0;
	}
	i = -1;
	while (++i < data.sprite_nbr - 1)
	{
		if (sprite[i].dist < sprite[i + 1].dist)
		{
			b->temp_sprite = sprite[i];
			sprite[i] = sprite[i + 1];
			sprite[i + 1] = b->temp_sprite;
			i = 0;
		}
	}
	sprite = sort_sprites(sprite, data);
	return (sprite);
}

t_object	get_sprite_coords(t_data *data
, t_object *sprite, t_b *b, t_bas *bas)
{
	pick_up(data, &b->player, sprite);
	sprite->x = render_sprite(b->player, sprite, b->sectors, bas)
	- sprite->size / 2;
	sprite->y2 = sprite->y1 + sprite->size;
	sprite->y2 = clamp(sprite->y2, bas->ytop[bas->x], bas->ybottom[bas->x]);
	if (sprite->x_count < sprite->size && data->x_draw
	> sprite->x && sprite->x > 0 && data->sectqueue[sprite->sectorno]
		<= data->sectqueue[data->now_sect])
	{
		draw_resized_column(data, sprite);
		sprite->x_count++;
	}
	if (sprite->x_count > 0)
	{
		sprite->x_count = data->x_draw - sprite->x;
		if (sprite->x_count < 0)
			sprite->x_count = 0;
	}
	return (*sprite);
}
