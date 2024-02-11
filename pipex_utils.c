/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:31:42 by akrid             #+#    #+#             */
/*   Updated: 2024/02/11 12:34:49 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	cmds_parse(char **argv, t_pipex *pipex, char **envp)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->path1 = get_cmd_path(pipex->cmd1[0], envp);
	pipex->path2 = get_cmd_path(pipex->cmd2[0], envp);
}

void	check_args(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	pipex->fd_input = open(argv[1], O_RDONLY);
	if (pipex->fd_input == -1)
	{
		ft_printf("Error: %s \"%s\"\n", strerror(errno), argv[1]);
		exit(EXIT_FAILURE);
	}
	pipex->fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_output == -1)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pipe(pipex->pipe_fd) < 0)
	{
		ft_printf("Error creating pipe: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	cmds_execute(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("Error: %s\n", strerror(errno));
        cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		execute1(pipex);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			ft_printf("Error: %s\n", strerror(errno));
            cmds_clear(pipex);
			exit(EXIT_FAILURE);
		}
		if (pid2 == 0)
			execute2(pipex);
	}
	wait(NULL);
}

void	cmds_clear(t_pipex *pipex)
{
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	free(pipex->path1);
	free(pipex->path2);
	close(pipex->fd_output);
	close(pipex->fd_input);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
