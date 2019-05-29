//
// Created by Lokilanka on 2019/5/25.
//

#ifndef C_BIG_WORK_LINKEDLIST_H
#define C_BIG_WORK_LINKEDLIST_H

#define NAMELENGTH 20

typedef struct info {
    int score;
    char name[20];
    struct info *next;
} PLAYERINFO;


PLAYERINFO *CreatenewLinkedlist();

PLAYERINFO *InsertNode(PLAYERINFO *phead, int Score, char *name);

PLAYERINFO *AddLastNode(PLAYERINFO *cur);
//PLAYERINFO *DeleteNode(PLAYERINFO *phead, PLAYERINFO *Node);



#endif //C_BIG_WORK_LINKEDLIST_H
