/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:44:21 by rchaumei          #+#    #+#             */
/*   Updated: 2025/11/13 16:35:46 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static void	free_all(char **dest, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

static int	fill_dest(char **dest, const char *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			dest[j] = ft_substr(s, start, i - start);
			if (!dest[j])
				return (free_all(dest, j), 0);
			j++;
		}
	}
	dest[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_counter(s, c) + 1));
	if (!dest)
		return (NULL);
	if (fill_dest(dest, s, c) != 1)
		return (NULL);
	return (dest);
}

/*int main(void)
{
	char **tab;
	int i = 0;
	char c = '/';
	char *s = "salut/les/gars";

	tab = ft_split(s, c);
	if (!tab)
		return (1);

	while (tab[i])
	{
		printf("%s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}*/