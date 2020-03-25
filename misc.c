/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:08:14 by rklein            #+#    #+#             */
/*   Updated: 2020/03/11 15:03:09 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* The ft_seccmp fucntion is called in the case of the -t option flag. 
** It compares the time of last modification of files. */ 

int  ft_seccmp(time_t a, time_t b)
{
	if (a < b)
		return (1);
	else if (a > b)
		return (-1);
	else
		return (0);
}

/* The ft_path function creates a string of the relative path, which is needed
** when files are listed recursively (-R option flag). */

char	*ft_path(char *path, char *file)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, file);
	free(tmp);
	return (str);
}

/* The ft_sl_path creates a string of the path of a symbolic link, which is
** displayed in the long format (-l option flag), after the file name*/

char	*ft_sl_path(char *path)
{
	char	*sl_path;

	sl_path = ft_strjoin("-> ", path);
	return (sl_path);
}
