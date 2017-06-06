#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "../libft/src/libft.h"

# define KNRM 	"\x1B[0m"
# define KRED 	"\x1B[91m"
# define KGRN 	"\x1B[92m"
# define KYEL 	"\x1B[93m"
# define KBLU 	"\x1B[94m"
# define KMAG 	"\x1B[95m"
# define KCYN 	"\x1B[96m"
# define KWHT 	"\x1B[97m"

# define WINDOW_W	1360
# define WINDOW_H	768

# define XSTEP 	10.0
# define YSTEP 	10.0

# define ESC	53	

typedef struct		s_point {
	double			x;
	double			y;
	double			z;
	int				color;
}					t_point;

typedef struct		s_env {
	void			*mlx;
	void			*win;
	void			*img;
	// int				r_x;
	// int				r_y;
	// int				r_z;
	t_point			*cntr;
	t_point			***map;
	int				len_p;
	int				len_l;
	int				width;
	int				height;
}					t_env;

void				process_file(char *file_name, t_env **env);

int					key_hook(int keycode, t_env *env);

t_point				***init_map(int *sizes);
t_env				*init_env(int *sizes);

void				free_env(t_env *env);
void				strarr_free(char **str_arr);

void				error_call(char *message);

#endif
