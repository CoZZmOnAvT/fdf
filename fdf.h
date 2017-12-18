/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:59:53 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:00:27 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <time.h>
# include "libft.h"

# define W_WIDTH 1200
# define W_HEIGHT 1200

# define DEFAULT_CENTER W_HEIGHT / 2

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_ARR_UP 126
# define KEY_ARR_DOWN 125
# define KEY_ARR_LEFT 123
# define KEY_ARR_RIGHT 124
# define M_B_LEFT 1
# define M_B_RIGHT 2
# define M_SCROLL_UP 4
# define M_SCROLL_DOWN 5
# define KEY_ESC 53

typedef unsigned char	t_uchar;

typedef struct	s_env
{
	void		*mlx_p;
	void		*win;
	int			width;
	int			height;
	double		rx;
	double		ry;
	double		rz;
	double		pivot_x;
	double		pivot_y;
	double		scale;
	intmax_t	wf_color;
	char		wf_mode;
	int			max_z;
	int			min_z;
	intmax_t	zero_c;
	intmax_t	high_c;
	intmax_t	low_c;
}				t_env;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	intmax_t	color;
}				t_point;

typedef struct	s_squad
{
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			d;
	struct s_squad	*next;
}				t_squad;

typedef struct	s_object
{
	t_squad		*squads;
	t_point		**p;
	int			rows;
	int			cols;
	intmax_t	sd_c;
}				t_object;

typedef struct	s_trash
{
	t_env		*env;
	t_object	*plane;
	t_point		**z_buff;
}				t_rash;

t_point			**ft_init_z_buffer(void);

void			ft_clear_z_buffer(t_point	**z_buff);

void			ft_parse_z_buffer(t_object object, t_point **z_buff, t_env env);

intmax_t		ft_count_lines(int *fd, char *filename);

void			ft_count_points(intmax_t *c, char **row, t_env *env);

void			ft_clean_trash(char *str, char **tmp);

void			ft_input(int fd, char *filename, t_object *object, t_env *env);

void			ft_add_squads(t_object *object);

void			ft_draw_squads(t_object object, t_point **z_buff, t_env env);

void			ft_draw_wireframe(t_object object, t_point **z_buff, t_env env);

void			ft_draw_line(t_point p[2], intmax_t solid,
								t_point **z_buff, t_env env);

intmax_t		ft_g_color(intmax_t c1, intmax_t c2, double k);

t_uchar			ft_get_alpha(intmax_t c);

t_uchar			ft_get_red(intmax_t c);

t_uchar			ft_get_green(intmax_t c);

t_uchar			ft_get_blue(intmax_t c);

t_point			ft_xyztoxy(t_point p, t_env env);

double			ft_coef_point(double a, double b, double t);

double			ft_p_distance(t_point p1, t_point p2);

intmax_t		ft_clalc_height_color(double z, t_env env);

void			ft_recalc_points(t_object *object, t_env env);

void			ft_recalc_squads(t_object object);

int				key_handler(int key, t_rash *t);

int				mouse_handler(int key, int x, int y, t_rash *t);

void			ft_error_handler(char *err, char *add);

t_squad			*ft_new_squad(t_squad tmp);

t_squad			*ft_push_squad(t_squad **dest, t_squad tmp);

void			ft_validate(int *fd, int ac, char **av, t_env *env);

void			ft_invitation(void);

#endif
