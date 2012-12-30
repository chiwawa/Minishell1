#ifndef FORMAT_INPUT_H__
# define FORMAT_INPUT_H__

typedef struct s_formatedInput {
   char        **datas;
}             FormatedInput;

FormatedInput* formatInput(char *rawInput);

#endif
