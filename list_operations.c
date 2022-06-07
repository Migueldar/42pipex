/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:32:20 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/06/06 18:01:14 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_and_free(t_pid	*first)
{
	t_pid	*aux;

	while (first != NULL)
	{
		waitpid(first->pid, NULL, 0);
		aux = first;
		first = first->next;
		free(first);
	}
}

void	pid_add_front(t_pid **first, int pid)
{
	t_pid	*new;

	new = ft_calloc(1, sizeof(t_pid));
	if (!new)
		free_write_exit("Malloc failed\n", NULL, NULL, 1);
	new->pid = pid;
	if (*first != NULL)
		new->next = *first;
	else
		new->next = NULL;
	*first = new;
}
