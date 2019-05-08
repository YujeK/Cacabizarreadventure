/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_boxed_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 01:56:55 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 23:05:46 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int	nested_extrude(t_map map)
{
	if (in_sector(map, map.vertex[map.vertex_length - 1]) != -1)
		return (1);
	if (in_sector(map, map.vertex[map.vertex_length - 2]) != -1)
		return (1);
	return (0);
}
