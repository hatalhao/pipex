/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/12 09:20:35 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		keeper;
	int		*fd;
	int		pipefd[2];
}				t_data;

/*			pipex.c			*/
void	pipex(int ac, char **av, char **envp);
void	add_to_list(t_cmd **list, t_cmd *new);
t_data	*assignements(t_data *info, int ac, char **av, char **envp);
// void	preliminaries(int ac, char **av, char **envp);


/*			utiles.c		*/
void	executions(t_cmd **list, t_data *info);
void	file_to_pipe(t_data *info, t_cmd *cmd);
void	pipe_to_pipe(t_data *info, t_cmd *cmd);
void	pipe_to_file(t_data *info, t_cmd *cmd);

/*			utiles2.c		*/
t_cmd	*last_node(t_cmd *list);
t_cmd	*make_node(t_data *info, char *av);
void	mid_cmd(t_cmd *cmd, t_data *info);
void	last_cmd(t_cmd *cmd, t_data *info);
void	first_cmd(t_cmd *cmd, t_data *info);

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