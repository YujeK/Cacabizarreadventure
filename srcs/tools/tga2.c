/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzgao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:56:01 by ybouzgao          #+#    #+#             */
/*   Updated: 2019/05/07 05:56:42 by ybouzgao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void				tga_display(const t_tga *specs)
{
	printf("id: %hhd\ncolor_map: %hhd\ntype: %hhd\nfirst_entry_index: %hu\n"
			"color_map_len: %hu\nbpp: %hhu\nx_offset: %hu\ny_offset: %hu\n"
			"width: %hu\nheight: %hu\ndepth: %hhu\ndescriptor: %hhu\n",
			specs->id, specs->color_map, specs->type, specs->first_entry_index,
			specs->color_map_len, specs->bpp, specs->x_offset, specs->y_offset,
			specs->width, specs->height, specs->depth, specs->descriptor);
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
