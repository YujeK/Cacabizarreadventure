/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:19:45 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 07:22:47 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbw(char *s, char c)
{
	int i;
	int sym;
	int count;

	i = 0;
	sym = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			sym = 1;
			i++;
		}
		while (s[i] == c && s[i])
		{
			count += sym;
			sym = 0;
			i++;
		}
	}
	return (count + 2);
}

static int	nbc(char *s, int i, char c)
{
	int count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count + 1);
}

char		**ft_strsplit(char *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	s = ft_strtrim_2(s, c);
	if (!s || !(res = malloc(sizeof(char*) * nbw((char*)s, c))))
		return (NULL);
	while (s[i])
	{
		k = 0;
		if (!(res[j] = malloc(sizeof(c) * nbc((char*)s, i, c))))
			return (NULL);
		while (s[i] != c && s[i])
			res[j][k++] = s[i++];
		while (s[i] == c && s[i])
			i++;
		res[j++][k] = '\0';
	}
	res[j] = NULL;
	if (s)
		ft_strdel(&s);
	return (res);
}
