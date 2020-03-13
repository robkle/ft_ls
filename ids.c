/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:19:33 by rklein            #+#    #+#             */
/*   Updated: 2020/03/10 16:44:02 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_user(uid_t st_uid)
{
	struct passwd	*u;

	u = getpwuid(st_uid);
	return (ft_strdup(u->pw_name));
}

char	*ft_group(gid_t st_gid)
{
	struct group	*g;

	g = getgrgid(st_gid);
	return (ft_strdup(g->gr_name));
}
