/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:37:11 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/06/06 03:03:20 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first(char *cmd, char **env, int fdin, int pipeout[2])
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		free_write_exit("Malloc failed\n", NULL, NULL, 1);
	cmd_path = find_path(cmd_args[0], env, &status);
	if (status == 1)
		free_write_exit("pipex: PATH not found\n", cmd_args, NULL, 1);
	if (status == 2)
		free_write_exit("Malloc failed\n", cmd_args, NULL, 1);
	if (status == 3)
		free_write_exit("pipex: command not found\n", cmd_args, NULL, 1);
	dup2(fdin, 0);
	close(fdin);
	close(pipeout[0]);
	dup2(pipeout[1], 1);
	close(pipeout[1]);
	execve(cmd_path, cmd_args, env);
	perror(NULL);
	free_write_exit(NULL, cmd_args, cmd_path, 1);
}

void	execute(char *cmd, char **env, int pipein[2], int pipeout[2])
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		free_write_exit("Malloc failed\n", NULL, NULL, 1);
	cmd_path = find_path(cmd_args[0], env, &status);
	if (status == 1)
		free_write_exit("pipex: PATH not found\n", cmd_args, NULL, 1);
	if (status == 2)
		free_write_exit("Malloc failed\n", cmd_args, NULL, 1);
	if (status == 3)
		free_write_exit("pipex: command not found\n", cmd_args, NULL, 1);
	close(pipeout[0]);
	dup2(pipein[0], 0);
	close(pipein[0]);
	dup2(pipeout[1], 1);
	close(pipeout[1]);
	execve(cmd_path, cmd_args, env);
	perror(NULL);
	free_write_exit(NULL, cmd_args, cmd_path, 1);
}

void	execute_last(char *cmd, char **env, int pipein[2], int fdout)
{
	char	**cmd_args;
	char	*cmd_path;
	int		status;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		free_write_exit("Malloc failed\n", NULL, NULL, 1);
	cmd_path = find_path(cmd_args[0], env, &status);
	if (status == 1)
		free_write_exit("pipex: PATH not found\n", cmd_args, NULL, 1);
	if (status == 2)
		free_write_exit("Malloc failed\n", cmd_args, NULL, 1);
	if (status == 3)
		free_write_exit("pipex: command not found\n", cmd_args, NULL, 1);
	dup2(pipein[0], 0);
	close(pipein[0]);
	dup2(fdout, 1);
	close(fdout);
	execve(cmd_path, cmd_args, env);
	perror(NULL);
	free_write_exit(NULL, cmd_args, cmd_path, 1);
}
