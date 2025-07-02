/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:48:33 by szmadeja          #+#    #+#             */
/*   Updated: 2024/12/10 01:32:29 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!nstr)
		return (NULL);
	while (s1[i])
	{
		nstr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		nstr[j] = s2[i];
		i++;
		j++;
	}
	nstr[j] = '\0';
	return (nstr);
}
