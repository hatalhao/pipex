/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/31 02:48:31 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"
#include <sys/wait.h>

typedef	struct	s_cmd
{
	char		*path;
	char		**args;
}				t_cmd;


#endif