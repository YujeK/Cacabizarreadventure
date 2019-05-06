/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 23:03:06 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/06 02:49:53 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Color		ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

void			ft_set_string(SDL_Rect rect, char *text,
		SDL_Color color, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	if (!(surface = TTF_RenderText_Blended(data->font, text, color)))
		ft_error_exit("couldnt load font", data);
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	if (SDL_BlitScaled(surface, 0, data->wind.screen, &sdl_rect) == -1)
		ft_error_exit("couldnt put string", data);
	SDL_FreeSurface(surface);
}

void			ft_set_nbrstring(int value, SDL_Rect rect,
					SDL_Color color, t_data *data)
{
	char	*str;

	if (!(str = ft_itoa(value)))
		ft_error_exit("couldnt put nbrstring", data);
	ft_set_string(rect, str, color, data);
	ft_strdel(&str);
}

SDL_Color		ft_color_nb_state(int nb)
{
	if (nb >= 0 && nb < 25)
		return (ft_hex_to_rgb(0xFF0000FF));
	if (nb >= 25 && nb < 50)
		return (ft_hex_to_rgb(0xFFA500FF));
	if (nb >= 50 && nb < 75)
		return (ft_hex_to_rgb(0xFFFF00FF));
	if (nb >= 75 && nb <= 100)
		return (ft_hex_to_rgb(0x32CD32FF));
	return (ft_hex_to_rgb(0xFFFF00FF));
}

void			ft_start_game(t_data *data)
{
	SDL_Rect		rect;

		// setting timer //
	if (data->timer_start && data->zawarudo == 0)
	{
		rect = (SDL_Rect){431, 50, 60, 60};
		data->timer = time(0) - data->timer_start;
		ft_set_nbrstring(data->timer, rect, ft_color_nb_state(1), data);
	}
	if (data->zawarudo == 1 && data->timer_start)
	{
		rect = (SDL_Rect){431, 50, 60, 60};
		ft_set_nbrstring(data->timer, rect, ft_color_nb_state(1), data);
	}
	if (data->story_step == 0 && data->msg_readen == 0)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "1 new message, press 'J' to read", ft_hex_to_rgb(0xFF1493FF), data);
	}
	if (data->story_step == 0 && data->msg_readen == 1)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Salut, pour commencer appel le mysterieux receleur d'armes en appuyant sur 'TAB'", ft_hex_to_rgb(0xFF1493), data);
	}
	if (data->story_step == 1)
	{
		rect = (SDL_Rect){260, 580, 30, 35};
		ft_set_string(rect, "OLA YO SOY MIGUEL TACO QUESADILLA , TOU VEUX BUYER QUOI KHOYA ?", ft_hex_to_rgb(0xFFFF00FF), data);
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Voici Miguel Taco Quesadilla, fils d'un pere Algerien et d'une mere Mexicaine,", ft_hex_to_rgb(0xFF1493FF), data);
		rect = (SDL_Rect){60, 330, 25, 25};
		ft_set_string(rect, "ayant marre de vendre des tours eiffels au trocadero il est devenu receleur d'arme,", ft_hex_to_rgb(0xFF1493FF), data);
		rect = (SDL_Rect){60, 350, 25, 25};
		ft_set_string(rect, "tu devrait te procurer une arme aupres de lui", ft_hex_to_rgb(0xFF1493FF), data);
	}
	if(data->story_step == 2)
	{
		rect = (SDL_Rect){60, 310, 25, 25};
		ft_set_string(rect, "Te voila arme jusqu'aux doigts , par contre si tu tes tromper d'arme c'est trop tard", ft_hex_to_rgb(0xFF1493FF), data);
		rect = (SDL_Rect){60, 330, 25, 25};
		ft_set_string(rect, "Carlo..euh Miguel est parti manger un taco, pour lancer la partie il faudra que tu appuie sur 'M'", ft_hex_to_rgb(0xFF1493FF), data);
		rect = (SDL_Rect){60, 350, 25, 25};
		ft_set_string(rect, "si tu veux comprendre les regles demande aux 3 bolosses ou a YujeKok, bonne chance", ft_hex_to_rgb(0xFF1493FF), data);
	}
	if (data->story_step == 3)
	{
		rect = (SDL_Rect){400, 0, 60, 60};
		ft_set_string(rect, "TIMER", ft_color_nb_state(0), data);
	}
}
void			ft_value_display(t_data *data)
{
	SDL_Rect		rect;
	if (data->which_weapon != 0)
	{
		rect = (SDL_Rect){0, 80, 60, 30};
		ft_set_string(rect, "AMMO", ft_color_nb_state(data->weapon_ammo), data);
		rect = (SDL_Rect){0, 120, 60, 30};
		ft_set_nbrstring(data->weapon_ammo, rect, ft_color_nb_state(data->weapon_ammo), data);
		rect = (SDL_Rect){200, 0, 60, 60};
		ft_set_string(rect, "SCORE", ft_color_nb_state(data->score), data);
		rect = (SDL_Rect){240, 50, 60, 60};
		ft_set_nbrstring(data->score, rect, ft_color_nb_state(data->score), data);
	}
	ft_crosshair(data);
	ft_start_game(data);
}
