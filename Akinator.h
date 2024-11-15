#ifndef AKINATOR
#define AKINATOR

#include <stdio.h>

struct file_t
{
    FILE*  file_ptr;
    size_t file_size;
    size_t index_buf;
    char*  buffer;
};

const size_t NO_SPACE = 15;

size_t SkipSpaces         (struct file_t* akin, size_t index);
size_t ScanFile           (struct file_t* akin);

int CheckFile             (FILE* file);

void CheckFclose          (FILE* file_ptr);
void ChangeSymbolInBuffer (struct file_t* buf_struct, size_t size_buffer, char symbol1, char symbol2);

char* BufferCtor          (struct file_t* akin);

#endif
