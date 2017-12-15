/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:20:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/15 22:09:15 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**ft_init_z_buffer(void)
{
	t_point		**buff;
	intmax_t	it;

	if (!(buff = (t_point **)malloc(sizeof(t_point *) * W_HEIGHT)))
		exit(0);
	it = -1;
	while (++it < W_HEIGHT)
		if (!(buff[it] = (t_point *)malloc(sizeof(t_point) * W_WIDTH)))
			exit(0);
	return (buff);
}

void	ft_clear_z_buffer(t_point **z_buff)
{
	intmax_t	x;
	intmax_t	y;

	y = -1;
	while (++y < W_HEIGHT && (x = -1))
		while (++x < W_WIDTH)
			z_buff[y][x] = (t_point){0, 0, 0, 0};
}

void	ft_parse_z_buffer(t_object object, t_point **z_buff, t_env env)
{
	intmax_t	x;
	intmax_t	y;

	mlx_clear_window(env.mlx_p, env.win);
	ft_clear_z_buffer(z_buff);
	ft_draw_wireframe(object, z_buff, env);
	ft_draw_squads(object, z_buff, env);
	y = -1;
	while (++y < W_HEIGHT && (x = -1))
		while (++x < W_WIDTH)
			if (z_buff[y][x].color && z_buff[y][x].color != -1)
				mlx_pixel_put(env.mlx_p, env.win, x, y, z_buff[y][x].color);
}
