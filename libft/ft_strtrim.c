/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:20:08 by smerelo           #+#    #+#             */
/*   Updated: 2019/05/08 07:23:12 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s)
{
	char			*ss;
	int				i;
	int				j;
	int				k;

	if (s)
	{
		i = 0;
		j = ft_strlen(s) - 1;
		{
			while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
				i++;
			k = -1;
			if ((ss = (char*)malloc(sizeof(ss) * (j - i + 1))) == NULL)
				return (NULL);
			while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
				j--;
			i--;
			while (i <= j)
				ss[++k] = s[++i];
			ss[k] = '\0';
			return (ss);
		}
	}
	return (NULL);
}
