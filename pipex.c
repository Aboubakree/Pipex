/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 05:30:53 by akrid             #+#    #+#             */
/*   Updated: 2024/02/15 15:24:53 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	lmarda_saffi(t_pipex *pipex)
{
	char	c[1];

	if (ft_strncmp(pipex->cmd1[0], "cat", 3) == 0 && pipex->cmd1[1] == NULL)
	{
		while (read(0, c, 1))
			if (c[0] == '\n')
				break ;
		exit(EXIT_SUCCESS);
	}
}

void	execute1(t_pipex *pipex, char **envp)
{
	if (pipex->fd_input == STDIN_FILENO)
		lmarda_saffi(pipex);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	dup2(pipex->fd_input, 0);
	if (execve(pipex->path1, pipex->cmd1, envp) == -1)
	{
		ft_printf("zsh: command not found: \"%s\"\n", pipex->cmd1[0]);
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	execute2(t_pipex *pipex, char **envp)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], 0);
	dup2(pipex->fd_output, 1);
	if (execve(pipex->path2, pipex->cmd2, envp) == -1)
	{
		ft_printf("zsh: command not found: \"%s\"\n", pipex->cmd2[0]);
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

char	**get_all_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**all_paths;
	char	*path;
	char	*temp;

	all_paths = get_all_paths(envp);
	i = 0;
	while (all_paths && all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free_cmd(all_paths);
			return (path);
		}
		free(path);
		i++;
	}
	if (all_paths)
		free_cmd(all_paths);
	return (ft_strdup(cmd));
}
