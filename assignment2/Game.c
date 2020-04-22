// Individual work done by Queenie Ji z5191512
// Assignment2 Game.c

#include <stdlib.h>
#include <stdio.h>

#include "Card.h"
#include "Game.h"

typedef struct _state {
    int curplayer;//current player number
    int curturn;//current turn number
    Card lastcard;//last card in discards
    int num_move;//the number of move should be made in the action
    color curcolor;//current color
    int cards_drawn;//the number of cards drawn
    int top_discards_turn_num;//the turn number of top discard
    int discard_player;//player who put the final card
}*state;

struct player{
    int point;//current point of one player (sum of the value of the hand cards)
    int numHcards;//number of cards in hand
    struct node *handcards;
    struct _playerMove turnmove;//move made in current turn
};

struct node {
    Card card;
    struct node *next;
};

typedef struct _game {
    int deckSize;
    struct node *cards;//cards on the desk
    struct node *initial_deck;//Cards on the initial deck
    struct node *discards;//cards played on the desk
    int num_discards;//number of discards
    struct player players[4];
    struct _state *state;
    int num_active_twos; // the number of active DRAW_TWO on the top
}*Game;

static struct node *newnode (Card card);
static struct node *newc (int i, value values[], color colors[], 
                        suit suits[]);
static void player_initialise(Game game);
static void initialise_current_state (Game newGame);
static void initial_hand(Game newGame); 
Game newGame(int deckSize, value values[], color colors[], suit suits[]);
static void destroy_nodes(struct node *c);
void destroyGame(Game game);
int numCards(Game game);
int numOfSuit(Game game, suit suit);
int numOfColor(Game game, color color);
int numOfValue(Game game, value value);
int currentPlayer(Game game);
int currentTurn(Game game);
static int point_calculator(int player, Game game);
int playerPoints(Game game, int player);
Card topDiscard(Game game);
int numTurns(Game game);
int currentTurnMoves(Game game);
int getNumberOfTwoCardsAtTop(Game game);
int getCurrentColor(Game game);
static int discard_player(Game game);
int getPreviousTurnPlayer(Game game);
int getTopDiscardTurnNumber(Game game);
int getActiveDrawTwos(Game game);
int playerCardCount(Game game, int player);
int handCardCount(Game game);
Card handCard(Game game, int card);
static int check_same_cards(Card card1, Card card2);
static int check_hand_cards(Game game, playerMove move);
static int check_END_TURN(Game game, playerMove move);
static int check_PLAY_CARD(Game game, playerMove move);
int isValidMove(Game game, playerMove move);
static void check_deck_card (Game game);
static void update_PLAY_CARD (Game game, playerMove move);
static void update_hand_card(Game game, playerMove move);
static void update_DRAW_CARD (Game game, playerMove move);
void playMove(Game game, playerMove move);
int gameWinner(Game game);
static Card find_card(struct node *card, int n);
Card getDeckCard (Game game, int n);
Card getDiscardPileCard (Game game, int n);
Card getHandCard (Game game, int player, int n);

//A function to malloc for each node
static struct node *newnode (Card card) {
    struct node *new = malloc(sizeof(struct node));
    new->card = card;
    new->next = NULL;
    return new;
}

// Give each card a value, color, suit
static struct node *newc (int i, value values[], color colors[], 
        suit suits[]) {
    struct node *newdeck = NULL;
    while (i >= 0) {    
        struct node *n = newnode(newCard(values[i], colors[i], suits[i]));
        n->next = newdeck;
        newdeck = n;

        i--;
    } 
    return newdeck;
}

// Initialise the players' handcards
static void player_initialise(Game game) {
    struct player *players;
    int playerindex = 0;
    while (playerindex < 4) {
        game->players[playerindex].handcards = NULL;
        game->players[playerindex].numHcards = 7;
        game->players[playerindex].point = 0;
        game->players[playerindex].turnmove.action = END_TURN;
        game->players[playerindex].turnmove.nextColor = 0;
        game->players[playerindex].turnmove.card = NULL;
        playerindex++;
    }

}

// Initialise the current state
static void initialise_current_state (Game newGame) {
    newGame->state->curplayer = 0;
    newGame->state->curturn = 0;
    newGame->state->lastcard = NULL;
    newGame->state->num_move = 0;
    newGame->state->curcolor = 0;
    newGame->state->top_discards_turn_num = -1;
    newGame->state->discard_player = -1;
}

// Initialise the player hand
static void initial_hand(Game newGame) {
    int index_counter = 0;
    int player = 0;//player index
    while (index_counter < 28) {
        player = index_counter % 4;
        struct node *temp = newGame->cards;
        newGame->cards = newGame->cards->next;
        temp->next = newGame->players[player].handcards;
        newGame->players[player].handcards = temp;
        index_counter++;
    }
}

// Create a new game engine.
Game newGame(int deckSize, value values[], color colors[], suit suits[]) {
    Game newGame = malloc(sizeof(struct _game));
    newGame->state = malloc(sizeof(struct _state));
    newGame->deckSize = deckSize;
    newGame->num_discards = 0;
    newGame->discards = NULL;
    newGame->state->cards_drawn = 0;
    newGame->num_active_twos = 0;

    initialise_current_state (newGame);
    //give each card a value, suit, color
    int i = deckSize - 1;
    newGame->initial_deck = newc (i, values, colors, suits);
    newGame->cards = newc (i, values, colors, suits);    
    player_initialise(newGame);
    //each players have 7 cards at the begining of the game
    initial_hand(newGame);
    //update the initial state
    newGame->discards = newGame->cards;
    newGame->cards = newGame->cards->next;
    newGame->discards->next = NULL;
    newGame->state->lastcard = newGame->discards->card;
    newGame->num_discards = 1;
    //special cases: firt card is A or DRAW_TWO, D does not matter
    //because it will not declare a color
    if (cardValue(newGame->state->lastcard) == A) {
        newGame->state->curplayer++;
    } else if (cardValue(newGame->state->lastcard) == DRAW_TWO) {
        newGame->num_active_twos = 1;
    }
    return newGame;
}

// Destroy a list of nodes. Recursion is used to detroy every node.
static void destroy_nodes(struct node *c) {
    if (c != NULL) {
        destroy_nodes(c->next);
        destroyCard(c->card);
        free(c);
    }
}

// Destroy an existing game.
void destroyGame(Game game) {
    destroy_nodes(game->initial_deck);
    destroy_nodes(game->cards);
    destroy_nodes(game->discards);
    destroy_nodes(game->players[0].handcards);
    destroy_nodes(game->players[1].handcards);
    destroy_nodes(game->players[2].handcards);
    destroy_nodes(game->players[3].handcards);
    free(game->state);    
    free(game);

}

// Get the number of cards that were in the initial deck.
int numCards(Game game) {
    return game->deckSize;
}

// Get the number of cards in the initial deck of a particular suit.
int numOfSuit(Game game, suit suit) {
    int counter = 0;
    int numdeck = game->deckSize;     
    struct node *node = game->initial_deck;
    while (node != NULL) {
        if (cardSuit(node->card) == suit) {
            counter++;
        }
        node = node->next;
    }
    return counter;
}

// Get the number of cards in the initial deck of a particular color.
int numOfColor(Game game, color color) {
    int i = 0;
    int counter = 0;
    int numdeck = game->deckSize; 
    struct node *node = game->initial_deck;
    while (i < numdeck && node != NULL) {
        if (cardColor(node->card) == color) {
            counter++;
        }
        node = node->next;
        i++;
    }
    return counter;
}

// Get the number of cards in the initial deck of a particular value.
int numOfValue(Game game, value value) {
    int i = 0;
    int counter = 0;
    int numdeck = game->deckSize;
    struct node *node = game->initial_deck;
    while (i < numdeck && node != NULL) {
        if (cardValue(node->card) == value) {
            counter++;
        }
        node = node->next;
        i++;
    }
    return counter;
}

// Get the number of the player whose turn it is.
int currentPlayer(Game game) {
    return game->state->curplayer;
}

// Get the current turn number.
int currentTurn(Game game) {
    return game->state->curturn;
}

// calculate the current points of the player
static int point_calculator(int player, Game game) {
    int sum = 0;
    int i = 0;
    struct player _player = game->players[player];
    while (i < _player.numHcards) {
        sum = sum + cardValue(_player.handcards->card);
        _player.handcards = _player.handcards->next;
        i++;
    }
    return sum;
}

// Get the number of points for a given player.
int playerPoints(Game game, int player) {
    int playerpoints = point_calculator(player, game);
    return playerpoints;

}

// Get the card that is on the top of the discard pile.
Card topDiscard(Game game) {
    return game->state->lastcard;
}

// This function returns the number of turns that have occurred in the
// game so far including the current turn.
int numTurns(Game game) {
    int numturns = game->state->curturn + 1;
    return numturns;
}

// Get the number of moves (actions) that happened on the current turn.
int currentTurnMoves(Game game) {
    return game->state->num_move;
}

// Get the number of consecutive cards with value "2" at the top of the 
// discard pile.
int getNumberOfTwoCardsAtTop(Game game) {
    int numoftwo = 0;
    struct node *curr = game->discards;
    while (curr != NULL && cardValue(curr->card) == DRAW_TWO) {
        curr = curr->next;
        numoftwo ++;
    }
    return numoftwo;
}

// If the last player played a card with value "D" and declared a color, 
// the following function returns that declared color as the current color. 
// For all other cases, the function returns the color of the card at 
// the top of the discard pile. 
int getCurrentColor(Game game) {
    int curplayer = currentPlayer(game);
    int prevp = discard_player(game);
    if (prevp == -1) {
        game->state->curcolor = cardColor(game->state->lastcard);
    } else if (cardValue(game->state->lastcard) == D) {
        game->state->curcolor = game->players[prevp].turnmove.nextColor;
    } else {
        game->state->curcolor = cardColor(game->state->lastcard);
    }
    return game->state->curcolor;
}

// Find the player number of the top discard
static int discard_player(Game game) {
    return game->state->discard_player;
}

// The function returns the player who played the previous turn.
int getPreviousTurnPlayer(Game game) {
    int value = game->state->curturn;//return value
    if (game->state->curturn == 0) {
        return -1;
    } else if (cardValue(game->state->lastcard) == A && 
            (discard_player(game) + 2) % 4 == currentPlayer(game) % 4) {
        value = (currentPlayer(game) - 2 + 4) % 4;
    } else {
        value = (currentPlayer(game) - 1 + 4) % 4;
    }
    return value;
}

// Get the turn number that played the card that is on the top of 
// the discard pile.
int getTopDiscardTurnNumber(Game game) {
    return game->state->top_discards_turn_num;
}

// Get the number of "active" cards with value "2" at the top of the 
// discard pile. 
int getActiveDrawTwos(Game game) {
    return game->num_active_twos;
}

// Get the number of cards in a given player's hand.
int playerCardCount(Game game, int player) {
    int count = 0;
    struct node *curcards = game->players[player].handcards;
    while (curcards != NULL) {
        count++;
        curcards = curcards->next;
    }
    game->players[player].numHcards = count;
    return count;
}

// Get the number of cards in the current player's hand.
int handCardCount(Game game) {
    int curplayer = currentPlayer(game);
    int count = 0;
    struct node *curcards = game->players[curplayer].handcards;
    while (curcards != NULL) {
        count++;
        curcards = curcards->next;
    }
    game->players[curplayer].numHcards = count;
    return count;

}

// View a card from the current player's own hand.
Card handCard(Game game, int card) {
    int curplayer = currentPlayer(game);
    if (card > game->players[curplayer].numHcards || card < 0) {
        return NULL;
    }
    //find the handcards of current player and use a loop to get 
    //the exact card,then return card.
    int i = 0;
    struct node *handcard = game->players[curplayer].handcards;
    while (i < card) {
        handcard = handcard->next;
        i++;
    }
    if (handcard == NULL) {
        return NULL;
    }
    return handcard->card;
}

// Check whether the two cards are exactly same. If they are the same,
// return 1, if not, return 0.
static int check_same_cards(Card card1, Card card2) {
    if ((cardValue(card1) == cardValue(card2)) && 
            (cardColor(card1) == cardColor(card2)) && 
            (cardSuit(card1) == cardSuit(card2))) {
        return TRUE;
    }
    return FALSE;

}

// Check whether the player have the card he want to play. If the player
// have the card, return 1, if not, return 0.
static int check_hand_cards(Game game, playerMove move) {
    int curplayer = currentPlayer(game);
    struct node *cardtoplay = game->players[curplayer].handcards;
    while (cardtoplay != NULL) {
        if (check_same_cards(cardtoplay->card,move.card) == 1) {
            return TRUE;
        }    
        cardtoplay = cardtoplay->next;
    }
    return FALSE;
}

// Check when the action is END_TURN, the player should either draw enough
// card or play right card.
static int check_END_TURN(Game game, playerMove move) {
    int valid = FALSE;
    Card curcard = game->state->lastcard;
    int curplayer = currentPlayer(game);
    if (cardValue(curcard) == DRAW_TWO) {
        if (game->state->num_move == 2 * getActiveDrawTwos(game)) {
            valid = TRUE;
        } else if (game->players[curplayer].turnmove.action == PLAY_CARD)
        {
            valid = TRUE;
        }    
    } else if (game->players[curplayer].turnmove.action != END_TURN) {
        valid = TRUE;
    }
    return valid;
}
// Check when the action is PLAY_CARD. The player is not allowed to play
// a card after DRAW_CARD, and the card should be in his hand and match 
// the components of the top card in the top discard pile.
static int check_PLAY_CARD(Game game, playerMove move) {
    int valid = FALSE;
    Card curcard = topDiscard(game);
    int curplayer = currentPlayer(game);
    if (cardValue(curcard) == DRAW_TWO && getActiveDrawTwos(game) != 0)
    {//special card DRAW_TWO
        if (cardValue(move.card) == DRAW_TWO) {
            valid = TRUE;
        } 
        //special card D
    } else if (cardValue(curcard) == D) {
        if (cardColor(move.card) == game->state->curcolor ||
                (cardValue(move.card) == ZERO) || (cardValue(move.card) 
                    == cardValue(curcard)) || (cardSuit(move.card) 
                    == cardSuit(curcard))) {
            valid = TRUE;
        }
        //Non-special card
    } else if ((cardValue(move.card) == ZERO) || (cardValue(move.card) 
                == cardValue(curcard)) || (cardColor(move.card)
                == cardColor(curcard)) || (cardSuit(move.card) 
                == cardSuit(curcard))) {
        valid = TRUE;
    }    
    return valid;
}

// Check if a given move is valid. Go through all three posible actions
// by using helpful functions
int isValidMove(Game game, playerMove move) {
    int valid = FALSE;
    Card curcard = game->state->lastcard;
    int curplayer = currentPlayer(game);
    if (move.action == END_TURN && game->state->num_move != 0) {
        valid = check_END_TURN(game, move);
        //when the action is play card
    } else if (move.action == PLAY_CARD && check_hand_cards(game, move) 
            == 1 && game->players[curplayer].turnmove.action 
            == END_TURN)
    {
        valid = check_PLAY_CARD(game, move);
        // when the action is draw cards
    } else if (move.action == DRAW_CARD) {
        if (game->players[curplayer].turnmove.action == END_TURN) {
            valid = TRUE;
        } else if (cardValue(curcard) == DRAW_TWO && 
                getActiveDrawTwos(game) != 0) {
            if (game->state->num_move < 2 * getActiveDrawTwos(game)) {
                valid = TRUE;
            }
        }
    }
    return valid;
}

//Check whether there is a card on the deck
static void check_deck_card (Game game) {
    // Check there is no card on the deck card pile
    if (game->cards == NULL) {
        struct node *new = NULL;
        struct node *cur = game->discards->next;
        while (cur != NULL) {
            struct node *temp = cur;
            cur = cur->next;
            temp->next = new;
            new = temp;
        }
        game->cards = new;
        game->discards->next = NULL;
        game->num_discards = 1;    
    }    
}

// Update when the move action is PLAY_CARD
static void update_PLAY_CARD (Game game, playerMove move) {
    int curplayer = currentPlayer(game);
    game->state->num_move ++;
    game->num_discards ++;
    game->players[curplayer].numHcards --;
    game->players[curplayer].turnmove.action = PLAY_CARD;
    game->players[curplayer].turnmove.card = move.card;
    game->players[curplayer].turnmove.nextColor = move.nextColor;
    game->state->top_discards_turn_num = game->state->curturn;
    update_hand_card(game, move);
    game->state->lastcard = move.card;
    game->state->curcolor = getCurrentColor(game);
    game->state->discard_player = currentPlayer(game);
    if (cardValue(move.card) == DRAW_TWO) {
        game->num_active_twos ++;
    } else {
        game->num_active_twos = 0;
    }
}

// Update hand card after playing a card
static void update_hand_card(Game game, playerMove move) {
    int curplayer = currentPlayer(game);
    struct node *playedcard = game->players[curplayer].handcards;
    struct node *prev = NULL;
    while (playedcard != NULL && playedcard->card !=
            move.card) {//find the card played by the player in player hand
        prev = playedcard;
        playedcard = playedcard->next;
    }
    if (playedcard != NULL) {
        if (prev == NULL) {
            game->players[curplayer].handcards = 
                game->players[curplayer].handcards->next;
            playedcard->next = game->discards;
            game->discards = playedcard;
        } else {
            prev->next = playedcard->next;
            playedcard->next = game->discards;
            game->discards = playedcard; 
        }
    }
}

// Update after the DRAW_CARD action
static void update_DRAW_CARD (Game game, playerMove move) {
    int curplayer = currentPlayer(game);
    game->state->num_move ++;
    game->state->cards_drawn += 1;
    game->players[curplayer].turnmove.action = DRAW_CARD;
    game->players[curplayer].turnmove.card = NULL;
    struct node *temp = game->cards;
    game->cards  = temp->next;
    temp->next = game->players[curplayer].handcards;
    game->players[curplayer].handcards = temp;
    game->players[curplayer].numHcards ++;
}

// Play the given action for the current player
void playMove(Game game, playerMove move) {
    //go through all the things in the state structure
    int curplayer = currentPlayer(game);
    Card discard = getDiscardPileCard(game, 0);
    if (move.action == PLAY_CARD) {
        update_PLAY_CARD(game, move);
    } else if (move.action == DRAW_CARD) {
        update_DRAW_CARD(game, move);
    }
    if (move.action == END_TURN) {
        game->state->curturn ++;
        if (game->players[curplayer].turnmove.action == PLAY_CARD) {
            if (cardValue(move.card) == A) {
                game->state->curplayer = (currentPlayer(game) + 2) % 4;
            } else {
                game->state->curplayer = (currentPlayer(game) + 1) % 4;
            }
        } else if (cardValue(discard) == DRAW_TWO && 
                game->state->num_move == 2 * game->num_active_twos) {
            game->num_active_twos = 0;
            game->state->curplayer = (currentPlayer(game) + 1) % 4;
        } else {
            game->state->curplayer = (currentPlayer(game) + 1) % 4;
        }
        game->state->num_move = 0;
        game->players[curplayer].turnmove.action = END_TURN;
    }
    // check whether deck pile should be updated
    check_deck_card (game);
}

// Check the game winner
int gameWinner(Game game) {
    int player = 0;//player number 
    if (getDeckCard(game, 0) == NULL && game->num_discards == 1) {
        return NO_WINNER;
    } else {
        while ((player < 4) && (game->players[player].numHcards != 0)) {
            player++;
        }
        if (player == 4) {
            return NOT_FINISHED;
        } else {
            return player;
        }
    }
}

// Find a specific card in a card pile
static Card find_card(struct node *card, int n) {
    int i = 0;
    struct node *cur = card;
    while (i < n && cur->next != NULL) {
        cur = cur->next;
        i++;
    }
    if (cur == NULL) {
        return NULL;
    }
    return cur->card;
}

// Get nth card from the deck
Card getDeckCard (Game game, int n) {
    int i = 0;
    Card card = find_card(game->cards, n);
    return card;
}

// Get nth card from the discard pile
Card getDiscardPileCard (Game game, int n) {
    if (n >= (game->num_discards)) {
        return NULL;
    }
    if (n == 0) {
        return game->discards->card;
    } else {
        Card card = find_card(game->discards, n);
        return card;
    }
    return NULL;
}

// Get nth card from the hand of a player.
Card getHandCard (Game game, int player, int n) {
    int i = 0;
    int numhand = playerCardCount(game, player);
    if (n >= numhand) {
        return NULL;
    } 
    if (game->players[player].handcards == NULL) {
        return NULL;
    } else {
        Card card = find_card(game->players[player].handcards, n);
        return card;
    } 
}

