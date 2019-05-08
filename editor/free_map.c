/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 23:22:47 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:47:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

void	free_map(t_map map)
{
	int i;

	free(map.edges);
	free(map.vertex);
	i = -1;
	while (++i < map.sector_length)
		free(map.sector[i].edges);
	free(map.sector);
}
