#include "fdf.h"

void			process_zoom(t_env *env)
{
	int			i;
	int			j;

	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			env->map[i][j]->x = env->map[i][j]->sx * env->zoom;
			env->map[i][j]->y = env->map[i][j]->sy * env->zoom;
			env->map[i][j]->z = env->map[i][j]->sz * env->zoom / 20 * (10 * env->z_mult) / 10;
		}
	}
	//ft_printf("X %i, Y %i, Z %i\n", env->map[i - 1][j - 1]->x, env->map[i - 1][j - 1]->y, env->map[i - 1][j - 1]->z);
}

void			process_offset(t_env *env)
{
	int			i;
	int			j;

	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			env->map[i][j]->x += env->x_off * env->zoom;
			env->map[i][j]->y += env->y_off * env->zoom;
		}
	}
}

static double	d_to_r(int deg)
{
	return ((double)deg / 180.0 * M_PI);
}

static void		expose_point(t_point *p, t_env *env)
{
	int			tx;
	int			ty;
	int			tz;

	// x
	ty = p->y;
	tz = p->z;
	p->y = WINDOW_H / 2 + ty * cos(d_to_r(env->rx)) + tz * sin(d_to_r(env->rx));
	p->z = -ty * sin(d_to_r(env->rx)) + tz * cos(d_to_r(env->rx));

	// y
	tx = p->x;
	tz = p->z;
	p->x = WINDOW_W / 2 + tx * cos(d_to_r(env->ry)) + tz * sin(d_to_r(env->ry));
	p->z = -tx * sin(d_to_r(env->ry)) + tz * cos(d_to_r(env->ry));

	//z
	tx = p->x - WINDOW_W / 2;
	ty = p->y - WINDOW_H / 2;
	p->x = WINDOW_W / 2 + tx * cos(d_to_r(env->rz)) - ty * sin(d_to_r(env->rz));
	p->y = WINDOW_H / 2 + tx * sin(d_to_r(env->rz)) + ty * cos(d_to_r(env->rz));
}

void			expose_points(t_env *env)
{
	int			i = -1;
	int			j;

	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
			expose_point(env->map[i][j], env);
	}
}