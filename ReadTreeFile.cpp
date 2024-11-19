#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "Akinator.h"

node_t* ReadTree(struct node_t* parent, struct file_t* akin)
{
    //assert(parent);
    assert(akin);

    printf("\nREAD_TREE\n");

    node_t* new_subtree = NULL;

    printf("number_elems = %lu\nakin->index_buf = %lu\n", akin->file_size, akin->index_buf);

    // for (size_t i = 0; i < akin->file_size; i++)
    // {
    //     if (SkipSpacesForPrint(akin, i) != i) {continue;}
    //     //printf("buffer[%lu] = %c\n", i, akin->buffer[i]);
    //     printf("%c", akin->buffer[i]);
    // }

    int symbol = akin->buffer[akin->index_buf];

    if (symbol == '{')
    {
        char* word = (char*) calloc(100, sizeof(char));
        printf("%p\n", word);
        sscanf(&akin->buffer[akin->index_buf], "{\"%[^\"]\"", word);

        printf("word = %s\n", word);
        printf("index = %lu\n", akin->index_buf);

        new_subtree = CreateNode(parent, word);

        free(word);

        symbol = 0;
        akin->index_buf++;
        //SkipSpacesToSymbols(akin, symbol, (int)'{', (int)'}', (int)EOF);

        while ((symbol != '{') && (symbol != '}') && (symbol != EOF))
        {
            symbol = akin->buffer[akin->index_buf];
            printf("buffer[%lu] = %c\n", akin->index_buf, symbol);
            akin->index_buf++;
        }
        akin->index_buf--;
        printf("index after first while = %lu\n", akin->index_buf);

        if (symbol == '}')
        {
            //SkipSpacesToSymbols(akin, symbol, (int)'{', (int)EOF, (int)';');
            while ((symbol != '{') && (symbol != EOF) && (symbol != ';'))
            {
                symbol = akin->buffer[akin->index_buf];
                printf("buffer[%lu] = %c\n", akin->index_buf, symbol);
                akin->index_buf++;
            }
            akin->index_buf--;

            return new_subtree;
        }

        else
        {
            new_subtree->left  = ReadTree(new_subtree, akin);
            new_subtree->right = ReadTree(new_subtree, akin);
        }

        return new_subtree;
    }

    return NULL;

}

void CheckFclose(FILE* file_ptr)
{
    assert(file_ptr);

    printf("\nCHECK FCLOSE\n");

    int fclose_return = fclose(file_ptr);

    if (fclose_return != 0)
    {
        printf("file closed wrong, fclose_return = %d\n", fclose_return);
    }
}

void SkipSpacesToSymbols(struct file_t* akin, int symbol0, int symbol1, int symbol2, int symbol3)
{
        printf("\n %d %d %d %d\n", symbol0, symbol1, symbol2, symbol3);
        while ((symbol0 != symbol1) && (symbol0 != symbol2) && (symbol0 != symbol3))
        {
            symbol0 = akin->buffer[akin->index_buf];
            printf("buffer[%lu] = %c\n", akin->index_buf, symbol0);
            akin->index_buf++;
        }
        akin->index_buf--;
}
