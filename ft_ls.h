#ifndef FT_LS_H
# define FT_LS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>
#include "libft/libft.h"

typedef struct	s_flag
{
	_Bool	a;
	_Bool	l;
	_Bool	r;
	_Bool	R;
	_Bool	t;
}				t_flag;

typedef struct	s_param
{
	char			*name;
	time_t			secs;
	struct s_param	*next;
}				t_param;

typedef struct	s_dir
{
	char			*name;
	struct s_dir	*next;
}				t_dir;

typedef struct	s_file
{
	char			*name;
	char			*sl_path;
	char			*path;
	time_t			secs;
	char			*mode;
	char			*bytes;
	char			*links;
	char			*user;
	char			*group;	
	struct s_file	*left;
	struct s_file	*right;
}				t_file;

int		ft_flags(int ac, char **av, t_flag *flags);
void    ft_ls(int ac, char **av, int i, t_flag *flags);
void    *ft_param_sort(t_param *param, t_flag *flags);
t_param	*ft_dir_list(t_param *dlst, char *str, time_t secs);
char 	ft_type(char *type);
void    ft_insert_tree(t_file **ftree, char *str, char *path, t_flag *flags, struct stat buf);
void	ft_print_tree(t_file *ftree, t_flag *flags);
int  	ft_seccmp(time_t a, time_t b);
int	ft_open_dir(char *str, t_flag *flags, int count);
void	ft_dirscan_tree(t_file *ftree, t_flag *flags);
void 	ft_direct(t_file *ptree, t_param *dlst, t_flag *flags, int count);
char    *ft_mode(char *mode);
char    *ft_date(time_t secs);
char	*ft_path(char *path, char *file);
void    ft_allign_field(t_file *ftree, t_flag *flags);
char    *ft_user(uid_t st_uid);
char    *ft_group(gid_t st_gid);
char    *ft_sl_path(char *path);
void    ft_bytes(t_file *ftree, struct stat buf);
void	ft_free_tree(t_file *ftree, t_flag *flag);
void	ft_free_list(t_param *list);
#endif
