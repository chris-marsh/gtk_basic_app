#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "config.h"


typedef struct Window *WindowPtr;


struct Window {
    char *title;
    GtkWidget *win;
    Config *config;
};


static void on_key_press(GtkWidget *window, GdkEventKey *eventkey)
{
    switch (eventkey->keyval) {
        case GDK_KEY_q:
        case GDK_KEY_Escape:
            gtk_widget_destroy(window);
            break;
        case GDK_KEY_h:
            puts("Hello, world.");
            break;
    }
}


WindowPtr create_window(const char *title, const char *config_filename)
{
    WindowPtr window = malloc(sizeof *window);

    if (window) {
        /* read config example */
        if (config_filename) {
            window->config = read_config_file(config_filename);
            Option option;
            while (window->config!=NULL) {
                option = pop_option(&(window->config));
                printf("%s  =  %s\n", option.key, option.value);
                free_option(option);
            }
            free(window->config);
        }

        window->title = strdup(title);

        window->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_type_hint(GTK_WINDOW(window->win), GDK_WINDOW_TYPE_HINT_DIALOG);
        gtk_window_set_title(GTK_WINDOW(window->win), title);
        gtk_window_set_default_size(GTK_WINDOW(window->win), 200, 200);
        g_signal_connect(GTK_WINDOW(window->win), "key_press_event", G_CALLBACK(on_key_press), NULL);
        g_signal_connect (GTK_WIDGET (window->win), "destroy", G_CALLBACK (gtk_main_quit), NULL);

        GtkWidget *label = gtk_label_new("Hello, world.");
        gtk_container_add(GTK_CONTAINER(window->win), label); 

        gtk_widget_show_all(window->win);
    }
    return window;
}


void destroy_window(WindowPtr window)
{
    if (gtk_main_level() !=0 && window->win != NULL) {
        gtk_widget_destroy(window->win);
    }
    free(window);
}

