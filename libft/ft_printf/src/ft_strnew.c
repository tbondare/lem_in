/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:18:52 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/04 20:32:40 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (!(str = (char*)malloc(size + 1)))
		return (NULL);
	ft_bzero(str, size);
	str[size] = '\0';
	return (str);
}
