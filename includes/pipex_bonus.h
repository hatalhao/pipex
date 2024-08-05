/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 07:18:27 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:07:36 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

void				clean_data_only_heredoc(t_data *info);
void				clean_all_heredoc(t_data *info, t_cmd **list);
/*					cleaning_heredoc.c					*/

void				fill_the_doc(t_data *info);
t_data				*heredoc_assignements(t_data *info, int ac, \
					char **av, char **envp);
t_cmd				**init_list_heredoc(t_cmd **list, t_data *info);
void				offset_reposition(t_data *info, t_cmd **list);
void				pipex_heredoc(int ac, char **av, char **envp);
/*					the_heredoc.c					*/

void				heredoc_or_simple_file(int ac, char **av, char **envp);
/*					main_bonus.c								*/

#endif