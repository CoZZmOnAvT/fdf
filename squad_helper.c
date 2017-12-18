/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squad_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:52:26 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/18 15:51:58 by pgritsen         ###   ########.fr       */
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

t_squad		*ft_push_squad(t_squad **dest, t_squad tmp)
{
	t_squad		*new;

	if (!dest || !(new = ft_new_squad(tmp)))
		return (NULL);
	if (!*dest)
		return (*dest = new);
	new->next = *dest;
	*dest = new;
	return (*dest);
}

void		ft_add_squads(t_object *o)
{
	int		it[2];

	it[0] = -1;
	while (o->p[++it[0]] && (it[1] = -1))
		while (o->p[it[0]][++it[1]].color != -1)
			if (o->p[it[0]][it[1] + 1].color != -1 && o->p[it[0] + 1]
				&& ++o->sd_c)
				ft_push_squad(&o->squads, (t_squad){o->p[it[0]][it[1]],
					o->p[it[0]][it[1] + 1], o->p[it[0] + 1][it[1] + 1],
					o->p[it[0] + 1][it[1]], NULL});
}

void		ft_recalc_squads(t_object o)
{
	int		it[2];
	t_squad	*tmp;

	tmp = o.squads;
	it[0] = -1;
	while (o.p[++it[0]] && (it[1] = -1))
		while (o.p[it[0]][++it[1]].color != -1)
			if (o.p[it[0]][it[1] + 1].color != -1 && o.p[it[0] + 1])
			{
				tmp->a = o.p[it[0]][it[1]];
				tmp->b = o.p[it[0]][it[1] + 1];
				tmp->c = o.p[it[0] + 1][it[1] + 1];
				tmp->d = o.p[it[0] + 1][it[1]];
				tmp = tmp->next;
			}
}
