/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:53:18 by asamir-k          #+#    #+#             */
/*   Updated: 2019/04/20 14:21:08 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void	ft_free_texture(t_data *data) function to free wall textures if quit
{
	if (data->tex.north)
		SDL_FreeSurface(data->tex.north);
}
*/

/*void	ft_free_items(t_data *data) function to free inventory textures if quit
{
	if (data->tex.weapon_exemple)
		SDL_FreeSurface(data->tex.weapon_exemple);
}*/

void	ft_error_exit(char *str, t_data *data) // how to : protect an error case with this , just call it, second param allows you to write the error message !
{
//	if (data->surface)
//		SDL_FreeSurface(data->surface);
//	ft_free_texture(data);
//	ft_free_items(data);
	if (data->font)
		TTF_CloseFont(data->font);
	/*if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer);
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window);
        */
	TTF_Quit();
	//Mix_Quit();
	SDL_Quit();
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_exit(t_data *data)
{
	/*
	if (data->surface)                   need to free the screen surface
		SDL_FreeSurface(data->surface);
	//ft_free_texture(data);
	//ft_free_items(data);
	if (data->font)
		TTF_CloseFont(data->font);
	if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer); to free the sdl rendering
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window);

	TTF_Quit();
	//Mix_Quit(); <- quit sdl mixer (sound)
	SDL_Quit();
	exit(EXIT_SUCCESS);
}*/
