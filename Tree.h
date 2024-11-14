#ifndef TREE
#define TREE

struct node_t
{
    const char*    word;
    node_t*        left;
    node_t*        right;
};

const int TREE_SIZE    = 10;
const int NUMBER_ELEMS = 1;

node_t* TreeCtor      (struct node_t* root);
//node_t* FindLow       (struct node_t* subtree);
node_t* CreateSubtree (struct node_t* parent, const char* word);

int GetWord           (struct node_t* parent, struct node_t* subtree);
int TreeDtor          (struct node_t* node);

#endif
