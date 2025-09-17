/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:46:20 by aalbugar          #+#    #+#             */
/*   Updated: 2025/09/17 16:53:38 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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