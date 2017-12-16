/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:46:20 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 21:37:21 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_check_file(int *fd, char *fn, t_env *env)
{
	int			lines;
	intmax_t	cols;
	intmax_t	t_cols;
	char		*str;
	char		**tmp;

	lines = 0;
	cols = 0;
	while (ft_get_next_line(*fd, &str) == 1 && ++lines)
	{
		ft_count_points(&t_cols, (tmp = ft_strsplit(str, ' ')), env);
		!cols ? cols = t_cols : 0;
		cols && t_cols != cols ?
			exit(ft_printf("Error: %s: File is invalid\n", fn) * 0 - 1) : 0;
		ft_clean_trash(str, tmp);
	}
	if (!lines)
		exit(ft_printf("Error: %s: File is empty\n", fn) * 0 - 1);
	close(*fd);
	(*fd = open(fn, O_RDONLY)) == -1 ? ft_error_handler("Error", fn) : 0;
}

void	ft_validate(int *fd, int ac, char **av, t_env *env)
{
	if (ac < 2)
		exit(ft_printf("Usage: ./fdf <filename> [ wf color_set ]\n\
	[wf]:\t\twire frame mode\n\
	[color_set]:\t(zero_color high_color low_color)\n") * 0);
	ac == 3 && !ft_strcmp(av[2], "wf") ? env->wf_mode = 1 : 0;
	if (ac == 6 && !ft_strcmp(av[2], "color_set"))
	{
		env->zero_c = ft_atol_base(av[3], 16);
		env->high_c = ft_atol_base(av[4], 16);
		env->low_c = ft_atol_base(av[5], 16);
	}
	(*fd = open(av[1], O_RDONLY)) == -1 ? ft_error_handler("Error", av[1]) : 0;
	read(*fd, NULL, 0) == -1 ? ft_error_handler("Error", av[1]) : 0;
	ft_check_file(fd, av[1], env);
	ft_invitation();
}

void	ft_invitation(void)
{
	ft_printf("{green}|----------------------------------------------------|\n\
|--------------------{white}INSTRUCTIONS{green}--------------------|\n\
|----------------------------------------------------|\n\
|                                                    |\n\
|{nc} {cyan}! U can rotate figure use {red}WASD{cyan} buttons !           \
{green}|\n\
| {cyan}! U can move figure on display, use {red}ARROW KEYS{cyan} !   \
{green}|\n\
| {cyan}! U can scale figure, {red}SCROLL MOUSE{cyan} to scale it !   \
{green}|\n\
| {cyan}! Press {red}MOUSE LEFT BUTTON{cyan} to move                  \
{green}|\n\
|                       {cyan}figure next to your cursor ! {green}|\n\
| {cyan}! Press {red}MOUSE RIGHT BUTTON{cyan} to move                 \
{green}|\n\
|              {cyan}figure next to center of the window ! {green}|\n\
|                                                    |\n\
|----------------------------------------------------|{nc}\n");
}
