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
    if (rawLine == 0) continue ;
    FormatedInput* format = formatInput(rawLine);
    if (format == 0) continue ;
    Execution(format, &env);
        
    /*
 * Get Raw Entry
 * Format Entry
 * Handle the Parsed Entry to Execution
 */

  }
}
