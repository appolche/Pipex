/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:35:13 by dleaves           #+#    #+#             */
/*   Updated: 2021/08/25 17:56:24 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

void	absolute_path_exec(char **cmd)
{
	if (!access(cmd[0], X_OK))
	{
		if (execve(cmd[0], cmd, 0) == -1)
			malloc_free(cmd);
		show_error("Error: Cmd execution failed\n");
	}
	malloc_free(cmd);
	show_error("Error: Path not found\n");
}
