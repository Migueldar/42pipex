/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:34:12 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/06/06 02:58:04 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//joins 3 strings
static char	*ft_strjoin3(char const *str1, char const *str2, char const *str3)
{
	char	*ret;
	char	*move;

	ret = ft_calloc(ft_strlen(str1)
			+ ft_strlen(str2) + ft_strlen(str3) + 1, 1);
	if (!ret)
		return (NULL);
	move = ret;
	while (*str1)
		*(move++) = *(str1++);
	while (*str2)
		*(move++) = *(str2++);
	while (*str3)
		*(move++) = *(str3++);
	return (ret);
}

//had to split the below function because it was 33 lines long
static char	*norminette_find_path(char **rutas, char *cmd, int *status)
{
	int		counter;
	char	*path;

	if (!rutas)
		return (*status = 2, NULL);
	counter = 0;
	while (rutas[counter])
	{
		path = ft_strjoin3(rutas[counter], "/", cmd);
		if (!path)
			return (free_write_exit(NULL, rutas, NULL, 0), *status = 2, NULL);
		if (access(path, X_OK) == 0)
			return (free_write_exit(NULL, rutas, NULL, 0), *status = 0, path);
		counter++;
		free(path);
	}
	return (free_write_exit(NULL, rutas, NULL, 0), *status = 3, NULL);
}

//finds path of a command
//status takes value 0 if all ok, 1 Path no found
//2 Malloc fail, 3 command not found
//(,) is a funny operator, good to pass norminette
//check it out on internet or ask me if you dont know what it does
char	*find_path(char *cmd, char **env, int *status)
{
	char	*path;
	char	**rutas;

	if (access(cmd, X_OK) == 0)
		return (*status = 0, cmd);
	while (!(*env) || ft_strncmp(*env, "PATH=", 5))
	{
		if (!(*env))
			return (*status = 1, NULL);
		env++;
	}
	path = ft_substr(*env, 5, ft_strlen(*env) - 4);
	if (!path)
		return (*status = 2, NULL);
	rutas = ft_split(path, ':');
	free(path);
	return (norminette_find_path(rutas, cmd, status));
}

//e = 1 if wanna exit
void	free_write_exit(const char *str, char **fr1, char *fr2, int e)
{
	int	counter;

	if (fr1)
	{
		counter = 0;
		while (fr1[counter])
		{
			free(fr1[counter]);
			counter++;
		}
		free(fr1);
	}
	if (fr2)
		free(fr2);
	if (str)
		write(2, str, ft_strlen(str));
	if (e)
		exit(1);
}

void	swap_pipes(int pipes[2][2])
{
	int	aux;

	aux = pipes[0][0];
	pipes[0][0] = pipes[1][0];
	pipes[1][0] = aux;
	aux = pipes[0][1];
	pipes[0][1] = pipes[1][1];
	pipes[1][1] = aux;
}
