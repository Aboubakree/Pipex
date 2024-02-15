/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:31:42 by akrid             #+#    #+#             */
/*   Updated: 2024/02/15 12:37:35 by akrid            ###   ########.fr       */
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
	pipex->cmd1 = ft_split_v2(argv[2], " \t\n");
	pipex->cmd2 = ft_split_v2(argv[3], " \t\n");
	if (pipex->cmd1[0] == NULL )
	{
		free_cmd(pipex->cmd1);
		pipex->cmd1 = ft_split_v2("more", " \t\n");
	}
	if (pipex->cmd2[0] == NULL )
	{
		free_cmd(pipex->cmd2);
		pipex->cmd2 = ft_split_v2("cat", " \t\n");
	}
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
	if (ft_strncmp(argv[1], "/dev/stdin", 11) != 0)
		pipex->fd_input = open(argv[1], O_RDONLY);
	else
		pipex->fd_input = STDIN_FILENO;
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

void	cmds_execute(t_pipex *pipex, pid_t pid1, pid_t pid2, char **envp)
{
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf("Error: %s\n", strerror(errno));
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		execute1(pipex, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_printf("Error: %s\n", strerror(errno));
		cmds_clear(pipex);
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		execute2(pipex, envp);
	if (ft_strncmp(pipex->cmd1[0], "sleep", 5) == 0 || ft_strncmp(pipex->cmd2[0], "sleep", 5) == 0 ||
		pipex->fd_input == STDIN_FILENO)
		wait(NULL);
	wait(NULL);
}

int	args_len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
