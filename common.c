#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

char *strdup (const char *source_str)
{
    char *dest_str = malloc (strlen(source_str) + 1);   // Allocate memory
    if (dest_str != NULL) strcpy (dest_str,source_str); // Copy string if okay
    return dest_str;                                    // Return new memory
}


int trim_spaces(char *source_str)
{
    char *dest_str = source_str;
    int length = strlen(dest_str);

    /* zero trailing spaces */
    while (dest_str[length - 1] == SPACE)
        dest_str[--length] = 0;

    /* Increment pointer skipping leading spaces */
    while (*dest_str && *dest_str == SPACE)
        ++dest_str, --length;

    /* Copy the trimmed string back to the input string */
    memmove(source_str, dest_str, length + 1);

    return length;
}  
