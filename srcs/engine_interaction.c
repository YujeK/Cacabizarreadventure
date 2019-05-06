/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 09:15:20 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/06 09:22:53 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void	move_interaction(t_b *b)
{
	if (b->player.moving)
	{
		b->px = b->player.where.x;
		b->py = b->player.where.y;
		b->dx = b->player.velocity.x;
		b->dy = b->player.velocity.y;
		b->sect = b->sectors[b->player.sector];
		b->vert = b->sect.vertex;
		b->s = -1;
		while (++b->s < b->sect.npoints)
		{
			if (IntersectBox(b->px, b->py, b->px + b->dx, b->py + b->dy, b->vert[b->s + 0].x, b->vert[b->s + 0].y, b->vert[b->s + 1].x, b->vert[b->s + 1].y) && pointside(b->px + b->dx, b->py + b->dy, b->vert[b->s + 0].x, b->vert[b->s + 0].y, b->vert[b->s + 1].x, b->vert[b->s + 1].y) < 0)
			{
				b->hole_low = b->sect.neighbors[b->s] < 0 ? 9e9 : max(b->sect.floor, b->sectors[b->sect.neighbors[b->s]].floor);
				b->hole_high = b->sect.neighbors[b->s] < 0 ? -9e9 : min(b->sect.ceil, b->sectors[b->sect.neighbors[b->s]].ceil);
				if (b->hole_high < b->player.where.z + HeadMargin || b->hole_low > b->player.where.z - b->eyeheight + KneeHeight)
				{
					b->xd = b->vert[b->s + 1].x - b->vert[b->s + 0].x, b->yd = b->vert[b->s + 1].y - b->vert[b->s + 0].y;
					b->dx = b->xd * (b->dx * b->xd + b->yd * b->dy) / (b->xd * b->xd + b->yd * b->yd);
					b->dy = b->yd * (b->dx * b->xd + b->yd * b->dy) / (b->xd * b->xd + b->yd * b->yd);
					b->player.moving = 0;
				}
			}
		}
		b->player = Move_player(b->dx, b->dy, b->player, b->sectors, b->NumSectors);
		b->player.falling = 1;
	}
}

void	engine_interaction(t_b *b)
{
	if (b->player.falling)
	{
		b->player.velocity.z -= 0.02f;
		b->nextz = b->player.where.z + b->player.velocity.z;
		if (b->player.velocity.z < 0 && b->nextz < b->sectors[b->player.sector].floor + b->eyeheight)
		{
			b->player.where.z = b->sectors[b->player.sector].floor + b->eyeheight;
			b->player.velocity.z = 0;
			b->player.falling = 0;
			b->player.ground = 1;
		}
		else if (b->player.velocity.z > 0 && b->nextz > b->sectors[b->player.sector].ceil)
		{
			b->player.velocity.z = 0;
			b->player.falling = 1;
		}
		if (b->player.falling)
		{
			b->player.where.z += b->player.velocity.z;
			b->player.moving = 1;
		}
	}
	move_interaction(b);
}
