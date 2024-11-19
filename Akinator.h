#ifndef AKINATOR
#define AKINATOR

#include <stdio.h>

const int TREE_SIZE      = 10;
const int NUMBER_ELEMS   = 1;
const int NUMBER_SYMBOLS = 100;

const size_t SCAN_FILE_POISON = 153153;
const size_t NO_SPACE         = 15;

struct file_t
{
    FILE*  file_ptr;
    size_t file_size;
    size_t index_buf;
    char*  buffer;
};

struct node_t
{
    char    word[NUMBER_SYMBOLS];
    node_t* left;
    node_t* right;
    node_t* parent;
};

enum user_comands
{
    ADD_ANSWER         = 1,
    DONT_ADD_ANSWER    = 2,
    PLAY_AKINATOR      = 1,
    DONT_PLAY_AKINATOR = 2,
};

node_t* AkinatorCtor      (struct node_t* root);
node_t* CreateNode        (struct node_t* parent, const char* word);
node_t* ReadTree          (struct node_t* parent, struct file_t* akin);

size_t ScanFile           (struct file_t* akin);
size_t FindNoSpace        (struct file_t* akin, size_t index);
size_t SkipSpacesForPrint (struct file_t* akin, size_t index);

int CheckFile             (FILE* file);
int GuessWord             (struct node_t* node, struct node_t* root);
int AkinatorDtor          (struct node_t* node, struct file_t* akin);

void CheckFclose          (FILE* file_ptr);
void RewriteTree          (struct node_t* node, FILE* file_ptr);
void IfAddAnswer          (struct node_t* node, struct node_t* root);
void CreateNewAnswer      (struct node_t* node, struct node_t* root);
void Game                 (struct node_t* node, struct node_t* root);
void SkipSpacesToSymbols  (struct file_t* akin, int symbol0, int symbol1, int symbol2, int symbol3);
void ChangeSymbolInBuffer (struct file_t* buf_struct, size_t size_buffer, char symbol1, char symbol2);

char* BufferCtor          (struct file_t* akin);

#endif
