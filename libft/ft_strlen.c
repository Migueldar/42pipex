/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:03:43 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/05/31 00:31:46 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	char				aux;
	unsigned long		counter;

	if (!str)
		return (0);
	aux = 1;
	counter = 0;
	while (aux != 0)
	{
		aux = *(str + counter);
		counter++;
	}
	return (--counter);
}
