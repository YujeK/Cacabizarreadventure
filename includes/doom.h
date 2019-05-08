/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 06:51:46 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:35:49 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "libft.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "get_next_line.h"
# include "tga.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>

# define TRUE 1
# define FALSE 0
# define SH 1000
# define SCREEN_WIDTH 1000
# define TEXTURE 500
# define EYEHEIGHT 6
# define DUCKHEIGHT 2.5
# define HEADMARGIN 1
# define KNEEHEIGHT 2
# define HFOV (0.73f * SH)
# define VFOV (0.2f * SH)
# define CROSSHAIR_X 500
# define CROSSHAIR_Y 500
# define FPS 60

# define RED 0xad1313
# define CYAN 0x2d6f9b
# define BLUE 0x114fb2
# define PURPLE 0x67438c
# define YELLOW 0xFd1c657
# define ORANGE 0xfd6824f
# define GREEN 0x27a348
# define INDIGO 0x1ea3cc
# define WHITE 0xFFFAFA

typedef struct		s_pixels
{
	Uint32			*pixels;
	Uint32			pixel;
	Uint32			color;
	Uint8			r;
	Uint8			g;
	Uint8			b;
}					t_pixel;

typedef struct		s_coord
{
	int		x;
	int		y;
}					t_coord;

typedef	struct		s_line
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
}					t_line;

typedef	struct		s_rect
{
	int			x;
	int			y;
	int			x2;
	int			y2;
}					t_rect;

typedef struct		s_vector
{
	double		x;
	double		y;
}					t_vector;

typedef struct		s_all
{
	t_vector	start;
	t_vector	end;
}					t_wall;
typedef struct		s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}					t_wind;

typedef struct		s_texture
{
	SDL_Surface	*north;
	SDL_Surface	*south;
	SDL_Surface	*west;
	SDL_Surface	*east;
	SDL_Surface	*portal;
	SDL_Surface	*door;
}					t_texture;

typedef struct		s_button
{
	int				pos_x;
	int				pos_y;
	double			size;
	char			*name;
	int				len;
	unsigned int	*img;
	int				select;
}					t_button;

typedef	struct		s_sector
{
	float			floor;
	float			ceil;
	t_vector		*vertex;
	signed char		*neighbors;
	unsigned int	npoints;
}					t_sector;

typedef struct		s_xyz
{
	double		x;
	double		y;
	double		z;
}					t_xyz;

typedef struct		s_plyr
{
	t_xyz			where;
	t_xyz			velocity;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;
	unsigned int	sector;
	int				hp;
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
}					t_plyr;

typedef	struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

typedef struct		s_object
{
	int				sectorno;
	t_xyz			where;
	int				sprite;
	unsigned int	*img;
	int				size;
	int				bx;
	int				ex;
	int				y1;
	int				y2;
	int				x;
	int				i;
	int				x_count;
	float			dist;
	t_tga			specs;
	t_tga			specs1;
	unsigned int	*res_img;
	unsigned int	*dead_img;
	int				status;
}					t_object;

typedef struct		s_inter
{
	float x0;
	float y0;
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float py;
	float px;
}					t_inter;

typedef struct		s_data
{
	t_coord			pos;
	int				win;
	time_t			death_timer;
	int				score;
	int				eyesofthedead;
	int				count_frames;
	int				which_menu;
	int				menu_state;
	int				game_start;
	float			sprint;
	Uint32			starting_tick;
	int				greyscale_step;
	int				msg_readen;
	TTF_Font		*font;
	time_t			timer;
	time_t			stand_timer;
	time_t			startgame_timer;
	time_t			timer_start;
	Mix_Chunk		*stand_warudo;
	Mix_Chunk		*target_hit;
	Mix_Chunk		*tp_sound;
	Mix_Chunk		*ak;
	Mix_Music		*menutheme;
	Mix_Chunk		*eye_sound;
	Mix_Music		*zawarudotheme;
	Mix_Music		*maintheme;
	SDL_Event		*ev;
	t_plyr			player;
	t_wind			wind;
	int				zawarudo;
	int				wpn_repos;
	float			yaw;
	int				story_step;
	int				wpn_y;
	int				wpn_x;
	int				weapon_state;
	int				weapon_ammo;
	int				weap_cd;
	int				is_cd;
	int				inventory_state;
	int				which_weapon;
	t_object		widoff;
	t_object		menustart;
	t_object		menu;
	t_object		widon;
	t_object		handoff;
	t_object		handon;
	t_object		akimbon;
	t_object		akimboff;
	t_object		invoff;
	t_object		invon;
	t_object		rbw;
	t_object		pepo;
	t_object		*sprite;
	int				sprite_nbr;
	int				aim;
	double			luminosity;
	double			prev_lum;
	int				numsectors;
	int				x_draw;
	int				sectqueue[33];
	int				now_sect;
	int				flag;
}					t_data;

typedef struct		s_b
{
	t_plyr			player;
	t_sector		*sectors;
	t_sector		sect;
	t_vector		*vert;
	t_vector		tempo;
	t_object		temp_sprite;
	unsigned int	numsectors;
	unsigned int	s;
	char			*str;
	int				fd;
	int				ret;
	char			*buf;
	char			**map;
	float			xd;
	float			yd;
	float			eyeheight;
	float			nextz;
	float			hole_low;
	float			hole_high;
	float			dx;
	float			dy;
	float			px;
	float			py;
	float			temp;
	int				pushing;
	float			acceleration;
	float			move_vec[2];
	int				i;
	int				j;
	t_coord			point;
	t_coord			next_point;
	t_line			line;
	SDL_Rect		rect;
	int				x;
	int				y;
}					t_b;

typedef	struct		s_rv
{
	int				x1;
	int				x;
	int				y1;
	int				y2;
	int				top;
	int				middle;
	int				bottom;
	int				ya;
	int				yb;
	double			height;
}					t_rv;

typedef struct		s_bas
{
	unsigned int	numsectors;
	t_item			queue[32];
	t_item			*head;
	t_item			*tail;
	t_item			now;
	int				sectqueue[33];
	int				ytop[SCREEN_WIDTH];
	int				ybottom[SCREEN_WIDTH];
	int				renderedsectors[25];
	int				i;
	t_sector		sect;
	int				x;
	int				pixel;
	int				s;
	int				y1a;
	int				y2a;
	int				ny1a;
	int				ny2a;
	int				beginx;
	int				y1b;
	int				y2b;
	int				ny1b;
	int				ny2b;
	int				endx;
	int				x1;
	int				x2;
	int				z;
	int				ya;
	int				yb;
	int				cya;
	int				nya;
	int				nyb;
	int				cyb;
	int				cnya;
	int				cnyb;
	float			vx1;
	float			vy1;
	float			vx2;
	float			vy2;
	float			pcos;
	float			psin;
	float			tx1;
	float			tx2;
	float			tz1;
	float			tz2;
	float			ttx1;
	float			ttx2;
	float			ttz1;
	float			ttz2;
	float			nearz;
	float			farz;
	float			nearside;
	float			farside;
	float			xscale1;
	float			xscale2;
	float			yscale1;
	float			yscale2;
	float			yceil;
	float			yfloor;
	float			nyceil;
	float			nyfloor;
	float			ratio;
	float			width;
	float			float_x;
	float			to_intersection;
	float			to_end;
	float			point_in_image;
	t_vector		intersection;
	int				neighbor;
	unsigned int	r;
	unsigned int	r1;
	unsigned int	r2;
	t_vector		i1;
	t_vector		i2;
	unsigned int	*img;
	unsigned int	*res_img;
	float			dist;
	int				y1;
	int				xt;
	int				y2;
	float			yc;
	float			yf;
	float			xscale;
	float			yscale;
	t_vector		t1;
	t_vector		sp;
}					t_bas;

typedef struct		s_fls2
{
	int				i;
	int				f;
	int				part;
	int				v;
	int				save;
	int				save2;
	int				n;
}					t_fls2;

typedef	struct		s_lsect
{
	t_sector		*sect;
	int				i;
	int				j;
	int				t;
	int				c;
	int				st;
	int				f;
	int				part;
	int				v;
	int				save;
	int				save2;
	int				n;
}					t_lsect;

typedef	struct		s_lvert
{
	int				i;
	int				j;
	int				v;
	int				y;
	int				vt;
	int				st;
	int				s;
	int				c;
	int				t;
	t_vector		*vertex;
}					t_lvert;

void				put_pixel32(SDL_Surface *surface,
					int x, int y, Uint32 pixel);
int					ft_iatoi(char *wall, int index);
t_wind				init_wind(t_wind wind);
unsigned int		*resize(unsigned int *pixels, t_tga specs, double size);

/*
**  TOOLS
*/

void				wpn_bobbing(t_data *data);
float				max(float a, float b);
int					imax(int a, int b);
int					imin(int a, int b);
float				min(float a, float b);
float				pv(float x0, float y0, float x1, float y1);
int					intersectbox(t_inter *ic);
float				yaw(float y, float z, float yaw);
float				pointside(t_inter *ic);
float				ft_iatof(char *wall, int index);
float				clamp(float a, int min, int max);
float				fclamp(float a, float min, float max);
int					overlap(float a1, float a2, float b1, float b2);
t_vector			intersect(t_bas *bas, float x3, float x4);
float				ft_iatof(char *wall, int index);
int					ft_draw_line3(t_wind wind,
					t_coord point, t_coord next_point, t_line line);
void				display_img(t_coord pos,
					t_wind wind, int size, unsigned int *res_img);
int					ft_in_hitbox(t_data *data);
void				cap_framerate(t_data *data);
void				fillrect(SDL_Rect rect, t_wind wind);
int					rbw(int x, unsigned int numsectors);
SDL_Color			ft_hex_to_rgb(int hexa);
t_object			get_sprite_coords(t_data *data,
					t_object *sprite, t_b *b, t_bas *bas);
t_object			*sprite_size(t_object *sprite,
					t_plyr player, t_data data, t_b *b);
void				pick_up(t_data *data, t_plyr *player, t_object *sprite);
int					in_sector_full(t_sector *sectors,
					t_vector point, unsigned int numsectors);
void				ft_set_nbrstring(int value,
					SDL_Rect rect, SDL_Color color, t_data *data);
void				ft_set_string(SDL_Rect rect,
					char *text, SDL_Color color, t_data *data);
SDL_Color			ft_color_nb_state(int nb);
char				*ft_readfile(const char *filepath, size_t *usize);
unsigned int		*pixels_to_rgba(unsigned int *pixels, size_t n);

/*
** EVENTS
*/

int					check_keydown(t_wind wind);
int					event_keyboard(t_plyr *player,
					t_data *data, float *move_vec, t_sector *sector);
void				event_mouse(t_plyr *player, t_data *data);
t_plyr				move_player(t_b *b);
void				stand_ev(t_data *data, Uint8 *state, t_plyr *player);
void				stand_activation(t_data *data);
void				event_manager(t_data *data, t_b *b);
void				movement_ev(t_data *data, Uint8 *state,
					float *move_vec, t_plyr *player);
void				inv_ev(t_data *data, Uint8 *state);

/*
**  Parsing
*/

int					count_vertex(char *str);
int					ft_iatoi(char *str, int i);
t_vector			*load_vertex(char **map);
t_plyr				load_player(t_sector *sectors, char **map);
t_sector			*load_sectors(char **map,
					unsigned int *numsectors, t_vector *vertex);
t_fls2				init_fill_sectors(char *str, t_sector *sectors, int *c);

/*
**	INIT FONCTIONS
*/
t_wind				init_wind(t_wind wind);
void				init_img(t_data *data);
void				init_sprites(t_data *data, char **map);
void				end_game(t_data *data);
void				init_ingame_vars(t_data *data, t_b *b);
void				start_menu(t_data *data);
t_bas				init_draw_vars(t_data *data, t_b *b, t_bas *bas);
void				init_intersect_vars2(t_bas *bas);
void				recycle_vline(t_bas *bas, t_rv *rv);
void				recycle_vline2(t_bas *bas, t_rv *rv);
void				recycle_vline3(t_bas *bas, t_rv *rv);
void				recycle_vline4(t_bas *bas, t_rv *rv);
void				recycle_vline21(t_bas *bas, t_rv *rv);
void				init_pointside(t_b *b, t_inter *ips);
void				init_inter(t_b *b, t_inter *ic);
void				init_inter2(t_b *b, t_inter *ic, t_vector *vert, int s);
void				init_pointside2(t_b *b,
					t_inter *ips, int s, t_vector *vert);
void				move_interaction(t_b *b);

/*
** EXIT FONCTIONS
*/
void				ft_exit(void);
void				ft_error_exit(char *str);

/*
**  RENDER
*/

void				vline(t_data *data, t_rv *rv);
void				vline2(t_data *data, t_bas *bas, t_rv *rv);
void				draw_screen(t_data *data, t_b *b);
void				draw_map(t_b *b, t_data *data);
void				draw_items(t_data *data);
void				draw_inventory(t_data *data);
int					render_sprite(t_plyr player,
					t_object *sprite, t_sector *sectors, t_bas *bas);
void				draw_resized_column(t_data *data, t_object *sprite);
int					luminosity(int r1, double z, double luminosity);
void				engine_interaction(t_b *b);
void				game_loop(t_data *data, t_b *b);
void				init_main_v(t_data *data, t_b *b, char *arg);
void				draw_neighbor(t_data *data, t_bas *bas, t_rv *rv);
void				draw_edges(t_bas *bas, t_data *data, t_b *b);
void				while_edges(t_bas *bas, t_data *data, t_b *b);
void				transform_vertex(t_b *b, t_bas *bas);
void				into_screen(t_b *b, t_bas *bas);

/*
**	UI
*/

void				ft_value_display(t_data *data);
void				ft_crosshair(t_data *data);
void				story_0and1(t_data *data, SDL_Rect rect);
void				story_2and3(t_data *data, SDL_Rect rect);

#endif
