#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "envHandler.h"

extern char **environ;

static int  countEnvVar = 0;
static Environ* this;
static char* varSearched = 0;
static char* varResult = 0;

static
void
__iterOnDoubleTab(char **env,
                  bool (*stop)(char *, int), 
                  void (*applyOnLine)(char *, int)) {
  int i = 0;
  while ((*stop)(env[i], i)) {
    (*applyOnLine)(env[i], i);
    ++i;
  }
}

static
void
__incCountEnvVar(char *line, int i) {
  ++countEnvVar;
}

static
void
__copyTab(char *line, int i) {
   this->envp[i] = strdup(environ[i]);
}

static
void
__matchVar(char* line, int i){
  if (strncmp(line, varSearched, strlen(varSearched)) == 0) varResult = strdup(line);
}

static
bool
__nullByteStop(char* line, int i) {
  return line != 0;
}

static
bool
__nullByteOrFoundStop(char* line, int i) {
   return line != 0 && varResult == 0;
}

static
char*
__find(Environ* t, char *s) {
  this = t;
  varSearched = s;
  varResult = 0;
  __iterOnDoubleTab(this->envp, &__nullByteOrFoundStop, &__matchVar);
  return varResult;  
}

void
newEnviron(Environ* env) {
  this = env;
  this->find = &__find;
  countEnvVar = 0;
  __iterOnDoubleTab(environ, &__nullByteStop, &__incCountEnvVar);
  this->envp = malloc(sizeof(*(this->envp)) * (countEnvVar + 1));
  if (this->envp == 0) exit(0);
  __iterOnDoubleTab(environ, &__nullByteStop, &__copyTab);
}
