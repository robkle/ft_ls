/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:57:17 by rklein            #+#    #+#             */
/*   Updated: 2020/03/12 14:47:28 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> //TEMP

/* Opens and reads directories. The contents of directories is send to a 
** ft_insert_tree (a function for creating and appending to a b-tree),
** afterwhich the b-tree is printed, and in case of the -R option,
** directories are handled recursively*/

int		ft_read_dir(char *str, t_flag *flags, int count) //STATIC FOR NOW
{
	struct dirent	*pDirent;
	struct stat		buf;
	DIR				*pDir;
	t_file			*ftree;
	blkcnt_t		total;
	char			*path;

	ftree = NULL;
	if (!(pDir = opendir(str)))
	{
		printf("ft_ls: %s: %s\n", str, strerror(errno));
		return (-1);
	}
	if (count > 1)
		printf("\n%s:\n", str); //temporary; only works with multiple files/dirs
	total = 0;
	while ((pDirent = readdir(pDir)) != NULL)
	{
		path = ft_path(str, pDirent->d_name);
		lstat(path, &buf);
		ft_insert_tree(&ftree, pDirent->d_name, path, flags, buf);
		if (flags->a == 1 || (flags->a == 0 && pDirent->d_name[0] != '.'))
			total = total + buf.st_blocks;
	}
	closedir (pDir);
	if (flags->l == 1)
	{	
		printf("total %llu\n", total); //should not display if dir is empty
		ft_allign_field(ftree, flags); //ADD FLAGS TO TAKE INTO ACCOUNT ., .. and .files
	}
	ft_print_tree(ftree, flags);
	if (flags->R)
		ft_dirscan_tree(ftree, flags);
	return (1);
}

/* Handles the parameters. Creates, appends to and print a b-tree for files.
** Creates, appends to and sorts a linked-list for directories, which is then
** send to the ft_read_dir function to be opened, read and printed.*/

void ft_direct(t_file *ptree, t_param *dlst, t_flag *flags, int count)
{
    ft_allign_field(ptree, flags);
	ft_print_tree(ptree, flags);
    ft_param_sort(dlst, flags);
    while (dlst)
    {
        ft_read_dir(dlst->name, flags, count);
        dlst = dlst->next;
    }
    //free dlst
}

void    ft_ls(int ac, char **av, int i, t_flag *flags)
{
    struct stat buf;
	char		type;
    t_param     *dlst;
    t_file      *ptree;
    int         count;

    dlst = NULL;
    ptree = NULL;
    count = 0;
    if (!av[i])
        dlst = ft_dir_list(dlst, ".", 0);
    while (i < ac)
    {
        if (lstat(av[i], &buf) == -1)
			printf("ft_ls: %s: No such file or directory\n", av[i]);
		else
		{
			type = ft_type(ft_itoa_base(buf.st_mode, 8));
            if (type == 'd')
            	dlst = ft_dir_list(dlst, av[i], buf.st_mtime);
        	else
				ft_insert_tree(&ptree, av[i], av[i], flags, buf);
		}
        count++;
        i++;
    }
    ft_direct(ptree, dlst, flags, count);
}
