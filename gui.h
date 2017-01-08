#ifndef GUI_H
#define GUI_H

typedef struct Window* WindowPtr;
WindowPtr create_window(const char *title, const char *config_filename);
void destroy_window(WindowPtr window);

#endif
