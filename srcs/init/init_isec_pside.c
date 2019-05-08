/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_isec_pside.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:38:58 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 02:25:00 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_inter(t_b *b, t_inter *ic)
{
	ic->x0 = b->px;
	ic->y0 = b->py;
	ic->x1 = b->px + b->dx;
	ic->y1 = b->py + b->dy;
	ic->x2 = b->vert[b->s + 0].x;
	ic->y2 = b->vert[b->s + 0].y;
	ic->x3 = b->vert[b->s + 1].x;
	ic->y3 = b->vert[b->s + 1].y;
}

void	init_pointside(t_b *b, t_inter *ips)
{
	ips->px = b->px + b->dx;
	ips->py = b->py + b->dy;
	ips->x0 = b->vert[b->s + 0].x;
	ips->y0 = b->vert[b->s + 0].y;
	ips->x1 = b->vert[b->s + 1].x;
	ips->y1 = b->vert[b->s + 1].y;
}

void	init_inter2(t_b *b, t_inter *ic, t_vector *vert, int s)
{
	ic->x0 = b->px;
	ic->y0 = b->py;
	ic->x1 = b->px + b->dx;
	ic->y1 = b->py + b->dy;
	ic->x2 = vert[s].x;
	ic->y2 = vert[s].y;
	ic->x3 = vert[s + 1].x;
	ic->y3 = vert[s + 1].y;
}

void	init_pointside2(t_b *b, t_inter *ips, int s, t_vector *vert)
{
	ips->px = b->px + b->dx;
	ips->py = b->py + b->dy;
	ips->x0 = vert[s].x;
	ips->y0 = vert[s].y;
	ips->x1 = vert[s + 1].x;
	ips->y1 = vert[s + 1].y;
}
