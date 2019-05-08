/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recycle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:36:54 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/07 14:40:08 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	recycle_vline3(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->ytop[bas->x];
	rv->y2 = bas->cya - 1;
	rv->top = 0x111111;
	rv->middle = 0x3f3f3f;
	rv->bottom = 0x111111;
}

void	recycle_vline4(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->cyb + 1;
	rv->y2 = bas->ybottom[bas->x];
	rv->top = 0x992c42;
	rv->middle = 0x6b3636;
	rv->bottom = 0x992c42;
}

void	recycle_vline(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->cya;
	rv->y2 = bas->cnya - 1;
	rv->top = 0;
	rv->middle = bas->x == bas->x1 || bas->x == bas->x2 ? 0 : bas->r1;
	rv->bottom = 0;
}

void	recycle_vline2(t_bas *bas, t_rv *rv)
{
	rv->x = bas->x;
	rv->y1 = bas->cnyb + 1;
	rv->y2 = bas->cyb;
	rv->top = 0;
	rv->middle = bas->x == bas->x1 || bas->x == bas->x2 ? 0 : bas->r2;
	rv->bottom = 0;
}
