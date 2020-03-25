/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:44:59 by rklein            #+#    #+#             */
/*   Updated: 2020/03/12 14:47:54 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Functions to allign the text in the long format (-l), by creating spacepads.
** First the length of the spacepad is determined with ft_scan_len, recursively
** going through the binary tree, finding the longest string in each column. 
** The function ft_space_allign goes through the binary tree recursively 
** adding a spacepad through the ft_create_pad function, adding padding to the
** front or back ('f' or 'b')*/

static void	ft_scan_len(t_file *ftree, t_flag *flags, int *len)
{
	int	tmp;

	if (ftree)
	{
		ft_scan_len(ftree->left, flags, len);
		if (flags->a == 1 || (flags->a == 0 && ftree->name[0] != '.'))
		{
			tmp = ft_strlen(ftree->links);
			len[0] = tmp > len[0] ? tmp : len[0];
			tmp = ft_strlen(ftree->user);
			len[1] = tmp > len[1] ? tmp : len[1];
			tmp = ft_strlen(ftree->group);
			len[2] = tmp > len[2] ? tmp : len[2];
			tmp = ft_strlen(ftree->bytes);
			len[3] = tmp > len[3] ? tmp : len[3];
		}
		ft_scan_len(ftree->right, flags, len);
	}
}

static void	ft_create_pad(char **str, int len, char c)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strmake(' ', len - ft_strlen(*str));
	tmp2 = (c == 'f') ? ft_strjoin(tmp1, *str) : ft_strjoin(*str, tmp1);
	free(*str);
	free(tmp1);
	*str = tmp2;
}

static void	ft_space_allign(t_file *ftree, int *len)
{
	if (ftree)
	{
		ft_space_allign(ftree->left, len);
		ft_create_pad(&ftree->links, len[0], 'f');
		ft_create_pad(&ftree->user, len[1], 'b');
		ft_create_pad(&ftree->group, len[2], 'b');
		ft_create_pad(&ftree->bytes, len[3], 'f');
		ft_space_allign(ftree->right, len);
	}
}

void	ft_allign_field(t_file *ftree, t_flag *flags)
{
	int	len[4];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	len[3] = 0;

	ft_scan_len(ftree, flags, len);
	ft_space_allign(ftree, len);
}
