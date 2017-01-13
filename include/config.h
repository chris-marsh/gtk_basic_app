/******************************************************************************
 *                                                                            *
 *                   Copyright (C) 2016 Chris Marsh                           *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU General Public License as published by the      *
 * Free Software Foundation, either version 3 of the License, or any later    *
 * version.                                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * at <http://www.gnu.org/licenses/> for more details.                        *
 *                                                                            *
 ******************************************************************************/


#ifndef CONFIG_H
#define CONFIG_H


#define APP_NAME "example""
#define CONFIG_NAME APP_NAME "rc"


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


int push_option(Config **head, const char *key, const char *value);
Option pop_option(Config **head);
void free_option(Option option);
Config *read_config_file(const char *filename);

#endif
