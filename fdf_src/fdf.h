/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:45:41 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:45:59 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define PI 		3.1415926535

# define WINDOW_W	1360
# define WINDOW_H	768

# define ZOOM 	30

# define ROT_X	0
# define ROT_Y	0
# define ROT_Z	0

# define KESC	53

# define KRXL	87
# define KRXR	84

# define KRYL	83
# define KRYR	85

# define KRZL	86
# define KRZR	88

# define ZIN	69
# define ZOUT	78
# define ZUP	67
# define ZDOWN	75

# define MVL	123
# define MVR	124
# define MVD	125
# define MVU	126

typedef struct		s_point {
	int				x;
	int				y;
	int				z;
	int				sx;
	int				sy;
	int				sz;
	int				color;
}					t_point;

typedef struct		s_env {
	void			*mlx;
	void			*win;
	void			*img;
	int				rx;
	int				ry;
	int				rz;
	int				zoom;
	int				z_mult;
	t_point			*cntr;
	t_point			***map;
	int				len_p;
	int				len_l;
	int				width;
	int				height;
	int				x_off;
	int				y_off;
}					t_env;

void				process_file(char *file_name, t_env **env);
int					key_hook(int keycode, t_env *env);
t_point				***init_map(int *sizes);
t_env				*init_env(int *sizes);
void				free_env(t_env *env);
void				strarr_free(char **str_arr);
void				error_call(char *message);
void				brasenham_line(void *mlx, void *win, t_point t0,
									t_point t1);
void				process_zoom(t_env *env);
void				process_offset(t_env *env);
void				expose_points(t_env *env);
void				draw_lines(t_env *env);
void				get_color(t_point *p, int z_mult);

#endif
