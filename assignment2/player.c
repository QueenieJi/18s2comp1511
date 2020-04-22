// Individual work done by Queenie Ji z5191512
// Assignment2 player.c

#include "player.h"
#include "Game.h"
#include "Card.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
    Card card;
    struct node *next;
};

static int valid_card(Game game, Card discard, Card handcard);
static Card zero(Game game);
static Card find_biggest_valid_card(Game game);
static struct node *validcard(Game game);
static int numOfTwoInHand(Game game);
static Card find_same_value(Game game);
static color most_color(Game game, playerMove move);

// The main strategy is that try to end turn and if it is not valid, try
// to play a card of a certain value which the value repeated twice or 
// more to keep the variety of hand cards. Then, if there is no card is 
// valid to this move, than try to find the biggest possible card in hand
// to reduce the points. And double check whether 0 card is possible to 
// play, otherwise draw a card.
playerMove decideMove(Game game) {
    Card discard = topDiscard(game);
    playerMove move;
    move.action = END_TURN;
    if (isValidMove(game, move) == FALSE) {
        if (validcard(game) != NULL) {
            move.action = PLAY_CARD;
            if (find_same_value(game) != NULL) {
                move.card = find_same_value(game);
                if (cardValue(move.card) == D) {
                    move.nextColor = most_color(game, move);
                }
            } if (isValidMove(game, move) == FALSE) {
                move.action = PLAY_CARD;
                move.card = find_biggest_valid_card(game);
                if (cardValue(move.card) == D) {
                    move.nextColor = most_color(game, move);
                }
            }
            if (isValidMove(game, move) == TRUE) {
                return move;
            }
        } else if (zero(game) != NULL) {
            move.action = PLAY_CARD;
            move.card = zero(game);
        }
        if (isValidMove(game, move) == FALSE) {
            move.action = DRAW_CARD;
        }
    }
    return move;
}

// Find the color has the highest frequency in the player hand.
static color most_color(Game game, playerMove move) {
    int color[5] = {0};
    int n = 0;
    while (n < handCardCount(game)) {
        Card cur = handCard(game, n);
        int i = 0;
        while (cardValue(cur) != i && i < 5) {
            i++;
        }
        if (cardColor(cur) == i) {
            color[i]++;
        }
        n++;
    }
    int max;
    if (cardColor(move.card) != RED) {
        max = color[0];
    } else {
        max = color[1];
    }
    n = 0;
    while (n < 5) {
        if (color[n] > max) {
            if (n != cardColor(move.card)) {
                max = color[n];
            }
        }
        n++;
    }
    return max;
}

// Find a possible card to play. If there is no more than one DRAW_TWO in
// hand, never play it until someone plays it or it is the last card.
static struct node *validcard(Game game) {
    struct node *valid = NULL;
    Card discard = topDiscard(game);
    //Only play the draw two when other player plays it or has more than
    //one DRAW_TWO on his hand
    if (getActiveDrawTwos(game) != 0) {
        int n = 0;
        while (n < handCardCount(game)) {
            if (cardValue(handCard(game, n)) == DRAW_TWO) {
                struct node *cur = malloc(sizeof(struct node));
                cur->card = handCard(game, n);
                cur->next = valid;
                valid = cur;
            }
            n++;
        }
    //If the draw_two is the last card on the player's hand, then play it
    } else if (numOfTwoInHand(game) > 2 || numOfTwoInHand(game) == 
                handCardCount(game)) {
        int i = 0;
        while (i < handCardCount(game)) {
            if (valid_card(game, discard, handCard(game, i)) == 1) {
                struct node *cur = malloc(sizeof(struct node));
                cur->card = handCard(game, i);
                cur->next = valid;
                valid = cur;
            }
            i++;
        }
    } else {// put any valid card in the valid card list
        int i = 0;
        while (i < handCardCount(game)) {
            if (valid_card(game, discard, handCard(game, i)) == 1 &&
                cardValue(handCard(game, i)) != DRAW_TWO) {
                struct node *cur = malloc(sizeof(struct node));
                cur->card = handCard(game, i);
                cur->next = valid;
                valid = cur;
            }
            i++;
        }
    }
    return valid;
}

// Find a zero card
static Card zero(Game game) {
    int n = 0;
    while (n < handCardCount(game)) {
        Card cur = handCard(game, n);
        if (cardValue(cur) == ZERO) {
            return cur;
        };
        n++;
    }
    return NULL;
};

// Find whether the card has any component that matches the top discard
static int valid_card(Game game, Card discard, Card handcard) {
    int valid = 0;
    if (cardValue(handcard) == cardValue(discard) || 
        cardColor(handcard) == cardColor(discard) || 
        cardSuit(handcard) == cardSuit(discard)) {
        valid = 1;
    }
    return valid;
}

// Always try to play the biggest card to reduce score
static Card find_biggest_valid_card(Game game) {
    int maxvalue = 0;
    struct node *find = validcard(game);
    while (find != NULL) {
        if (maxvalue < cardValue(find->card)) {
            maxvalue = cardValue(find->card);
        }
        find = find->next;
    }
    find = validcard(game);
    while (cardValue(find->card) != maxvalue) {
        find = find->next;
    }
    return find->card;
}

// Go through all the cards to find how many DRAW_TWO in hand
static int numOfTwoInHand(Game game) {
    int n = 0;
    int counter = 0;
    while (n < handCardCount(game)) {
        Card cur = handCard(game, n);
        if (cardValue(cur) == DRAW_TWO) {
            counter++;
        };
        n++;
    }
    return counter;
}

// Find the card with same value and try to play it.
static Card find_same_value(Game game) {
    Card discard = topDiscard(game);
    int card[16] = {0};
    int n = 0;
    while (n < handCardCount(game)) {
        Card cur = handCard(game, n);
        int i = 1;
        while (cardValue(cur) != i && i < 15) {
            i++;
        }
        if (cardValue(cur) == i) {
            card[i]++;
        }
        if (card[i] > 0) {
            if (valid_card(game, discard, cur) == 1) {
                return cur;
            }
        }
        n++;
    }
    return NULL;
}
