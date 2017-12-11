/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:59:53 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/11 18:39:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

typedef unsigned char t_uchar;

typedef struct	s_env
{
	void	*mlx_p;
	void	*win;
	int		width;
	int		height;
	double	rx;
	double	ry;
	double	rz;
}				t_env;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	intmax_t	color;
}				t_point;

extern t_env	g_env;

intmax_t	ft_g_color(intmax_t c1, intmax_t c2, double k);

t_uchar		ft_get_red(intmax_t	c);

t_uchar		ft_get_green(intmax_t	c);

t_uchar		ft_get_blue(intmax_t	c);

#endif
