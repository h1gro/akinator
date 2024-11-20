#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"
#include "Dump.h"

static const char* TREE_FILE = "Tree.txt";

//TODO научиться давать определения по заданному слову(елементу дерева), если оно есть в дереве
//TODO уметь отличать два элемента дерева друг от друга и писать чем они отличаются и чем похожи

int main()
{
    struct file_t akin = {};

    node_t* root = NULL;

    akin.file_ptr = fopen(TREE_FILE, "r");

    assert(akin.file_ptr);

    //root = AkinatorCtor(root);

    if (ScanFile(&akin) == SCAN_FILE_POISON)
    {
        return -1;
    }

    root = ReadTree(root, &akin);

    CheckFclose(akin.file_ptr);

    TreeDump(root);

    PlayMode(root, root);

    AkinatorDtor(root, &akin);
    free(akin.buffer);
    return 0;
}
