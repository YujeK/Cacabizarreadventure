/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:18:32 by snicolet          #+#    #+#             */
/*   Updated: 2019/05/08 07:16:29 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H
# define TGA_TYPE_TC_RAW		2

# define TGA_LR(x)				((x & 0xff000000) >> 8)
# define TGA_LG(x)				((x & 0x00ff0000) >> 8)
# define TGA_LB(x)				((x & 0x0000ff00) >> 8)
# define TGA_LA(x)				((x & 0x000000ff) << 24)
# define TGA_L(x)				(TGA_LR(x) | TGA_LG(x) | TGA_LB(x) | TGA_LA(x))

# define TGA_SR(x)				((x & 0xff000000) >> 24)
# define TGA_SG(x)				((x & 0x00ff0000) >> 8)
# define TGA_SB(x)				((x & 0x0000ff00) << 8)
# define TGA_SA(x)				((x & 0x000000ff) << 24)
# define TGA_S(x)				(TGA_SR(x) | TGA_SG(x) | TGA_SB(x) | TGA_SA(x))

# pragma pack(push, 1)

typedef struct					s_tga
{
	char						id;
	char						color_map;
	char						type;
	unsigned short				first_entry_index;
	unsigned short				color_map_len;
	unsigned char				bpp;
	unsigned short				x_offset;
	unsigned short				y_offset;
	unsigned short				width;
	unsigned short				height;
	unsigned char				depth;
	unsigned char				descriptor;
	char						drop[3];
}								t_tga;

# pragma pack(pop)

# define TGA_SIZE				sizeof(t_tga)

unsigned int					*tga_load(const char *filepath, t_tga *specs);
int								tga_save(const char *filepath,
								const t_tga *specs, const unsigned int *pixels);
void							tga_display(const t_tga *specs);

#endif
