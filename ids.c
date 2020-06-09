/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:19:33 by rklein            #+#    #+#             */
/*   Updated: 2020/06/09 16:51:39 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Functions to retrieve the user and group ids
*/

char	*ft_user(uid_t st_uid)
{
	struct passwd	*u;

	if (!(u = getpwuid(st_uid)))
	{
		if (u == 0)
			return (ft_itoa(st_uid));
		else
			return (NULL);
	}
	return (ft_strdup(u->pw_name));
}

char	*ft_group(gid_t st_gid)
{
	struct group	*g;

	if (!(g = getgrgid(st_gid)))
	{
		if (g == 0)
			return (ft_itoa(st_gid));
		else
			return (NULL);
	}
	return (ft_strdup(g->gr_name));
}
