#include <gtk/gtk.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"


#define VERSION "1.0"


static void usage(int exit_code)
{
    puts("\nUSAGE");
    puts("    basic [options]\n");
    puts("OPTIONS");
    puts("    -h, --help     - display this help");
    puts("    -v, --version  - output version information\n");

    exit(exit_code);
}


static void version(void)
{
    printf("Version %s (compiled %s)\n", VERSION, __DATE__);
    exit(0);
}


static int get_command_line_options(
        int argc, char *argv[])
{
    int optc = 0;
    static struct option const longopts[] = {
        {"help",     no_argument, NULL, 'h'},
        {"version",  no_argument, NULL, 'V'},
        {NULL, 0, NULL, 0}
    };

    while ((optc = getopt_long(argc, argv, "x:y:smhv", longopts, NULL)) != -1) {
        switch (optc) {
            case 'h':
                usage(0);
                break;
            case 'v':
                version();
                break;
            default:
                usage (-1);
        }
    }

    if (optind < argc) {
        if (argc-optind > 0) {
            /* Get the other arguments from argv[optind]*/
        } else
            usage(-1);
    }

    return optc;
}


int main(int argc, char *argv[])
{
    get_command_line_options(argc, argv);
    gtk_init(&argc, &argv);
    WindowPtr window = create_window("The Title", "./basicrc");
    gtk_main();
    destroy_window(window);
    return 0;
}
