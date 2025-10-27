/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:29:31 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/27 12:31:32 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_word(t_redir *cmd, t_token *tok)
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
void free_cmds(t_redir *cmds)
{
    t_redir *tmp;
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
t_redir *new_cmd(void)
{
    t_redir *cmd;

    cmd = malloc(sizeof(t_redir));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->infile = STDIN_FILENO;   /* default: read from keyboard */
    cmd->outfile = STDOUT_FILENO; /* default: write to screen */
    cmd->next = NULL;
    return (cmd);
}