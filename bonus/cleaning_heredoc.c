/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:08:55 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:28:19 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*		Free heap-allocated memory
and close open files based on the given flag	*/
void	clean_data_only_heredoc(t_data *info, int flag)
{
	if (flag == 2)
	{
		close(info->infile);
		close(info->outfile);
	}
	else if (flag == 1)
		close(info->outfile);
	else if (flag == 0)
		close(info->infile);
	if (info->paths)
		free_arr(info->paths);
	free (info);
	info = NULL;
}
