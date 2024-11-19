#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

node_t* AkinatorCtor(struct node_t* root)
{
    root = (node_t*) calloc(1, sizeof(node_t));
    //printf("root ctor1 = %p\n", root);

    assert(root);

    //root->word  = NULL;
    root->left  = NULL;
    root->right = NULL;

    return root;
}

int AkinatorDtor(struct node_t* node, struct file_t* akin)
{
    if(!node)
    {
        return 0;
    }

    AkinatorDtor(node->left, akin);
    AkinatorDtor(node->right, akin);

    free(node->word);
    //free(node);

    node = NULL;
    return 0;
}


