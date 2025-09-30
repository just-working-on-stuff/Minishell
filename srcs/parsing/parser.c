/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:52:46 by aalbugar          #+#    #+#             */
/*   Updated: 2025/09/30 10:53:38 by aalbugar         ###   ########.fr       */
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

static void handle_heredoc(t_cmd *cmd, char *delimiter)
{
    (void)cmd;
    (void)delimiter;
    /* 🔹 Placeholder for heredoc handling */
}

void parse_redir(t_cmd *cmd, t_token *tok)
{
    char *filename;

    if (!tok->next || tok->next->type != TOK_CMD)
        return ;
    filename = tok->next->str;
    if (tok->type == TOK_REDIR_IN)
        cmd->infile = open_infile(filename);
    else if (tok->type == TOK_REDIR_OUT)
        cmd->outfile = open_outfile_trunc(filename);
    else if (tok->type == TOK_APPEND)
        cmd->outfile = open_outfile_append(filename);
    else if (tok->type == TOK_HEREDOC)
        handle_heredoc(cmd, filename);
}
