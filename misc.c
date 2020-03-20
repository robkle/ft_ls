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

/*char *ft_itoa_base(uintmax_t value, int base) //part of ft_printf in libft
{
    char        *base_char;
    char        *str;
    uintmax_t   tmp;
    int         len;

    base_char = "0123456789abcdef";
    tmp = value;
    len = 1;
    while (tmp /= base)
        len++;
    if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    str[len] = '\0';
    while (len-- > 0)
    {
        str[len] = base_char[value % base];
        value /= base;
    }
    return (str);
}*/

int  ft_seccmp(time_t a, time_t b)
{
	if (a < b)
		return (1);
	else if (a > b)
		return (-1);
	else
		return (0);
}

char	*ft_path(char *path, char *file)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, file);
	free(tmp);
	return (str);
}

char	*ft_sl_path(char *path)
{
	char	*arrow;

	arrow = ft_strdup("-> ");
	return(ft_strjoin(arrow, path));
}
