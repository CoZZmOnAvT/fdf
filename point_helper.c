/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:28:19 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/15 22:41:23 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		ft_xyztoxy(t_point p, t_env env)
{
	t_env	rot;
	t_point	p0;
	t_point	p1;
	t_point	p2;

	rot.rx = ft_degtorad(env.rx);
	rot.ry = ft_degtorad(env.ry);
	rot.rz = ft_degtorad(env.rz);
	p.z = round(p.z * (env.scale + 2.0));
	p0.x = p.x;
	p0.y = p.y * cos(rot.rx) + p.z * sin(rot.rx);
	p0.z = p.z * cos(rot.rx) - p.y * sin(rot.rx);
	p1.x = p0.x * cos(rot.ry) - p0.z * sin(rot.ry);
	p1.y = p0.y;
	p1.z = p0.z * cos(rot.ry) + p0.x * sin(rot.ry);
	p2.x = p1.x * cos(rot.rz) + p1.y * sin(rot.rz) + env.pivot_x;
	p2.y = p1.y * cos(rot.rz) - p1.x * sin(rot.rz) + env.pivot_y;
	p2.z = p1.z;
	return (p2);
}

void		ft_recalc_points(t_object *object, t_env env)
{
	int		xy[2];
	int		it[2];

	xy[1] = (object->rows / 2) * (-10 * env.scale);
	it[0] = -1;
	while (object->p[++it[0]] && (it[1] = -1))
	{
		xy[0] = (object->cols / 2 + 1) * (-10 * env.scale);
		while (object->p[it[0]][++it[1]].color != -1)
		{
			object->p[it[0]][it[1]].x = (xy[0] += (10 * env.scale));
			object->p[it[0]][it[1]].y = xy[1];
		}
		xy[1] += (10 * env.scale);
	}
}

double		ft_coef_point(double a, double b, double t)
{
	return (a + (b - a) * t);
}

intmax_t	ft_clalc_height_color(double z)
{
	z > 0 ? z = z / 100.0 + 0.5 : 0;
	z < 0 ? z = z / 100.0 - 0.5 : 0;
	z > 1 ? z = 1 : 0;
	z < -1 ? z = -1 : 0;
	if (z < 0)
		return (ft_g_color(0x00FF00, 0x0000FF, ABS(z)));
	return (ft_g_color(0x00FF00, 0xFF0000, z));
}

double		ft_p_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}
