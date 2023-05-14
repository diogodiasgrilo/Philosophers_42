/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:07:48 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/14 17:14:14 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	total;
	int	sign;

	sign = 1;
	total = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		total *= 10;
		total += str[i] - 48;
		i++;
	}
	return (total * sign);
}

static void	changer(char *dst, const char *src)
{
	int	i;
	int	index;

	i = 0;
	index = ft_strlen(dst);
	while (src[i])
		dst[index++] = src[i++];
}

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int	dst_len;
	int	src_len;
	int	i;
	int	sub;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	sub = ft_strlen(dst);
	i = -1;
	if (dstsize == 0)
		return (ft_strlen(src));
	else if (dstsize < 0)
	{
		changer(dst, src);
		return (dst_len + src_len);
	}
	if (dst_len < dstsize)
	{
		while (++i < dstsize - sub - 1 && *src)
			dst[dst_len++] = *src++;
		dst[dst_len] = '\0';
	}
	else
		return (dstsize + src_len);
	return (ft_strlen(dst) + ft_strlen(src));
}

unsigned long int	ft_strlcpy(char *dst, const char *src, \
		unsigned long int dstsize)
{
	unsigned long int	i;

	i = 0;
	if (dstsize <= 0)
		return (ft_strlen(src));
	while (src && src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src && src[i])
		i++;
	return (i);
}
