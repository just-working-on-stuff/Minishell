/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:29:31 by aalbugar          #+#    #+#             */
/*   Updated: 2025/09/30 12:53:40 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_word(t_cmd *cmd, t_token *tok)
{
	int		argc;
	int		i;
	char	**new_argv;

	argc = 0;
	if (cmd->argv)
		while (cmd->argv[argc])
			argc++;
	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (i < argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[argc] = ft_strdup(tok->str);
	new_argv[argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv; 
}
/*
** Free a linked list of commands and their argv.
*/
void free_cmds(t_cmd *cmds)
{
    t_cmd *tmp;
    int    i;

    while (cmds)
    {
        tmp = cmds->next;
        if (cmds->argv)
        {
            i = 0;
            while (cmds->argv[i])
            {
                free(cmds->argv[i]);
                i++;
            }
            free(cmds->argv);
        }
        if (cmds->infile > 2)
            close(cmds->infile);
        if (cmds->outfile > 2)
            close(cmds->outfile);
        free(cmds);
        cmds = tmp;
    }
}
/*
** Allocate and initialize a new command node.
*/
t_cmd *new_cmd(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->infile = STDIN_FILENO;   /* default: read from keyboard */
    cmd->outfile = STDOUT_FILENO; /* default: write to screen */
    cmd->next = NULL;
    return (cmd);
}
