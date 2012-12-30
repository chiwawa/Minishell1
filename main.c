#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "getRawInput.h"
#include "formatInput.h"
#include "envHandler.h"
#include "execution.h"

extern char **environ;

int
main() {
  Environ env;
  bool go = true;

  newEnviron(&env);
  while (go == true) {
    char* rawLine = getRawInput();
    if (rawLine == 0) {
       go = false;
    } else {
     FormatedInput* format = formatInput(rawLine);
     if (format == 0) continue ;
     Execution(format, &env); 
     //free(format);
    }
  //free(rawLine);
 }
}
