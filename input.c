/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:57:31 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/16 17:59:43 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static intmax_t	ft_count_lines(int *fd, char *filename)
{
	int		lines;
	char	*str;

	lines = 0;
	while (ft_get_next_line(*fd, &str) == 1)
		lines++;
	close(*fd);
	if ((*fd = open(filename, O_RDONLY)) == -1)
		exit(0);
	return (lines);
}

static void		ft_count_points(intmax_t *c, char **row, t_env *env)
{
	int		h;

	*c = 0;
	while (*row++)
	{
		if (*row && (h = ft_atoi(*row)) > env->max_z)
			env->max_z = h;
		if (*row && h < env->min_z)
			env->min_z = h;
		(*c)++;
	}
}

void			ft_input(int fd, char *filename, t_object *object, t_env *env)
{
	char		*str;
	char		**tmp;
	intmax_t	s[2];
	int			xy[2];
	int			it[2];

	s[0] = ft_count_lines(&fd, filename);
	object->rows = s[0];
	!(object->p = malloc(sizeof(t_point *) * (s[0] + 1))) ? exit(0) : 0;
	it[0] = -1;
	xy[1] = s[0] / 2 * (-10 * env->scale);
	while (ft_get_next_line(fd, &str) == 1 && !(it[1] = 0))
	{
		ft_count_points(&s[1], (tmp = ft_strsplit(str, ' ')), env);
		xy[0] = (s[1] / 2 + 1) * (-10 * env->scale);
		!object->cols ? object->cols = s[1] : 0;
		!(object->p[++it[0]] = malloc(sizeof(t_point) * ++s[1])) ? exit(0) : 0;
		while (--s[1])
			object->p[it[0]][it[1]] = (t_point){xy[0] += (10 * env->scale),
				xy[1], (s[0] = ft_atoi(tmp[it[1]++])), 0};
		object->p[it[0]][it[1]] = (t_point){0, 0, 0, -1};
		xy[1] += (10 * env->scale);
	}
	object->p[++it[0]] = NULL;
}
