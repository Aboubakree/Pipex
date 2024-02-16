/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 04:42:08 by akrid             #+#    #+#             */
/*   Updated: 2024/02/16 09:49:25 by akrid            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_args(argc, argv, &pipex);
	cmds_parse(argv, &pipex, envp);
	cmds_execute(&pipex, -1, -1, envp);
	cmds_clear(&pipex);
	return (0);
}
