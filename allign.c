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
#include <stdio.h>

static void	ft_scan_len(t_file *ftree, int *len)
{
	int	tmp;

	if (ftree)
	{
		ft_scan_len(ftree->left, len);
		tmp = ft_strlen(ftree->links);
		len[0] = tmp > len[0] ? tmp : len[0];
		tmp = ft_strlen(ftree->user);
		len[1] = tmp > len[1] ? tmp : len[1];
		tmp = ft_strlen(ftree->group);
		len[2] = tmp > len[2] ? tmp : len[2];
		tmp = ft_strlen(ftree->bytes);
		len[3] = tmp > len[3] ? tmp : len[3];
		ft_scan_len(ftree->right, len);
	}
}

char	*ft_strmake(char c, int size) //TEMPORARY; until ft_printf files are added
{
	char	*s;
	int		i;

	size = size < 0 ? 0 : size;
	if (!(s = (char*)malloc(sizeof(*s) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
		s[i++] = c;
	s[i] = '\0';
	return (s);
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

static void	ft_space_pad(t_file *ftree, int *len)
{
	if (ftree)
	{
		ft_space_pad(ftree->left, len);
		ft_create_pad(&ftree->links, len[0], 'f');
		ft_create_pad(&ftree->user, len[1], 'b');
		ft_create_pad(&ftree->group, len[2], 'b');
		ft_create_pad(&ftree->bytes, len[3], 'f');
		ft_space_pad(ftree->right, len);
	}
}

/*static void	ft_space_pad(t_file *ftree, int len, char c)
{
	char	*tmp1;
	char	*tmp2;

	if (ftree)
	{
		ft_space_pad(ftree->left, len, c);
		if (c == 'b')
		{
			tmp1 = ft_strmake(' ', len - ft_strlen(ftree->bytes));
			tmp2 = ft_strjoin(tmp1, ftree->bytes);
			free(ftree->bytes);
			free(tmp1);
			ftree->bytes = tmp2;
		}
		else if (c == 'l')
		{
			tmp1 = ft_strmake(' ', len - ft_strlen(ftree->links));
			tmp2 = ft_strjoin(tmp1, ftree->links);
			free(ftree->links);
			free(tmp1);
			ftree->links = tmp2;
		}
		ft_space_pad(ftree->right, len, c);
	}
}*/

void	ft_allign_field(t_file *ftree)
{
	int	len[4];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	len[3] = 0;

	ft_scan_len(ftree, len);
	ft_space_pad(ftree, len);
}
