/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:08:55 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 16:50:59 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	clean_data_only_heredoc(t_data *info)
{
	close(info->infile);
	close(info->outfile);
	free_arr(info->paths);
	free (info->limiter);
	free (info);
	info = NULL;
}

void	clean_all_heredoc(t_data *info, t_cmd **list)
{
	free_list(list);
	clean_data_only_heredoc(info);
}
