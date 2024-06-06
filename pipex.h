/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/06 07:29:21 by hatalhao         ###   ########.fr       */
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
	
}				t_data;



#endif