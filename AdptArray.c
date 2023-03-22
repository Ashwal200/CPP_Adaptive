#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    PElement *array;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
    int size;
} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print_f)
{
    PAdptArray new_AdptArray = (PAdptArray)malloc(sizeof(AdptArray));
    new_AdptArray->array = (PElement *)calloc(1, sizeof(PElement));
    new_AdptArray->copy_func = copy;
    new_AdptArray->del_func = del;
    new_AdptArray->print_func = print_f;
    new_AdptArray->size = 0;
    return new_AdptArray;
};
void DeleteAdptArray(PAdptArray padptArray)
{
    if (padptArray == NULL)
    {
        return;
    }
    for (int i = 0; i < padptArray->size; i++)
    {
        if (padptArray->array[i] != NULL)
        {
            padptArray->del_func(padptArray->array[i]);
        }
    }
    free(padptArray->array);
    free(padptArray);
}

Result SetAdptArrayAt(PAdptArray padptArray, int index, PElement pelement)
{
    if (padptArray == NULL)
    {
        return FAIL;
    }

    if (index < 0)
    {
        return FAIL;
    }

    // if the size is bigger we only need to
    // put the element in the right place
    if (index < padptArray->size)
    {
        if (padptArray->array[index] != NULL)
        {
            // free the element
            padptArray->del_func(padptArray->array[index]);
        }
        padptArray->array[index] = padptArray->copy_func(pelement);
        return SUCCESS;
    }
    // if the size is smaller from the index we will make
    // new array that all the elements are NULL
    else if (index >= padptArray->size)
    {
        PElement *new_array = (PElement *)calloc(index + 1, sizeof(PElement));
        if (new_array == NULL)
        {
            return FAIL;
        }
        for (int i = 0; i < padptArray->size; i++)
        {
            if (padptArray->array[i] != NULL)
            {
                new_array[i] = padptArray->copy_func(padptArray->array[i]);
                padptArray->del_func(padptArray->array[i]);
            }
        }
        free(padptArray->array);
        padptArray->array = new_array;
        padptArray->size = index + 1;
        if (padptArray->array[index] != NULL)
        {
            padptArray->del_func(padptArray->array[index]);
        }
        padptArray->array[index] = padptArray->copy_func(pelement);
        return SUCCESS;
    }
    return FAIL;
}

PElement GetAdptArrayAt(PAdptArray padptArray, int index)
{
    if (padptArray == NULL)
    {
        return NULL;
    }

    if (index < 0)
    {
        return NULL;
    }

    if (padptArray->array[index] == NULL)
    {
        return NULL;
    }

    PElement answer = padptArray->copy_func(padptArray->array[index]);
    return answer;
}

int GetAdptArraySize(PAdptArray padptArray)
{
    if (padptArray == NULL)
    {
        return -1;
    }

    return padptArray->size;
}

void PrintDB(PAdptArray padptArray)
{
    if (padptArray == NULL)
    {
        return;
    }

    for (int i = 0; i < padptArray->size; i++)
    {
        if (padptArray->array[i] != NULL)
        {
            padptArray->print_func(padptArray->array[i]);
        }
    }
}