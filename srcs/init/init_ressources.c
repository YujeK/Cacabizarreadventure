/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:50:50 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:38:37 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_img2(t_data *data)
{
	if (!(data->handoff.img = tga_load(
		"ressources/weapon/handoff.tga", &data->handoff.specs)))
		ft_error_exit("I couldnt load tga handoff");
	data->handoff.res_img = resize(data->handoff.img, data->handoff.specs, 800);
	if (!(data->handon.img = tga_load(
		"ressources/weapon/handon.tga", &data->handon.specs)))
		ft_error_exit("I couldnt load tga handon");
	data->handon.res_img = resize(data->handon.img, data->handon.specs, 800);
	if (!(data->akimbon.img = tga_load(
		"ressources/weapon/akimbon.tga", &data->akimbon.specs)))
		ft_error_exit("I couldnt load tga akimbon");
	data->akimbon.res_img = resize(data->akimbon.img
	, data->akimbon.specs, 1050);
	if (!(data->akimboff.img = tga_load(
		"ressources/weapon/akimboff.tga", &data->akimboff.specs)))
		ft_error_exit("I couldnt load tga akimboff");
	data->akimboff.res_img = resize(data->akimboff.img
	, data->akimboff.specs, 1050);
	if (!(data->invon.img = tga_load(
		"ressources/inventory/invon.tga", &data->invon.specs)))
		ft_error_exit("I couldnt load tga invon");
	data->invon.res_img = resize(data->invon.img, data->invon.specs, 600);
	if (!(data->invoff.img = tga_load(
		"ressources/inventory/invoff.tga", &data->invoff.specs)))
		ft_error_exit("I couldnt load tga invoff");
}

void	init_sound(t_data *data)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		ft_error_exit("I couldnt OpenAudio");
	if (!(data->maintheme = Mix_LoadMUS("ressources/sounds/maintheme.wav")))
		ft_error_exit("I couldnt load wav maintheme");
	if (!(data->menutheme = Mix_LoadMUS("ressources/sounds/menumusic.wav")))
		ft_error_exit("I couldnt load wav menumusic");
	if (!(data->zawarudotheme = Mix_LoadMUS(
		"ressources/sounds/zawarudotheme.wav")))
		ft_error_exit("I couldnt load wav menumusic");
	if (!(data->stand_warudo = Mix_LoadWAV("RESSOURCES/sounds/zawarudo.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect");
	if (!(data->tp_sound = Mix_LoadWAV("RESSOURCES/sounds/tp.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect tp");
	if (!(data->eye_sound = Mix_LoadWAV("RESSOURCES/sounds/eyesofthedead.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect eyes");
	if (!(data->ak = Mix_LoadWAV("RESSOURCES/sounds/ak.wav")))
		ft_error_exit("Wolf3d: Unable to load sound ak");
	if (!(data->target_hit = Mix_LoadWAV("RESSOURCES/sounds/target_hit.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect eyes");
}

void	init_sound2(t_data *data)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		ft_error_exit("I couldnt OpenAudio");
	if (!(data->maintheme = Mix_LoadMUS("ressources/sounds/maintheme.wav")))
		ft_error_exit("I couldnt load wav maintheme");
	if (!(data->menutheme = Mix_LoadMUS("ressources/sounds/menumusic.wav")))
		ft_error_exit("I couldnt load wav menumusic");
	if (!(data->zawarudotheme = Mix_LoadMUS(
		"ressources/sounds/zawarudotheme.wav")))
		ft_error_exit("I couldnt load wav menumusic");
	if (!(data->stand_warudo = Mix_LoadWAV("RESSOURCES/sounds/zawarudo.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect");
	if (!(data->tp_sound = Mix_LoadWAV("RESSOURCES/sounds/tp.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect tp");
	if (!(data->eye_sound = Mix_LoadWAV("RESSOURCES/sounds/eyesofthedead.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect eyes");
	if (!(data->ak = Mix_LoadWAV("RESSOURCES/sounds/ak.wav")))
		ft_error_exit("Wolf3d: Unable to load sound ak");
	if (!(data->target_hit = Mix_LoadWAV("RESSOURCES/sounds/target_hit.wav")))
		ft_error_exit("Wolf3d: Unable to load sound effect eyes");
	init_img2(data);
}

void	init_img(t_data *data)
{
	init_sound2(data);
	data->invoff.res_img = resize(data->invoff.img, data->invoff.specs, 100);
	if (!(data->menu.img = tga_load(
		"ressources/inventory/cacamenu.tga", &data->menu.specs)))
		ft_error_exit("I couldnt load tga widon");
	data->menu.res_img = resize(data->menu.img, data->menu.specs, 1001);
	if (!(data->menustart.img = tga_load(
		"ressources/inventory/cacamenustarter.tga", &data->menustart.specs)))
		ft_error_exit("I couldnt load tga menu");
	data->menustart.res_img = resize(data->menustart.img
	, data->menustart.specs, 1001);
	if (!(data->rbw.img = tga_load(
		"ressources/enemies/rbww.tga", &data->rbw.specs)))
		ft_error_exit("I couldnt load tga rbw");
	if (!(data->pepo.img = tga_load(
		"ressources/enemies/popow.tga", &data->pepo.specs)))
		ft_error_exit("I couldnt load tga popow");
	if (!(data->widoff.img = tga_load(
		"ressources/weapon/widoff.tga", &data->widoff.specs)))
		ft_error_exit("I couldnt load tga widoff");
	data->widoff.res_img = resize(data->widoff.img, data->widoff.specs, 800);
	if (!(data->widon.img = tga_load(
		"ressources/weapon/widon.tga", &data->widon.specs)))
		ft_error_exit("I couldnt load tga widon");
	data->widon.res_img = resize(data->widon.img, data->widon.specs, 800);
}
