#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "formatInput.h"

static int wordCount = 0;
static int charCount = 0;
static char* cleanedString = 0;
static int indexCleanedString = 0;

static
void
__wordCounter(char c, bool isInWord) {
  if (isInWord == true) ++wordCount;
}

static
void
__charCounter(char c, bool isInWord) {
  ++charCount;
}

static
void
__copyCleanStringEndWord(char c, bool isInWord) {
  if (isInWord == true) {
    cleanedString[indexCleanedString] = ' ';
    ++indexCleanedString;
  }
}

static
void
__copyCleanStringWord(char c, bool isInWord) {
  cleanedString[indexCleanedString++] = c;
}

static
void
__endCleanStringCopy(char c, bool isInWord) {
  cleanedString[indexCleanedString] = 0;
  indexCleanedString = 0;
}

static
void
__applyOnString(char *s,
                void (*charCase)(char, bool),
                void (*nonCharCase)(char, bool),
                void (*beforeReturn)(char, bool)) {
  int i = 0;
  bool isInWord = false;

  while (s[i]) {
     if (s[i] == ' ' || s[i] == '\t') {
       if (charCase != 0) (*charCase)(s[i], isInWord); 
       isInWord = false; 
     } else {
       if (nonCharCase != 0) (*nonCharCase)(s[i], isInWord);
       isInWord = true;
     }
     ++i;
  }
  if (beforeReturn != 0) beforeReturn(s[i], isInWord);
}

static
char*
__preproc(char *s) {
  __applyOnString(s, &__wordCounter, 0, &__wordCounter);
  __applyOnString(s, &__charCounter, 0, 0);
  cleanedString = malloc(sizeof(*cleanedString) * (wordCount + charCount + 1));
                          
                           
  if (cleanedString == 0) return 0;
  __applyOnString(s, &__copyCleanStringEndWord, &__copyCleanStringWord, &__endCleanStringCopy); 
  return cleanedString;
}

FormatedInput*
formatInput(char *rawInput) {
  FormatedInput *input = malloc(sizeof(*input));
  if (input == 0) return 0;
  char *buff = 0;
  wordCount = 0;
  charCount = 0;

  int i = 0;
  char *strtokparam = __preproc(rawInput); 
  input->datas = malloc(sizeof(*(input->datas)) * (wordCount + 1));
  if (input->datas == 0) return 0;
  while ((buff = strtok(strtokparam, " "))) {
    input->datas[i] = buff;
    strtokparam = 0;
    ++i;
  }
  return input;
}
