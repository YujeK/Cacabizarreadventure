/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:22:54 by asamir-k          #+#    #+#             */
/*   Updated: 2019/04/29 18:42:22 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_error_exit(char *str, t_data *data) // how to : protect an error case with this , just call it, second param allows you to write the error message !
{
/* 	if (data->wind.screen)
		SDL_FreeSurface(data->wind.screen);
	ft_free_texture(data);
	ft_free_items(data);
	if (data->font)
		TTF_CloseFont(data->font);
	if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer);
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window); */
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_exit(t_data *data)
{
	/*
	if (data->surface)                   need to free the screen surface
		SDL_FreeSurface(data->surface);
	*/
	//ft_destroy_texture(data); -> free all tex and items !!!!!
	//ft_destroy_items(data);
	//if (data->font)
		//TTF_CloseFont(data->font);
/*	if (data->sdl.renderer)
		SDL_DestroyRenderer(data->sdl.renderer); to free the sdl rendering
	if (data->sdl.window)
		SDL_DestroyWindow(data->sdl.window);
*/
	TTF_Quit(); // font quit
	Mix_Quit(); // sound mixer quit
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
