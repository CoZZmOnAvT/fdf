/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:53:29 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:05:51 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	int				fd;
	t_point			**z_buff;
	t_rash			trash;
	static t_object	plane;
	static t_env	env = {

	.width = W_WIDTH, .height = W_HEIGHT, .scale = 3,
	.rx = -45, .ry = 45, .rz = 0,
	.pivot_x = DEFAULT_CENTER, .pivot_y = DEFAULT_CENTER,
	.wf_color = 0xFFFFFF, .wf_mode = 0,
	.zero_c = 0x00FF00, .high_c = 0xFF0000, .low_c = 0x0000FF};
	ft_validate(&fd, ac, av, &env);
	ft_input(fd, av[1], &plane, &env);
	ft_add_squads(&plane);
	ft_printf("\n{green}Data was succesfuly parsed!\n{cyan}Enjoy...{nc}\n");
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
