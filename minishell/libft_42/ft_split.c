/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:38:30 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/15 14:45:34 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static int	contword(const char *str, char c)
{
	int	i;
	int	conter;

	i = 0;
	conter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
		{
			conter++;
		}
		i++;
	}
	return (conter);
}

static char	**ta3emira(char **word, const char *s, char c, int con)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (con > i)
	{
		k = 0;
		while (s[j] == c)
			j++;
		while (s[j] != '\0' && s[j] != c)
		{
			word[i][k] = s[j];
			k++;
			j++;
		}
		word[i][k] = '\0';
		i++;
	}
	return (word);
}

static char	**size_aloo(char **word, const char *s, char c, int con)
{
	int	i;
	int	j;
	int	cont;

	i = 0;
	j = 0;
	while (con > i)
	{
		while (s[j] == c)
			j++;
		cont = 0;
		while (s[j] != '\0' && s[j] != c)
		{
			cont++;
			j++;
		}
		word[i] = (char *)malloc((cont + 1) * sizeof(char));
		if (word[i] == NULL)
		{
			free_words(word);
			return (NULL);
		}
		i++;
	}
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**word;
	int		con;
	char	**tmp;

	if (s == NULL)
	{
		tmp = (char **)malloc(sizeof(char *));
		tmp[0] = NULL;
		return (tmp);
	}
	con = contword(s, c);
	word = (char **)malloc((con + 1) * sizeof(char *));
	if (word == NULL)
		return (NULL);
	word = size_aloo(word, s, c, con);
	if (word == NULL)
		return (NULL);
	word = ta3emira(word, s, c, con);
	word[con] = NULL;
	return (word);
}
