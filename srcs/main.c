/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:10:23 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/22 14:23:45 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **env)
// {
// 	char *line;
// 	char *expanded;
// 	int last_status;
// 	t_shell_state state; /* track $? locally */

// 	(void)argc;
// 	(void)argv;

// 	state.active_child = 0;
// 	last_status = 42; // simulate last exit code
// 	state.env = ft_strdup_array(env);
// 	// state.env = env_to_list(env);
// 	setup_parent_signals();
// 	disable_echoctl();

// 	while (1)
// 	{
// 		errno = 0;
// 		line = read_full_line();
// 		if (!line)
// 		{
// 			if (errno == EINTR) /* Ctrl-C at prompt */
// 			{
// 				last_status = 130;
// 				continue;
// 			}
// 			return (last_status); /* Ctrl-D exits minishell */
// 		}
// 		if (*line != '\0')
// 			add_history(line);

// 		/* 🔹 Test expander */
// 		expanded = expand_value(line, state.env, last_status);
// 		if (expanded)
// 		{
// 			/* ======== BUILTINS HANDLER ======== */
// 			if (ft_strncmp(expanded, "echo", 4) == 0)
// 			{
// 				char *args[100];
// 				char *token;
// 				int i = 0;

// 				args[i++] = "echo";
// 				token = expanded + 4;
// 				while (*token && *token == ' ')
// 					token++;
// 				if (*token)
// 				{
// 					args[i++] = token;
// 					while (*token)
// 					{
// 						if (*token == ' ')
// 						{
// 							*token = '\0';
// 							token++;
// 							while (*token && *token == ' ')
// 								token++;
// 							if (*token)
// 								args[i++] = token;
// 						}
// 						token++;
// 					}
// 				}
// 				args[i] = NULL;
// 				ft_echo(args);
// 			}
// 			else if (ft_strcmp(expanded, "pwd") == 0)
// 				ft_pwd();

// 			else if (ft_strcmp(expanded, "env") == 0)
// 				ft_env(state.env);

// 			/* ✅ NEW: UNSET BLOCK (handles unset + args) */
// 			else if (ft_strncmp(expanded, "unset", 5) == 0)
// 			{
// 				char *args[100];
// 				char *token;
// 				int i = 0;

// 				args[i++] = "unset";
// 				token = expanded + 5;
// 				// Skip leading spaces
// 				while (*token && *token == ' ')
// 					token++;
// 				// Split arguments by spaces
// 				while (*token)
// 				{
// 					args[i] = token; // Store the start of the argument
// 					while (*token && *token != ' ')
// 						token++;
// 					if (*token)
// 					{
// 						*token++ = '\0'; // Null terminate and move to next char
// 						while (*token && *token == ' ')
// 							token++;
// 					}
// 					i++;
// 				}
// 				args[i] = NULL;
// 				exec_unset(args, &state); // Pass state to maintain environment
// 			}
// 			/* ================================== */

// 			/* ✅ EXIT BLOCK (handles exit + args) */
// 			else if (ft_strncmp(expanded, "exit", 4) == 0)
// 			{
// 				char *arg_start;
// 				char *args[10];
// 				int i;

// 				arg_start = expanded + 4;
// 				while (*arg_start == ' ')
// 					arg_start++;
// 				i = 0;
// 				args[i++] = "exit";
// 				if (*arg_start)
// 				{
// 					char *token = ft_strdup(arg_start);
// 					args[i++] = token;
// 					args[i] = NULL;
// 					exec_exit(args, &state);
// 					free(token);
// 				}
// 				else
// 				{
// 					args[i] = NULL;
// 					exec_exit(args, &state);
// 				}
// 			}
// 			/* ================================== */
//             /* ✅ CD BLOCK (handles cd + args) */
//             else if (ft_strncmp(expanded, "cd", 2) == 0)
//             {
//                 char *args[100];
//                 char *token;
//                 int i = 0;

//                 args[i++] = "cd";
//                 token = expanded + 2;
//                 while (*token && *token == ' ')
//                     token++;
//                 if (*token)
//                 {
//                     args[i++] = token;
//                     while (*token)
//                     {
//                         if (*token == ' ')
//                         {
//                             *token = '\0';
//                             token++;
//                             while (*token && *token == ' ')
//                                 token++;
//                             if (*token)
//                                 args[i++] = token;
//                         }
//                         token++;
//                     }
//                 }
//                 args[i] = NULL;
//                 ft_cd(args, &state.env);
//             }
// 			else if (ft_strncmp(expanded, "export", 6) == 0)
// 			{
// 			    char *args[100];
// 			    char *token;
// 			    int i = 0;
			
// 			    args[i++] = "export";
// 			    token = expanded + 6;
// 			    while (*token && *token == ' ')
// 			        token++;
// 			    if (*token)
// 			    {
// 			        args[i++] = token;
// 			        while (*token)
// 			        {
// 			            if (*token == ' ')
// 			            {
// 			                *token = '\0';
// 			                token++;
// 			                while (*token && *token == ' ')
// 			                    token++;
// 			                if (*token)
// 			                    args[i++] = token;
// 			            }
// 			            token++;
// 			        }
// 			    }
// 			    args[i] = NULL;
// 			    ft_export(args, &state.env);
// 			}
//             /* ================================== */
// 			else
// 				printf("Expanded: [%s]\n", expanded);

// 			free(expanded);
// 		}

// 		/* 🔹 Later: send line to lexer + parser */
// 		// tokens = lexer(line);
// 		// cmds = parser(tokens, env);
// 		// execute(cmds, &state);

// 		free(line);
// 	}
// 	return (0);
// }

int main(int argc, char **argv, char **env)
{
	char *line;
	char *expanded;
	int last_status;
	t_shell_state state;

	(void)argc;
	(void)argv;

	state.active_child = 0;
	last_status = 42;
	state.env = ft_strdup_array(env);
	setup_parent_signals();
	disable_echoctl();

	while (1)
	{
		errno = 0;
		line = read_full_line();
		if (!line)
		{
			if (errno == EINTR)
			{
				last_status = 130;
				continue;
			}
			return (last_status);
		}
		if (*line != '\0')
			add_history(line);

		expanded = expand_value(line, state.env, last_status);
		if (expanded)
		{
			// Use unified builtins handler
			int builtin_result = handle_builtins(expanded, &state);
			if (builtin_result == -1)
			{
				// Not a builtin command
				printf("Expanded: [%s]\n", expanded);
			}
			else
			{
				// Update last_status if needed
				state.last_status = builtin_result;
			}

			free(expanded);
		}

		free(line);
	}
	return (0);
}