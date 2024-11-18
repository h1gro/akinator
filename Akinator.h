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

struct node_t
{
    const char*    word;
    node_t*        left;
    node_t*        right;
};

static const char* TREE_FILE = "Tree.txt";

const int TREE_SIZE    = 10;
const int NUMBER_ELEMS = 1;

const size_t NO_SPACE  = 15;

node_t* AkinatorCtor      (struct node_t* root);
node_t* CreateSubtree     (struct node_t* parent, const char* word);
node_t* ReadTree          (struct node_t* parent, struct file_t* akin);
//node_t* FindLow       (struct node_t* subtree);
//
// int GetWord           (struct node_t* parent, struct node_t* subtree);

size_t FindNoSpace        (struct file_t* akin, size_t index);
size_t SkipSpaces         (struct file_t* akin, size_t index);
size_t ScanFile           (struct file_t* akin);

int AkinatorDtor          (struct node_t* node);
int CheckFile             (FILE* file);

void CheckFclose          (FILE* file_ptr);
void ChangeSymbolInBuffer (struct file_t* buf_struct, size_t size_buffer, char symbol1, char symbol2);

char* BufferCtor          (struct file_t* akin);

#endif
