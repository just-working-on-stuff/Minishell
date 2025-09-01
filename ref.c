/*
- [ ]  **G:** Implement `loop()` with `readline()` and `add_history()`
    - **How:**
        - `char *line = readline(prompt)`.
        - If `line == NULL` (Ctrl-D): `printf("exit\n"); exit(state->last_status);`.
        - Skip empty/space-only lines; otherwise `add_history(line)`.

        Mental picture (one cycle)
[show prompt] → [readline()] → (EOF? exit) 
             → (empty/blank? skip) 
             → add_history(line) 
             → hand off line to: lexer/expander/parser/executor (later days)
             → free(line) → loop again


Prompt: You’ll supply a string (Day 2 A handles formatting/TTY; here we just call a get_prompt(state) stub).

Read: char *line = readline(prompt);

EOF (Ctrl-D): line == NULL → print exit\n and exit(state->last_status);

Empty/blank line: just ignore (do nothing this round).

Non-empty: add_history(line);

Pass downstream: later days will actually tokenize/execute; for now just stub the call.

Memory: always free(line) before next iteration.

Keep “last status” as state->last_status and pass state* everywhere. Don’t store it globally.
*/