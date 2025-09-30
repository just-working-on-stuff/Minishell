/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:44 by aalbugar          #+#    #+#             */
/*   Updated: 2025/09/30 10:52:24 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *parser(t_token *tokens, char **envp)
{
	t_cmd *cmds;
	t_cmd *current;

	(void)envp;
	cmds = 	NULL;	
	current = new_cmd();
	add_cmd_back(&cmds, current);

	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			current = new_cmd();
			add_cmd_back(&cmds, current);
		}
		else if (tokens->type == TOK_REDIR_IN
			|| tokens->type == TOK_REDIR_OUT
			||tokens->type == TOK_APPEND
			|| tokens->type == TOK_HEREDOC)
			parse_redir(current, tokens);
		else
			pars_word(current, tokens);
		tokens = tokens->next;
	}
	return (cmds);
}
