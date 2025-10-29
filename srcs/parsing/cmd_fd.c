/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:52:46 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/27 20:00:00 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int open_infile(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror(filename);
	return (fd);
}

static int open_outfile_trunc(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

static int open_outfile_append(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

static void handle_heredoc_redir(t_cmd *cmd, char *delimiter, t_data *data)
{
	int	fd;

	fd = handle_heredoc(delimiter, data);
	if (fd != -1)
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		cmd->infile = fd;
	}
	else
		cmd->skip_cmd = true;
}

void parse_redir(t_cmd *cmd, t_token *tok, t_data *data)
{
	char *filename;

	if (!tok->next || tok->next->type != TOK_CMD)
		return;
	filename = tok->next->str;
	if (tok->type == TOK_REDIR_IN)
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		cmd->infile = open_infile(filename);
		if (cmd->infile == -1)
			cmd->skip_cmd = true;
	}
	else if (tok->type == TOK_REDIR_OUT)
	{
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		cmd->outfile = open_outfile_trunc(filename);
	}
	else if (tok->type == TOK_APPEND)
	{
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		cmd->outfile = open_outfile_append(filename);
	}
	else if (tok->type == TOK_HEREDOC)
		handle_heredoc_redir(cmd, filename, data);
}
