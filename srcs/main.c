// #include "minishell.h"

// int main(int argc, char **argv, char **env)
// {
//     char            *line;
//     char            *expanded;
//     int             last_status;
//     t_shell_state   state;       /* track $? locally */

//     (void)argc;
//     (void)argv;
//     (void)env;

//     state.active_child = 0;
//     last_status = 42; // simulate last exit code
//     setup_parent_signals();
//     disable_echoctl();

//     while (1)
//     {
//         errno = 0;
//         line = read_full_line();
//         if (!line)
//         {
//             if (errno == EINTR)   /* Ctrl-C at prompt */
//             {
//                 last_status = 130;
//                 continue;
//             }
//             return (last_status); /* Ctrl-D at main prompt exits */
//         }
//         if (*line != '\0')
//             add_history(line);

//         /* 🔹 Test expander */
//         expanded = expand_value(line, env, last_status);
//         if (expanded)
//         {
//             printf("Expanded: [%s]\n", expanded);
//             free(expanded);
//         }

//         /* 🔹 Later: send line to lexer + parser */
//         // tokens = lexer(line);
//         // cmds = parser(tokens, env);
//         // execute(cmds, &state);

//         free(line);
//     }
//     return (0);
// }

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	char *expanded;
	int last_status;
	t_shell_state state; /* track $? locally */

	(void)argc;
	(void)argv;
	(void)env;

	state.active_child = 0;
	last_status = 42; // simulate last exit code
	setup_parent_signals();
	disable_echoctl();

	while (1)
	{
		errno = 0;
		line = read_full_line();
		if (!line)
		{
			if (errno == EINTR) /* Ctrl-C at prompt */
			{
				last_status = 130;
				continue;
			}
			return (last_status); /* Ctrl-D exits minishell */
		}
		if (*line != '\0')
			add_history(line);

		/* 🔹 Test expander */
		expanded = expand_value(line, env, last_status);
		if (expanded)
		{
			/* ======== BUILTINS HANDLER ======== */
			if (ft_strncmp(expanded, "echo", 4) == 0)
			{
				char *args[100];
				char *token;
				int i = 0;

				args[i++] = "echo";
				token = expanded + 4;
				while (*token && *token == ' ')
					token++;
				if (*token)
				{
					args[i++] = token;
					while (*token)
					{
						if (*token == ' ')
						{
							*token = '\0';
							token++;
							while (*token && *token == ' ')
								token++;
							if (*token)
								args[i++] = token;
						}
						token++;
					}
				}
				args[i] = NULL;
				ft_echo(args);
			}
			else if (ft_strcmp(expanded, "pwd") == 0)
				ft_pwd();

			else if (ft_strcmp(expanded, "env") == 0)
				ft_env(env);

			/* ✅ NEW: UNSET BLOCK (handles unset + args) */
			else if (ft_strncmp(expanded, "unset", 5) == 0)
			{
				char *args[100];
				char *token;
				int i = 0;

				args[i++] = "unset";
				token = expanded + 5;

				// Skip leading spaces
				while (*token && *token == ' ')
					token++;

				// Split arguments by spaces
				while (*token)
				{
					args[i++] = token;
					while (*token && *token != ' ')
						token++;
					if (*token)
					{
						*token = '\0';
						token++;
						while (*token && *token == ' ')
							token++;
					}
				}
				args[i] = NULL;
				exec_unset(args, &state);
			}
			/* ================================== */

			/* ✅ EXIT BLOCK (handles exit + args) */
			else if (ft_strncmp(expanded, "exit", 4) == 0)
			{
				char *arg_start;
				char *args[10];
				int i;

				arg_start = expanded + 4;
				while (*arg_start == ' ')
					arg_start++;
				i = 0;
				args[i++] = "exit";
				if (*arg_start)
				{
					char *token = ft_strdup(arg_start);
					args[i++] = token;
					args[i] = NULL;
					exec_exit(args, &state);
					free(token);
				}
				else
				{
					args[i] = NULL;
					exec_exit(args, &state);
				}
			}
			/* ================================== */

			else
				printf("Expanded: [%s]\n", expanded);

			free(expanded);
		}

		/* 🔹 Later: send line to lexer + parser */
		// tokens = lexer(line);
		// cmds = parser(tokens, env);
		// execute(cmds, &state);

		free(line);
	}
	return (0);
}
