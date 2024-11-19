#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

void Game(struct node_t* node, struct node_t* root)
{
    assert(node);

    int comand_for_play = 0;

    scanf("%d", &comand_for_play);

    if (comand_for_play == PLAY_AKINATOR)
    {
        printf("\nOKEY LETS PLAY!!!\n");
        GuessWord(node, root);
    }
    else if (comand_for_play == DONT_PLAY_AKINATOR)
    {
        printf("\nITS SAD :(\n");
    }
    else
    {
        printf("\nYOU WROTE WRONG COMMAND!!!\nrepeat!\n");
        Game(node, root);
    }
}
