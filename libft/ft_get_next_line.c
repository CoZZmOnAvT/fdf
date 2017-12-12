/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:32:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:57:05 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	n_l_found(char *str)
{
	long	it;

	if (!str)
		return (-1);
	it = -1;
	while (str[++it])
		if (str[it] == '\n')
			return (it);
	return (-1);
}

t_list		*ft_find_file(t_list **files, const int fd)
{
	while (*files)
	{
		if ((int)(*files)->content_size == fd)
			return (*files);
		files = &(*files)->next;
	}
	ft_lstadd(files, ft_lstnew(ft_strnew(0), 0));
	(*files)->content_size = fd;
	return (*files);
}

static int	sync_buff(t_list *files, const int fd, char **line)
{
	long			n_l_pos;

	while (files)
	{
		if ((int)files->content_size == fd)
		{
			if ((n_l_pos = n_l_found(files->content)) != -1)
			{
				if (!(*line = ft_strsub(files->content, 0, n_l_pos)))
					return (-1);
				ft_strshift(files->content, n_l_pos + 1);
				return (1);
			}
			else if (!(*line = ft_strdup(files->content)))
				return (-1);
			ft_memdel(&files->content);
			return (0);
		}
		files = files->next;
	}
	*line = ft_strnew(0);
	return (0);
}

static int	cut_to_n_l(char *str, char *trash, long n_l_pos, char **line)
{
	if (!(*line = ft_strnjoin(trash, str, '\n')))
		return (-1);
	ft_memdel((void **)&trash);
	ft_strshift(str, n_l_pos + 1);
	return (1);
}

int			ft_get_next_line(const int fd, char **line)
{
	char			*buff;
	char			*tmp;
	static t_list	*files;
	t_list			*tmp_f;
	long			n_l_pos;

	if (!line)
		return (-1);
	tmp_f = ft_find_file(&files, fd);
	if ((n_l_pos = sync_buff(tmp_f, fd, line)))
		return (n_l_pos);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	while (read(fd, buff, BUFF_SIZE))
	{
		tmp_f->content = ft_strdup(buff);
		tmp = *line;
		if ((n_l_pos = n_l_found(tmp_f->content)) != -1)
			return (cut_to_n_l(tmp_f->content, tmp, n_l_pos, line));
		*line = ft_strjoin(*line, buff);
		ft_memdel((void **)&tmp);
	}
	return (0);
}
