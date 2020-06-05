/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:15:11 by rklein            #+#    #+#             */
/*   Updated: 2020/06/05 11:46:59 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		ft_type(char *type)
{
	char	c;

	if (ft_strlen(type) == 5)
	{
		if (type[0] == '4')
			c = 'd';
		else if (type[0] == '2')
			c = 'c';
		else if (type[0] == '6')
			c = 'b';
		else
			c = 'p';
	}
	else
	{
		if (type[1] == '0')
			c = '-';
		else if (type[1] == '2')
			c = 'l';
		else
			c = 's';
	}
	free(type);
	return (c);
}

static void	ft_permissions(char *perm, char *mode)
{
	int	len;
	int	i;

	len = ft_strlen(mode);
	i = 4;
	while (--i >= 0)
	{
		if (mode[len - i] == '0')
			perm = ft_strcat(perm, "---");
		else if (mode[len - i] == '1')
			perm = ft_strcat(perm, "--x");
		else if (mode[len - i] == '2')
			perm = ft_strcat(perm, "-w-");
		else if (mode[len - i] == '3')
			perm = ft_strcat(perm, "-wx");
		else if (mode[len - i] == '4')
			perm = ft_strcat(perm, "r--");
		else if (mode[len - i] == '5')
			perm = ft_strcat(perm, "r-x");
		else if (mode[len - i] == '6')
			perm = ft_strcat(perm, "rw-");
		else if (mode[len - i] == '7')
			perm = ft_strcat(perm, "rwx");
	}
}

static void	ft_set_perm(char *perm, char m)
{
	if (m == '4' || m == '5' || m == '6' || m == '7')
		perm[2] = (perm[2] == '-') ? 'S' : 's';
	if (m == '2' || m == '3' || m == '6' || m == '7')
		perm[5] = (perm[5] == '-') ? 'S' : 's';
	if (m == '1' || m == '3' || m == '5' || m == '7')
		perm[8] = (perm[8] == '-') ? 'T' : 't';
}

char		*ft_mode(char *mode)
{
	char		*perm;

	perm = ft_strnew(12);
	perm[0] = ft_type(mode);
	ft_permissions(perm, mode);
	ft_set_perm(perm, mode[ft_strlen(mode) - 4]);
	perm[10] = ' ';
	perm[11] = '\0';
	return (perm);
}
