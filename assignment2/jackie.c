//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//
// By zxxxxxx
//
// Written on 2018-10-25
//
// Zachary (day24-lab)

#include <stdio.h>
#include <assert.h>

#include "Game.h"
#include "Card.h"

#define STARTING_HAND_SIZE 7
#define NUM_PLAYERS 4

#define NUM_VALUES 16
#define NUM_COLORS 5
#define NUM_SUITS 5

static void testGame(void);
static void checkPlayerHand(Game game, int player, value values[], 
                                          color colors[], suit suits[]);
static void checkDeck(Game game, int deck_size, value values[], 
                                          color colors[], suit suits[]);
static void checkDiscardPile(Game game, int deck_size, value values[], 
                                          color colors[], suit suits[]);
static void checkGameState(Game game, int expectedPlayer, int expectedTurn,
    int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn);
static int cardIsInHand(Game game, int player, int alreadyMatched[],
                                            value v, color c, suit s);
static int cardMatchesComponents(Card card, value v, color c, suit s);

static void checkPlayer0Turn1(Game game);
static void checkPlayer1Turn1(Game game);
static void checkPlayer2Turn1(Game game);
static void checkPlayer3Turn1(Game game);
static void checkPlayer0Turn2(Game game);
static void checkPlayer1Turn2(Game game);

static void checkcurrstate(Game game, int player, int turn, int moves,
                 int currcolor, int previousPlayer, int topDiscardTurn);
static Card findCardInHand(Game game, int player, value values, 
                                        color colors, suit suits);
static int sameTopDiscard(Game game, Card card);
static void testGame2(void);
static void checkGameWinner(Game game);

int main() {
    printf("THE TEST START!\n");
    testGame();
    testGame2();
    return 0;
}

//given the initial deck
static void testGame(void) {
    int decksize = 36;
    
    value values[] = {
        B, DRAW_TWO, DRAW_TWO, DRAW_TWO, B, D, B, B, B,
        B, B, B, B, B, B, B, B, B,
        B, B, B, B, B, B, B, B, B,
        B, A, B, B, B, B, B, B, B
    };
    
    color colors[] = {
        RED, YELLOW, BLUE, RED, RED, RED, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
    };
    
    suit suits[] = {
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, SPADES,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, 
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
    };
    
    Game game = newGame(decksize, values, colors, suits);
    
    printf("Decksize is 36\n\n");
    assert(numCards(game) == 36);
    printf("Current player is 0\n\n");
    assert(currentPlayer(game) == 1);
    printf("Top of discard pile was played in turn -1\n\n");
    assert(getTopDiscardTurnNumber(game) == -1);
    printf("Current turn is 0\n\n");
    assert(currentTurn(game) == 0);
    printf("Current moves in turn is 0\n\n");
    assert(currentTurnMoves(game) == 0);
    printf("Number of turns is 1\n\n");
    assert(numTurns(game) == 1);
    printf("Player from previous turn is -1\n\n");
    assert(getPreviousTurnPlayer(game) == -1);
    
    checkDeck(game, decksize, values, colors, suits);
    printf("\n");
    checkDiscardPile(game, decksize, values, colors, suits);
    printf("\n");
    checkPlayerHand(game, 0, values, colors, suits);
    printf("\n");
    checkPlayerHand(game, 1, values, colors, suits);
    printf("\n");
    checkPlayerHand(game, 2, values, colors, suits);
    printf("\n");
    checkPlayerHand(game, 3, values, colors, suits);
    printf("\n");
    checkPlayer0Turn1(game);
    checkPlayer1Turn1(game);
    checkPlayer2Turn1(game);
    checkPlayer3Turn1(game);
    checkPlayer0Turn2(game);
    checkPlayer1Turn2(game);
    
    printf("GAME IS OVER! DESTROY THE GAME!\n");
    destroyGame(game);
}

static void checkDeck(Game game, int deck_size, value values[], 
                                        color colors[], suit suits[]){
    printf("31 cards of value B\n");
    assert(numOfValue(game, B) == 31);
    printf("31 cards of color BLUE.\n");
    assert(numOfColor(game, BLUE) == 31);
    printf("35 cards of type CLUBS.\n\n");
    assert(numOfSuit(game, CLUBS) == 35);
    int deckStart = NUM_PLAYERS * STARTING_HAND_SIZE + 1;
    int expected = deck_size - NUM_PLAYERS * STARTING_HAND_SIZE - 1;

    int i = 0;
    Card card = getDeckCard(game, i);
    while (card != NULL && i < expected){
        int j = deckStart + i;

        int v = values[j];
        int c = colors[j];
        int s = suits[j];

        printf("Checking card %d in deck is ", i);
        printf("\n");

        assert(cardMatchesComponents(card, v, c, s));

        i += 1;
        card = getDeckCard(game, i);
    }

    printf("Checking the deck has %d cards\n", expected);
    assert(i == expected);
}

static void checkDiscardPile(Game game, int deck_size, 
                        value values[], color colors[], suit suits[]){
    Card card;
    int firstCard = NUM_PLAYERS * STARTING_HAND_SIZE;

    card = getDiscardPileCard(game, 0);
    assert(cardMatchesComponents(card, values[firstCard], 
                            colors[firstCard], suits[firstCard]));

    printf("Checking there are no other cards in the discard pile\n");

    card = getDiscardPileCard(game, 1);
    assert(card == NULL);
}

static void checkGameState(Game game, int expectedPlayer, int expectedTurn,
        int expectedMoves, int expectedPreviousPlayer, int expectedTopDiscardTurn){

    assert(currentPlayer(game) == expectedPlayer);
    assert(currentTurn(game) == expectedTurn);
    assert(numTurns(game) == expectedTurn + 1);
    assert(currentTurnMoves(game) == expectedMoves);
    assert(getPreviousTurnPlayer(game) == expectedPreviousPlayer);
    assert(getTopDiscardTurnNumber(game) == expectedTopDiscardTurn);
}

static void checkPlayerHand(Game game, int player, value values[],
                                        color colors[], suit suits[]) {
    int playernum = player;

    int alreadyMatched[STARTING_HAND_SIZE];
    for (int i = 0; i < STARTING_HAND_SIZE; i++){
        alreadyMatched[i] = FALSE;
    }

    for(int k = 0; k < STARTING_HAND_SIZE; k++){

        int v = values[playernum];
        int c = colors[playernum];
        int s = suits [playernum];
        playernum = playernum + NUM_PLAYERS;

        printf("Checking card ");
        printf(" is in player %d's hand\n", player);

        assert(cardIsInHand(game, player, alreadyMatched, v, c, s));
    }

    Card card = getHandCard(game, player, STARTING_HAND_SIZE);
    assert( card == NULL );

    printf("Player %d passed\n ", player);

}

static int cardIsInHand(Game game, int player, int alreadyMatched[], 
                                    value v, color c, suit s) {
    int i = 0;
    Card card = getHandCard(game, player, i);
    while (card != NULL){
        if (cardMatchesComponents(card, v, c, s) && !alreadyMatched[i]){
            alreadyMatched[i] = TRUE;
            return TRUE;
        }

        i++;
        card = getHandCard(game, player, i);
    }

    return FALSE;
}


static int cardMatchesComponents(Card card, value v, color c, suit s){
    return cardValue(card) == v && cardColor(card) == c && cardSuit(card) == s;
}

static void checkPlayer0Turn1(Game game) {
    checkcurrstate(game, 0, 0, 0, BLUE, -1, -1);
    printf("Player 0 is skipped.\n\n");
}

static void checkPlayer1Turn1(Game game) {
    playerMove move;
    Card card;
    
    printf("Player 1 turn 1\n");
    printf("Checking player 1 has DRAW_TWO YELLOW CLUBS\n");
    card = findCardInHand(game, 1, DRAW_TWO, YELLOW, CLUBS);
    assert(card != NULL);

    printf("Player 1  plays this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);

    printf("Checking the game state\n");
    checkGameState(game, 1, 0, 0, -1, -1);

    printf("Playing the card\n");
    playMove(game, move);
    
    printf("The top discard changed.\n");
    sameTopDiscard(game, card);
    
    printf("Checking player 1 no longer has DRAW_TWO YELLOW CLUBS\n");
    card = findCardInHand(game, 1, DRAW_TWO, YELLOW, CLUBS);
    assert(card == NULL);
    
    printf("Checking the game state\n");
    checkGameState(game, 1, 0, 1,-1, 1);

    printf("Ending player 1's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
}

static void checkPlayer2Turn1(Game game) {
    playerMove move;
    Card card;
    
    printf("Player 2 turn 1\n");
    printf("Checking player 2 has DRAW_TWO BLUE CLUBS\n");
    card = findCardInHand(game, 2, DRAW_TWO, BLUE, CLUBS);
    assert(card != NULL);
    
    printf("Player 2  plays this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Playing the card\n");
    playMove(game, move);
    
    printf("Ending player 2's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
}

static void checkPlayer3Turn1(Game game) {
    playerMove move;
    Card card;
    
    printf("Player 3 turn 1\n");
    printf("Checking player 3 has DRAW_TWO BLUE CLUBS\n");
    card = findCardInHand(game, 3, DRAW_TWO, BLUE, CLUBS);
    assert(card != NULL);
    
    printf("Player 3 plays this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Playing the card\n");
    playMove(game, move);
    
    printf("Ending player 3's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
}

static void checkPlayer0Turn2(Game game) {
    playerMove move;
    Card card;
    
    printf("Player 0 turn 2\n");
    printf("Checking player 0 does not have DRAW_TWO BLUE CLUBS\n");
    card = findCardInHand(game, 0, DRAW_TWO, BLUE, CLUBS);
    assert(card == NULL);
    assert(getNumberOfTwoCardsAtTop(game) == 1);
    
    printf("Player 0 draws a card\n");
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Drawing the card\n");
    playMove(game, move);
    
    printf("Ending player 0's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    
    printf("Player 0 draws a card\n");
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Drawing the card\n");
    playMove(game, move);
    
    printf("Ending player 0's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
}

static void checkPlayer1Turn2(Game game) {
    playerMove move;
    Card card;
    
    printf("Player 1 turn 2\n");
    printf("Checking player 1 has B BLUE CLUBS\n");
    card = findCardInHand(game, 1, B, BLUE, CLUBS);
    assert(card != NULL);
    assert(getActiveDrawTwos(game) == 0);
    assert(handCardCount(game) == 6);
    
    printf("Player 1 plays this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Playing the card\n");
    playMove(game, move);
    assert(playerCardCount(game, 1) == 5);
    
    printf("Ending player 1's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
}

static void checkcurrstate(Game game, int player, int turn, int moves,
                int currcolor, int previousPlayer, int topDiscardTurn) {
    assert(currentTurn(game) == turn);
    assert(numTurns(game) == turn + 1);
    assert(currentPlayer(game) == player);
    assert(getCurrentColor(game) == currcolor);
    assert(getPreviousTurnPlayer(game) == previousPlayer);
    assert(getTopDiscardTurnNumber(game) == topDiscardTurn);
}

static Card findCardInHand(Game game, int player, value values, 
                                        color colors, suit suits) {
    int i = 0;
    Card card = getHandCard(game, player, i);
    while (card != NULL) {
        if (cardValue(card) == values && cardColor(card) == colors &&
              cardSuit(card) == suits) {
            return card;
        }
        i++;
        card = getHandCard(game, player, i);
    }
    return NULL;
}

static int sameTopDiscard(Game game, Card card) {
    Card discard = getDiscardPileCard (game, 0);
    if (card == discard) {
        return TRUE;
    }
    return FALSE;
}

static void testGame2(void) {
    int decksize = 30;
    
    value values[] = {
        B, D, D, DRAW_TWO, B, D, B, B, B,
        B, B, B, B, B, B, B, B, B,
        B, B, B, B, B, B, B, B, B,
        B, DRAW_TWO, B
    };
    
    color colors[] = {
        RED, YELLOW, BLUE, RED, RED, RED, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE
    };
    
    suit suits[] = {
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, SPADES,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, 
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
        CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS,
    };
    
    Game game = newGame(decksize, values, colors, suits);
    
    printf("Decksize is 30\n\n");
    assert(numCards(game) == 30);
    printf("Current player is 0\n\n");
    assert(currentPlayer(game) == 0);
    printf("Top of discard pile was played in turn -1\n\n");
    assert(getTopDiscardTurnNumber(game) == -1);
    printf("Current turn is 0\n\n");
    assert(currentTurn(game) == 0);
    printf("Current moves in turn is 0\n\n");
    assert(currentTurnMoves(game) == 0);
    printf("Number of turns is 1\n\n");
    assert(numTurns(game) == 1);
    printf("Player from previous turn is -1\n\n");
    assert(getPreviousTurnPlayer(game) == -1);
    checkGameWinner(game);
    printf("GAME IS OVER! DESTROY THE GAME!\n");
    destroyGame(game);
}

static void checkGameWinner(Game game) {
    playerMove move;
    Card card;
    printf("Player 0 turn 1\n");
    printf("Checking player 0 does not have DRAW_TWO BLUE CLUBS\n");
    card = findCardInHand(game, 0, DRAW_TWO, BLUE, CLUBS);
    assert(card == NULL);
    
    printf("Player 0 draws a card\n");
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    
    printf("Drawing the card\n");
    playMove(game, move);
    assert(handCard(game, 7) != NULL);
    
    printf("Ending player 0's turn\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    
    printf("Checking game winner is no winner\n");
    assert(gameWinner(game) == NO_WINNER);
    printf("Player0 score: %d\n", playerPoints(game, 0));
    printf("Player1 score: %d\n", playerPoints(game, 1));
    printf("Player2 score: %d\n", playerPoints(game, 2));
    printf("Player3 score: %d\n", playerPoints(game, 3));
}
