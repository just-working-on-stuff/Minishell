#include "../minishell.h"

/* Helper: turn waitpid()'s status into a shell exit code for $? */
static int compute_status_from_wait(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status)); /* e.g., SIGINT(2) -> 130 */
    return (1);
}

int run_simple_command(char *const argv[], char *const envp[], t_shell_state *state)
{
    pid_t pid;
    int   status;

    pid = fork();
    if (pid < 0)
    {
        perror("minishell: fork");
        return (1);
    }
    if (pid == 0)
    {
        /* --- Child process --- */
        setup_child_signals();                     /* restore SIGINT/SIGQUIT defaults */
        execve(argv[0], (char *const *)argv, (char *const *)envp);
        /* If execve returns, it failed: choose 126 vs 127 by errno */
        perror("minishell: execve");
        _exit((errno == EACCES) ? 126 : 127);
    }

    /* --- Parent process --- */
    state->active_child = pid;                     /* we’re executing a child now */
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("minishell: waitpid");
        state->active_child = 0;
        return (1);
    }
    state->active_child = 0;                       /* back to prompt */
    return (compute_status_from_wait(status));     /* normalize to $? */
}
