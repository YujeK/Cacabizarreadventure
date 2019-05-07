/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:57:44 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 08:24:01 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		render_sprite(t_plyr player, t_object *sprite, t_sector *sectors)
{
	t_vector		sp;
	t_vector		sp2;
	int				x1;
	int				x2;
	float			yceil;
	float			yfloor;
	float			xscale;
	float			yscale;
	float			yscale2;
	int				y1;
	int				y2;
	int				sx;
	int				i;
	float			dist;
	t_vector		t1;

	yceil = sectors[sprite->sectorno].ceil - player.where.z;
	yfloor = sectors[sprite->sectorno].floor - player.where.z;
	sp.x = sprite->where.x - player.where.x;
	sp.y = sprite->where.y - player.where.y;
	t1.x = sp.x * player.anglesin - sp.y * player.anglecos;
	t1.y = sp.x * player.anglecos + sp.y * player.anglesin;
	if (t1.y <= 0)
		return (-1);
	xscale = hfov / t1.y;
	yscale = vfov / t1.y;
	x1 = SCREEN_WIDTH / 2 - (int)(t1.x * xscale);
	x2 = x1 + sprite->size;
	y1 = SH / 2 - (int)(yaw(yfloor, t1.y, player.yaw) * yscale);
	y2 = SH / 2 - (int)(yaw(yceil, t1.y, player.yaw) * yscale);
	sprite->x = x1;
	sprite->y1 = (y1 + y2) / 2;
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
	while (++i < data.sprite_nbr)
	{
		sprite[i].dist = sqrt(pow(sprite[i].where.x -
		player.where.x, 2) + pow(sprite[i].where.y - player.where.y, 2));
		b->temp = sprite[i].dist / 10;
		sprite[i].size = 250 / b->temp;
		sprite[i].x = 0;
		sprite[i].x_count = 0;
	}
	i = -1;
	while (++i < data.sprite_nbr)
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

t_object	get_sprite_coords(t_data *data, t_object *sprite,
				t_plyr *player, t_sector *sectors, int ytop, int ybottom)
{
	pick_up(data, player, sprite);
	sprite->x = render_sprite(*player, sprite, sectors) - sprite->size / 2;
	sprite->y2 = sprite->y1 + sprite->size;
	sprite->y2 = clamp(sprite->y2, ytop, ybottom);
	if (sprite->x_count < sprite->size && data->x_draw
	> sprite->x && sprite->x > 0 && data->sectqueue[sprite->sectorno]
		<= data->sectqueue[data->now_sect])
	{
		draw_resized_column(data, sprite, data->wind, ytop, ybottom);
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
