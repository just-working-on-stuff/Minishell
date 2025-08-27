#include "libft.h"
#include "../include/minishell.h"


char	*get_prompt(t_shell_state *state)
{
	char	*p;

	(void)state;

//true (1) → you’re at a real terminal (keyboard/screen).
//false (0) → input is a pipe/file (non-interactive).
false (0) → input is a pipe/file (non-interactive).

	if (!isatty(0))
	{
		p = malloc(1);
		if (!p)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	return (ft_strdup("minishell$ "));
}