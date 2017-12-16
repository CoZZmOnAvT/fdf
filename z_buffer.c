/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:20:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 20:03:44 by pgritsen         ###   ########.fr       */
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

void	ft_debug_info(t_object o, t_env e, int p_d)
{
	char		*s;

	mlx_string_put(e.mlx_p, e.win, 10, 5, 0X008C00, "FdF - 42");
	mlx_string_put(e.mlx_p, e.win, 10, 25, 0X008C00, "Author: pgritsen");
	mlx_string_put(e.mlx_p, e.win, 10, 45, 0X008C00, "Polygons: ");
	mlx_string_put(e.mlx_p, e.win, 110, 45, 0X008C00, (s = ft_itoa(o.sd_c)));
	ft_memdel((void **)&s);
	mlx_string_put(e.mlx_p, e.win, 10, 65, 0X008C00, "Pixels: ");
	s = p_d
		? (s = ft_itoa(p_d)) : ft_strdup("nan");
	mlx_string_put(e.mlx_p, e.win, 90, 65, 0X008C00, s);
	ft_memdel((void **)&s);
	mlx_string_put(e.mlx_p, e.win, 10, 85, 0X008C00, "Rotate_X: ");
	mlx_string_put(e.mlx_p, e.win, 120, 85, 0X008C00, (s = ft_itoa(e.rx)));
	ft_memdel((void **)&s);
	mlx_string_put(e.mlx_p, e.win, 10, 105, 0X008C00, "Rotate_Y: ");
	mlx_string_put(e.mlx_p, e.win, 120, 105, 0X008C00, (s = ft_itoa(e.ry)));
	ft_memdel((void **)&s);
	mlx_string_put(e.mlx_p, e.win, 10, 125, 0X008C00, "Rotate_Z: ");
	mlx_string_put(e.mlx_p, e.win, 120, 125, 0X008C00, (s = ft_itoa(e.rz)));
	ft_memdel((void **)&s);
}

void	ft_fill_image(char *img_buff, t_point **z_buff, int *p_d, int d[3])
{
	int			xy[2];
	unsigned	c;

	xy[1] = -1;
	*p_d = 0;
	while (++xy[1] < W_HEIGHT && (xy[0] = -1))
		while (++xy[0] < W_WIDTH)
			if (z_buff[xy[1]][xy[0]].color
				&& z_buff[xy[1]][xy[0]].color != -1 && ++*p_d)
			{
				c = (unsigned)z_buff[xy[1]][xy[0]].color;
				if (d[1])
					ft_strrev((char *)&c);
				ft_memcpy(img_buff + xy[1] * d[0] + xy[0] * 4, &c, 4);
			}
}

void	ft_parse_z_buffer(t_object o, t_point **z_buff, t_env e)
{
	int			s_l;
	int			endian;
	int			bpp;
	void		*img;
	static int	p_d = 0;

	mlx_clear_window(e.mlx_p, e.win);
	ft_clear_z_buffer(z_buff);
	ft_draw_wireframe(o, z_buff, e);
	!e.wf_mode ? ft_draw_squads(o, z_buff, e) : 0;
	img = mlx_new_image(e.mlx_p, W_WIDTH, W_HEIGHT);
	ft_fill_image(mlx_get_data_addr(img, &bpp, &s_l, &endian),
		z_buff, &p_d, (int[3]){s_l, endian, bpp});
	mlx_put_image_to_window(e.mlx_p, e.win, img, 0, 0);
	ft_debug_info(o, e, p_d);
	mlx_destroy_image(e.mlx_p, img);
}
