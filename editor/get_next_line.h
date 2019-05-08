/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:13:32 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/02 05:13:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include "libft/libft.h"
# define BUFF_SIZE 2000
# include <fcntl.h>
# include <unistd.h>

int	get_next_line(int fd, char **line);

#endif
