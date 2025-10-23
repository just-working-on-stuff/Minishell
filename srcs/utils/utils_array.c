#include "minishell.h"

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**dup_str_array(char **array)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	while (array && array[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
			return (free_str_array(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}