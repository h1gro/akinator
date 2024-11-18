#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "Akinator.h"

node_t* ReadTree(struct node_t* parent, struct file_t* akin)
{
    assert(parent);
    assert(akin);

    int n = 0;
    size_t number = 0;

    node_t* new_subtree = NULL;

    size_t number_elems = ScanFile(akin);

    printf("number_elems = %lu\nakin->index_buf = %lu\n", number_elems, akin->index_buf);

    for (size_t hyi = 0; hyi < number_elems; hyi++)
    {
        if (SkipSpaces(akin, hyi) != hyi) {continue;}
        //printf("buffer[%lu] = %c\n", hyi, akin->buffer[hyi]);
        printf("%c", akin->buffer[hyi]);
    }

    if (akin->buffer[akin->index_buf] == '{')
    {
        char symbol = akin->buffer[akin->index_buf + 1];
        printf("symbol = %c\n", symbol);

        if (symbol != '}')
        {
            char* word = (char*) calloc(52, sizeof(char));

            sscanf(akin->buffer, "{%s[^\"]%n", word, number);

            printf("word = %s\nnumber = %lu\n", word, number);

            new_subtree = CreateSubtree(parent, word);

            free(word);

            if (akin->buffer[akin->index_buf + number] == EOF){return 0;}

            size_t shift_for_first_symbol = FindNoSpace(akin, akin->index_buf + number);

            printf("shift_for_first_symbol = %lu\n", shift_for_first_symbol);

            akin->index_buf = akin->index_buf + number + shift_for_first_symbol;

            printf("akin->index_buf after shift and number elems = %lu\n", akin->index_buf);

        }

        else
        {
            if (akin->buffer[akin->index_buf + number] == EOF){return 0;}
        }
//         for (size_t i = akin->index_buf + 1; i < number_elems; i++)
//         {
//             printf("i = %lu\n", i);
//
//             if ((akin->buffer[i] == '}') || (akin->buffer[i] == '\n') || (akin->buffer[i] == EOF) || (akin->buffer[i] == '\0') || (akin->buffer[i] == ';'))
//             {
//                 printf("сделал первый иф buffer[%lu] = %c\n", i, akin->buffer[i]);
//                 i += 1;
//                 continue;
//             }
//
//             if ((akin->buffer[i] == '{') && (akin->buffer[i + 1] == '}'))
//             {
//                 printf("сделал первый иф buffer[%lu] = %c\n", i, akin->buffer[i]);
//                 i += 1;
//                 continue;
//             }
//
//             if (SkipSpaces(akin, i) != i) {continue;}
//
//             //printf("\n in while \n");
//
//             char* word = (char*) calloc(52, sizeof(char));
//
//             sscanf(akin->buffer, "%[^\"]\"%n", word, &number);
//             printf("word = %s, number = %d\n", word, number);
//
//             akin->buffer += number;
//             i += number - 1;
//             printf("i = %lu\n\n", i);
//
// //             for (size_t j = 0; j < number_elems; j++)
// //             {
// //                 if (SkipSpaces(akin, j) != j) {continue;}
// //                 printf("%c", word[j]);
// //             }
// //
// //             printf("i tyt\n");
//
//             new_subtree = CreateSubtree(parent, word);
//
//             free(word);
//             //akin->index_buf = i + 1;
//
//             if (akin->buffer[i] == ';') {return NULL;}
//        }

    }

    else
    {
        printf("file_ptr is damaged!\n");
        return NULL;
    }

    new_subtree->left  = ReadTree(new_subtree, akin);
    new_subtree->right = ReadTree(new_subtree, akin);

    free(akin->buffer);
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

    ChangeSymbolInBuffer(file_struct, file_struct->file_size, '\r', '\0');
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

size_t FindNoSpace(struct file_t* akin, size_t index)
{
    assert(akin);
    assert(akin->buffer);

    size_t shift = 0;

    if (akin->buffer[index] == '}'){index += 1;}

    while ((akin->buffer[index] == ' ') || (akin->buffer[index] == '\n') || (akin->buffer[index] == '\0'))
    {
        index++;
        shift++;
    }

    return shift;
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
