/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 07:18:27 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 14:28:19 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "pipex.h"
# include <signal.h>
# include <sys/wait.h>

# define STDIN 0  /* Standard input.  */
# define STDOUT 1 /* Standard output.  */

void				pipex(int ac, char **av, char **envp);
void				add_to_list(t_cmd **list, t_cmd *new_node);
void				final_curtain(t_cmd **list, t_data *info, int boool);
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
void				free_struct(t_cmd *cmd);
void				free_list(t_cmd **list);
/*					free_variants.c						*/

char				**get_args(char *cmd);
char				**get_paths(char *envp);
char				*envp_path(char **envp);
char				*extract_path(char **paths, t_cmd *cmd);
/*					args_and_paths.c					*/

void				clean_data_only_heredoc(t_data *info);
void				clean_all_heredoc(t_data *info, t_cmd **list);
void				clean_exp_fds(t_data *info, t_cmd **list);
/*					cleaning_heredoc.c					*/

void				pipex_heredoc(int ac, char **av, char **envp);
/*					the_heredoc.c					*/

void				heredoc_or_simple_file(int ac, char **av, char **envp);
/*					main.c								*/

#endif