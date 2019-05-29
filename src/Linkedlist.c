//
// Created by Lokilanka on 2019/5/25.
//

#include <Linkedlist.h>
#include <stdlib.h>
#include <string.h>


PLAYERINFO *CreatenewLinkedlist() {
    PLAYERINFO *phead = (PLAYERINFO *) malloc(sizeof(PLAYERINFO));
    phead->next = (PLAYERINFO *) malloc(sizeof(PLAYERINFO));
    phead->score = 99999;
    phead->next->score = -1;
    strcpy(phead->next->name, "");
    phead->next->next = NULL;
    return phead;
}

PLAYERINFO *InsertNode(PLAYERINFO *phead, int Score, char *name) {
    PLAYERINFO *cur, *pre, *tmp;
    tmp = (PLAYERINFO *) malloc(sizeof(PLAYERINFO));
    tmp->score = Score;
    strcpy(tmp->name, name);

    cur = phead->next;
    pre = phead;
    while (cur) {
        if (Score >= cur->score) {
            tmp->next = cur;
            pre->next = tmp;
            break;
        }
        pre = pre->next;
        cur = cur->next;
    }
    if (cur == NULL) {
        pre->next = tmp;
        tmp->next = NULL;
    }
    return phead;
}

PLAYERINFO *AddLastNode(PLAYERINFO *cur){
    cur->next = (PLAYERINFO *)malloc(sizeof(PLAYERINFO));
    strcpy(cur->next->name,"");
    cur->next->score = -1;
    cur->next->next = NULL;
    return cur->next;
}

//PLAYERINFO *DeleteNode(PLAYERINFO *phead, PLAYERINFO *Node){
//    PLAYERINFO *tmp = phead->next;
//    while ()
//
//}

