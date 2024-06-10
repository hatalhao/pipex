/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/10 07:00:00 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"
#include <sys/wait.h>

typedef	struct		s_cmd
{
	char			*path;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct	s_data
{
	int		ac;
	char	**av;
	char	**envp;
	char	**paths;
	int		pid;
	int		*fd;
	int		*pfd;
}				t_data;

/*			utiles.c		*/
void	executions(t_cmd **list, t_data *info);
void	file_to_pipe(t_data *info, t_cmd *cmd);
void	pipe_to_pipe(t_data *info, t_cmd *cmd);
void	pipe_to_file(t_data *info, t_cmd *cmd);

/*			utiles2.c		*/
t_cmd	*last_node(t_cmd *list);
t_cmd	*mk_node(t_data *info, char *av);
void	mid_cmd(t_cmd *cmd, int *pfd);
void	last_cmd(char **av, t_cmd *cmd, int *fd, int *pfd);
void	first_cmd(char **av, t_cmd *cmd, int *fd, int *pfd);

/*			utiles3.c		*/
void	free_arr(char **arr);
void	free_struct(t_cmd *cmd);
void	free_list(t_cmd **list);


/*			utiles4.c		*/
char	**get_args(char *cmd);
char	**get_paths(char *envp);
char	*envp_path(char **envp);
char	*extract_path(char **paths, t_cmd *cmd);

#endif