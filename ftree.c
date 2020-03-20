/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:12:29 by rklein            #+#    #+#             */
/*   Updated: 2020/03/12 14:47:32 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_info_tree(t_file *ftree, char *str, char *path, struct stat buf, t_flag *flags)
{
	char	sl_buf[256];
	int		buf_size;
		
	ftree->name = ft_strdup(str);
	ftree->path = ft_strdup(path);
	ftree->secs = buf.st_mtime;
	ftree->mode = ft_mode(ft_itoa_base(buf.st_mode, 8));
	if (flags->l == 1)
	{
		if (ftree->mode[0] == 'l')
		{
			buf_size = 256;
			readlink(ftree->path, sl_buf, buf_size);
			ftree->sl_path = ft_sl_path(sl_buf);
		}
		else
			ftree->sl_path = NULL;
		ft_bytes(ftree, buf);
		ftree->links = ft_itoa(buf.st_nlink);
		ftree->user = ft_user(buf.st_uid);
		ftree->group = ft_group(buf.st_gid);
	}
	ftree->left = NULL;
	ftree->right = NULL;
}

/* Function to create and append file names to a binary tree. The pointer to the
** specific position in the tree is send to ft_info_tree to add info required by
** the -l option.*/

void	ft_insert_tree(t_file **ftree, char *str, char *path, t_flag *flags, struct stat buf)
{
	int			cmp;

	if (*ftree == NULL)
	{
		*ftree = malloc(sizeof(t_file));
		ft_info_tree(*ftree, str, path, buf, flags);
	}
	else
	{
		if (flags->t == 1)
		{
			cmp = ft_seccmp(buf.st_mtime, (*ftree)->secs);
			if (cmp == 0)
				cmp = ft_strcmp(str, (*ftree)->name);
		}
		else
			cmp = ft_strcmp(str, (*ftree)->name);
		if ((cmp <= 0 && !flags->r) || (cmp >= 0 && flags->r))
			ft_insert_tree(&(*ftree)->left, str, path, flags, buf);
		else
			ft_insert_tree(&(*ftree)->right, str, path, flags, buf);
	}
}

static void	ft_print_files(t_file *ftree, t_flag *flags)
{
	char	*date;

	if (flags->l == 1)
	{
		ft_printf("%s ", ftree->mode);
		ft_printf("%s ", ftree->links);
		ft_printf("%s  ", ftree->user);
		ft_printf("%s  ", ftree->group);
		ft_printf("%s ", ftree->bytes);
		date = ft_date(ftree->secs);
		ft_printf("%s ", date);
	//	free(date);
		if (ftree->sl_path)
			ft_printf("%s %s\n",ftree->name, ftree->sl_path);
		else
			ft_printf("%s\n", ftree->name);
	}
	else
		ft_printf("%s\n", ftree->name);
}

/* Navigates through the b-tree and sends each file to ft_print_files to be 
** printed.*/
 
void	ft_print_tree(t_file *ftree, t_flag *flags)
{
	if (ftree)
	{
		ft_print_tree(ftree->left, flags);
		if (flags->a == 1 && ftree->name[0] == '.')
			ft_print_files(&*ftree, flags);
		else if (ftree->name[0] != '.')
			ft_print_files(&*ftree, flags);
		ft_print_tree(ftree->right, flags);
	}
}

/* Only used for the -R (recursive) option. Searches thee b-tree for directories
** and sends each one  back to the ft_read_dir function.*/

void	ft_dirscan_tree(t_file *ftree, t_flag *flags)
{
	if (ftree)
	{
		ft_dirscan_tree(ftree->left, flags);
		if (ftree->mode[0] == 'd')
		{
			if (ft_strcmp(ftree->name, ".")  != 0 && ft_strcmp(ftree->name, "..") != 0)
			{
				if (flags->a == 1 || (flags->a == 0 && ftree->name[0] != '.'))
				{
					write(1, "\n", 1);
					ft_read_dir(ftree->path, flags, 2);
				}
			}
		}
		ft_dirscan_tree(ftree->right, flags);
	}
}

