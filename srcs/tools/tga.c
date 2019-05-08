/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:41:43 by snicolet          #+#    #+#             */
/*   Updated: 2019/05/08 23:20:41 by asamir-k         ###   ########.fr       */
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
	ft_putendl(error);
	return (NULL);
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

unsigned int		*tga_load(const char *filepath, t_tga *specs)
{
	size_t			file_size;
	size_t			pixels_size;
	unsigned int	*pixels;
	char			*file_content;
	t_tga			*header;

	ft_bzero(specs, TGA_SIZE);
	if (!(file_content = ft_readfile(filepath, &file_size)))
		return (load_tga_error("unable to read file\n", NULL));
	if (file_size <= TGA_SIZE)
		return (load_tga_error("invalid file or no content\n", file_content));
	header = (t_tga*)(size_t)file_content;
	if ((header->type != TGA_TYPE_TC_RAW) || (header->depth < 24))
		return (load_tga_error("unsupported file format\n", file_content));
	pixels_size = header->width * header->height * (header->depth >> 3) + 1;
	if ((pixels = malloc(pixels_size)))
	{
		ft_memcpy(pixels, &file_content[TGA_SIZE], pixels_size);
		*specs = *header;
		free(file_content);
		if (specs->depth == 24)
			return (tga_px3((void*)(size_t)pixels, specs));
		return (pixels_to_rgba(pixels, specs->height * specs->width));
	}
	return (load_tga_error("failed to get pixels\n", file_content));
}
