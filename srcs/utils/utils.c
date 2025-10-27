/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:46:20 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/13 16:41:00 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void    disable_echoctl(void)
{
    struct termios t;

    if (tcgetattr(STDIN_FILENO, &t) == -1)
        return;                          /* silently fail if not a tty */

#ifdef ECHOCTL
    t.c_lflag &= ~ECHOCTL;               /* clear the flag → hide control chars */
#endif

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/// extra find somewhere better to keep this

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}