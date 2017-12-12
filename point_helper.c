/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:28:19 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/12 13:41:19 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		ft_xyztoxy(t_point p)
{
	t_env	rot;
	t_point	p0;
	t_point	p1;
	t_point	p2;

	rot.rx = ft_degtorad(g_env.rx);
	rot.ry = ft_degtorad(g_env.ry);
	rot.rz = ft_degtorad(g_env.rz);
	p0.x = p.x;
	p0.y = p.y * cos(rot.rx) + p.z * sin(rot.rx);
	p0.z = p.z * cos(rot.rx) - p.y * sin(rot.rx);
	p1.x = p0.x * cos(rot.ry) - p0.z * sin(rot.ry);
	p1.y = p0.y;
	p1.z = p0.z * cos(rot.ry) + p0.x * sin(rot.ry);
	p2.x = p1.x * cos(rot.rz) + p1.y * sin(rot.rz) + g_env.pivot_x;
	p2.y = p1.y * cos(rot.rz) - p1.x * sin(rot.rz) + g_env.pivot_y;
	return (p2);
}
