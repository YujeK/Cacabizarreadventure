/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:50:50 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/03 05:00:04 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_img(t_data *data)
{
	// overwatch rifle init
	if (!(data->widoff.img = tga_load("ressources/weapon/widoff.tga", &data->widoff.specs)))
		ft_error_exit("I couldnt load tga widoff", data);
	data->widoff.res_img = resize(data->widoff.img, data->widoff.specs, 800);
	if (!(data->widon.img = tga_load("ressources/weapon/widon.tga", &data->widon.specs)))
		ft_error_exit("I couldnt load tga widon", data);
	data->widon.res_img = resize(data->widon.img, data->widon.specs, 800);
	if (!(data->handoff.img = tga_load("ressources/weapon/handoff.tga", &data->handoff.specs)))
		ft_error_exit("I couldnt load tga handoff", data);
	data->handoff.res_img= resize(data->handoff.img, data->handoff.specs, 800);
	if (!(data->handon.img = tga_load("ressources/weapon/handon.tga", &data->handon.specs)))
		ft_error_exit("I couldnt load tga handon", data);
	data->handon.res_img = resize(data->handon.img, data->handon.specs, 800);
	if (!(data->akimbon.img = tga_load("ressources/weapon/akimbon.tga", &data->akimbon.specs)))
		ft_error_exit("I couldnt load tga akimbon", data);
	data->akimbon.res_img = resize(data->akimbon.img, data->akimbon.specs, 1050);
	if (!(data->akimboff.img = tga_load("ressources/weapon/akimboff.tga", &data->akimboff.specs)))
		ft_error_exit("I couldnt load tga akimboff", data);
	data->akimboff.res_img = resize(data->akimboff.img, data->akimboff.specs, 1050);
	// inventory init
	if (!(data->invon.img = tga_load("ressources/inventory/invon.tga", &data->invon.specs)))
		ft_error_exit("I couldnt load tga invon", data);
	data->invon.res_img = resize(data->invon.img, data->invon.specs, 600);
	if (!(data->invoff.img = tga_load("ressources/inventory/invoff.tga", &data->invoff.specs)))
		ft_error_exit("I couldnt load tga invoff", data);
	printf("%d\n", data->invoff.specs.width);
	data->invoff.res_img = resize(data->invoff.img, data->invoff.specs, 100);
	if (!(data->sprite[0].img = tga_load("ressources/inventory/toiletashkan.tga", &data->sprite[0].specs)))
		ft_error_exit("I couldnt load tga toiletashkan", data);
	//texture init
/* 	data->wall_tex = tga_load("ressources/lava.tga", &specs);
	data->res_wall_tex = resize(data->wall_tex, specs, 600);
 */
	// sound
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		ft_error_exit("I couldnt OpenAudio", data);
	if (!(data->maintheme = Mix_LoadMUS("ressources/sounds/maintheme.wav")))
		ft_error_exit("I couldnt load wav maintheme", data);
	if (!(data->menutheme = Mix_LoadMUS("ressources/sounds/menumusic.wav")))
		ft_error_exit("I couldnt load wav menumusic", data);
	if (!(data->zawarudotheme = Mix_LoadMUS("ressources/sounds/zawarudotheme.wav")))
		ft_error_exit("I couldnt load wav menumusic", data);
	if (!(data->stand_warudo = Mix_LoadWAV("RESSOURCES/sounds/zawarudo.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect", data);

}
