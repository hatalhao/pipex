/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:27:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 16:55:59 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <signal.h>
# include <sys/wait.h>

# define STDIN 0  /* Standard input.  */
# define STDOUT 1 /* Standard output.  */

typedef struct s_cmd
{
	char			*path;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*limiter;
	char			**av;
	char			**envp;
	char			**paths;
	int				ac;
	int				non_cmd;
	int				exit_status;
	int				keeper;
	int				infile;
	int				outfile;
	int				pipefd[2];
	pid_t			pid;
	pid_t			*pids;
}					t_data;

void				pipex(int ac, char **av, char **envp);
void				add_to_list(t_cmd **list, t_cmd *new_node);
void				final_curtain(t_cmd **list, t_data *info, int flag);
t_data				*assignements(t_data *info, int ac, char **av, char **envp);
/*					pipex.c							*/

void				error_exit(void);
void				file_to_pipe(t_data *info, t_cmd *cmd, t_cmd **list);
void				pipe_to_pipe(t_data *info, t_cmd *cmd, t_cmd **list);
void				pipe_to_file(t_data *info, t_cmd *cmd, t_cmd **list);
void				executions(t_cmd **list, t_data *info);
/*					execution.c						*/

t_cmd				*last_node(t_cmd *list);
t_cmd				*make_node(t_data *info, char *av);
/*					utiles2.c						*/

void				free_arr(char **arr);
void				free_node(t_cmd *cmd);
void				free_list(t_cmd **list);
/*					free_variants.c						*/

char				**get_args(char *cmd);
char				**get_paths(char *envp);
char				*envp_path(char **envp);
char				*extract_path(char **paths, t_cmd *cmd);
/*					args_and_paths.c					*/

void				clean_data_mandatory(t_data *info, int flag);
/*					cleaning.c*/

#endif