/* 
 * File:   table.h
 * Author: nanner
 *
 * Created on May 9, 2013, 6:59 PM
 */

#ifndef TABLE_H
#define	TABLE_H

#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include "player.h"
#include "card.h"
#include "event.h"

#define CONTINUE_GAME 1
#define STOP_GAME 0

typedef struct {
    /* Shared Variables */
    unsigned int gameState;
    event_t eventList[MAX_EVENTS];
    unsigned int numberOfEvents;
    
    unsigned int playersAwaited;
    player_t players[10];
    unsigned int numberOfPlayers;
    
    unsigned int currentTurn;
    unsigned int roundNumber;
    
    unsigned int dealerID;
    unsigned int firstPlayerID;
    
    unsigned int cardsDealt;
    card_t deck[DECK_CARDS];
    
    card_t tableCards[DECK_CARDS];
    unsigned int numberOfCardsOnTable;

    /* Sync Variables*/
    pthread_mutex_t dealingCardsLock;
    pthread_cond_t dealingCardsCond;

    pthread_mutex_t tableAccessLock;
    pthread_cond_t turnChangeCond;
    
    pthread_mutex_t playerWaitLock;
    pthread_cond_t playerWaitCond;
    
    pthread_mutex_t addingEventLock;
} table_t;

table_t* create_table(char* tableName, int tableSize);

table_t* attach_table(char* tableName, int tableSize);

bool init_sync_variables_in_table(table_t* table);

void destroy_table(table_t* table, char* tableName, int tableSize);

#endif	/* TABLE_H */

