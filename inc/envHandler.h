#ifndef __ENV_HANDLER_H__
# define __ENV_HANDLER_H__

typedef struct s_env {
   char **envp;
   char* (*find)(struct s_env *, char *);
}              Environ;

void newEnviron(Environ* env);

#endif
