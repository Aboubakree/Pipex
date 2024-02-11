/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 05:30:53 by akrid             #+#    #+#             */
/*   Updated: 2024/02/11 12:35:04 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute1(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	dup2(pipex->fd_input, 0);
	if (execve(pipex->path1, pipex->cmd1, NULL) == -1)
	{
		ft_printf("Error: %s \"%s\"\n", strerror(errno), pipex->cmd1[0]);
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
}

void	execute2(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], 0);
	dup2(pipex->fd_output, 1);
	if (execve(pipex->path2, pipex->cmd2, NULL) == -1)
	{
		ft_printf("Error: %s \"%s\"\n", strerror(errno), pipex->cmd2[0]);
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
}

char	**get_all_paths(char **envp)
{
	int		i;

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

int	args_len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
