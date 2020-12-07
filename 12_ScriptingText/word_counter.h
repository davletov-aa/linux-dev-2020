#include <glib.h>

gint compare(gconstpointer a, gconstpointer b)
{
    return b - a;
}

