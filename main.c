#include <unistd.h>
#include <stdbool.h>
#include "getRawInput.h"
#include "formatInput.h"

int
main() {
  bool go = true;

  while (go == true) {
    char* rawLine = getRawInput();
    if (rawLine == 0) continue ;
    FormatedInput* format = formatInput(rawLine);
    printf("+%s+%s+\n", format->datas[0], format->datas[1]);
    
    /*
 * Get Raw Entry
 * Format Entry
 * Handle the Parsed Entry to Execution
 */

  }
}
