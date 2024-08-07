/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:56:17 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:23:28 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*		Free heap-allocated memory
and close open files based on the given flag	*/
void	clean_data_mandatory(t_data *info, int flag)
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
