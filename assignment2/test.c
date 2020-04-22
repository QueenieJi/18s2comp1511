#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Game.h"
#include "Card.h"

#define START_HAND_SIZE 7
#define NUM_PLAYERS 4

//functions for test 1
static void test1_newgame(void);
static void check_newGame(Game game);
static void check_cardpiles(Game game, int decksize, value values[], 
                            color colors[], suit suits[]);
static void check_players(Game game, value values[], color colors[], 
                            suit suits[]);
static void check_deck(Game game, int decksize, value values[],
                        color colors[], suit suits[]);
static void check_discard(Game game, int decksize, value values[],
                            color colors[], suit suits[]); 
static void playertest(Game game, int player, value values[], 
                           color colors[], suit suits[]);
static void check_cardInHand(Game game, int player, value values[],
                             color colors[], suit suits[]);
static void check_initial_decksuit(Game game);
static void check_initial_deckcolor(Game game);
static void check_initial_deckvalue(Game game);
static bool samecard(Card card, value v, color c, suit s);

//functions for test 2
static void test2_action(void);
static void testPlayer0Turn1(Game game);
static void testPlayer1Turn1(Game game);
static void testPlayer2Turn1(Game game);
static void testPlayer3Turn1(Game game);
static void testPlayer0Turn2(Game game);
static void testPlayer1Turn2(Game game);
static void testplayer2Turn2(Game game);
static void testplayer3Turn2(Game game);

static void checkcurrstate(Game game, int player, int turn, int moves,
                 int currcolor, int previousPlayer, int topDiscardTurn);
static Card findCardInHand(Game game, int player, value values, 
                                        color colors, suit suits);
static bool sameTopDiscard(Game game, Card card);

//funtions for test 3 
static void test3_extremeCases(void);
static void player0turn(Game game);
static void endGame(Game game);

//functions fot test 4
static void test4_draw_twos(void);
static void gameBegin(Game game);

static void player0Turn1(Game game);
static void player1Turn1(Game game);
static void player2Turn1(Game game);
static void player3Turn1(Game game);

static void player0Turn2(Game game);
static void player1Turn2(Game game);
static void player2Turn2(Game game);
static void player3Turn2(Game game);

static void player0Turn3(Game game);
static void player1Turn3(Game game);
static void player2Turn3(Game game);
static void player3Turn3(Game game);

static void player0Turn4(Game game);
static void player1Turn4(Game game);
static void player2Turn4(Game game);
static void player3Turn4(Game game);

static void player0Turn5(Game game);
static void player1Turn5(Game game);
static void player2Turn5(Game game);
static void checkNewPiles(Game game);
static void player3Turn5(Game game);

static void player0Turn6(Game game);
static void player1Turn6(Game game);
static void player2Turn6(Game game);
static void player3Turn6(Game game);

static void player0Turn7(Game game);
static void player1Turn7(Game game);

static void gameEnd(Game game);

int main () {
    //Test 1: test whether the new game is set up correctly
    printf("Test 1 Starts!\n\n");
    test1_newgame();
    printf("Test 1 passed! Awesome!!!\n");
    
    //Test 2: check the move and turn of the players and some actions
    //check some functions not covered in test one
    printf("\n=====================================================\n");
    printf("Test 2 Starts!\n\n");
    test2_action();
    printf("Test 2 passed! Awesome!!!\n");
    
    //Test 3: An extreme case 
    //Test the the discards pile can be converted to draw pile
    //test the game can end properly
    printf("\n=====================================================\n");
    printf("Test 3 Starts!\n\n");
    test3_extremeCases();
    printf("Test 3 passed! Awesome!!!\n");
    
    //Test4: check some cases with the special DRAW_TWO
    //It is a whole game
    printf("\n=====================================================\n");
    printf("Test 4 Starts!\n\n");
    test4_draw_twos();
    printf("Test 4 passed! Awesome!!!\n");
    printf("---------YOU PASSED ALL THE TESTS!!  AWESOME!!!--------\n");
    return 0;
}

//Following 9 functions for test 1
//Test1: checking whether the new game is set up properly
static void test1_newgame(void) {
    int decksize = 30;
    value values[] = {
        ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE,
        SIX, SEVEN, EIGHT, NINE, A, B, C, D, E,
        F, F, D, C, B, A, NINE, EIGHT, SEVEN, 
        SIX, FIVE, FOUR, THREE, DRAW_TWO, ONE
    };
    
    color colors[] = {
        RED, GREEN, BLUE, YELLOW, PURPLE, BLUE,
        GREEN, BLUE, BLUE, RED, YELLOW, PURPLE,
        YELLOW, PURPLE, BLUE, GREEN, GREEN, YELLOW,
        RED, RED, BLUE, PURPLE, GREEN, PURPLE,
        YELLOW, PURPLE, GREEN, BLUE, RED, GREEN
    };
    
    suit suits[] = {
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,CLUBS,
        DIAMONDS, SPADES, QUESTIONS, HEARTS, CLUBS, SPADES,
        HEARTS, SPADES, QUESTIONS, SPADES, CLUBS, HEARTS,
        DIAMONDS, HEARTS, CLUBS, QUESTIONS, HEARTS, SPADES,
        SPADES, QUESTIONS, CLUBS, DIAMONDS, DIAMONDS, CLUBS
    };  
    Game newgame = newGame(decksize, values, colors, suits);
    check_newGame(newgame);  
    check_cardpiles(newgame, decksize, values, colors, suits);
    check_players(newgame, values, colors, suits);
    printf("Destory the game.");
    destroyGame(newgame);
}

static void check_newGame(Game game) {
    printf("Checking if the deck size is 30\n");
    assert(numCards(game) == 30);
    
    printf("Checking the cards in the initial deck.\n");
    check_initial_decksuit(game);
    check_initial_deckcolor(game);
    check_initial_deckvalue(game);
    
    printf("Checking if the current player is 0\n");
    assert(currentPlayer(game) == 0);
    
    printf("Checking if the current turn is 0\n");
    assert(currentTurn(game) == 0);
    
    printf("Checking if number of turns is 1\n");
    assert(numTurns(game) == 1);
    
    printf("Checking if number of moves in current turn is 0\n");
    assert(currentTurnMoves(game) == 0);
    
    printf("Checking if the player number of previous turn is -1\n\n");
    assert(getPreviousTurnPlayer(game) == -1);
}

//check the initial deck pile and the discard pile
static void check_cardpiles(Game game, int decksize, value values[], 
                            color colors[], suit suits[]) {
    printf("Checking if the turn number is -1\n");
    assert(getTopDiscardTurnNumber(game) == -1); 
    
    printf("Checking there is only one card in the discard pile\n\n");
    assert(getDiscardPileCard(game, 1) == NULL); 
    
    printf("Checking the pick up pile is correct\n"); 
    check_deck(game, decksize, values, colors, suits); 
    printf("The pile passed the test!\n\n");    
    
    printf("Checking the initial discard pile is correct\n"); 
    check_discard(game, decksize, values, colors, suits); 
    printf("The pile passed the test!\n\n");                
}

static void check_players(Game game, value values[], color colors[], 
                            suit suits[]) {
    int numplayer = 0;
    while (numplayer < NUM_PLAYERS) {
        printf("***************************************************\n");
        printf("\nChecking player %d \n", numplayer);
        playertest(game, numplayer, values, colors, suits);
        printf("Player %d passed!\n", numplayer);
        numplayer++;
    } 
    printf("All the players passed!\n\n");                         
}

//check the deck before the game starts
static void check_deck(Game game, int decksize, value values[],
                        color colors[], suit suits[]) {
    //Number of card handed out or put in the discard pile
    int j = START_HAND_SIZE * NUM_PLAYERS + 1;
    //Total number of cards in the initial deck
    int num = decksize - j;
    Card card = getDeckCard(game,0);
    int i = 0;
    while (card != NULL && i < num) {
        int v = values[i + j];
        int c = colors[i + j];
        int s = suits[i + j];
        assert(samecard(card, v, c, s) == 1);
        printf("The %d card is correct!\n", i);
        i++;
        card = getDeckCard(game, i);
    }
    assert(i == num);
    printf("The number of cards in the initial deck is correct!\n");                  
}

//check the initial discard pile
static void check_discard(Game game, int decksize, value values[], 
                            color colors[], suit suits[]) {
    Card card = getDiscardPileCard(game, 0);
    int firstCard = NUM_PLAYERS * START_HAND_SIZE;
    int v = values[firstCard];
    int c = colors[firstCard];
    int s = suits[firstCard];
    assert(samecard(card, v, c, s) == 1);                            
    printf("The top of discard pile is correct!\n");   
}
    
//check the cards in the players are correct 
static void playertest(Game game, int player, value values[], 
                        color colors[], suit suits[]) {
    printf("The number of cards in current player's hand is 7.\n");
    assert(handCardCount(game) == 7);    
    printf("Checking cards in players hand\n"); 
    check_cardInHand(game, player, values, colors, suits);
    printf("Count initial points of player %d\n", player);
    assert(playerPoints(game, 0) == 55);
    assert(playerPoints(game, 1) == 55);
    assert(playerPoints(game, 2) == 56);
    assert(playerPoints(game, 3) == 57);
    printf("Player %d got the 7 cards!\n", player);                  
}   

//check each player has 7 correct cards and only has senven cards
static void check_cardInHand(Game game, int player, value values[],
                              color colors[], suit suits[]) {
    int i = 0;//hand cards
    int j = 0 + player;//cards in deck
    Card card = getHandCard(game, player, 0);
    while (card != NULL && i < START_HAND_SIZE) {
        int v = values[j];
        int c = colors[j];
        int s = suits[j];
        card = getHandCard(game, player,6 - i);
        printf("The %d card in player %d hand is correct!\n", i, player);
        assert(samecard(card, v, c, s) == 1);                            
        i++;
        j += 4;
    }
    card = getHandCard(game, player, START_HAND_SIZE);
    assert(card == NULL );
}

static void check_initial_decksuit(Game game) {
    printf("Check the number of card in each suit.\n\n");
    
    printf("6 cards of type HEARTS.\n");
    assert(numOfSuit(game, HEARTS) == 6);
    
    printf("5 cards of type DIAMONDS\n");
    assert(numOfSuit(game, DIAMONDS) == 5);
    
    printf("7 cards of type SPADES.\n");
    assert(numOfSuit(game, SPADES) == 7);
    
    printf("5 cards of type QUESTIONS.\n");
    assert(numOfSuit(game, QUESTIONS) == 5);
    
    printf("7 cards of type CLUBS.\n\n");
    assert(numOfSuit(game, CLUBS) == 7);
}

static void check_initial_deckcolor(Game game) {
    printf("Check the number of card of each color.\n\n");
    
    printf("5 cards of color RED.\n");
    assert(numOfColor(game, RED) == 5);
    
    printf("5 cards of color YELLOW.\n");
    assert(numOfColor(game, YELLOW) == 5);
    
    printf("7 cards of color BLUE.\n");    
    assert(numOfColor(game, BLUE) == 7);
    
    printf("7 cards of color GREEN.\n");  
    assert(numOfColor(game, GREEN) == 7);  
    
    printf("6 cards of color PURPLE.\n\n");  
    assert(numOfColor(game, PURPLE) == 6);
}
static void check_initial_deckvalue(Game game) {
    printf("Check the number of cards of each value.\n");
    
    assert(numOfValue(game, ZERO) == 1);
    assert(numOfValue(game, ONE) == 2);
    assert(numOfValue(game, DRAW_TWO) == 2);
    assert(numOfValue(game, THREE) == 2);
    assert(numOfValue(game, FOUR) == 2);
    assert(numOfValue(game, FIVE) == 2);
    assert(numOfValue(game, SIX) == 2);
    assert(numOfValue(game, SEVEN) == 2);
    assert(numOfValue(game, EIGHT) == 2);
    assert(numOfValue(game, NINE) == 2);
    assert(numOfValue(game, A) == 2);
    assert(numOfValue(game, B) == 2);
    assert(numOfValue(game, C) == 2);
    assert(numOfValue(game, D) == 2);
    assert(numOfValue(game, E) == 1);
    assert(numOfValue(game, F) == 2);
    
    printf("All values are correct!\n\n");
}
//check whether the card we get is exactly the same as what we except
static bool samecard(Card card, value v, color c, suit s) {
    
    if (cardValue(card) == v && cardColor(card) == c && cardSuit(card) == s) {
        return true;
    } else {
        return false;
    }
}

//End of test 1
//
//Following 12 functions for test 2
//Test 2: test some basic actions, change of current state, check 
//whether the player move is valid
//and test some special cases
static void test2_action(void) {
    int decksize = 40;
    
    value values[] = {
        E, SEVEN, DRAW_TWO, THREE, ZERO, FOUR, THREE, NINE,
        DRAW_TWO, A, ONE, FIVE, F, EIGHT, SIX, ZERO,
        D, DRAW_TWO, SEVEN, FIVE, D, C, E, ONE,
        A, FOUR, EIGHT, NINE, B, D, SIX, THREE,
        F, E, C ,B, SEVEN, FOUR, FIVE, DRAW_TWO
    };
    
    color colors[] = {
        RED, PURPLE, BLUE, RED, BLUE, GREEN, PURPLE, YELLOW,
        GREEN, YELLOW, BLUE, RED, BLUE, PURPLE, GREEN, RED,
        PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, RED, GREEN, RED,
        BLUE, RED, GREEN, PURPLE, BLUE, PURPLE, YELLOW, RED,
        YELLOW, YELLOW, GREEN, RED, RED, BLUE, PURPLE, RED
    };
    
    suit suits[] = {
        SPADES, QUESTIONS, DIAMONDS, DIAMONDS, SPADES, 
        SPADES, CLUBS, CLUBS, HEARTS, QUESTIONS, 
        HEARTS, QUESTIONS, QUESTIONS, SPADES, CLUBS,
        DIAMONDS, HEARTS, QUESTIONS, CLUBS, CLUBS,
        SPADES, HEARTS, SPADES, DIAMONDS, QUESTIONS,
        CLUBS, HEARTS, SPADES, QUESTIONS, DIAMONDS,
        QUESTIONS, CLUBS, DIAMONDS, CLUBS, DIAMONDS,
        HEARTS, QUESTIONS, CLUBS, DIAMONDS, SPADES
    };
    
    Game game = newGame(decksize, values, colors, suits);
    
    testPlayer0Turn1(game);
    testPlayer1Turn1(game);
    testPlayer2Turn1(game);
    testPlayer3Turn1(game);
    testPlayer0Turn2(game);
    testPlayer1Turn2(game);
    testplayer2Turn2(game);
    testplayer3Turn2(game);
    printf("Destory the game.");
    destroyGame(game);
} 

//The first player can play F BLUE QUESTIONS
//The isValidMove function should not change the state
//after played the it should not be in the players hand 
//the top of the discard pile is F BLUE QUESTIONS
//the 29th card is B QUESTIONS BLUE
static void testPlayer0Turn1(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 1********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 0, 0, 0, BLUE, -1, -1);
    
    printf("Checking player 0 has F BLUE QUESTIONS.\n");
    card = findCardInHand(game, 0, F, BLUE, QUESTIONS);
    assert(card != NULL);
    
    p0.action = PLAY_CARD;
    p0.card = card;
    printf("Checking player 0 can play that card.\n");
    assert(isValidMove(game, p0) == TRUE);
    checkcurrstate(game, 0, 0, 0, BLUE, -1, -1);
    
    playMove(game, p0);
    printf("The top of discard pile is now F BLUE QUESTIONS.\n");
    assert(sameTopDiscard(game, card) == true);  
    printf("Checking player 0 should not have F BLUE QUESTIONS.\n");
    card = findCardInHand(game, 0, F, BLUE, QUESTIONS);
    assert(card == NULL);
    
    printf("Check current state:\n");
    checkcurrstate(game, 0, 0, 1, BLUE, -1, 0);
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

//first checking the current state changed properly
//player 1 want to end turn without draw or play a card
//isValidMove return false
//then play a card he does not have
//isValidMove return false
//play a special card A YELLOW QUESTIONS
static void testPlayer1Turn1(Game game) {
    playerMove p1;
    Card card;
 
    printf("\n******************PLAYER 1 TURN 1********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 1, 1, 0, BLUE, 0, 0);
    
    printf("Player 1 cannot end turn.\n");
    p1.action = END_TURN;
    assert(isValidMove(game, p1) == FALSE);
    
    printf("Player 1 does not have F BLUE QUESTIONS.\n");
    card = findCardInHand(game, 1, F, BLUE, QUESTIONS);
    assert(card == NULL);
    
    p1.action = PLAY_CARD;
    p1.card = newCard(F, BLUE, QUESTIONS);
    printf("Player 1 can not play that card.\n");
    assert(isValidMove(game, p1) == FALSE);
    checkcurrstate(game, 1, 1, 0, BLUE, 0, 0);
    
    printf("Checking player 1 has A YELLOW QUESTIONS.\n");
    card = findCardInHand(game, 1, A, YELLOW, QUESTIONS);
    assert(card != NULL);
    
    p1.action = PLAY_CARD;
    p1.card = card;
    printf("Checking player 1 can play that card.\n");
    assert(isValidMove(game, p1) == TRUE);
    
    playMove(game, p1);
    printf("The top of discard pile is now A YELLOW QUESTIONS\n");
    assert(sameTopDiscard(game, card) == true);  
    printf("Checking player 1 should not have A YELLOW QUESTIONS.\n");
    card = findCardInHand(game, 1, A, YELLOW, QUESTIONS);
    assert(card == NULL);
    
    printf("Check current state:\n");
    checkcurrstate(game, 1, 1, 1, YELLOW, 0, 1);
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

//player 2's turn should be skipped
//the current player number should be 3
static void testPlayer2Turn1(Game game) { 
    printf("\n*************PLAYER 2 TURN 1 IS SKIPPED**************\n");   
}

//the current state is proper
//player 3 wanted to play THREE RED DIAMONDS
//the move is not valid
//player wanted to draw a card
//player 3 had NINE YELLOW CLUBS
//player 3 wanted to play that card
//the move is not valid
//the move is valid
static void testPlayer3Turn1(Game game) {
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 1********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 3, 2, 0, YELLOW, 1, 1);
    
    printf("Checking player 3 has THREE RED DIAMONDS.\n");
    card = findCardInHand(game, 3, THREE, RED, DIAMONDS);
    assert(card != NULL);
    
    p3.action = PLAY_CARD;
    p3.card = card;
    printf("Player 3 cannot play that card.\n");
    assert(isValidMove(game, p3) == FALSE);
    checkcurrstate(game, 3, 2, 0, YELLOW, 1, 1);
    
    p3.action = DRAW_CARD;
    printf("Player 3 can draw a card.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
    
    printf("Check current state:\n");
    checkcurrstate(game, 3, 2, 1, YELLOW, 1, 1);
    
    printf("Checking player 3 has NINE YELLOW CLUBS.\n");
    Card newcard = findCardInHand(game, 3, NINE, YELLOW, CLUBS);
    assert(newcard != NULL);
        
    p3.action = PLAY_CARD;
    p3.card = newcard;
    printf("Player 3 cannot play that card.\n");
    assert(isValidMove(game, p3) == FALSE);
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

//the second turn of player 0
//check and play D YELLOW SPADES
//declared color BLUE
//attemped to play one more card E RED SPADES
//not valid move
static void testPlayer0Turn2(Game game) {
    playerMove p0;
    Card card;
    printf("\n******************PLAYER 0 TURN 2********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 0, 3, 0, YELLOW, 3, 1);
    
    printf("Checking player 0 has D YELLOW SPADES.\n");
    card = findCardInHand(game, 0, D, YELLOW, SPADES);
    assert(card != NULL);
    
    p0.action = PLAY_CARD;
    p0.card = card;
    p0.nextColor = BLUE;
    printf("Player 0 declares color BLUE.\n");
    assert(isValidMove(game, p0) == TRUE);
    printf("Checking player 0 can play that card.\n");
    playMove(game, p0);
    checkcurrstate(game, 0, 3, 1, BLUE, 3, 3);
    
    printf("The top of discard pile is now D YELLOW SPADES.\n");
    assert(sameTopDiscard(game, card) == true);  
    printf("Checking player 0 should not have D YELLOW SPADES.\n");
    card = findCardInHand(game, 0, D, YELLOW, SPADES);
    assert(card == NULL);

    printf("Checking player 0 has E RED SPADES.\n");
    Card newcard = findCardInHand(game, 0, E, RED, SPADES);
    assert(newcard != NULL);
    playMove(game, p0);
    
    p0.action = PLAY_CARD;
    p0.card = newcard;
    printf("Checking player 0 cannot play two cards.\n");
    assert(isValidMove(game, p0) == FALSE);
    checkcurrstate(game, 0, 3, 1, BLUE, 3, 3);

    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

//Player1 attempted to play FOUR GREEN SPADES
//not valid move because the color should be BLUE
//DRAW_CARD valid
//END_TURN
static void testPlayer1Turn2(Game game) {
    playerMove p1;
    Card card;
 
    printf("\n******************PLAYER 1 TURN 2********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 1, 4, 0, BLUE, 0, 3);

    p1.action = PLAY_CARD;
    printf("Checking player 1 has FOUR GREEN SPADES.\n");
    card = findCardInHand(game, 1, FOUR, GREEN, SPADES);
    assert(card != NULL);
    p1.card = card;
    
    printf("Player 1 can not play that card.\n");
    assert(isValidMove(game, p1) == FALSE);
    checkcurrstate(game, 1, 4, 0, BLUE, 0, 3);
    
    
    p1.action = DRAW_CARD;
    printf("Checking player 1 can draw a card.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
    
    printf("Check current state:\n");
    checkcurrstate(game, 1, 4, 1, BLUE, 0, 3);
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);	
}

//Player 2 players a DRAW_TWO
//Then END_TURN
static void testplayer2Turn2(Game game) {
    playerMove p2;
    Card card;
    printf("\n******************PLAYER 2 TURN 2********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 2, 5, 0, BLUE, 1, 3);
    
    p2.action = PLAY_CARD;
    printf("Checking player 2 has DRAW_TWO BLUE DIAMONDS.\n");
    card = findCardInHand(game, 2, DRAW_TWO, BLUE, DIAMONDS);
    assert(card != NULL);
    p2.card = card;
    
    p2.action = PLAY_CARD;
    p2.card = card;
    printf("Checking player 2 can play that card.\n");
    assert(isValidMove(game, p2) == TRUE);
    
    playMove(game, p2);
    printf("The top of discard pile is now DRAW_TWO BLUE DIAMONDS\n");
    assert(sameTopDiscard(game, card) == true);  
    printf("Checking player 2 should not have DRAW_TWO BLUE DIAMONDS.\n");
    card = findCardInHand(game, 2, DRAW_TWO, BLUE, DIAMONDS);
    assert(card == NULL);
    
    printf("Check current state:\n");
    checkcurrstate(game, 2, 5, 1, BLUE, 1, 5);
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);	
}

//Player 3 did not have DRAW_TWO so he had to draw two cards
//draw one valid and want to end turn couldn't end turn
//draw one more and end turn
static void testplayer3Turn2(Game game) {
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 2********************\n");
    printf("Check current state:\n");
    checkcurrstate(game, 3, 6, 0, BLUE, 2, 5);
    
    p3.action = DRAW_CARD;
    printf("Player 3 can draw a card.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
    
    printf("Check current state:\n");
    checkcurrstate(game, 3, 6, 1, BLUE, 2, 5);
    
    p3.action = END_TURN;
    printf("Player 3 cannot end his turn.\n");
    assert(isValidMove(game, p3) == FALSE);
        
    p3.action = DRAW_CARD;
    printf("Player 3 can draw a card.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3); 
    
    printf("Check current state:\n");
    checkcurrstate(game, 3, 6, 2, BLUE, 2, 5);
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
}
//check the current state of the game
static void checkcurrstate(Game game, int player, int turn, int moves,
             int currcolor, int previousPlayer, int topDiscardTurn) {
    printf("The current turn is %d\n", turn);
    assert(currentTurn(game) == turn);
    
    printf("The number of turns is %d\n", turn + 1);
    assert(numTurns(game) == turn + 1);
    
    printf("The current player is %d\n", currentPlayer(game));
    assert(currentPlayer(game) == player);
    
    printf("The current color is %d\n",getCurrentColor(game));
    assert(getCurrentColor(game) == currcolor);
    
    printf("The previous turn player is %d\n", previousPlayer);
    assert(getPreviousTurnPlayer(game) == previousPlayer);
    
    printf("The top discard turn number is %d\n\n", topDiscardTurn);
    assert(getTopDiscardTurnNumber(game) == topDiscardTurn);
}

//find the card in the player hand must be the exactly the same value
//same suit and same color
static Card findCardInHand(Game game, int player, value values,
                                        color colors, suit suits) {
    int num = 0;
    Card card = getHandCard(game, player, num);
    while (card != NULL) {
        if (samecard(card, values, colors, suits) == true) {
            return card;
        }
        num++;
        card = getHandCard(game, player, num);
    }
    return NULL;

}
//if the top discard is the same as we expected return ture
static bool sameTopDiscard(Game game, Card card) {
    Card discard = getDiscardPileCard (game, 0);
    int v = cardValue(card);
    int c = cardColor(card);
    int s = cardSuit(card);
    if (samecard(discard, v, c, s) == true) {
        return true;
    }
    return false;
}

//End of test2
//
//Following functions for test 3
//Test an extreme case and whether the game ends properly
static void test3_extremeCases(void) {
    int decksize = 30;
    
    value values[] = {
        THREE, THREE, THREE, THREE, THREE, THREE,
        THREE, THREE, THREE, THREE, THREE, THREE,
        THREE, THREE, THREE, THREE, THREE, THREE,
        THREE, THREE, THREE, THREE, THREE, THREE,
        THREE, THREE, THREE, THREE, FOUR, FIVE                            
    };
    
    color colors[] = {
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, YELLOW, GREEN
    };
    
    suit suits[] = {
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS,
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS,
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS,
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS,
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS 
    };
    
    Game new = newGame(decksize, values, colors, suits);
    
    player0turn(new);
    endGame(new);
    printf("Destroy the game.\n");
    destroyGame(new);
}

//the only turn in this game
static void player0turn(Game game) {
    playerMove p0;
    
    printf("Player 0 can draw a card.\n");
    p0.action = DRAW_CARD;
    playMove(game, p0);
    
    printf("Player 0 ends his turn.\n");
    p0.action = END_TURN;
    playMove(game, p0);
}

//End the game
static void endGame(Game game) {
    printf("No one can play a card, the game ends!\n");
    printf("What a shame! The game has no winner.\n");
    assert(gameWinner(game) == 4);

    int player0Points = playerPoints(game, 0);
    assert(player0Points == 26);
    int player1Points = playerPoints(game, 1);
    assert(player1Points == 21);
    int player2Points = playerPoints(game, 2);
    assert(player2Points == 21);
    int player3Points = playerPoints(game, 3);
    assert(player3Points == 21);
    
    printf("THE FINAL POINTS:\n");
    printf("===========PLAYER 0 GOT %d :D===========\n", player0Points);
    printf("===========PLAYER 1 GOT %d :D===========\n", player1Points);
    printf("===========PLAYER 2 GOT %d :D===========\n", player2Points);
    printf("===========PLAYER 3 GOT %d :D===========\n", player3Points);        
}

//Test 4: cases with twos and complete a whole game
static void test4_draw_twos(void) {
    int decksize = 36;
    
    value values[] = {
        FOUR, DRAW_TWO, DRAW_TWO, ONE, ONE, FOUR,
        FIVE, SEVEN, THREE, SIX, SEVEN, B,
        FOUR, FIVE, FIVE, C, E, E,
        SIX, EIGHT, SEVEN, A, EIGHT, THREE, 
        EIGHT,SEVEN, NINE, ONE, DRAW_TWO, B,
        C, E, F, THREE, FOUR, SIX
        
    };
    
    color colors[] = {
        PURPLE, BLUE, PURPLE, PURPLE, RED, BLUE,
        BLUE, PURPLE, BLUE, RED, GREEN, RED,
        GREEN, GREEN, RED, GREEN, BLUE, GREEN, 
        RED, BLUE, RED, YELLOW, YELLOW, PURPLE,
        PURPLE, PURPLE, PURPLE, BLUE, RED, BLUE,
        PURPLE, RED, GREEN, YELLOW, RED, BLUE 
    };
    
    suit suits[] = {
        CLUBS, HEARTS, QUESTIONS, DIAMONDS,
        QUESTIONS, HEARTS, DIAMONDS, HEARTS,
        HEARTS, DIAMONDS, DIAMONDS, HEARTS,
        HEARTS, HEARTS, HEARTS, SPADES, 
        DIAMONDS, QUESTIONS, SPADES, SPADES,
        SPADES, SPADES, CLUBS, QUESTIONS,
        HEARTS, CLUBS, QUESTIONS, DIAMONDS,
        CLUBS, HEARTS, CLUBS, HEARTS,
        QUESTIONS, SPADES, HEARTS, DIAMONDS   
    };
    
    Game newgame = newGame(decksize, values, colors, suits);
        
	gameBegin(newgame);
	gameEnd(newgame);
    printf("Destroy the game.\n");
    destroyGame(newgame);
}

static void gameBegin(Game game) {
    player0Turn1(game);
    player1Turn1(game);
    player2Turn1(game);
    player3Turn1(game);
                
    player0Turn2(game);
    player1Turn2(game);
    player2Turn2(game);
    player3Turn2(game);
    
    player0Turn3(game);
    player1Turn3(game);
    player2Turn3(game);
    player3Turn3(game);

    player0Turn4(game);
    player1Turn4(game);
    player2Turn4(game);
    player3Turn4(game);

    player0Turn5(game);
    player1Turn5(game);
    player2Turn5(game);
    checkNewPiles(game);
    player3Turn5(game);

    player0Turn6(game);
    player1Turn6(game);
    player2Turn6(game);
    player3Turn6(game);

    player0Turn7(game);
    player1Turn7(game);
}

//The top diacard is DRAW_TWO RED CLUBS
//Player 0 didn't have twos so he draw two cards
static void player0Turn1(Game game) {
    playerMove p0;
    printf("\n******************PLAYER 0 TURN 1********************\n");
    printf("Player 0 didn't have a DRAW_TWO, draw two cards\n");
    p0.action = DRAW_CARD;
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
    p0.action = DRAW_CARD;
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
    
    Card card = findCardInHand(game, 0, THREE, BLUE, HEARTS);
    assert(card != NULL);
    p0.action = END_TURN;
    assert(isValidMove(game, p0) == TRUE);
    printf("Player 0's turn ends.\n");
    playMove(game, p0);   
}

//player 1 plays a two
static void player1Turn1(Game game) {
    playerMove p1;
    Card card;
 
    printf("\n******************PLAYER 1 TURN 1********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played DRAW_TWO BLUE HEARTS.\n");
    card = findCardInHand(game, 1, DRAW_TWO, BLUE, HEARTS);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);	
}

//player 2 has a DRAW_TWO and played it
static void player2Turn1(Game game) {
    playerMove p2;
    Card card;
 
    printf("\n******************PLAYER 2 TURN 1********************\n");

    p2.action = PLAY_CARD;
    printf("Checking player 2 played DRAW_TWO PURPLE QUESTIONS.\n");
    card = findCardInHand(game, 2, DRAW_TWO, PURPLE, QUESTIONS);
    assert(card != NULL);
    p2.card = card;
    
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);    
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);	
}

//player 3 didn't has a DRAW_TWO
//he must draw four cards
//check the active draw two is 2 before player3 draws
static void player3Turn1(Game game) {
    playerMove p3;
 
    printf("\n******************PLAYER 3 TURN 1********************\n");
    printf("The number is %d\n", getActiveDrawTwos(game));
    printf("The active twos is 2.\n");
    assert(getActiveDrawTwos(game) == 2);
    
    p3.action = DRAW_CARD;
    printf("Checking player 3 should draw four cards.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    p3.action = DRAW_CARD;
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3); 
    p3.action = DRAW_CARD;
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3); 
    p3.action = DRAW_CARD;
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3); 
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);	
}

//Almost all the players are able to play cards in the following
//24 turns except player 2. What a coincidence!!
static void player0Turn2(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 2********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played FOUR PURPLE CLUBS.\n");
    card = findCardInHand(game, 0, FOUR, PURPLE, CLUBS);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn2(Game game) {    
    playerMove p1;
    Card card1;

    printf("\n******************PLAYER 1 TURN 2********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played FOUR BLUE HEARTS.\n");
    card1 = findCardInHand(game, 1, FOUR, BLUE, HEARTS);
    assert(card1 != NULL);
    p1.card = card1;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void player2Turn2(Game game) {    
    playerMove p2;
    Card card2;
 
    printf("\n******************PLAYER 2 TURN 2********************\n");

    p2.action = PLAY_CARD;
    printf("Checking player 2 played FIVE BLUE DIAMONDS.\n");
    card2 = findCardInHand(game, 2, FIVE, BLUE, DIAMONDS);
    assert(card2 != NULL);
    p2.card = card2;
    
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);    
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);
}

static void player3Turn2(Game game) {    
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 2********************\n");

    p3.action = PLAY_CARD;
    printf("Checking player 3 played ONE PURPLE DIAMONDS.\n");
    card = findCardInHand(game, 3, ONE, PURPLE, DIAMONDS);
    assert(card != NULL);
    p3.card = card;
    
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

//All the players are able to play cards in the following
//24 turns. What a coincidence!!
static void player0Turn3(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 3********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played ONE RED QUESTIONS.\n");
    card = findCardInHand(game, 0, ONE, RED, QUESTIONS);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn3(Game game) {    
    playerMove p1;
    Card card;

    printf("\n******************PLAYER 1 TURN 3********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played SIX RED DIAMONDS.\n");
    card = findCardInHand(game, 1, SIX, RED, DIAMONDS);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void player2Turn3(Game game) {    
    playerMove p2;
    Card card;
 
    printf("\n******************PLAYER 2 TURN 3********************\n");

    p2.action = PLAY_CARD;
    printf("Checking player 2 played SEVEN GREEN DIAMONDS.\n");
    card = findCardInHand(game, 2, SEVEN, GREEN, DIAMONDS);
    assert(card != NULL);
    p2.card = card;
    
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);    
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);
}

static void player3Turn3(Game game) {    
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 3********************\n");

    p3.action = PLAY_CARD;
    printf("Checking player 3 played SEVEN PURPLE HEARTS.\n");
    card = findCardInHand(game, 3, SEVEN, PURPLE, HEARTS);
    assert(card != NULL);
    p3.card = card;
    
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

//All the players are able to play cards in the following
//24 turns. What a coincidence!!
static void player0Turn4(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 4********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played THREE BLUE HEARTS.\n");
    card = findCardInHand(game, 0, THREE, BLUE, HEARTS);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn4(Game game) {    
    playerMove p1;
    Card card;

    printf("\n******************PLAYER 1 TURN 4********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played FIVE GREEN HEARTS.\n");
    card = findCardInHand(game, 1, FIVE, GREEN, HEARTS);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void player2Turn4(Game game) {    
    playerMove p2;
    Card card;
 
    printf("\n******************PLAYER 2 TURN 4********************\n");

    p2.action = PLAY_CARD;
    printf("Checking player 2 played FIVE RED HEARTS.\n");
    card = findCardInHand(game, 2, FIVE, RED, HEARTS);
    assert(card != NULL);
    p2.card = card;
    
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);    
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);
}

static void player3Turn4(Game game) {    
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 4********************\n");

    p3.action = PLAY_CARD;
    printf("Checking player 3 played B RED HEARTS.\n");
    card = findCardInHand(game, 3, B, RED, HEARTS);
    assert(card != NULL);
    p3.card = card;
    
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

static void player0Turn5(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 5********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played FOUR GREEN HEARTS.\n");
    card = findCardInHand(game, 0, FOUR, GREEN, HEARTS);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn5(Game game) {    
    playerMove p1;
    Card card;

    printf("\n******************PLAYER 1 TURN 5********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played E GREEN QUESTIONS.\n");
    card = findCardInHand(game, 1, E, GREEN, QUESTIONS);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void player2Turn5(Game game) {    
    playerMove p2;
    Card card;
 
    printf("\n******************PLAYER 2 TURN 5********************\n");

    p2.action = DRAW_CARD;
    printf("Player 2 had to draw a card.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);    
    
    p2.action = END_TURN;
    printf("Player 2's turn ends.\n");
    assert(isValidMove(game, p2) == TRUE);
    playMove(game, p2);
}

//no card left in deck pile
//Checking discard pile becomes new draw pile
static void checkNewPiles(Game game) {
    printf("\n--------------Checking new card piles!---------------\n");
    printf("There is only one card in the discard pile! Awesome!!\n");
    Card card = getDiscardPileCard(game, 1);
    assert(card == NULL);
    
    printf("The card in the discard pile is E GREEN QUESTIONS.\n");
    Card discard = getDiscardPileCard(game, 0);
    assert(samecard(discard, E, GREEN, QUESTIONS) == true);
    
    printf("The first card in deck is DRAW_TWO RED CLUBS.\n");
    Card first = getDeckCard(game, 0);
    assert(samecard(first, DRAW_TWO, RED, CLUBS) == true);
    printf("The last card in deck is FOUR GREEN HEARTS.\n");
    Card last = getDeckCard(game, 15);
    printf("%d %d %d\n", cardValue(last), cardColor(last), cardSuit(last));
    assert(samecard(last, FOUR, GREEN, HEARTS) == true);
}

static void player3Turn5(Game game) {    
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 5********************\n");

    p3.action = PLAY_CARD;
    printf("Checking player 3 played C GREEN SPADES.\n");
    card = findCardInHand(game, 3, C, GREEN, SPADES);
    assert(card != NULL);
    p3.card = card;
    
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

static void player0Turn6(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 6********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played SEVEN RED SPADES.\n");
    card = findCardInHand(game, 0, SEVEN, RED, SPADES);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn6(Game game) {    
    playerMove p1;
    Card card;

    printf("\n******************PLAYER 1 TURN 6********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played A YELLOW SPADES.\n");
    card = findCardInHand(game, 1, A, YELLOW, SPADES);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);    
    
    p1.action = END_TURN;
    printf("Player 1's turn ends.\n");
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void player2Turn6(Game game) {    
    printf("\n*************PLAYER 2 TURN 6 IS SKIPPED**************\n");
}

static void player3Turn6(Game game) {    
    playerMove p3;
    Card card;
 
    printf("\n******************PLAYER 3 TURN 6********************\n");

    p3.action = PLAY_CARD;
    printf("Checking player 3 played EIGHT BLUE SPADES.\n");
    card = findCardInHand(game, 3, EIGHT, BLUE, SPADES);
    assert(card != NULL);
    p3.card = card;
    
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);    
    
    p3.action = END_TURN;
    printf("Player 3's turn ends.\n");
    assert(isValidMove(game, p3) == TRUE);
    playMove(game, p3);
}

static void player0Turn7(Game game) {
    playerMove p0;
    Card card;
 
    printf("\n******************PLAYER 0 TURN 7********************\n");

    p0.action = PLAY_CARD;
    printf("Checking player 0 played EIGHT PURPLE HEARTS.\n");
    card = findCardInHand(game, 0, EIGHT, PURPLE, HEARTS);
    assert(card != NULL);
    p0.card = card;
    
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);    
    
    p0.action = END_TURN;
    printf("Player 0's turn ends.\n");
    assert(isValidMove(game, p0) == TRUE);
    playMove(game, p0);
}

static void player1Turn7(Game game) {    
    playerMove p1;
    Card card;

    printf("\n******************PLAYER 1 TURN 7********************\n");

    p1.action = PLAY_CARD;
    printf("Checking player 1 played SEVEN PURPLE CLUBS.\n");
    card = findCardInHand(game, 1, SEVEN, PURPLE, CLUBS);
    assert(card != NULL);
    p1.card = card;
    
    assert(isValidMove(game, p1) == TRUE);
    playMove(game, p1);
}

static void gameEnd(Game game) {
    printf("Player1 played all his cards, the game ends!\n");
    printf("PLAY 1 WONS!.\n");
    assert(gameWinner(game) == 1);
    assert(playerCardCount(game, 1) == 0);
}

