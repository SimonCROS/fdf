#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <stdio.h>

# include "libft.h"
# include "graphics.h"

/*** Definitions **************************************************************/

# define BUFF_SIZE 50

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

/*** General ******************************************************************/

struct s_vars
{
	void			*mlx;
	void			*win;
	t_vertex_map	*map;
	t_camera		*camera;
	t_bifunction	init_image;
	t_pixel_writer	set_pixel;
	t_biconsumer	on_finished;
	t_biconsumer	free_image;
	t_consumer		on_exit;
};

struct s_vertex
{
	t_color		color;
	t_vector3f	position;
};

struct s_vertex_map
{
	t_vertex	**vertexs;
	int			width;
	int			height;
};

t_vertex_map	*parse(char *file);

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

char			**ft_split_first(char *s, char c);
int				get_next_line(int fd, char **line);
int				gnl_init(char ***current, char **tmp_line, ssize_t *result);

/*** Logs utils ***************************************************************/

enum e_log_type
{
	INFO,
	WARN,
	ERROR,
	DEBUG,
	FATAL
};

int				log_nl(void);
int				log_cr(void);
int				log_prev_line(void);
int				log_msg_arg(t_log_type type, char *str, const char *arg);
int				log_msg(t_log_type type, char *str);
int				is_debug_enabled(void);
int				set_debug(int debug);

#endif
