/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 04:41:17 by akrid             #+#    #+#             */
/*   Updated: 2024/02/14 09:11:57 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd_output;
	int		fd_input;
	int		pipe_fd[2];
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}			t_pipex;

void		free_cmd(char **cmd);
void		cmds_clear(t_pipex *pipex);
char		**get_all_paths(char **envp);
char		*get_cmd_path(char *cmd, char **envp);
int			args_len(char **str);
void		cmds_parse(char **argv, t_pipex *pipex, char **envp);
void		check_args(int argc, char **argv, t_pipex *pipex);
void		execute1(t_pipex *pipex, char **envp);
void		execute2(t_pipex *pipex, char **envp);
void		cmds_execute(t_pipex *pipex, pid_t pid1, pid_t pid2, char **envp);

#endif