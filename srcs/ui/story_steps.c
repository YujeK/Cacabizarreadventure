/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   story_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:05:36 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 06:19:33 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	story_1(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 1)
	{
		rect = (SDL_Rect){250, 580, 30, 35};
		ft_set_string(rect,
			"OLA YO SOY MIGUEL TACO QUESADILLA , TOU VEUX BUYER QUOI KHOYA ?",
				ft_hex_to_rgb(0xFFFF00FF), data);
		rect = (SDL_Rect){60, 420, 25, 25};
		ft_set_string(rect, "Voici Miguel Taco Quesadilla, \
			\fils d'un pere Algerien et d'une mere Mexicaine,",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 440, 25, 25};
		ft_set_string(rect, "ayant marre de vendre des tours eiffels \
			au trocadero il est devenu receleur d'arme,",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 460, 25, 25};
		ft_set_string(rect, "procure toi une arme aupres de lui",
			ft_hex_to_rgb(WHITE), data);
	}
}

void	story_0and1(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 0 && data->msg_readen == 0)
	{
		rect = (SDL_Rect){60, 420, 25, 25};
		ft_set_string(rect, "1 new message, press 'J' to read",
			ft_hex_to_rgb(WHITE), data);
	}
	if (data->story_step == 0 && data->msg_readen == 1)
	{
		rect = (SDL_Rect){60, 410, 25, 25};
		ft_set_string(rect, "Je t'envoi ce message afin te prevenir \
		d'un terrrrrrrrible danger", ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 440, 25, 25};
		ft_set_string(rect, "tu va devoir redoubler d'effort pour detruire \
			ces cibles immobiles et inoffensive , press 'tab' to continue",
			ft_hex_to_rgb(WHITE), data);
	}
	story_1(data, rect);
}

void	story_2and3(t_data *data, SDL_Rect rect)
{
	if (data->story_step == 2)
	{
		rect = (SDL_Rect){60, 410, 25, 25};
		ft_set_string(rect, "te voici maintenant equipe pour commencer \
			ta mission presse 'M'", ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 430, 25, 25};
		ft_set_string(rect, "Cependant attention, ton nombre de \
			balles est limite et",
				ft_hex_to_rgb(WHITE), data);
		rect = (SDL_Rect){60, 450, 25, 25};
		ft_set_string(rect, "la partie sera perdue si tu n'en \
			a plus, Bonne Chance",
				ft_hex_to_rgb(WHITE), data);
	}
	if (data->story_step == 3 || data->story_step == 4)
	{
		rect = (SDL_Rect){400, 0, 60, 60};
		ft_set_string(rect, "TIMER", ft_color_nb_state(0), data);
	}
}
