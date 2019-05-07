/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:41:43 by snicolet          #+#    #+#             */
/*   Updated: 2019/05/07 05:58:18 by ybouzgao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static size_t		ft_filesize(const char *filepath)
{
	struct stat		st;

	if (stat(filepath, &st) != 0)
		return (0);
	return ((size_t)st.st_size);
}

char				*ft_readfile(const char *filepath, size_t *usize)
{
	const size_t	size = ft_filesize(filepath);
	ssize_t			ret;
	int				fd;
	char			*data;

	data = NULL;
	if ((!size) || (!(data = malloc(sizeof(char) * (size)))) ||
			(!(fd = open(filepath, O_RDONLY))))
	{
		if (usize)
			*usize = 0;
		if (data)
			free(data);
		return (NULL);
	}
	ret = read(fd, data, size);
	data[ret] = '\0';
	close(fd);
	if (usize)
		*usize = size;
	return (data);
}

static void			*load_tga_error(const char *error, void *file_content)
{
	if (file_content)
		free(file_content);
	printf("error: %s\n", error);
	return (NULL);
}

static unsigned int	*pixels_to_rgba(unsigned int *pixels, size_t n)
{
	while (n--)
		pixels[n] = TGA_L(pixels[n]);
	return (pixels);
}

static unsigned int	*tga_px3(unsigned char *pixels, const t_tga *specs)
{
	const size_t		pixels_total = specs->width * specs->height;
	const size_t		size = pixels_total * 3;
	size_t				p;
	unsigned int		*buffer;
	unsigned int		*px;

	if (!(buffer = malloc(pixels_total * 4)))
		return (load_tga_error("failed to alloc the second stage", pixels));
	px = buffer;
	p = 0;
	while (p < size)
	{
		*(px++) = ((unsigned int)0xff << 24) |
			((unsigned int)pixels[p + 2]) |
			((unsigned int)pixels[p + 1] << 8) |
			((unsigned int)pixels[p] << 16);
		p += 3;
	}
	free(pixels);
	return (buffer);
}
