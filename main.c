/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 04:42:08 by akrid             #+#    #+#             */
/*   Updated: 2024/02/11 12:35:11 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_args(argc, argv, &pipex);
	cmds_parse(argv, &pipex, envp);
	cmds_execute(&pipex);
	cmds_clear(&pipex);
	return (0);
}
