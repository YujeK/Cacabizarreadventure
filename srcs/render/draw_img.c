/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:45:44 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 17:23:24 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_weapon(t_data *data)
{
	t_coord pos;

	if (data->weapon_state == 1)
	{
		if (data->which_weapon == 2)
		{
			pos = (t_coord){410 + data->wpn_y, 220 + data->wpn_x};
			display_img(pos, data->wind, 800, data->widon.res_img);
		}
		else if (data->which_weapon == 1)
		{
			pos = (t_coord){410 + data->wpn_y, 210 + data->wpn_x};
			display_img(pos, data->wind, 800, data->handon.res_img);
		}
		else if (data->which_weapon == 3)
		{
			pos = (t_coord){-25 + data->wpn_y, 300 + data->wpn_x};
			display_img(pos, data->wind, 1050, data->akimbon.res_img);
		}
	}
}

void	draw_items(t_data *data)
{
	t_coord pos;

	if (data->inventory_state == 0)
	{
		if (data->weapon_state == 0)
		{
			pos = (t_coord){370 + data->wpn_y, 380 + data->wpn_x};
			if (data->which_weapon == 2)
			{
				display_img(pos, data->wind, 800, data->widoff.res_img);
			}
			else if (data->which_weapon == 1)
				display_img(pos, data->wind, 800, data->handoff.res_img);
			else if (data->which_weapon == 3)
			{
				pos = (t_coord){-25 + data->wpn_y, 300 + data->wpn_x};
				display_img(pos, data->wind, 1050, data->akimboff.res_img);
			}
		}
		draw_weapon(data);
	}
}

void	draw_inventory(t_data *data)
{
	t_coord pos;

	if (data->inventory_state == 1)
	{
		pos = (t_coord){-15, 400};
		display_img(pos, data->wind, 600, data->invon.res_img);
	}
	if (data->story_step != 3)
	{
		pos = (t_coord){-15, 400};
		display_img(pos, data->wind, 100, data->invoff.res_img);
	}
}
