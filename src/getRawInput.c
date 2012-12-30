#include <unistd.h>
#include <string.h>
#include "getRawInput.h"

static char buff[BUFF_SIZE];

char *
getRawInput() {
  int nbRead;

  nbRead = read(0, buff, BUFF_SIZE);
  if (nbRead == -1) return 0;
  return (nbRead == 0 ? 0 : strndup(buff, nbRead - 1));
}
