/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:45:44 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/04 00:48:18 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void	draw_items(t_data *data)
{
	if (data->which_weapon == 2)
	{
		if (data->weapon_state == 0 && data->inventory_state == 0)
			display_img(370 + data->wpn_y, 380 + data->wpn_x, data->wind, 800, data->widoff.res_img);
		else if (data->weapon_state == 1 && data->inventory_state == 0)
			display_img(410 + data->wpn_y, 220 + data->wpn_x, data->wind, 800, data->widon.res_img);
	}
	else if (data->which_weapon == 1 && data->inventory_state == 0)
	{
		if (data->weapon_state == 0 && data->inventory_state == 0)
			display_img(370 + data->wpn_y, 380 + data->wpn_x, data->wind, 800, data->handoff.res_img);
		else if (data->weapon_state == 1)
			display_img(410 + data->wpn_y, 210 + data->wpn_x, data->wind, 800, data->handon.res_img);
	}
	else if (data->which_weapon == 3 && data->inventory_state == 0)
	{
		if (data->weapon_state == 0 && data->inventory_state == 0)
			display_img(-25 + data->wpn_y, 300 + data->wpn_x, data->wind, 1050, data->akimboff.res_img);
		else if (data->weapon_state == 1 && data->inventory_state == 0)
			display_img(-25 + data->wpn_y, 300 + data->wpn_x, data->wind, 1050, data->akimbon.res_img);
	}
}

void	draw_inventory(t_data *data)
{
	if (data->inventory_state == 1)
		display_img(-15, 400, data->wind, 600, data->invon.res_img);
	if (data->story_step != 4)
		display_img(-15, 290, data->wind, 100, data->invoff.res_img);
}
