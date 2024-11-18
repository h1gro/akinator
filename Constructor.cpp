#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

node_t* AkinatorCtor(struct node_t* root)
{
    root = (node_t*) calloc(1, sizeof(node_t));
    //printf("root ctor1 = %p\n", root);

    assert(root);

    return root;
}

int AkinatorDtor(struct node_t* node)
{
    if(!node)
    {
        return 0;
    }

    AkinatorDtor(node->left);
    AkinatorDtor(node->right);

    free(node);

    node = NULL;

    return 0;

}


