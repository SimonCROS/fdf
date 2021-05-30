#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <stdio.h>

# include "libft.h"
# include "graphics.h"

/*** Definitions **************************************************************/

# define BUFF_SIZE 50

# define WIDTH 500
# define HEIGHT 500

# ifdef __APPLE__
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_DOWN 125
#  define K_UP 126
#  define K_ESC 53
#  define K_ENTER 36
#  define K_A 0
#  define K_B 11
#  define K_C 8
#  define K_D 2
#  define K_F 3
#  define K_M 46
#  define K_N 45
#  define K_O 31
#  define K_P 35
#  define K_S 1
#  define K_U 32
#  define K_V 9
#  define K_W 13
#  define K_X 7
#  define K_Z 6
#  define K_ESP 49
#  define K_LSHIFT 257
# else
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_DOWN 65364
#  define K_UP 65362
#  define K_ESC 65307
#  define K_ENTER 65293
#  define K_A 113
#  define K_B 98
#  define K_C 99
#  define K_D 100
#  define K_F 102
#  define K_M 109
#  define K_N 110
#  define K_O 111
#  define K_P 112
#  define K_S 115
#  define K_U 117
#  define K_V 118
#  define K_W 122
#  define K_X 120
#  define K_Z 122
#  define K_ESP 32
#  define K_LSHIFT 65505
# endif

/*** Types ********************************************************************/

typedef struct s_vars		t_vars;

typedef enum e_log_type		t_log_type;

typedef struct s_vertex_map	t_vertex_map;
typedef struct s_vertex		t_vertex;

typedef struct s_image		t_image;
typedef enum e_click_type	t_click_type;
typedef void				(*t_pixel_writer)(void *, int, int, t_color);

typedef struct s_camera		t_camera;

typedef struct s_gnl_entry	t_gnl_entry;

typedef enum e_read_status	t_read_status;

/*** Mlx implementation *******************************************************/

/*** Mlx implementation *******************************************************/

struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

# ifdef __APPLE__

#  define SCROLL_UP 5
#  define SCROLL_DOWN 4

enum e_click_type
{
	CLICK_NONE,
	CLICK_LEFT,
	CLICK_RIGHT,
	CLICK_MIDDLE
};
# else

#  define SCROLL_UP 4
#  define SCROLL_DOWN 5

enum e_click_type
{
	CLICK_NONE,
	CLICK_LEFT,
	CLICK_MIDDLE,
	CLICK_RIGHT
};
# endif

void			launch_game(t_vars *vars);
void			init_window(char *file, t_vertex_map *map);
void			force_put_image(t_vars *vars, t_image *image);
void			init_window_size(t_vars *vars);
t_image			*mlx_init_image(t_vars *vars);
void			mlx_set_pixel(t_image *image, int x, int y, t_color color);

void			mlx_free_image(t_image *image, t_vars *vars);

void			mlx_exit(t_vars *vars);
void			reset_keys(t_vars *vars);

/*== Hooks ==*/

int				key_pressed_hook(int key, t_vars *vars);
int				key_released_hook(int key, t_vars *vars);
int				mouse_pressed_hook(int button, int x, int y, t_vars *vars);
int				close_hook(t_vars *vars);

/*== Events ==*/

int				on_close(t_vars *vars);
int				on_scroll(t_vars *vars, int direction);

/*** General ******************************************************************/

struct s_vars
{
	void			*mlx;
	void			*win;
	t_vertex_map	*map;
	t_camera		*camera;
	t_function		init_image;
	t_pixel_writer	set_pixel;
	t_biconsumer	on_finished;
	t_biconsumer	free_image;
	t_consumer		on_exit;
	t_bounding_box	screen;
	t_image			*render;
	float			*z_buffer;
	int				flush;
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				up;
	int				down;
	int				scroll_direction;
	int				click_type;
	int				cam_left;
	int				cam_right;
	int				cam_up;
	int				cam_down;
};

struct s_vertex
{
	t_vector3f	position;
	t_color		color;
};

struct s_vertex_map
{
	t_vertex	*vertexs;
	int			width;
	int			height;
};

t_vertex_map	*parse(char *file);
void			*free_map(t_vertex_map *map);
int				read_file(char *file, t_list *nodes);

t_vertex		get_vertex(t_vertex_map *map, int x, int y);

void			exit_fdf(t_vars *vars, int __status);

/*** Engine *******************************************************************/

int				render(t_vars *vars);
void			project(t_vars *vars, t_vertex v1, t_vertex v2);
void			draw_line(t_vars *vars, t_line ln, t_color color, float dist);

void			fill_z_buff(float *z_buffer, size_t length);
float			*get_z_buffer_value(float *z_buffer, int x, int y, int width);

/*** Camera *******************************************************************/

struct s_camera
{
	t_vec3f		position;
	t_vec3f		direction;
	t_vec3f		flat;
	t_vec3f		right;
	t_vec3f		up;
	t_matrix44	c2w;
	t_matrix44	w2c;
	float		hlen;
};

t_camera		*new_camera(t_vec3f position, t_vec3f direction, float fov);
void			reload_camera(t_camera *camera);

/*** Parsing utils ************************************************************/

enum e_read_status
{
	READ_ERROR,
	READ_SUCCESS,
	READ_EOF
};

/*** GNL **********************************************************************/

struct s_gnl_entry
{
	void	*next;
	int		fd;
	char	*content;
};

char			**ft_gnl_split(char *s, char c);
int				get_next_line(int fd, char **line);
int				gnl_init(char ***current, char **tmp_line, ssize_t *result);

/*** Logs utils ***************************************************************/

enum e_log_type
{
	INFO,
	WARN,
	ERROR,
	FATAL
};

int				log_nl(void);
int				log_cr(void);
int				log_prev_line(void);
int				log_msg_arg(t_log_type type, char *str, const char *arg);
int				log_msg(t_log_type type, char *str);

/*** Misc ********************************************************************/

int				ft_atohex_full(char *str, int *result);
char			**ft_split_first(char *s, char c);

#endif
