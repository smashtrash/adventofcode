#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

gint sort_function(gconstpointer a, gconstpointer b) {
    int *int_a = (int *)a;
    int *int_b = (int *)b;

    return (*int_a) - (*int_b);
}


gint arr_index(gint *arr, gint value, gint length) {
    // Search for first occurance of value in array
    gint i;
    for (i = 0; i < length; i++) {
        if (arr[i] == value) {
            return i;
        }
    }

    // return -1 if value not in array
    return -1;
}

char **transpose_array(GArray *data, gint *columns) {
    gchar **col_array;
    gint i, col;
    guint row;
    char *line;

    (*columns) = strlen(g_array_index(data, char *, 0));

    // Initialize and allocate memory for columns
    col_array = g_new0(gchar *, *columns);
    for (i = 0; i < *columns; i++)
        col_array[i] = g_new0(gchar, data->len + 1);

    // "Transpose" the input array and make sure the char* arrays
    // are NULL terminated.
    for (row = 0; row < data->len; row++) {
        line = g_array_index(data, gchar *, row);
        for (col = 0; col < *columns; col++) {
            col_array[col][row] = line[col];
            if (row == data->len -1) {
                col_array[col][row + 1] = '\0';
            }
        }
    }

    return col_array;

}

char* solve_part_1(GArray *data) {
    guint i;
    gint col;
    gint columns;
    gchar **col_array;
    GString *message;
    gint *count;
    gint max_index;

    // Allocation of memory for base arrays
    col_array = transpose_array(data, &columns);
    message = g_string_new("");

    // Count characters in each column by using offset to 'a' as index.
    // Add character at each max position to return string 'message'
    for (col = 0; col < columns; col++) {
        count = g_new0(gint, 26);
        for (i = 0; i < data->len; i++) {
            count[col_array[col][i] - 'a']++;
        }
        max_index = arr_index(count, max(count, 26), 26);
        message = g_string_append_c(message, (gchar)(max_index + 'a'));
        g_free(count);
    }

    /* Freeing up allocated memory */
    for (col = 0; col < columns; col++) {
        g_free(col_array[col]);
    }
    g_free(col_array);

    return message->str;
}

char *solve_part_2(GArray *data) {
    guint i;
    gint col;
    gint columns;
    gchar **col_array;
    gchar *message;
    gint *count;
    gint min_index;

    // Allocation of memory for base arrays
    col_array = transpose_array(data, &columns);
    message = g_new0(gchar, columns + 1);

    // Count characters in each column by using offset to 'a' as index.
    // Add character at each min position to return string 'message'
    for (col = 0; col < columns; col++) {
        count = g_new0(gint, 26);
        for (i = 0; i < data->len; i++) {
            count[col_array[col][i] - 'a']++;
        }
        min_index = arr_index(count, min_non_zero(count, 26), 26);
        message[col] = (gchar)(min_index + 'a');
        g_free(count);
    }

    // Null terminate return string
    message[columns] = '\0';

    /* Freeing up allocated memory */
    for (col = 0; col < columns; col++) {
        g_free(col_array[col]);
    }
    g_free(col_array);

    return message;
}


int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);
    if (data) {
        TIMER_STR(1, solve_part_1(data), 1);
        TIMER_STR(2, solve_part_2(data), 1);

        g_array_free(data, TRUE);
    }
    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2016, 6), INT, 0);
    g_free(filename);
}
