/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:27:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 04:27:05 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
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
}					t_data;

/*			pipex.c							*/
void				pipex(int ac, char **av, char **envp);
void				add_to_list(t_cmd **list, t_cmd *new);
void				final_curtain(t_cmd **list, t_data *info, int bool);
t_data				*assignements(t_data *info, int ac, char **av, char **envp);

/*			execution.c						*/
void				error_exit(char *str);
void				file_to_pipe(t_data *info, t_cmd *cmd);
void				pipe_to_pipe(t_data *info, t_cmd *cmd);
void				pipe_to_file(t_data *info, t_cmd *cmd);
void				executions(t_cmd *list, t_data *info);

/*			utiles2.c						*/
t_cmd				*last_node(t_cmd *list);
t_cmd				*make_node(t_data *info, char *av);
void				heredoc_or_simple_file(int ac, char **av, char **envp);

/*			the_heredoc.c					*/
void				pipex_heredoc(int ac, char **av, char **envp);

/*			free_variants.c						*/
void				free_arr(char **arr);
void				free_struct(t_cmd *cmd);
void				free_list(t_cmd **list);

/*			args_and_paths.c						*/
char				**get_args(char *cmd);
char				**get_paths(char *envp);
char				*envp_path(char **envp);
char				*extract_path(char **paths, t_cmd *cmd);

/*			execution_heredoc.c			*/
void				executions_heredoc(t_cmd *list, t_data *info);

#endif