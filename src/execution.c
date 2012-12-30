#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "envHandler.h"
#include "formatInput.h"

static
char *
__binPath(Environ *env, FormatedInput* input) {
  char *path = env->find(env, "PATH");  
  if (path == 0) return 0;
  path += 5;
  char *buff;
  while ((buff = strtok(path, ":"))) {
    path = 0;
    buff = strdup(buff);
    if (buff == 0) return 0;
    buff = realloc(buff, strlen(buff) + strlen(input->datas[0]) + 2);
    buff = strcat(buff, "/");
    buff = strcat(buff, input->datas[0]);
    if (access(buff, X_OK) == 0) {
      return buff;
    }
  }
  return 0;
}

void
__exec(FormatedInput* input, Environ* env,
       char *path) {
  pid_t pid = fork();
  if (pid == -1) return ;
  else if (pid == 0) {
    execve(path, input->datas, env->envp);
    printf("%s : no such command\n", input->datas[0]);
    exit(EXIT_SUCCESS);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
}

void
Execution(FormatedInput* input, Environ* env) {
   char *path = __binPath(env, input);
   if (path == 0) {
      printf("%s : no such command\n", input->datas[0]);
      return ;
   }
   __exec(input, env, path);
}
