/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setstring_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:01:30 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:41:11 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_set_string(SDL_Rect rect, char *text,
					SDL_Color color, t_data *data)
{
	SDL_Rect			sdl_rect;
	SDL_Surface			*surface;

	sdl_rect = (SDL_Rect){rect.x, rect.y, rect.w, rect.h};
	if (!(surface = TTF_RenderText_Blended(data->font, text, color)))
		ft_error_exit("couldnt load font");
	sdl_rect.w = (sdl_rect.h * surface->w) / surface->h;
	if (SDL_BlitScaled(surface, 0, data->wind.screen, &sdl_rect) == -1)
		ft_error_exit("couldnt put string");
	SDL_FreeSurface(surface);
}

void			ft_set_nbrstring(int value, SDL_Rect rect,
					SDL_Color color, t_data *data)
{
	char	*str;

	if (!(str = ft_itoa(value)))
		ft_error_exit("couldnt put nbrstring");
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
