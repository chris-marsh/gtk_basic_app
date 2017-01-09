#include <gtk/gtk.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"
#include "common.h"


#define VERSION "1.0"
#define APP_NAME "basic"
#define CONFIG_NAME APP_NAME "rc"


static void usage(int exit_code)
{
    puts("\nUSAGE");
    puts("    basic [options]\n");
    puts("OPTIONS");
    puts("    -c, --config   - specify a config file path to load");
    puts("    -h, --help     - display this help");
    puts("    -v, --version  - output version information\n");

    exit(exit_code);
}


static void version(void)
{
    printf("Version %s (compiled %s)\n", VERSION, __DATE__);
    exit(0);
}


static char *process_arguments(int argc, char *argv[])
{
    int optc = 0;
    char *config_filename = NULL;
    static struct option const longopts[] = {
        {"config",   no_argument, NULL, 'c'},
        {"help",     no_argument, NULL, 'h'},
        {"version",  no_argument, NULL, 'V'},
        {NULL, 0, NULL, 0}
    };

    while ((optc = getopt_long(argc, argv, "c:hv", longopts, NULL)) != -1) {
        switch (optc) {
            case 'c':
                config_filename = strdup(optarg);
                break;
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

    return config_filename;
}


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    char *config_filename = process_arguments(argc, argv);
    WindowPtr window = create_window("The Title", config_filename);
    gtk_main();
    destroy_window(window);
    if (config_filename)
        free(config_filename);
    return 0;
}
