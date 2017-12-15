/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:53:29 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/15 20:16:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	int				fd;
	static t_object	plane;
	t_point			**z_buff;
	static t_env	env;
	t_rash			trash;

	env = (t_env){.width = W_WIDTH, .height = W_HEIGHT, .rx = 45, .ry = 45,
		.rz = 0, .pivot_x = DEFAULT_CENTER, .pivot_y = DEFAULT_CENTER,
		.scale = 3, .wf_color = 0xFFFFFF, .wf_mode = 0};
	ac < 2 ? exit(ft_printf("Usage: ./fdf <filename> [ wf_mode ]\n") * 0) : 0;
	ac == 3 && !ft_strcmp(av[2], "wf") ? env.wf_mode = 1 : 0;
	(fd = open(av[1], O_RDONLY)) == -1 ? exit(-1) : 0;
	ft_input(fd, av[1], &plane, env);
	ft_add_squads(&plane);
	z_buff = ft_init_z_buffer();
	env.mlx_p = mlx_init();
	env.win = mlx_new_window(env.mlx_p, env.height, env.width, "FdF");
	ft_parse_z_buffer(plane, z_buff, env);
	trash = (t_rash){&env, &plane, z_buff};
	mlx_hook(env.win, 2, 0, &key_handler, &trash);
	mlx_mouse_hook(env.win, &mouse_handler, &trash);
	mlx_hook(env.win, 17, 0, (int (*)())&exit, &trash);
	mlx_loop(env.mlx_p);
	return (0);
}
