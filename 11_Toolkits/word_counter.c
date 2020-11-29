#include <glib.h>
#include <stdio.h>


gint compare(gconstpointer a, gconstpointer b)
{
    return b - a;
}


int main(int argc, char** argv) {
    GHashTable *hash = g_hash_table_new(g_str_hash, g_int_equal);

    char inputLine[100];
    char **wordsList, **pointer;

    while (gets(inputLine) != NULL) {
        if (*inputLine == 0) {
            continue;
        }
        wordsList = (char **) g_strsplit(inputLine, " ", 80);
        for (pointer = wordsList; *pointer != NULL; pointer++) {
            if (g_hash_table_lookup(hash, *pointer) != NULL) {
                g_hash_table_insert(hash, *pointer, g_hash_table_lookup(hash, *pointer) + 1);
            } else {
                g_hash_table_insert(hash, *pointer, 1);
            }
        }
    }

    GList * list = NULL, *item;
    list = g_list_alloc();
    list = g_hash_table_get_values(hash);
    list = g_list_sort (list, (GCompareFunc) compare);

    printf("Sorted Frequencies:\n");

    for(item = list; item; item = item->next) {
        printf("%d\n", GPOINTER_TO_INT(item->data));
    }
    g_hash_table_destroy(hash);

    return 0;
}
