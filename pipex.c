/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:40:17 by dleaves           #+#    #+#             */
/*   Updated: 2021/08/22 17:40:22 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	path_search(char **path, char **cmd)
{
	char	*final_path;
	int		j;

	j = 1;
	while (path[j])
	{
		final_path = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(final_path, cmd[0]);
		if (!access(final_path, 0))
		{
			if (execve(final_path, cmd, 0) == -1)
			{
				malloc_free(path);
				malloc_free(cmd);
				if (final_path)
					free(final_path);
				show_error("Error: Cmd execution failed");
			}
		}
		if (final_path)
			free(final_path);
		j++;
	}
}

static void	ft_exec(char **cmd, char **envp)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if ((ft_strnstr(envp[i], "PATH=", 5)))
		{
			path = ft_split(envp[i], ':');
			break ;
		}
		i++;
	}
	if (path)
		path_search(path, cmd);
	malloc_free(cmd);
	if (path)
		malloc_free(path);
	show_error("Error: Path not found");
}

void	child_proc(char **argv, char **envp, int pipe_fd[2], int file_fd[2])
{
	int		new_file_fd;
	int		new_pipe_fd;
	char	**cmd;

	close(pipe_fd[0]);
	new_pipe_fd = dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	new_file_fd = dup2(file_fd[0], 0);
	cmd = ft_split(*argv, ' ');
	ft_exec(cmd, envp);
}

void	parent_proc(char **argv, char **envp, int pipe_fd[2], int file_fd[2])
{
	int		new_file_fd;
	int		new_pipe_fd;
	char	**cmd;

	close(pipe_fd[1]);
	new_pipe_fd = dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	new_file_fd = dup2(file_fd[1], 1);
	cmd = ft_split(*argv, ' ');
	ft_exec(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		file_fd[2];
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
		show_error("Usage Error: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe");
	file_fd[0] = open(argv[1], O_RDONLY);
	if (file_fd[0] == -1)
		show_error("Error: Open file1 failed");
	file_fd[1] = open(argv[4], O_WRONLY | O_CREAT, 0666);
	if (file_fd[1] == -1)
		show_error("Error: Open file2 failed");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork");
	if (pid == 0)
		child_proc(&argv[2], envp, pipe_fd, file_fd);
	else
		parent_proc(&argv[3], envp, pipe_fd, file_fd);
	close(file_fd[0]);
	close(file_fd[1]);
	return (0);
}
