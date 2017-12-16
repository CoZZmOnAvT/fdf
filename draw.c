/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:30:34 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 18:37:15 by pgritsen         ###   ########.fr       */
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

void		ft_bridge_edges(t_point e1[2], t_point e2[2], t_rash tr)
{
	t_point		pt_1;
	t_point		pt_2;
	double		t;
	double		k;

	k = 0.2 / fmin(ft_p_distance(e1[0], e1[1]), ft_p_distance(e2[0], e2[1]));
	t = 0;
	while ((t += k) <= 1.0 - k)
	{
		pt_1 = (t_point){ft_coef_point(e1[0].x, e1[1].x, t),
			ft_coef_point(e1[0].y, e1[1].y, t),
			ft_coef_point(e1[0].z, e1[1].z, t), !tr.env->wf_mode ? 0 : -1};
		pt_2 = (t_point){ft_coef_point(e2[0].x, e2[1].x, t),
			ft_coef_point(e2[0].y, e2[1].y, t),
			ft_coef_point(e2[0].z, e2[1].z, t), !tr.env->wf_mode ? 0 : -1};
		ft_draw_line((t_point[2]){pt_1, pt_2},
			!tr.env->wf_mode ? 0 : -1, tr.z_buff, *tr.env);
	}
}

void		ft_draw_squads(t_object o, t_point **z_buff, t_env env)
{
	double		t;

	while (o.squads && !(t = 0))
	{
		ft_bridge_edges((t_point[2]){o.squads->a, o.squads->d},
			(t_point[2]){o.squads->b, o.squads->c}, (t_rash){&env, &o, z_buff});
		if (o.squads->a.z != o.squads->d.z || o.squads->b.z != o.squads->c.z)
			ft_bridge_edges((t_point[2]){o.squads->a, o.squads->b},
				(t_point[2]){o.squads->d, o.squads->c},
				(t_rash){&env, &o, z_buff});
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
	k = 0.1 / ft_p_distance(pt_1, pt_2);
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
			xyzc[3] = !solid ?
				ft_clalc_height_color(p[0].z + (p[1].z - p[0].z) * t, env)
					: solid;
			z_buff[xyzc[1]][xyzc[0]] = (t_point){.z = xyzc[2],
				.color = xyzc[3]};
		}
}
