/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:47:48 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 14:47:54 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_handler(int key, t_rash *t)
{
	char	e;

	e = 0;
	key == KEY_A && (++e) ? t->env->ry = (long)(t->env->ry + 5) % 360 : 0;
	key == KEY_D && (++e) ? t->env->ry = (long)(t->env->ry - 5) % 360 : 0;
	key == KEY_W && (++e) ? t->env->rx = (long)(t->env->rx - 5) % 360 : 0;
	key == KEY_S && (++e) ? t->env->rx = (long)(t->env->rx + 5) % 360 : 0;
	key == KEY_Q && (++e) ? t->env->rz = (long)(t->env->rz + 5) % 360 : 0;
	key == KEY_E && (++e) ? t->env->rz = (long)(t->env->rz - 5) % 360 : 0;
	key == KEY_ARR_UP && (++e) ?
		t->env->pivot_y = t->env->pivot_y - 5 * t->env->scale : 0;
	key == KEY_ARR_DOWN && (++e) ?
		t->env->pivot_y = t->env->pivot_y + 5 * t->env->scale : 0;
	key == KEY_ARR_LEFT && (++e) ?
		t->env->pivot_x = t->env->pivot_x - 5 * t->env->scale : 0;
	key == KEY_ARR_RIGHT && (++e) ?
		t->env->pivot_x = t->env->pivot_x + 5 * t->env->scale : 0;
	key == KEY_ESC ? exit(0) : 0;
	e ? ft_parse_z_buffer(*t->plane, t->z_buff, *t->env) : 0;
	return (0);
}

int		mouse_handler(int key, int x, int y, t_rash *t)
{
	char	e;
	char	rc;

	e = 0;
	rc = 0;
	key == M_B_LEFT && (++e) ? (t->env->pivot_x = x)
		&& (t->env->pivot_y = y) : 0;
	key == M_B_RIGHT && (++e) ? (t->env->pivot_x = DEFAULT_CENTER)
		&& (t->env->pivot_y = DEFAULT_CENTER) : 0;
	key == M_SCROLL_UP && (++e) && (++rc) ? t->env->scale += 0.3 : 0;
	key == M_SCROLL_DOWN && t->env->scale > 0.3 && (++e)
		&& (++rc) ? t->env->scale -= 0.3 : 0;
	if (rc)
	{
		ft_recalc_points(t->plane, *t->env);
		ft_recalc_squads(*t->plane);
	}
	e ? ft_parse_z_buffer(*t->plane, t->z_buff, *t->env) : 0;
	return (0);
}

void	ft_error_handler(char *err)
{
	perror(err);
	exit(errno);
}
