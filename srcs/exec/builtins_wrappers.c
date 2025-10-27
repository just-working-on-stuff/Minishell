/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_wrappers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:28:07 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/27 18:28:10 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_cd(t_data *shell, t_cmd *command)
{
	return (ft_cd(shell, command->argv));
}

static int builtin_pwd(void)
{
	return (ft_pwd());
}

static int builtin_export(t_data *shell, t_cmd *command)
{
	return (ft_export(command->argv, &shell->env));
}

static int builtin_unset(t_data *shell, t_cmd *command)
{
	return (ft_unset(command->argv, &shell->env));
}

static int builtin_env(t_data *shell)
{
	return (ft_env(shell->env));
}