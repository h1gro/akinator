#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#include "Akinator.h"

static const char* TREE_FILE = "Tree.txt";

size_t ScanFile(struct file_t* file_struct)
{
    assert(file_struct->file_ptr);

    //printf("%s\n", __func__);

    if (CheckFile(file_struct->file_ptr) != -1)
    {
        char* file_struct_buffer = BufferCtor(file_struct);

        size_t number_elems = fread(file_struct_buffer, 1, file_struct->file_size, file_struct->file_ptr);

        if (number_elems != file_struct->file_size)
        {
            printf("fread return = %lu, stat return = %lu\n", number_elems, file_struct->file_size);
        }

        ChangeSymbolInBuffer(file_struct, file_struct->file_size, '\r', '\0');
        return file_struct->file_size;
    }

    else
    {
        return SCAN_FILE_POISON;
    }
}

char* BufferCtor(struct file_t* akin)
{
    assert(akin);

    //printf("%s\n", __func__);

    struct stat akin_file = {};

    stat(TREE_FILE, &akin_file);

    akin->buffer = (char*) calloc(akin_file.st_size, sizeof(char)); //+1 for EOF

    akin->file_size = akin_file.st_size;

    assert(akin->buffer);

    return akin->buffer;
}

size_t SkipSpacesForPrint(struct file_t* akin, size_t index)
{
    assert(akin);
    assert(akin->buffer);

    //printf("%s\n", __func__);

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

    //printf("%s\n", __func__);

    size_t shift = 0;

    if (akin->buffer[index] == '}'){index += 1;}

    while ((akin->buffer[index] == ' ') || (akin->buffer[index] == '\n') || (akin->buffer[index] == '\0'))
    {
        index++;
        shift++;
    }

    return shift;
}
