#include "ft_ls.h"

static int	ft_noflag(char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	write(1, &c, 1);
	write(1, "\nusage: ft_ls [-Ralrt] [file ...]\n", 34); 	
	return (-1);
}

static int	ft_isflag(char c, char	*ref)
{
	while (*ref)
	{
		if (c == *ref)
			return (1);
		ref++;
	}
	return (0);
}

int			ft_flags(int ac, char **av, t_flag *flags)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-' && !av[i][2])
			return (i + 1);
		j = 0;
		while (av[i][++j])
		{
			if (!ft_isflag(av[i][j], "alrRt"))
				return (ft_noflag(av[i][j]));
			if (av[i][j] == 'a')
			  	flags->a = 1;
			if (av[i][j] == 'l')
				flags->l = 1;
			if (av[i][j] == 'r')
			  	flags->r = 1;
			if (av[i][j] == 'R')
			  	flags->R = 1;
			if (av[i][j] == 't')
			  	flags->t = 1;
		}
	}
	return (i);
}
