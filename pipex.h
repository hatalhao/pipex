/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:49:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/12 21:40:13 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"

typedef	struct	s_cmd
{
	char		*path;
	char		**args;
}				t_cmd;


#endif