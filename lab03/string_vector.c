
#include "string_vector.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

StringVector* vector_create(size_t initial_capacity)
{
        StringVector *vec = malloc(sizeof(StringVector));

        if (vec== NULL)
        {
                return NULL;
        }

        (*vec).data = malloc(initial_capacity * sizeof(char *));

        if ((*vec).data == NULL)
        {
                free(vec);
                return NULL;
        }

        (*vec).capacity = initial_capacity;
        (*vec).size = 0;

        return vec;
}

int vector_push(StringVector *vec, const char *str)
{
        if ((*vec).size == (*vec).capacity)
        {
                (*vec).capacity *= 2;

                char **new_data = realloc((*vec).data, (*vec).capacity * sizeof(char *));

                if (new_data == NULL)
                {
                        return 0;
                }

                (*vec).data = new_data;
        }

        (*vec).data[(*vec).size] = strdup(str);

        if ((*vec).data[(*vec).size] == NULL)
        {
                return 0;
        }

        (*vec).size++;

        return 1;
}
const char* vector_get(const StringVector *vec, size_t index)

{
        if (index >= (*vec).size)
        {
                return NULL;
        }

        return (*vec).data[index];
}

void vector_free(StringVector *vec)

{
        for (size_t i = 0; i < (*vec).size; i++)
        {
                free((*vec).data[i]);
        }

        free((*vec).data);
        free(vec);
}
