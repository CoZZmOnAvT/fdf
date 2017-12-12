/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:53:29 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/12 17:25:31 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	g_env = {
	.width = 800,
	.height = 800,
	.rx = 45,
	.ry = 45,
	.rz = 0,
	.pivot_x = 400,
	.pivot_y = 400,
};

void	ft_draw_line(t_point p1, t_point p2)
{
	double	t;
	t_point	p_t1;
	t_point	p_t2;

	p_t1 = ft_xyztoxy(p1);
	p_t2 = ft_xyztoxy(p2);
	t = -0.001;
	while ((t += 0.001) <= 1.0)
		mlx_pixel_put(g_env.mlx_p, g_env.win, round(p_t1.x + (p_t2.x - p_t1.x) * t),
			round(p_t1.y + (p_t2.y - p_t1.y) * t), ft_g_color(p1.color, p2.color, t));
}

void	ft_draw(void)
{
	mlx_clear_window(g_env.mlx_p, g_env.win);
	ft_draw_line((t_point){-100, -100, 100, 0xFF0000}, (t_point){100, -100, 100, 0x0000FF});
	ft_draw_line((t_point){-100, -100, 100, 0xFFFF00}, (t_point){-100, 100, 100, 0x0000FF});
	ft_draw_line((t_point){100, 100, 100, 0xFF0000}, (t_point){-100, 100, 100, 0x0000FF});
	ft_draw_line((t_point){100, 100, 100, 0xFF0000}, (t_point){100, -100, 100, 0xFF0000});

	ft_draw_line((t_point){-100, 100, 100, 0xFF0000}, (t_point){-100, 100, -100, 0x0000FF});
	ft_draw_line((t_point){100, 100, 100, 0xFF0000}, (t_point){100, 100, -100, 0x0000FF});
	ft_draw_line((t_point){-100, 100, -100, 0x00FF00}, (t_point){100, 100, -100, 0xFFFFFF});

	ft_draw_line((t_point){-100, -100, 100, 0xFF0000}, (t_point){-100, -100, -100, 0x0000FF});
	ft_draw_line((t_point){100, -100, 100, 0xFF0000}, (t_point){100, -100, -100, 0x0000FF});
	ft_draw_line((t_point){-100, -100, -100, 0xFF0000}, (t_point){100, -100, -100, 0x0000FF});

	ft_draw_line((t_point){-100, -100, -100, 0xFF0000}, (t_point){-100, 100, -100, 0x0000FF});
	ft_draw_line((t_point){100, -100, -100, 0xFF0000}, (t_point){100, 100, -100, 0x0000FF});
}

int		key_handler(int key)
{
	int	event;

	event = 0;
	key == KEY_A && (++event) ? g_env.ry = (long)(g_env.ry + 5) % 360 : 0;
	key == KEY_D && (++event) ? g_env.ry = (long)(g_env.ry - 5) % 360 : 0;
	key == KEY_W && (++event) ? g_env.rx = (long)(g_env.rx - 5) % 360 : 0;
	key == KEY_S && (++event) ? g_env.rx = (long)(g_env.rx + 5) % 360 : 0;
	key == KEY_Q && (++event) ? g_env.rz = (long)(g_env.rz + 5) % 360 : 0;
	key == KEY_E && (++event) ? g_env.rz = (long)(g_env.rz - 5) % 360 : 0;
	key == KEY_ESC ? exit(0) : 0;
	event ? ft_draw() : 0;
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		ft_printf("Usage: ./fdf <filename>\n");
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	g_env.mlx_p = mlx_init();
	g_env.win = mlx_new_window(g_env.mlx_p, g_env.height, g_env.width, "FdF");
	ft_draw();
	mlx_hook(g_env.win, 2, 0, &key_handler, g_env.mlx_p);
	mlx_hook(g_env.win, 17, 0, (int (*)())&exit, g_env.mlx_p);
	mlx_loop(g_env.mlx_p);
	return (0);
}
