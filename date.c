/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:22:11 by rklein            #+#    #+#             */
/*   Updated: 2020/06/05 12:35:46 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This function creates a string with the correct format of the date of the
** last modification. If the modification time of the file is more than
** 6 months in the past or future, then the year of the last modification is
** displayed else instead of the hour and minutes
*/

char	*ft_date(time_t secs)
{
	time_t	begin_sec;
	char	*full_date;
	char	*d1;
	char	*d2;
	char	*date;

	full_date = ctime(&secs);
	d1 = ft_strsub(full_date, 4, 7);
	begin_sec = time(&begin_sec);
	if (secs < (begin_sec - 15778476) || secs > (begin_sec + 15778476))
		d2 = ft_strsub(full_date, 19, 5);
	else
		d2 = ft_strsub(full_date, 11, 5);
	date = ft_strjoin(d1, d2);
	free(d1);
	free(d2);
	return (date);
}
