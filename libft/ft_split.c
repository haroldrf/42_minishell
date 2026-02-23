/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:10:00 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/08/28 15:22:28 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int	count_words(char *s, char c)
{
	int	word_indice;
	int	counter;

	counter = 0;
	while (*s)
	{
		word_indice = 0;
		while (*s != 0 && *s != c)
		{
			if (word_indice == 0)
				counter++;
			word_indice++;
			s++;
		}
		if (*s != 0)
			s++;
	}
	return (counter);
}

static void	get_words_start_n_length(char *s, char c, int *start, int *length)
/*
Take a string s with delimiter c and find the start indexes of the n words as well as their length.
The result arrays "start" and "length" should be of size n and n+1 respectively.
NOTE: length is 0 terminated in order to save one argument (nb_words)
for malloc_n_copy_words later on...
*/
{
	int	i;
	int	j;
	int	nb_words;

	nb_words = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != 0 && s[i] != c)
		{
			if (j == 0)
			{
				nb_words++;
				start[nb_words - 1] = i;
			}
			j++;
			i++;
			if (s[i] == c || s[i] == 0)
				length[nb_words - 1] = j;
		}
		if (s[i])
			i++;
	}
	length[nb_words] = 0;
}

static int	malloc_n_copy_words(char *s, char **array, int *start, int *length)
/* returns one on error (malloc fail), zero otherwise*/
{
	int	i;

	i = 0;
	while (length[i])
	{
		array[i] = malloc(length[i] + 1);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			return (1);
		}
		ft_strlcpy(array[i], s + start[i], length[i] + 1);
		i++;
	}
	array[i] = NULL;
	return (0);
}

void	free_start_n_length(int **start_ptr, int **length_ptr)
{
	free(*start_ptr);
	free(*length_ptr);
}

char	**ft_split(char *s, char c)
{
	int		nb_words;
	char	**array;
	int		*start;
	int		*length;

	nb_words = count_words(s, c);
	array = malloc(sizeof(char *) * (nb_words + 1));
	start = malloc(sizeof(int) * nb_words);
	length = malloc(sizeof(int) * (nb_words + 1));
	if (!array || !start || !length)
	{
		free(array);
		free_start_n_length(&start, &length);
		return (NULL);
	}
	get_words_start_n_length(s, c, start, length);
	if (malloc_n_copy_words(s, array, start, length))
	{
		free(array);
		free_start_n_length(&start, &length);
		return (NULL);
	}
	free_start_n_length(&start, &length);
	return (array);
}
/*
int	main(void)
{
	char	s[] = "kaka  pipi p  kk prout longword s";
	int	i;
	char	**array;

	array = ft_split(s, ' ');
	i = 0;
	while (array[i] != NULL)
	{
		printf("%p\t%s\n", array[i], array[i]);
		free(array[i]);
		i++;
	}
	printf("%p\t%s\n", array[i], array[i]);
	free(array[i]);
	free(array);
}
*/
