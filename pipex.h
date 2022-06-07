/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:36:24 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/06/06 03:18:28 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}	t_pid;

char	*find_path(char *cmd, char **env, int *status);
void	execute(char *cmd, char **env, int pipein[2], int pipeout[2]);
void	execute_first(char *cmd, char **env, int fdin, int pipeout[2]);
void	execute_last(char *cmd, char **env, int pipein[2], int fdout);
void	pid_add_front(t_pid **first, int pid);
void	wait_and_free(t_pid	*first);
void	free_write_exit(const char *str, char **fr1, char *fr2, int e);
void	swap_pipes(int pipes[2][2]);

#endif