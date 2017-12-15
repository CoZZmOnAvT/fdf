/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squad_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:52:26 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/15 17:30:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_squad		*ft_new_squad(t_squad tmp)
{
	t_squad		*new;

	if (!(new = (t_squad *)malloc(sizeof(t_squad))))
		return (NULL);
	new->a = tmp.a;
	new->b = tmp.b;
	new->c = tmp.c;
	new->d = tmp.d;
	new->next = NULL;
	return (new);
}

t_squad		*ft_push_back_squad(t_squad **dest, t_squad tmp)
{
	t_squad		*new;
	t_squad		*d_t;

	if (!dest || !(new = ft_new_squad(tmp)))
		return (NULL);
	d_t = *dest;
	while (*dest)
		dest = &(*dest)->next;
	*dest = new;
	return (d_t);
}

void		ft_add_squads(t_object *o)
{
	int		it[2];

	it[0] = -1;
	while (o->p[++it[0]] && (it[1] = -1))
		while (o->p[it[0]][++it[1]].color != -1)
			if (o->p[it[0]][it[1] + 1].color != -1 && o->p[it[0] + 1])
				ft_push_back_squad(&o->squads, (t_squad){o->p[it[0]][it[1]],
					o->p[it[0]][it[1] + 1], o->p[it[0] + 1][it[1] + 1],
					o->p[it[0] + 1][it[1]], NULL});
}
