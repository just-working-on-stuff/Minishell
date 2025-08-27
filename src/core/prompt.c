#include "libft.h"
#include "../include/minishell.h"

// TTY? yes → get_prompt() → build_interactive_prompt()
//                     → dir resolved (CWD → PWD → ".")
//                     → build_from_dir(dir) → "/path $ "
// main loop: readline("/path $ ") → free(prompt)

// TTY? no  → get_prompt() → ft_strdup("")
// main loop: readline("") → free(prompt)


static char *build_from_dir(const char *dir)
{
    char *tmp = ft_strjoin(dir, " ");
    char *out;

    if (!tmp)
        return (NULL);

    out = ft_strjoin(tmp, "$ ");
    free(tmp);
    return (out);
}

static char *build_interactive_prompt(void)
{
    char  buf[1024];
    char *cwd = getcwd(buf, sizeof(buf));
    char *dir;

    if (cwd)
        dir = cwd;
    else if ((dir = getenv("PWD")))
        ; // use PWD
    else
//the dot means “current directory” in shell semantics.
//"." is a generic safe fallback.
        dir = ".";
    return build_from_dir(dir);
}

char *get_prompt(t_shell_state *state)
{
    (void)state;
    if (!isatty(STDIN_FILENO))
        return ft_strdup("");
    return build_interactive_prompt();
}
