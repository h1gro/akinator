#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "Akinator.h"
#include "Tree.h"

node_t* ReadTree(struct node_t* parent, struct file_t* akin)
{
    assert(parent);
    assert(akin);

    node_t* new_subtree = NULL;

    size_t number_elems = ScanFile(akin);

    char* word = (char*) calloc(52, sizeof(char));

    for (size_t hyi = 0; hyi < number_elems; hyi++)
    {
        if (SkipSpaces(akin, hyi) != hyi) {continue;}
        printf("buffer[%lu] = %c\n", hyi, akin->buffer[hyi]);
    }

    if (akin->buffer[akin->index_buf] == '{')
    {
        for (size_t i = akin->index_buf + 1; i < number_elems; i++)
        {
            printf("\nin if\n");
            while ((akin->buffer[i] != '}') && (akin->buffer[i] != '\n') && (akin->buffer[i] != EOF) && (akin->buffer[i] != '\0') && (akin->buffer[i] != ';'))
            {
                if (SkipSpaces(akin, i) != i) {continue;}

                if ((akin->buffer[i] == '{') && (akin->buffer[i + 1] == '}'))
                {
                    i++;
                    continue;
                }

                //printf("\n in while \n");
                sscanf(akin->buffer, "%s[^\"]", word);

                for (size_t j = 0; j < number_elems; j++)
                {
                    printf("%c", word[j]);
                }
            }

            printf("i tyt\n");

            new_subtree = CreateSubtree(parent, word);

            akin->index_buf = i + 1;

            if (akin->buffer[i] == ';') {return NULL;}
        }

    }

    else
    {
        printf("file_ptr is damaged!\n");
        return NULL;
    }

    new_subtree->left  = ReadTree(new_subtree, akin);
    new_subtree->right = ReadTree(new_subtree, akin);

    free(akin->buffer);
    free(word);
    return new_subtree;
}

void CheckFclose(FILE* file_ptr)
{
    assert(file_ptr);

    int fclose_return = fclose(file_ptr);

    if (fclose_return != 0)
    {
        printf("file closed wrong, fclose_return = %d\n", fclose_return);
    }
}

size_t ScanFile(struct file_t* file_struct)
{
    assert(file_struct->file_ptr);

    CheckFile(file_struct->file_ptr);

    char* file_struct_buffer = BufferCtor(file_struct);

    size_t number_elems = fread(file_struct_buffer, 1, file_struct->file_size, file_struct->file_ptr);

    if (number_elems != file_struct->file_size)
    {
        printf("fread return = %lu, stat return = %lu\n", number_elems, file_struct->file_size);
    }

    ChangeSymbolInBuffer(file_struct, number_elems, '\r', '\0');
    return number_elems;
}

int CheckFile(FILE* file)
{
    if (file == NULL)
    {
        printf("file not opened\n");
        return -1;
    }
    return 0;
}

char* BufferCtor(struct file_t* akin)
{
    assert(akin);

    struct stat akin_file = {};

    stat(TREE_FILE, &akin_file);

    akin->buffer = (char*) calloc(akin_file.st_size, sizeof(char));

    akin->file_size = akin_file.st_size;

    assert(akin->buffer);

    return akin->buffer;
}

size_t SkipSpaces(struct file_t* akin, size_t index)
{
    assert(akin);
    assert(akin->buffer);

    for (size_t i = index; i < akin->file_size; i++)
    {
        if ((akin->buffer[i] != ' ') && (akin->buffer[i] != '\0'))
        {
            return i;
        }
    }

    return NO_SPACE;
}

void ChangeSymbolInBuffer(struct file_t* buf_struct, size_t size_buffer, char symbol1, char symbol2)
{
    assert(buf_struct);
    assert(size_buffer > 0);

    for (unsigned long int i = 0; i < size_buffer; i++)
    {
        if (buf_struct->buffer[i] == symbol1)
        {
            buf_struct->buffer[i] = symbol2;
        }
    }
}
