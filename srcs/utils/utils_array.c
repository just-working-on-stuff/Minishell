#include "minishell.h"

// void	free_str_array(char **array)
// {
// 	int	i;

// 	if (!array)
// 		return ;
// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// char	**dup_str_array(char **array)
// {
// 	char	**copy;
// 	int		count;
// 	int		i;

// 	count = 0;
// 	while (array && array[count])
// 		count++;
// 	copy = malloc(sizeof(char *) * (count + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (i < count)
// 	{
// 		copy[i] = ft_strdup(array[i]);
// 		if (!copy[i])
// 			return (free_str_array(copy), NULL);
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

char	**lst_to_arr(t_list *env)
{
	t_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (list_length(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->str);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->str);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

//swap to elems in array
static void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

//sorts array
void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
	i++;
	}
}
