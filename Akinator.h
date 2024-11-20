#ifndef AKINATOR
#define AKINATOR

#include <stdio.h>

const int NUMBER_SYMBOLS  = 100;

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

struct addr_t
{
    node_t** nods_addresses;
    int      index;
};

enum user_comands
{
    PLAY_AKINATOR      = 1,
    DONT_PLAY_AKINATOR = 2,
    ADD_ANSWER         = 3,
    DONT_ADD_ANSWER    = 4,
    GET_DIF            = 5,
    DONT_GET_DIF       = 6,
};

enum find_word
{
    FIND_WORD_ERROR  = 9,
    WORD_WAS_FOUNDED = 10,
};

find_word FindWord        (struct node_t* node, struct addr_t* array, char* word);
find_word GetUserWord     (struct node_t* root, struct addr_t* array);

node_t* AkinatorCtor      (struct node_t* root);
node_t* CreateNode        (struct node_t* parent, const char* word);
node_t* ReadTree          (struct node_t* parent, struct file_t* akin);

size_t ScanFile           (struct file_t* akin);
size_t FindNoSpace        (struct file_t* akin, size_t index);
size_t SkipSpacesForPrint (struct file_t* akin, size_t index);

int CheckFile             (FILE* file);
int GuessWord             (struct node_t* node, struct node_t* root);
int AkinatorDtor          (struct node_t* node, struct file_t* akin);

void ClearBuffer          ();
void CheckFclose          (FILE* file_ptr);

void GetDifCommand        (struct node_t* root);
void RewriteTree          (struct node_t* node, FILE* file_ptr);

void PlayMode             (struct node_t* node, struct node_t* root);
void IfAddAnswer          (struct node_t* node, struct node_t* root);
void CreateNewAnswer      (struct node_t* node, struct node_t* root);
void Game                 (struct node_t* node, struct node_t* root);

void PrintfGameEnding     (struct node_t* node, struct node_t* root, char* answer);
void SkipSpacesToSymbols  (struct file_t* akin, int symbol0, int symbol1, int symbol2, int symbol3);
void ChangeSymbolInBuffer (struct file_t* buf_struct, size_t size_buffer, char symbol1, char symbol2);

char* BufferCtor          (struct file_t* akin);

#endif
