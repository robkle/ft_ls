/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:32:53 by rklein            #+#    #+#             */
/*   Updated: 2020/06/05 12:34:55 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_free_node(t_file *ftree, t_flag *flags)
{
	free(ftree->name);
	free(ftree->path);
	free(ftree->mode);
	if (flags->l == 1)
	{
		if (ftree->sl_path)
			free(ftree->sl_path);
		free(ftree->bytes);
		free(ftree->links);
		free(ftree->user);
		free(ftree->group);
	}
}

void		ft_free_tree(t_file *ftree, t_flag *flags)
{
	if (ftree == NULL)
		return ;
	ft_free_tree(ftree->left, flags);
	ft_free_tree(ftree->right, flags);
	ft_free_node(ftree, flags);
	free(ftree);
	ftree = NULL;
}

void		ft_free_list(t_param *list)
{
	t_param	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list->name);
		free(list);
		list = tmp;
	}
}
