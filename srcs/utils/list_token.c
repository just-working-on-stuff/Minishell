#include "../../include/minishell.h"

static int  token_new_element(t_token **new, char *str, int type)
{
    if (!str)
        return (0);
    (*new) = malloc(sizeof(t_token));
    if (*new == NULL)
    {
        free(str);
        return (0);
    }
    (*new)->str = str;
    (*new)->type = type;
    (*new)->next = NULL;
    (*new)->prev = NULL;
    return (1);
}
/*the function above puts shows how a new element is tokenized, allocating
a malloced string and the type of token it is, ensuring theres nothing
before or after it*/

static void add_first(t_token **list, t_token *new)
{
    (*list) = new;
    (*list)->prev = *list;
    (*list)->next = *list;
}

int append_token(t_token **list, char *str, int type)
{
    t_token *new;

    if (!token_new_element(&new, str, type))
        return (0);
    if (!(*list))
        add_first(list, new);
    else
    {
        new->prev = (*list)->prev;
        new->next = (*list);
        (*list)->prev->next = new;
        (*list)->prev = new;
    }
    return (1);
}
/*add note to what this function does*/
 
void    free_token(t_token **list)
{
    t_token *temp;
    t_token *current;

    if (!(*list))
        return ;
    current = *list;
    while (current->next != *list)
    {
        temp = current;
        current = current->next;
        free(temp->str);
        free(temp);
    }
    free(current->str);
    free(current);
    *list = NULL;
}
/*add note on what this does*/