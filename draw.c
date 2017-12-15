/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:30:34 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/15 22:45:35 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_draw_wireframe(t_object object, t_point **z_buff, t_env env)
{
	int		it[2];

	it[0] = -1;
	while (object.p[++it[0]] && (it[1] = -1))
		while (object.p[it[0]][++it[1]].color != -1)
		{
			if (object.p[it[0]][it[1] + 1].color != -1)
				ft_draw_line((t_point[2]){object.p[it[0]][it[1]],
					object.p[it[0]][it[1] + 1]}, !env.wf_mode
						? env.wf_color : 0, z_buff, env);
			if (object.p[it[0] + 1])
				ft_draw_line((t_point[2]){object.p[it[0]][it[1]],
					object.p[it[0] + 1][it[1]]}, !env.wf_mode
						? env.wf_color : 0, z_buff, env);
		}
}

void		ft_draw_squads(t_object o, t_point **z_buff, t_env env)
{
	t_point		pt_1;
	t_point		pt_2;
	double		t;
	double		k;

	while (o.squads && !(t = 0))
	{
		k = 1.0 / fmin(ft_p_distance(o.squads->a, o.squads->d),
				ft_p_distance(o.squads->b, o.squads->c));
		o.squads->a.z != o.squads->d.z
			|| o.squads->b.z != o.squads->c.z ? k /= 12.0 : 0;
		while ((t += k) <= 1.0)
		{
			pt_1 = (t_point){ft_coef_point(o.squads->a.x, o.squads->d.x, t),
				ft_coef_point(o.squads->a.y, o.squads->d.y, t),
				ft_coef_point(o.squads->a.z, o.squads->d.z, t),
				!env.wf_mode ? 0 : -1};
			pt_2 = (t_point){ft_coef_point(o.squads->b.x, o.squads->c.x, t),
				ft_coef_point(o.squads->b.y, o.squads->c.y, t),
				ft_coef_point(o.squads->b.z, o.squads->c.z, t),
				!env.wf_mode ? 0 : -1};
			ft_draw_line((t_point[2]){pt_1, pt_2},
				!env.wf_mode ? 0 : -1, z_buff, env);
		}
		o.squads = o.squads->next;
	}
}

void		ft_draw_line(t_point p[2], intmax_t solid,
							t_point **z_buff, t_env env)
{
	double		t;
	double		k;
	t_point		pt_1;
	t_point		pt_2;
	intmax_t	xyzc[4];

	pt_1 = ft_xyztoxy(p[0], env);
	pt_2 = ft_xyztoxy(p[1], env);
	k = 1.0 / ft_p_distance(pt_1, pt_2) / 5.0;
	t = -k;
	while ((t += k) <= 1.0)
		if ((xyzc[0] = pt_1.x + (pt_2.x - pt_1.x) * t) < W_WIDTH
			&& xyzc[0] >= 0
			&& (xyzc[1] = pt_1.y + (pt_2.y - pt_1.y) * t) < W_HEIGHT
			&& xyzc[1] >= 0
			&& (!z_buff[xyzc[1]][xyzc[0]].color
			|| (z_buff[xyzc[1]][xyzc[0]].color && z_buff[xyzc[1]][xyzc[0]].z
				< (xyzc[2] = pt_1.z + (pt_2.z - pt_1.z) * t))))
		{
			xyzc[3] = !solid
				? ft_clalc_height_color(p[0].z + (p[1].z - p[0].z) * t) : solid;
			z_buff[xyzc[1]][xyzc[0]] = (t_point){.z = xyzc[2],
				.color = xyzc[3]};
		}
}
