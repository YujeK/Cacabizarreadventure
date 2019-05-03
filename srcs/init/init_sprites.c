/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 04:37:02 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/03 01:58:15 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_sprites(t_data *data)
{
	int i;

	data->sprite_nbr = 2;
	if((data->sprite = (t_object*)malloc(sizeof(t_object) * data->sprite_nbr)) == NULL)
		ft_error_exit("quand je essaye de mallocer les sprites car le putain de ashkan ne se rien faire ta mere", data);
	i = 0;
	while(i < data->sprite_nbr)
	{
		data->sprite[i].where.x = 2;
		data->sprite[i].where.y = 7;
		data->sprite[i].sectorno = 0;
		i++;
	}
}
