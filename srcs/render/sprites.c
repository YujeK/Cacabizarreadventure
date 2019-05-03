/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:57:44 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/02 01:54:23 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int render_sprite(t_plyr player, t_object *sprite, t_sector *sectors)
{
    t_vector sp;
    t_vector sp2;
    int x1;
    int x2;
    float yceil;
    float yfloor;
    float xscale;
    float yscale;
    float xscale2;
    float yscale2;
    int y1;
    int y2;
    int x;
    int i;
    float dist;
    t_vector t1;
    t_vector t2;
    t_coord p1;
    t_coord p2;
    t_line line;
    static float tdist;

    line.color = 0xff0000;
    yceil = sectors[sprite->sectorno].ceil - player.where.z;
    yfloor = sectors[sprite->sectorno].floor - player.where.z;
    sp.x = sprite->where.x  - player.where.x;
    sp.y = sprite->where.y - player.where.y;
    sp2.x = sprite->where.x + 1 - player.where.x;
    sp2.y = sprite->where.y - player.where.y;
    t1.x = sp.x * player.anglesin - sp.y * player.anglecos;
    t1.y = sp.x * player.anglecos + sp.y * player.anglesin;
    t2.x = sp2.x * player.anglesin - sp2.y * player.anglecos;
    t2.y = sp2.y * player.anglecos + sp2.y * player.anglesin;
    if (t1.y <= 0 && t2.y <= 0)
        return (-1);
    xscale = hfov / t1.y;
    yscale = vfov / t1.y;
    xscale2 = hfov / t2.y;
    yscale2 = vfov / t2.y;
    x1 = SCREEN_WIDTH / 2 - (int)(t1.x * xscale);
    x2 = x1 + sprite->size;
    y1 = SCREEN_HEIGHT / 2 - (int)(yaw(yfloor, t1.y, player.yaw) * yscale);
    y2 = SCREEN_HEIGHT / 2 - (int)(yaw(yceil, t1.y, player.yaw) * yscale);
    sprite->x = x1;
    sprite->y1 = (y1 + y2) / 2;
    return (sprite->x);
}
