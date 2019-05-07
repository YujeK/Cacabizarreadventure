/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:16:46 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/07 15:21:21 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	*pixels_to_rgba(unsigned int *pixels, size_t n)
{
	while (n--)
	{
		pixels[n] = TGA_L(pixels[n]);
	}
	return (pixels);
}
