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

/* Opens and reads directories. The contents of directories is send to a 
** ft_insert_tree (a function for creating and appending to a b-tree),
** afterwhich the b-tree is printed, and in case of the -R option,
** directories are handled recursively*/

static void	ft_recursive_dir(t_file *ftree, t_flag *flags)
{
        if (flags->R)
	{
                ft_dirscan_tree(ftree, flags);
		ft_free_tree(ftree, flags); //FREE
	}
	else
		ft_free_tree(ftree, flags); //FREE
}

static blkcnt_t ft_read_dir(char *str, t_file **ftree, DIR *pDir, t_flag *flags)
{
        struct dirent   *pDirent;
        struct stat             buf;
        char                    *path;
        int     total;

        total = 0;
        while ((pDirent = readdir(pDir)) != NULL)
        {
                path = ft_path(str, pDirent->d_name);
                lstat(path, &buf);
                ft_insert_tree(ftree, pDirent->d_name, path, flags, buf);
		free(path);
                if (flags->a == 1 || (flags->a == 0 && pDirent->d_name[0] != '.'))
                	total = total + buf.st_blocks;
        }
        return (total);
}

int             ft_open_dir(char *str, t_flag *flags, int count)
{
        DIR                     *pDir;
        t_file                  *ftree;
        blkcnt_t                total;

        ftree = NULL;
        if (!(pDir = opendir(str)))
        {
                ft_printf("ft_ls: %s: %s\n", str, strerror(errno));
                return (-1);
        }
        if (count > 1)
                ft_printf("%s:\n", str);
       	total = ft_read_dir(str, &ftree, pDir, flags);
       	closedir (pDir);
        if (flags->l == 1)
        {
                if (total != 0)
                        ft_printf("total %llu\n", total);
                ft_allign_field(ftree, flags);
        }
        ft_print_tree(ftree, flags);
	ft_recursive_dir(ftree, flags);
        return (1);
}

/* Handles the parameters. Creates, appends to and print a b-tree for files.
** Creates, appends to and sorts a linked-list for directories, which is then
** send to the ft_open_dir function to be opened, read and printed.*/

void ft_direct(t_file *ptree, t_param *dlst, t_flag *flags, int count)
{
	t_param	*begin;

	if (flags->l == 1)
		ft_allign_field(ptree, flags);
	ft_print_tree(ptree, flags);
	if (ptree && dlst)
		write(1, "\n", 1);
	ft_free_tree(ptree, flags); //FREE 
	ft_param_sort(dlst, flags);
	begin = dlst;
	while (dlst)
	{
		ft_open_dir(dlst->name, flags, count);
		if ((dlst = dlst->next) != NULL)
			write(1, "\n", 1);
	}
	ft_free_list(begin); //FREE
}

void    ft_ls(int ac, char **av, int i, t_flag *flags)
{
    struct stat buf;
    t_param     *dlst;
    t_file      *ptree;
    int         count;

    dlst = NULL;
    ptree = NULL;
    count = 0;
    if (!av[i + 1])
        dlst = ft_dir_list(dlst, ".", 0);
    while (++i < ac)
    {
        if (lstat(av[i], &buf) == -1)
		ft_printf("ft_ls: %s: %s\n", av[i], strerror(errno));
	else
	{
		if (ft_type(ft_itoa_base(buf.st_mode, 8)) == 'd')
            		dlst = ft_dir_list(dlst, av[i], buf.st_mtime);
        	else
			ft_insert_tree(&ptree, av[i], av[i], flags, buf);
	}
        count++;
    }
    ft_direct(ptree, dlst, flags, count);
}
