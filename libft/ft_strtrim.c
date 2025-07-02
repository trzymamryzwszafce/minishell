/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:51:12 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/10 19:31:51 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(char c, char const *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dup;
	int		sta;
	int		end;
	int		i;

	i = 0;
	sta = 0;
	while (s1[sta] != '\0' && ft_issep(s1[sta], set))
		sta++;
	end = ft_strlen(s1);
	while (end > sta && ft_issep(s1[end - 1], set))
		end--;
	if (sta == end)
		return (ft_strdup(""));
	dup = (char *)malloc(sizeof(char) * (end - sta + 1));
	if (!dup)
		return (NULL);
	while (sta < end)
	{
		dup[i] = s1[sta];
		i++;
		sta++;
	}
	dup[i] = '\0';
	return (dup);
}
