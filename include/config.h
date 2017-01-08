#ifndef CONFIG_H
#define CONFIG_H


/* Option pairs */
typedef struct {
    char *key;
    char *value;
} Option;


/* Config stack of options */
typedef struct Config {
    Option option;
    struct Config *next;
} Config;


int push_option(Config **head, char *key, char *value);
Option pop_option(Config **head);
void free_option(Option option);
Config *read_config_file(char *filename);

#endif
