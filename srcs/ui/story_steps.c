/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   story_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:05:36 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 02:13:11 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	story_1(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 1)
	{
		rect = (SDL_Rect){260, 580, 30, 35};
		ft_set_string(rect,
			"OLA YO SOY MIGUEL TACO QUESADILLA , TOU VEUX BUYER QUOI KHOYA ?",
				ft_hex_to_rgb(0xFFFF00FF), data);
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Voici Miguel Taco Quesadilla, \
				fils d'un pere Algerien et d'une mere Mexicaine,",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 330, 25, 25};
		ft_set_string(rect, "ayant marre de vendre des tours eiffels au \
			trocadero il est devenu receleur d'arme,",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 350, 25, 25};
		ft_set_string(rect, "tu devrait te procurer une arme aupres de lui",
			ft_hex_to_rgb(WHITE), data);
	}
}

void	story_0and1(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 0 && data->msg_readen == 0)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "1 new message, press 'J' to read",
			ft_hex_to_rgb(WHITE), data);
	}
	if (data->story_step == 0 && data->msg_readen == 1)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Enchanté Carlos Cabrone,  \
		te voila bloqué dans mon monde, si tu veux en sortir \
		il faudra que tu abatte toutes les cibles et ceci avec \
		un nombre limité de balles, bonne chance",
			ft_hex_to_rgb(WHITE), data);
	}
	story_1(data, rect);
}

void	story_2and3(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 2)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Te voila arme jusqu'aux doigts , par contre si tu\
		tes tromper d'arme c'est trop tard", ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 330, 25, 25};
		ft_set_string(rect, "Carlo..euh Miguel est parti manger un taco, pour \
			lancer la partie il faudra que tu appuie sur 'M'",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 350, 25, 25};
		ft_set_string(rect, "si tu veux comprendre les regles demande aux 3 \
			bolosses ou a YujeKok, bonne chance",
				ft_hex_to_rgb(WHITE), data);
	}
	if (data->story_step == 3 || data->story_step == 4)
	{
		rect = (SDL_Rect){400, 0, 60, 60};
		ft_set_string(rect, "TIMER", ft_color_nb_state(0), data);
	}
}
