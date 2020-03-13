/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:57:21 by rklein            #+#    #+#             */
/*   Updated: 2020/03/12 14:48:02 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_bytes(t_file *ftree, struct stat buf)
{
	unsigned int	dev_num[2];
	char			*dn_str[2];
	char			*tmp[2];
	int				i;

	if (ftree->mode[0] == 'b' || ftree->mode[0] == 'c')
	{
		dev_num[0] = ((buf.st_rdev) >> 24) & 0xff;
		dev_num[1] = (buf.st_rdev) & 0xff;
		i = -1;
		while (++i < 2)
		{
			tmp[0] = ft_itoa(dev_num[i]);
			tmp[1] = ft_strmake(' ', 4 - ft_strlen(tmp[0]));
			dn_str[i] = ft_strjoin(tmp[1], tmp[0]);
			free(tmp[0]);
			free(tmp[1]);
		}
		tmp[0] = ft_strjoin(dn_str[0], ",");
		free(dn_str[0]);
		ftree->bytes = ft_strjoin(tmp[0], dn_str[1]);
		free(tmp[0]);
		free(dn_str[1]);
	}
	else
		ftree->bytes = ft_itoa(buf.st_size);
}
