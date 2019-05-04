/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:36:04 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/04 12:28:55 by asamir-k         ###   ########.fr       */
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
# define SCREEN_HEIGHT 1000
# define SCREEN_WIDTH 1000
# define TEXTURE 500
# define Eyeheight 6
# define DuckHeight 2.5
# define HeadMargin 1
# define KneeHeight 2
# define hfov (0.73f * SCREEN_HEIGHT)
# define vfov (.2f * SCREEN_HEIGHT)
# define CROSSHAIR_X 500
# define CROSSHAIR_Y 500
# define FPS 60

# define RED 0xFF0001
# define CYAN 0x00CCCC
# define BLUE 0x0000f
# define PURPLE 0x800080
# define YELLOW 0xFFFF00
# define ORANGE 0xffa500
# define GREEN 0x008000
# define INDIGO 0x4B0082
# define WHITE 0xF0FFF0
typedef struct  s_pixels
{
        Uint32          *pixels;
        Uint32          pixel;
        Uint32          color;
        Uint8           r;
        Uint8           g;
        Uint8           b;
}				t_pixel;

typedef struct	s_coord
{
	int x;
	int y;
}				t_coord;

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

typedef	struct	s_rect
{
	int			x;
	int			y;
	int			x2;
	int			y2;
}				t_rect;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}				t_wind;

typedef struct	s_texture
{
	SDL_Surface	*north;
	SDL_Surface	*south;
	SDL_Surface	*west;
	SDL_Surface	*east;
	SDL_Surface	*portal;
	SDL_Surface	*door;
}				t_texture;

typedef struct	s_button
{
	int				pos_x;
	int				pos_y;
	double			size;
	char			*name;
	int				len;
	unsigned int	*img;
	int				select;
}				t_button;

typedef	struct	s_sector
{
	float 			floor;
	float 			ceil;
	t_vector		*vertex;
	signed char		*neighbors;
	unsigned int	npoints;
}				t_sector;

typedef struct	s_xyz
{
	double		x;
	double		y;
	double		z;
}				t_xyz;

typedef struct	s_plyr
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
}				t_plyr;

typedef	struct 	s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct  s_object
{
    int             sectorno;
    t_xyz           where;
    int             sprite;
    unsigned int    *img;
    int             size;
    int             bx;
    int             ex;
    int             y1;
    int             y2;
    int             x;
	int				i;
    int             x_count;
	float			dist;
    t_tga           specs;
	t_tga           specs1;
	unsigned int	*res_img;
	unsigned int	*dead_img;
	int				status;
	time_t			death_timer;
}               t_object;

typedef struct	s_data
{
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
	Mix_Music		*menutheme;
	Mix_Music		*zawarudotheme;
	Mix_Music		*maintheme;
	SDL_Event		*ev;
	t_plyr			player;
	t_wind			wind;
	int				zawarudo;
	int				wpn_repos;
	float 			yaw;
	int				story_step;
	int				wpn_y;
	int				wpn_x;
	int				weapon_state;
	int				weapon_ammo;
/* 	t_tga			lava_specs;
	unsigned int	*lava;
	unsigned int 	*res_lava; */
	int				inventory_state;
	int				which_weapon;
	/* inventory tga load */
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
	t_object		*sprite;
	int				sprite_nbr;
	int				toto;
	int				aim;
	double			luminosity;
	double			prev_lum;
	int				numsectors;
	int				x_draw;
	int				sectqueue[33];
	int				now_sect;
	int				flag;
}					t_data;

void			put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
int				ft_iatoi(char *wall, int index);
t_wind			init_wind(t_wind wind);
unsigned int 	*resize(unsigned int *pixels, t_tga specs, double size);

/*
**  TOOLS
*/


void			wpn_bobbing(t_data *data);
float			max(float a, float b);
int				imax(int a, int b);
int				imin(int a, int b);
float 			min(float a, float b);
float			pv(float x0, float y0, float x1, float y1);
int 			IntersectBox(float x0, float y0, float x1, float y1, float x2, float y2,  float x3, float y3);
float			yaw(float y, float z, float Yaw);
float			pointside(float px, float py, float x0, float y0, float x1, float y1);
float			ft_iatof(char *wall, int index);
float			clamp(float a , int min, int max);
float 			fclamp(float a , float min, float max);
int 			overlap(float a1 ,float a2, float b1, float b2);
t_vector		Intersect(float x1, float y1, float x2, float y2, float x3, float  y3, float x4, float y4);
float			ft_iatof(char *wall, int index);
int				ft_draw_line3(t_wind wind, t_coord point, t_coord next_point, t_line line);
void   			display_img(int x, int y, t_wind wind, int size, unsigned int *res_img);
int         	ft_in_hitbox(t_data *data);
void        	cap_framerate(t_data *data);
void    		fillrect(SDL_Rect rect, int color, t_wind wind);
int             rbw(int x);
SDL_Color		ft_hex_to_rgb(int hexa);
t_object 		get_sprite_coords(t_data *data, t_object *sprite, t_plyr *player, t_sector *sectors, int ytop, int ybottom);
t_object 		*sprite_size(t_object *sprite, t_plyr player, t_data data);

/*
** EVENTS
*/

int				check_keydown(t_wind wind);
int				event_keyboard(t_plyr *player, t_data *data, float *move_vec);
void			event_mouse(t_plyr *player, t_data *data);
t_plyr			Move_player(float dx, float dy, t_plyr player, t_sector *sectors);
void    		stand_ev(t_data *data, Uint8 *state);

/*
**  Parsing
*/

int 			count_vertex(char *str);
t_vector		*Load_vertex(char **map);
t_plyr			Load_Player(t_sector *sectors, char **map);
t_sector		*Load_sectors(char **map, unsigned int *NumSectors, t_vector *vertex);

/*
**	INIT FONCTIONS
*/
t_wind			init_wind(t_wind wind);
void			init_img(t_data *data);
void			start_menu(t_data *data);
void			init_sprites(t_data *data, char **map);


/*
** EXIT FONCTIONS
*/
void			ft_exit(t_data *data);
void			ft_error_exit(char *str, t_data *data);

/*
**  RENDER
*/

void			vline2(int x1, int x, int y1, int y2, int top, int middle, int bottom, SDL_Surface *surface, unsigned int *img, int ya, int yb);
void			vline(t_data *data, int x, int y1, int y2, int top, int middle, int bottom, SDL_Surface *surface, unsigned int *img);
void 			draw_screen(t_data *data, t_plyr *player, t_sector *sectors, unsigned int NumSectors);
void			draw_map(t_vector *vert, t_sector *sectors, unsigned int NumSectors, t_wind wind, t_plyr player, t_data *data);
void			draw_items(t_data *data);
void			draw_inventory(t_data *data);
int 			render_sprite(t_plyr player, t_object *sprite, t_sector *sectors);
void			draw_resized_column(t_data *data,t_object *sprite, t_wind wind, int ytop, int ybot);
int				luminosity(int r1, double z, double luminosity);


/*
**	UI
*/
void			ft_value_display(t_data *data);
void			ft_crosshair(t_data *data);
#endif
