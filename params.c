#include "ft_ls.h"

/* Functions to sort a linked list of directories given as input, 
** lexicographically or chronologically depending on the given
** option*/

static void		ft_swap(t_param *param, t_param *temp)
{
	char	*tmp_name;
	time_t	tmp_sec;

	tmp_name = param->name;
	tmp_sec = param->secs;
	param->name = temp->name;
	param->secs = temp->secs;
	temp->name = tmp_name;
	temp->secs = tmp_sec;
}

static	t_param	*ft_data_sort(t_param *param, t_flag *flags, char sort)
{
	t_param 			*begin;
	t_param				*tmp_param;
	int					cmp;

	begin = param;
	while (param)
	{
		tmp_param = param->next;
		while (tmp_param)
		{
			if (sort == 'n')
				cmp = ft_strcmp(param->name, tmp_param->name);
			else
				cmp = ft_seccmp(param->secs, tmp_param->secs);
			if ((cmp > 0 && !flags->r) || (cmp < 0 && flags->r))
				ft_swap(param, tmp_param);
			tmp_param = tmp_param->next;
		}
		param = param->next;
	}
	return (begin);
}

void	*ft_param_sort(t_param *param, t_flag *flags)
{
	t_param	*begin;
	t_param *tmp;

	begin = param;
	ft_data_sort(param, flags, 'n');
	if (flags->t)
	{
		tmp = begin;
		ft_data_sort(tmp, flags, 't');
	}
	return (begin);
}

/* Functions to create and appending to a linked list of the directories given 
** as parameters*/ 

static void	ft_add_list(t_param *dlst, char *str, time_t secs)
{
	dlst->name = ft_strdup(str);
	dlst->secs = secs;
	dlst->next = NULL;
}
	
t_param	*ft_dir_list(t_param *dlst, char *str, time_t secs)
{
	t_param *tmp;
	t_param	*begin;
	
	if (dlst == NULL)
	{
		dlst = malloc(sizeof(t_param));
		begin = dlst;
		ft_add_list(dlst, str, secs);
	}
	else
	{
		tmp = dlst->next;
		while (tmp)
		{
			tmp = tmp->next;
			dlst = dlst->next;
		}
		dlst->next = malloc(sizeof(t_param));
		begin = dlst;
		dlst = dlst->next;
		ft_add_list(dlst, str, secs);
	}
	return (begin);
}
