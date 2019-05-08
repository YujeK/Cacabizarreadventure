/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:53:18 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 04:27:17 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_error_exit(char *str, t_data *data)
{
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_exit(t_data *data)
{
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
