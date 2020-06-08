/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:22:42 by rklein            #+#    #+#             */
/*   Updated: 2020/06/08 14:38:25 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_flag	*flags;
	int		i;

	flags = malloc(sizeof(t_flag));
	i = 1;
	if (argc > 1)
		i = ft_flags(argc, argv, flags);
	if (i == -1)
		return (0);
	ft_ls(argc, argv, i - 1, flags);
	free(flags);
	return (0);
}
