/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doome.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:33:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 12:17:11 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOME_H
# define DOOME_H

# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "SDL.h"
# include "libft.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

typedef struct	s_pixels
{
	Uint32		*pixels;
	Uint32		pixel;
	Uint32		color;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_wall
{
	t_coord		start;
	t_coord		end;
}				t_wall;

typedef struct	s_misc
{
	double		t;
	double		stp_dot_ste;
	double		squared_line_distance;
}				t_misc;

typedef	struct	s_line
{
	float		dx;
	int			sx;
	float		dy;
	int			sy;
	float		m;
	float		pb;
	int			intm;
	int			intb;
	int			color;
	t_coord		offset;
}				t_line;

typedef struct	s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}				t_wind;

typedef struct	s_sector
{
	int			num;
	int			edges_length;
	double		ceil_height;
	double		floor_height;
	int			*edges;
}				t_sector;

typedef struct	s_player
{
	int			sector_num;
	t_coord		pos;
}				t_player;

typedef struct	s_sprite_g
{
	t_coord		pos;
	int			sector_num;
}				t_sprite_g;

typedef struct	s_sprite_r
{
	t_coord		pos;
	int			sector_num;
	double		angle;
}				t_sprite_r;

typedef struct	s_map
{
	t_coord		*vertex;
	t_coord		*edges;
	t_sector	*sector;
	t_player	player;
	t_sprite_r	*r_sprite;
	t_sprite_g	*g_sprite;
	int			vertex_length;
	int			edges_length;
	int			sector_length;
	int			selected_sector;
	int			sprite_g_len;
	int			sprite_r_len;
	size_t		i;
	size_t		j;
}				t_map;

t_sector		initialize_sector(t_map map);
t_coord			*initialize_vertex(t_map map);
t_coord			*place_vertex(t_coord new_vertex_pos,
		t_coord *vertex, int vertex_length);
t_coord			*create_edge(t_coord vertex_indexes,
		t_coord *edges, int edge_length);
t_coord			get_closest_point_on_line(t_map map,
		t_coord world_pos, int edge_index);
t_coord			*initialize_edges(t_map map);
t_wind			init_wind(void);
t_wall			get_line_coordinates(t_map map, int i);
t_map			extrude_sector(t_map map, int edge_to_extrude,
		t_coord extrude_start, t_coord extrude_end);
t_map			divide_line(t_map map, int edge_index);
t_map			initialize_values(void);
t_map			check_key_press(t_wind wind, t_map map, t_coord mouse_pos);
t_map			create_mid_line_vertex(t_map map, t_coord world_pos);
t_map			translate_vertex(t_map map, int vertex_to_mv_index,
		t_coord new_vertex_pos);
t_map			add_edge_to_sector(t_map map, int altered_edge);
t_map			remove_all_duped_vertex(t_map map);
t_map			displace_edges(t_map map, int sector_to_change, int edge_index);
t_map			check_mouse_events(t_wind wind, t_map map, t_coord mouse_pos);
t_map			backup_map(t_map map, t_map backup_map);
t_map			remove_latest_sector(t_map map);
t_map			read_map(void);
t_map			create_edge_on_sector(t_map map, int sector_to_change,
		int edge_index);
t_map			add_edge_to_sector(t_map map, int altered_edge);
t_map			create_new_vertexes(t_map map, int edge_to_extrude_index,
		t_coord extrude_vector);
t_map			make_read_decision(t_map map, char **txt, size_t strlen);
t_map			init_map(void);
t_map			read_vertex(t_map map, char **txt);
t_map			read_sector(t_map map, char **txt);
t_map			read_player(t_map map, char **txt);
int				sector_contains_edge(t_sector sector, int altered_edge);
int				select_vertex_to_move(t_map map, t_coord mouse_pos);
int				get_point_distance(t_coord a, t_coord b);
int				point_in_segment(t_map map, t_coord point_in_line,
		int edge_index);
int				geometry_is_valid(t_map map);
int				get_line_distance(t_map map, t_coord world_pos, int edge_index);
int				ft_draw_line(t_wind wind, t_coord point,
		t_coord next_point, t_line line);
int				line_is_close(t_map map, t_coord world_pos, int i);
int				vector_cross_product(t_wall a, t_wall b);
int				all_sectors_are_convex(t_map map);
int				there_are_intersections(t_map map);
int				better_get_ln_dist(t_map map,
		t_coord mouse_pos, int edge_index);
int				select_edge_to_extrude(t_map map, t_coord mouse_pos);
int				in_sector(t_map map, t_coord point);
int				nested_extrude(t_map map);
int				line_intersects(t_coord p1, t_coord q1, t_coord p2, t_coord q2);
int				in_sector_full(t_map map, t_coord point);
int				player_outside(t_map map);
int				sprite_outside(t_map map);
int				get_fd_index(t_map map, t_coord to_find);
int				recursive(t_map map, int i, int current_y);
int				ft_iatoi(char *wall, int index);
void			exit_on_error(void);
void			draw_square(t_wind wind, t_coord vertex,
		int square_size, int color);
void			put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
void			clean_and_exit(t_wind wind);
void			draw_window(t_map map, t_wind wind);
void			write_vertexes(t_map map, int fd);
void			free_map(t_map map);
void			draw_rectangle(t_coord start, t_coord end, t_wind wind);
void			write_fd(t_map map);
void			write_neighbours(t_map map, int s_num, int fd);
void			write_player(t_map map, int fd);
void			write_sprites_globales(t_map map, int fd);

#endif
