/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:57:21 by rklein            #+#    #+#             */
/*   Updated: 2020/06/05 12:37:17 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Functions to retrieve the file size, or the major and minor device numbers
** in the case of block files and character files. These functions are only
** called in the case of the -l option flag (i.e. long format)
*/

static void	ft_device(t_file *ftree, struct stat buf)
{
	unsigned int	dev_num[2];
	char			*dn_str[2];
	char			*tmp[2];
	int				i;

	dev_num[0] = ((buf.st_rdev) >> 24) & 0xff;
	dev_num[1] = (buf.st_rdev) & 0xff;
	i = -1;
	while (++i < 2)
	{
		tmp[0] = ft_itoa(dev_num[i]);
		tmp[1] = ft_strmake(' ', 3 - ft_strlen(tmp[0]));
		dn_str[i] = ft_strjoin(tmp[1], tmp[0]);
		free(tmp[0]);
		free(tmp[1]);
	}
	tmp[0] = ft_strjoin(dn_str[0], ", ");
	free(dn_str[0]);
	ftree->bytes = ft_strjoin(tmp[0], dn_str[1]);
	free(tmp[0]);
	free(dn_str[1]);
}

void		ft_bytes(t_file *ftree, struct stat buf)
{
	if (ftree->mode[0] == 'b' || ftree->mode[0] == 'c')
		ft_device(ftree, buf);
	else
		ftree->bytes = ft_itoa(buf.st_size);
}
