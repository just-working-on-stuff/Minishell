/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:44 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/27 12:33:14 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_redir(int type)
{
	return (type == TOK_REDIR_IN
		|| type == TOK_REDIR_OUT || type == TOK_APPEND || type == TOK_HEREDOC);
}
// Add a command node to the end of the list.
void add_cmd_back(t_redir **lst, t_redir *new)
{
	t_redir *tmp;

	if (!new)
		return;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void start_new_cmd(t_redir **cmds, t_redir **current)
{
	*current = new_cmd();
	add_cmd_back(cmds, *current);
}

static void process_token(t_redir *current, t_token **tokens)
{
	if ((*tokens)->type == TOK_PIPE)
		start_new_cmd(NULL, &current); /* handled outside */
	else if (is_redir((*tokens)->type))
	{
		parse_redir(current, *tokens);
		*tokens = (*tokens)->next; /* skip filename */
	}
	else
		pars_word(current, *tokens);
}

/* ======================= MAIN PARSER ======================= */
t_redir *parser(t_token *tokens, char **envp)
{
	t_redir *cmds;
	t_redir *current;

	(void)envp;
	cmds = NULL;
	start_new_cmd(&cmds, &current);
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
			start_new_cmd(&cmds, &current);
		else
			process_token(current, &tokens);
		tokens = tokens->next;
	}
	return (cmds);
}
