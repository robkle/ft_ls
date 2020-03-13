#include "ft_ls.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_flag	*flags;
	int		i;
	
	flags = malloc(sizeof(t_flag));
	i = 1;
	if (argc > 1)
		i = ft_flags(argc, argv, flags);
	ft_ls(argc, argv, i, flags);
	return (0);
}
