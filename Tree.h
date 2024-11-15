#ifndef TREE
#define TREE

struct node_t
{
    const char*    word;
    node_t*        left;
    node_t*        right;
};

static const char* TREE_FILE = "Tree.txt";

const int TREE_SIZE    = 10;
const int NUMBER_ELEMS = 1;

node_t* AkinatorCtor      (struct node_t* root);
node_t* CreateSubtree (struct node_t* parent, const char* word);
node_t* ReadTree      (struct node_t* parent, struct file_t* akin);
//node_t* FindLow       (struct node_t* subtree);
//
// int GetWord           (struct node_t* parent, struct node_t* subtree);

int AkinatorDtor          (struct node_t* node);

#endif
