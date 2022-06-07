/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:33:30 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/06/07 17:17:06 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//its kinda funny, but the here_doc doesnt exec at 
//the same time, it executes first and then everything else
static void	here_doc(char **argv, int pipeout[2])
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		free_write_exit("Malloc failed\n", NULL, NULL, 1);
	write(1, "heredoc> ", 9);
	line = get_next_line(1);
	while (line && ft_strncmp(limiter, line, ft_strlen(argv[2]) + 2))
	{
		write(pipeout[1], line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 10);
		line = get_next_line(1);
	}
	if (!line)
		free_write_exit("Get next line error", NULL, limiter, 1);
	free(line);
	free(limiter);
	close(pipeout[1]);
}

static void	first_command(char **argv, char **en, int pipeout[2], t_pid **first)
{
	int	fdin;
	int	pid;

	fdin = open(argv[1], O_RDONLY);
	if (fdin < 0)
	{
		perror(NULL);
		exit(1);
	}
	pid = fork();
	pid_add_front(first, pid);
	if (pid == 0)
		execute_first(argv[2], en, fdin, pipeout);
	close(pipeout[1]);
	close(fdin);
}

static void	inter_command(char *cmd, char **env, int pipes[2][2], t_pid **first)
{
	int	pid;

	pid = fork();
	pid_add_front(first, pid);
	if (pid == 0)
		execute(cmd, env, pipes[0], pipes[1]);
	close(pipes[0][0]);
	close(pipes[1][1]);
}

static void	last_command(char **argv, char **env, int pipein[2], t_pid **first)
{
	int	fdout;
	int	pid;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		fdout = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fdout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout < 0)
	{
		perror(NULL);
		exit(1);
	}
	pid = fork();
	pid_add_front(first, pid);
	if (pid == 0)
		execute_last(argv[2], env, pipein, fdout);
	close(pipein[0]);
	close(fdout);
}

//the weird overwritting of argv at the end if bc i could only pass
//4 params to functions, and i needed the other 3
int	main(int argc, char **argv, char **env)
{
	int		counter;
	t_pid	*first;
	int		pipes[2][2];

	if (argc < 5 || (ft_strncmp("here_doc", argv[1], 9) == 0 && argc < 6))
		free_write_exit("Not enough arguments\n", NULL, NULL, 1);
	first = NULL;
	pipe(pipes[0]);
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		here_doc(argv, pipes[0]);
	else
		first_command(argv, env, pipes[0], &first);
	counter = 2;
	while (++counter < argc - 2)
	{
		pipe(pipes[1]);
		inter_command(argv[counter], env, pipes, &first);
		swap_pipes(pipes);
	}
	argv[2] = argv[argc - 2];
	argv[3] = argv[argc - 1];
	last_command(argv, env, pipes[0], &first);
	wait_and_free(first);
	return (0);
}
