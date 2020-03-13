/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:15:11 by rklein            #+#    #+#             */
/*   Updated: 2020/03/10 14:44:30 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char ft_type(char *type)
{
    char c;

    if (ft_strlen(type) == 5)
    {
        if (type[0] == '4')
            c = 'd';
        else if (type[0] == '2')
            c = 'c';
        else if (type[0] == '6')
            c = 'b';
        else
            c = 'p';
    }
    else
    {
        if (type[1] == '0')
            c = '-';
        else if (type[1] == '2')
            c = 'l';
        else
            c = 's';
    }
    free(type);
    return (c);
}

static void	ft_permissions(char *perm, char *mode)
{
	int	len;
	int i;
	
	len = ft_strlen(mode);
	i = 4;
	while (--i >= 0)
	{
		if (mode[len - i] == '0')
			perm = ft_strcat(perm, "---");
		else if (mode[len - i] == '1')
			perm = ft_strcat(perm, "--x");
		else if (mode[len - i] == '2')
			perm = ft_strcat(perm, "-w-");
		else if (mode[len - i] == '3')
			perm = ft_strcat(perm, "-wx");
		else if (mode[len - i] == '4')
			perm = ft_strcat(perm, "r--");
		else if (mode[len - i] == '5')
			perm = ft_strcat(perm, "r-x");
		else if (mode[len - i] == '6')
			perm = ft_strcat(perm, "rw-");
		else if (mode[len - i] == '7')
			perm = ft_strcat(perm, "rwx");
	}
}

char	*ft_mode(char *mode)
{
	char		*perm;

	perm = ft_strnew(12);
	perm[0] = ft_type(mode);
	ft_permissions(perm, mode);
	perm[10] = ' '; //temporary: reserved for @ and +;
	perm[11] = '\0';
	return (perm);
}
