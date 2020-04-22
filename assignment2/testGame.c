// Individual work done by Queenie Ji z5191512
// Assignment2 testGame.c

#include <stdio.h>
#include <assert.h>

#include "Game.h"
#include "Card.h"

#define STARTING_HAND_SIZE 7

static void test1_initial_state ();
static void checkdeckcards(Game game, value values[], color colors[], 
                           suit suits[]);
static int checkdiscard(Game game, value values, color colors, 
                        suit suits);
static void check_initial_player_hand(Game game, int player, value
                                      values[], color colors[],
                                      suit suits[]); 
static void check_initial_turn(Game game);
static void check_initial_playernumber(Game game);
static int cardmatch(Card card, value v, color c, suit s);
static void check_initial_num_turns(Game game);
static void check_before_start(Game game);
static void check_initial_player_point(Game game);
static void check_initial_hand_card_size(Game game);

static void test2_basic_actions ();
static void check_state(Game game, int turn_num, int player_num,
                        int num_move, int pre_player, int top_dis_turn);
static Card find_card_in_hand (Game game, int player, value v, 
                        color c, suit s); 
static void checkPlayer0Turn1(Game game);
static void checkPlayer1Turn1(Game game);
static void checkPlayer2Turn1(Game game);
static void checkPlayer3Turn1(Game game);
static void checkPlayer0Turn2(Game game);
static void checkPlayer1Turn2(Game game);
static void checkPlayer2Turn2(Game game);

static void test3_extreme_cases();
static void check_for_no_winner();
static void sub_player0(Game game);
static void sub_GAME_OVER (Game game);
static void check_many_draw_twos();
static void check_game_winner();
static void check_same_hands_card();
static void sub_player_turns(Game game);
static void sub_poor_player3(Game game);
static void win_the_game();
static void sub_repeated(Game game);
static void sub_repeated_again(Game game);
static void sub_keep_playing_card(Game game);
static void sub_update_deckcards(Game game);
static void sub_PLAYER0_WIN(Game game);
static void sub_active(Game game);

int main () {

    test1_initial_state ();

    test2_basic_actions ();

    test3_extreme_cases();

    printf("YOU PASSED ALL TESTS! WELL DONE!\n");
}

// Check all components initial state
static void test1_initial_state () {
    int decksize = 30;
    printf("===========================================\n");
    printf("Test1 Check Initial State\n\n");
    value values[] = {
        ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN, 
        EIGHT, NINE, A, B, C, D, E, F, ZERO, ONE, DRAW_TWO, 
        THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        A, B, C, D
    };

    color colors[] = {
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE
    };

    suit suits[] = { 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS 
    };

    Game game = newGame(decksize, values, colors, suits);
    checkdeckcards(game, values, colors, suits);
    assert (checkdiscard(game, C, BLUE, SPADES) == 1);
    printf("\nChecking initial discard is successful\n");
    printf("-------------------------------------------\n");
    check_initial_turn(game);
    check_initial_playernumber(game);
    int player = 0;
    check_initial_player_hand(game, player, values, colors, suits);
    check_initial_num_turns(game);
    check_before_start(game);
    check_initial_player_point(game);
    check_initial_hand_card_size(game);
    printf("Try to destroy the game\n");
    destroyGame(game);
    printf("\n\nTest 1 ALL SUCCESSFUL!!:D\n");
    printf("===========================================\n");
}

// Function to check the deck cards
static void checkdeckcards(Game game, value values[],
                            color colors[], suit suits[]) {
    printf("Checking the number of cards is 30\n");
    assert(numCards(game) == 30);

    printf("Checking the number of cards in each suit\n");
    printf("HEARTS = %d\n",numOfSuit(game,HEARTS));
    assert(numOfSuit(game, HEARTS) == 6);
    assert(numOfSuit(game, DIAMONDS) == 6);
    assert(numOfSuit(game, CLUBS) == 6);
    assert(numOfSuit(game, SPADES) == 6);
    assert(numOfSuit(game, QUESTIONS) == 6);

    printf("Checking the number of cards in each color\n");
    assert(numOfColor(game, RED) == 6);
    assert(numOfColor(game, GREEN) == 6);
    assert(numOfColor(game, YELLOW) == 6);
    assert(numOfColor(game, BLUE) == 6);
    assert(numOfColor(game, PURPLE) == 6);

    printf("Cheking the number of cards in each value\n");
    assert(numOfValue(game, ZERO) == 2);
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
    assert(numOfValue(game, F) == 1);

    printf("\nChecking initial deckcards is successful\n");
    printf("-------------------------------------------\n");
}

static int checkdiscard(Game game, value values, color colors, 
                        suit suits) {
    value disvalue = cardValue(topDiscard(game));
    color discolor = cardColor(topDiscard(game));
    suit dissuit = cardSuit(topDiscard(game));
    if (values == disvalue && colors == discolor && suits == dissuit) {
        return TRUE;
    }
    return FALSE;
}

static void check_initial_player_hand(Game game, int player, value
                                     values[], color colors[], 
                                     suit suits[]) {
    int i = 0;//index of initial deck card
    while (player < 4) {

        int j = 0;//index of player hand card
        while (i < 28 && j < STARTING_HAND_SIZE) {
            int v = values[i];
            int c = colors[i];
            int s = suits[i];
            Card card = getHandCard(game, player, 6 - j);
            printf("The card %d in player %d's hand is correct\n", j, player);
            printf("%p\n",card);
            assert(cardmatch(card, v, c, s) == 1);
            j++;
            i = i + 4;
        }
        player++;
        i = player;
    }
    player --;
    Card card = getHandCard(game, player, STARTING_HAND_SIZE);
    assert(card == NULL);
    printf("\nChecking initial player hand is successful\n");
    printf("-------------------------------------------\n");
}

// Find whether the two cards are same
static int cardmatch(Card card, value v, color c, suit s) {
    if (cardValue(card) == v && cardColor(card) == c && cardSuit(card) == s) {
        return 1;
    } else {
        return 0;
    }
}

// Check the initial turn number is 0
static void check_initial_turn(Game game) {
    printf("Checking the initial turn number is 0\n");
    int num_turn = currentTurn(game);
    assert(num_turn == 0);
    printf("\nChecking initial turn number is successful\n");
    printf("-------------------------------------------\n");
}

// Check the initial player is 0
static void check_initial_playernumber(Game game) {
    printf("Checking the initial player number is 0\n");
    int num_player = currentPlayer(game);
    assert(num_player == 0);
    printf("\nChecking initial player number is successful\n");
    printf("-------------------------------------------\n");
}

// Check the initial number of turn is 1
static void check_initial_num_turns(Game game) {
    printf("Checking the initial number of turns is 1\n");
    assert(numTurns(game) == 1);
    printf("\nChecking initial number of turns is successful\n");
    printf("-------------------------------------------\n");
}

// Check other state components at the beginning of the game
static void check_before_start(Game game) {
    printf("Checking if current moves in turn is 0\n");
    assert(currentTurnMoves(game) == 0);

    printf("Checking if player from previous turn is -1\n");
    assert(getPreviousTurnPlayer(game) == -1);

    printf("Checking if top of discard pile was played in turn -1\n");
    assert(getTopDiscardTurnNumber(game) == -1);
        
    printf("\nChecking before start is successful\n");
    printf("-------------------------------------------\n");
}

// Calculate the initial points are correct
static void check_initial_player_point(Game game) {
    printf("Checking if player 0 point is 36\n");
    assert(playerPoints(game, 0) == 36);

    printf("Checking if player 1 point is 43\n");
    assert(playerPoints(game, 1) == 43);

    printf("Checking if player 2 point is 50\n");
    assert(playerPoints(game, 2) == 50);

    printf("Checking if player 0 point is 57\n");
    assert(playerPoints(game, 3) == 57);

    printf("\nChecking initial player point is successful\n");
    printf("-------------------------------------------\n");
}

// Check each player has 7 cards initially
static void check_initial_hand_card_size(Game game) {
    printf("Checking if the player 0 has 7 cards\n");
    assert(playerCardCount(game, 0) == 7);

    printf("Checking if the player 1 has 7 cards\n");
    assert(playerCardCount(game, 1) == 7);

    printf("Checking if the player 2 has 7 cards\n");
    assert(playerCardCount(game, 2) == 7);

    printf("Checking if the player 3 has 7 cards\n");
    assert(playerCardCount(game, 3) == 7);

    printf("\nChecking initial player hand size is successful\n");
    printf("-------------------------------------------\n");
}

// Check some basic actions like draw cards, play cards and end turn, as 
// well as some special cards case
static void test2_basic_actions () {
    int decksize = 50;
    printf("===========================================\n");
    printf("Test2 Check Basic Actions\n\n");
    value values[] = {
        ZERO, ONE, DRAW_TWO, THREE, FOUR,
        FIVE, SIX, SEVEN, EIGHT, NINE, 
        A, B, C, D, E, 
        F, ZERO, ONE, DRAW_TWO, THREE,
        FOUR, FIVE, SIX, SEVEN, EIGHT, 
        NINE, A, B, C, D,
        E, F, ZERO, ONE, DRAW_TWO,
        THREE, FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE, A, B, C,
        D, E, F, ZERO, ONE
    };

    color colors[] = {
        RED, GREEN, YELLOW, BLUE, PURPLE,
        GREEN, YELLOW, BLUE, PURPLE, RED,
        YELLOW, BLUE, PURPLE, RED, GREEN, 
        BLUE, PURPLE, RED, GREEN, YELLOW,
        PURPLE, RED, GREEN, YELLOW, BLUE,
        PURPLE, RED, GREEN, YELLOW, BLUE,
        BLUE, PURPLE, RED, GREEN, YELLOW,
        YELLOW, BLUE, PURPLE, RED, GREEN, 
        GREEN, YELLOW, BLUE, PURPLE, RED,
        RED, GREEN, YELLOW, BLUE, PURPLE
    };

    suit suits[] = { 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS
    };

    Game game = newGame(decksize, values, colors, suits);
    checkPlayer0Turn1(game);
    checkPlayer1Turn1(game);
    checkPlayer2Turn1(game);
    checkPlayer3Turn1(game);
    checkPlayer0Turn2(game);
    checkPlayer1Turn2(game);
    checkPlayer2Turn2(game);
    printf("Try to destroy the game\n");
    destroyGame(game);
    printf("\n\nTest 2 ALL SUCCESSFUL!!:D\n");
    printf("===========================================\n");
}

// Check the state components
static void check_state(Game game, int turn_num, int player_num,
                        int num_move, int pre_player, int top_dis_turn) {
    assert(currentTurn(game) == turn_num);
    assert(currentPlayer(game) == player_num);
    assert(currentTurnMoves(game) == num_move);
    assert(getPreviousTurnPlayer(game) == pre_player);
    assert(getTopDiscardTurnNumber(game) == top_dis_turn);
    printf("Checking current state is successful\n");
}

// Find a card in a player's hand
static Card find_card_in_hand (Game game, int player, value v, 
                                color c, suit s) {
    int num = 0;
    Card card = getHandCard (game, player, num);
    while (card != NULL) {
        if (cardmatch(card, v, c, s)) {
            return card;
        } 
        num++;
        card = getHandCard (game, player, num);
    }
    num = 0;
    return NULL;
}

// Check player0Turn1, in this process, check the case that the player 
// cannot play a card that not match the topDiscard and after play a card
// successfully, the card is no longer in his hand.
static void checkPlayer0Turn1(Game game) {
    printf("PLAYER 0 TURN 1\n");
    playerMove move;
    Card card;
    //Check current state
    printf("Checking current state\n");
    check_state(game, 0, 0, 0, -1, -1);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, C, YELLOW, SPADES) == 1);

    printf("Checking player 0 has a BLUE QUESTION EIGHT\n");
    assert(find_card_in_hand(game, 0, EIGHT, BLUE, QUESTIONS) != NULL);
    card = find_card_in_hand(game, 0, EIGHT, BLUE, QUESTIONS);
    printf("Player 0 has this card\n");
    //But this card is not allowed to play
    printf("Checking player 0 cannot play this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == FALSE);

    printf("Checking player 0 has a PURPLE SPADES EIGHT\n");
    assert(find_card_in_hand(game, 0, EIGHT, PURPLE, SPADES) != NULL);
    card = find_card_in_hand(game, 0, EIGHT, PURPLE, SPADES);
    printf("Player 0 has this card\n");
    // We know that the player can play this card
    printf("Checking player 0 can play this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);

    //Check current state
    playMove(game, move);
    check_state(game, 0, 0, 1, -1, 0);

    //Now the player no longer have the card(EIGHT, PURPLE, SPADES)
    assert(find_card_in_hand(game, 0, EIGHT, PURPLE, SPADES) == NULL);
    assert(playerCardCount(game, 0) == 6);
    printf("Player 0 no longer has this card\n");

    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    check_state(game, 1, 1, 0, 0, 0);
    printf("-------------------------------------------\n");
}

// Check player1turn1. In this process, check the case that the player 
// want to play a card D and declare it color.
static void checkPlayer1Turn1(Game game) {
    printf("PLAYER 1 TURN 1\n");
    playerMove move;
    Card card;
    //Check current state
    printf("Checking current state\n");
    check_state(game, 1, 1, 0, 0, 0);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, EIGHT, PURPLE, SPADES) == 1);

    //Checking the player one has the card D, RED, SPADES
    printf("Checking player 1 has a RED SPADES D\n");
    assert(find_card_in_hand(game, 1, D, RED, SPADES) != NULL);
    card = find_card_in_hand(game, 1, D, RED, SPADES);
    // We know that the player can play this card
    printf("Checking player 1 can play this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    move.nextColor = GREEN;
    assert(isValidMove(game, move) == TRUE);
    //Check current state
    playMove(game, move);
    assert(getCurrentColor(game) == GREEN);
    check_state(game, 1, 1, 1, 0, 1);
    //Now the player no longer have the card(D, RED, SPADES)
    //in his hand
    assert(find_card_in_hand(game, 0, D, RED, SPADES) == NULL);
    assert(playerCardCount(game, 0) == 6);
    printf("Player 1 no longer has this card\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    check_state(game, 2, 2, 0, 1, 1);
    printf("-------------------------------------------\n");
}

// Check player2turn1. In this turn, check the case that the player always
// can draw a card at the beginning of his turn.
static void checkPlayer2Turn1(Game game) {
    printf("PLAYER 2 TURN 1\n");
    playerMove move;
    Card card;
    //Check current state
    printf("Checking current state\n");
    check_state(game, 2, 2, 0, 1, 1);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, D, RED, SPADES) == 1);
    
    //Checking the player two can draw a card
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);

    //Checking the player two has the card DRAW_TWO, GREEN, SPADES
    printf("Checking player 2 has a  GREEN SPADES DRAW_TWO\n");
    assert(find_card_in_hand(game, 2, DRAW_TWO, GREEN, SPADES) != NULL);
    card = find_card_in_hand(game, 2, DRAW_TWO, GREEN, SPADES);
    // We know that the player can play this card
    printf("Checking player 2 can play this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    //Check current state
    playMove(game, move);
    check_state(game, 2, 2, 1, 1, 2);
    //Now the player no longer have the card DRAW_TWO, GREEN, SPADES
    //in his hand
    assert(find_card_in_hand(game, 2, DRAW_TWO, GREEN, SPADES) == NULL);
    assert(playerCardCount(game, 2) == 6);
    printf("Player 2 no longer has this card\n");
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    check_state(game, 3, 3, 0, 2, 2);
    printf("-------------------------------------------\n");
}

// Check player3Turn1. Check the case that the player cannot play a card
// that is not in his hand, and he must draw enough cards to end turn.
// Also, after drawing a card, the player cannot play a card.
static void checkPlayer3Turn1(Game game) {
    printf("PLAYER 3 TURN 1\n");
    playerMove move;
    Card card;
    //Check current state
    printf("Checking current state\n");
    check_state(game, 3, 3, 0, 2, 2);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, DRAW_TWO, GREEN, SPADES) == 1);
    //Checking the player three cannot play a card
    printf("Checking player 3 does not have a THREE RED CLUBS\n");
    move.action = PLAY_CARD;
    assert(find_card_in_hand(game, 3, THREE, RED, CLUBS) == NULL);
    printf("The player does not have the card\n");
    Card new = newCard(THREE, RED, CLUBS);
    move.card = new;
    assert(isValidMove(game, move) == FALSE);
    //Checking the player two can draw a card
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Checking player 3 have a D, BLUE, QUESTIONS\n");
    assert(find_card_in_hand(game, 3, D, BLUE, QUESTIONS) != NULL);
    printf("The player have the card\n");
    check_state(game, 3, 3, 1, 2, 2);
    //Checking player 3 cannot end turn because he should draw two cards
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    printf("END_TURN is not valid\n");
    //Checking the player two can draw a card
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Checking player 3 have a E, BLUE, HEARTS\n");
    assert(find_card_in_hand(game, 3, E, BLUE, HEARTS) != NULL);
    printf("The player have the card\n");
    assert(playerCardCount(game, 3) == 9);
    check_state(game, 3, 3, 2, 2, 2);
    printf("The player can draw another card\n");
    //checking player 3 cannot play a card
    move.action = PLAY_CARD;
    assert(isValidMove(game, move) == FALSE);
    printf("PLAY_CARD is not valid\n");
    //Checking player 3 can end turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    //Check current state
    printf("Current player %d", currentPlayer(game));
    check_state(game, 4, 0, 0, 3, 2);
    printf("-------------------------------------------\n");
    destroyCard(new);
}

// Check player0turn2. Check the case that the player cannot end turn 
// without doing anything and 0 is a valid card in most cases.
static void checkPlayer0Turn2(Game game) {
    printf("PLAYER 0 TURN 2\n");
    playerMove move;
    Card card;
    //Checking current state
    printf("Checking current state\n");
    check_state(game, 4, 0, 0, 3, 2);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, DRAW_TWO, GREEN, SPADES) == 1);
    //Checking player cannot end turn now
    assert(getActiveDrawTwos(game) == 0); 
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    printf("END_TURN is not valid\n");
    printf("Checking the player have a ZERO, RED, HEARTS");
    assert(find_card_in_hand(game, 0, ZERO, RED, HEARTS) != NULL);
    printf("The player have the card\n");
    //Checking the player can play this card
    card = find_card_in_hand(game, 0, ZERO, RED, HEARTS);
    move.card = card;
    move.action = PLAY_CARD;
    assert(isValidMove(game, move) == TRUE);
    printf("PLAY_CARD is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 4, 0, 1, 3, 4);
    //Now the player no longer have the card(ZERO, RED, HEARTS)
    //in his hand
    assert(find_card_in_hand(game, 0, ZERO, RED, HEARTS) == NULL);
    assert(playerCardCount(game, 0) == 5);
    assert(handCardCount(game) == 5);
    printf("Player 0 no longer has this card\n");
    //Checking player 3 can end turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 5, 1, 0, 0, 4);
    printf("-------------------------------------------\n");
}

// Check the player1turn2.
static void checkPlayer1Turn2(Game game) {
    printf("PLAYER 1 TURN 2\n");
    playerMove move;
    Card card;
    //Checking current state
    printf("Checking current state\n");
    check_state(game, 5, 1, 0, 0, 4);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, ZERO, RED, HEARTS) == 1);
    printf("Checking the player have a FIVE, RED, DIAMONDS");
    assert(find_card_in_hand(game, 1, FIVE, RED, DIAMONDS) != NULL);
    printf("The player have the card\n");
    //Checking the player can play this card
    card = find_card_in_hand(game, 1, FIVE, RED, DIAMONDS);
    move.card = card;
    move.action = PLAY_CARD;
    assert(isValidMove(game, move) == TRUE);
    printf("PLAY_CARD is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 5, 1, 1, 0, 5);
    //Now the player no longer have the card(FIVE, RED, DIAMONDS)
    //in his hand
    assert(find_card_in_hand(game, 1, FIVE, RED, DIAMONDS) == NULL);
    assert(playerCardCount(game, 1) == 5);
    printf("Player 1 no longer has this card\n");
    //Checking player 3 can end turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 6, 2, 0, 1, 5);
    printf("-------------------------------------------\n");
}

// Check the player2turn2. Check the case that after an A is played, the
// next player turn will be skipped.
static void checkPlayer2Turn2(Game game) {
    printf("PLAYER 2 TURN 2\n");
    playerMove move;
    Card card;
    //Checking current state
    printf("Checking current state\n");
    check_state(game, 6, 2, 0, 1, 5);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, FIVE, RED, DIAMONDS) == 1);
    printf("Checking the player have a A, RED, DIAMONDS");
    assert(find_card_in_hand(game, 2, A, RED, DIAMONDS) != NULL);
    printf("The player have the card\n");
    //Checking the player can play this card
    card = find_card_in_hand(game, 2, A, RED, DIAMONDS);
    move.card = card;
    move.action = PLAY_CARD;
    assert(isValidMove(game, move) == TRUE);
    printf("PLAY_CARD is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 6, 2, 1, 1, 6);
    //Now the player no longer have the card(FIVE, RED, DIAMONDS)
    //in his hand
    assert(find_card_in_hand(game, 2, A, RED, DIAMONDS) == NULL);
    assert(playerCardCount(game, 2) == 5);
    printf("Player 2 no longer has this card\n");
    //Checking player 3 can end turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    //Check current state
    check_state(game, 7, 0, 0, 2, 6);
    printf("-------------------------------------------\n");
}

// Check some extreme cases and other functions like gameWinner.
static void test3_extreme_cases() {
    printf("===========================================\n");
    printf("Test3 Check Extreme Case\n\n");\
    check_for_no_winner();
    check_many_draw_twos();
    win_the_game();
    printf("\n\nTest 3 ALL SUCCESSFUL!!:D\n");
    printf("===========================================\n");
}

// Check the case that no one can play a card and there is only one card
// in the discard pile with the value DRAW_TWO.
static void check_for_no_winner() {
    printf("CASE 1: NO WINNER\n");
    int decksize = 30;
    value values[] = {
        B, B, B, B, B,
        B, B, B, B, B,
        B, B, B, B, B,
        B, B, B, B, B,
        B, B, B, B, B,
        B, B, B, ONE, B
    };
    
    color colors[] = {
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, GREEN, RED
    };
    
    suit suits[] = { 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, DIAMONDS, HEARTS
    };
    
    Game game = newGame(decksize, values, colors, suits);
    sub_player0(game);
    sub_GAME_OVER (game); 
    printf("Try to destroy the game\n");
    destroyGame(game);
    printf("-------------------------------------------\n");
}

// The player 0 should draw two cards but there is only one card on the 
// deck.
static void sub_player0(Game game) {
    //Check current state
    printf("Checking current state\n");
    check_state(game, 0, 0, 0, -1, -1);
    printf("Checking top discard pile\n");
    assert(checkdiscard(game, ONE, GREEN, DIAMONDS) == 1);
    printf("PLAYER 0 TURN 1\n");
    //Player 0 turn 0;
    playerMove move;
    Card card;
    printf("Checking player 0 has a B, RED, HEARTS\n");
    assert(find_card_in_hand(game, 0, B, RED, HEARTS) != NULL);
    card = find_card_in_hand(game, 0, B, RED, HEARTS);
    printf("Player 0 has this card\n");
    // We know that the player cannot play this card
    printf("Checking player 0 cannot play this card\n");
    move.action = PLAY_CARD;
    move.card = card;
    assert(isValidMove(game, move) == FALSE);
    //Checking player 0 cannot end turn
    move.action = END_TURN;
    assert(isValidMove(game, move) == FALSE);
    printf("END_TURN is not valid\n");
    //Checking player 0 can draw a card
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    printf("DRAW_CARD is valid\n");
    playMove(game, move);
    //Check the player 0 now have one more card
    assert(playerCardCount(game, 0) == 8);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move);
    check_state(game, 1, 1, 0, 0, -1);
}

// Check the game is end with no winner.
static void sub_GAME_OVER (Game game) {
    //Check game cards is empty
    printf("Checking gamecards is empty\n");
    assert(getDeckCard(game, 0) == NULL);
    printf("There is no card in deck pile\n"); 
    //Check game end with no winner
    assert(gameWinner(game) == NO_WINNER);
    printf("Game ends with no winners.\n");
    //Check the current point of each player
    int point0 = playerPoints(game, 0); 
    int point1 = playerPoints(game, 1);
    int point2 = playerPoints(game, 2);
    int point3 = playerPoints(game, 3);
    printf(">>>>>>>>>>> PLAYER 0 SCORE : %d <<<<<<<<<<<\n", point0);
    printf(">>>>>>>>>>> PLAYER 1 SCORE : %d <<<<<<<<<<<\n", point1);
    printf(">>>>>>>>>>> PLAYER 2 SCORE : %d <<<<<<<<<<<\n", point2);
    printf(">>>>>>>>>>> PLAYER 3 SCORE : %d <<<<<<<<<<<\n", point3);
}

// Check the case that there is a lot of draw twos on the top of discard
// and the case that the number of consetructive draw_twos is not same 
// as the active daw_twos.
static void check_many_draw_twos() {
    printf("CASE 2: MANY DRAW TWOS\n");
    int decksize = 40;
    value values[] = {
        DRAW_TWO, DRAW_TWO, DRAW_TWO, A, DRAW_TWO,
        THREE, DRAW_TWO, B, DRAW_TWO, C,
        DRAW_TWO, B, DRAW_TWO, E, DRAW_TWO,
        C, DRAW_TWO, B, F, ONE,
        DRAW_TWO, ONE, DRAW_TWO, D, DRAW_TWO,
        THREE, DRAW_TWO, E, DRAW_TWO, FOUR,
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO,
        DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO, DRAW_TWO,
    };
    
    color colors[] = {
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, GREEN, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED
    };
    
    suit suits[] = { 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, DIAMONDS, HEARTS,
        HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, 
        HEARTS, HEARTS, HEARTS, DIAMONDS, HEARTS
    };
    
    Game game = newGame(decksize, values, colors, suits);
    sub_player_turns(game);
    sub_poor_player3(game);
    sub_active(game);
    printf("Try to destroy the game\n");
    destroyGame(game);
    printf("-------------------------------------------\n");
}

// Put several draw_twos at the top of discard pile.
static void sub_player_turns(Game game) {
    assert(checkdiscard(game, DRAW_TWO, GREEN, DIAMONDS) == 1);
    printf("The top discard is DRAW_TWO, GREEN, DIAMONDS\n");
    //Player 0 is going to play a DRAW_TWO
    playerMove move0;
    Card card0;
    assert(find_card_in_hand(game, 0, DRAW_TWO, RED, HEARTS) != NULL);
    card0 = find_card_in_hand(game, 0, DRAW_TWO, RED, HEARTS);
    printf("Player 0 has a DRAW_TWO, RED, HEARTS\n");
    move0.action = PLAY_CARD;
    move0.card = card0;
    assert(isValidMove(game, move0) == TRUE);    
    printf("PLAY_CARD is valid\n");
    playMove(game, move0);
    move0.action = END_TURN;
    assert(isValidMove(game, move0) == TRUE);
    printf("END_TURN is valid\n");
    playMove(game, move0);
    check_state(game, 1, 1, 0, 0, 0);
    //Repeat for player 1 and 2
    playerMove move1;
    Card card1;
    card1 = find_card_in_hand(game, 1, DRAW_TWO, RED, HEARTS);
    move1.action = PLAY_CARD;
    move1.card = card1;
    assert(isValidMove(game, move1) == TRUE);    
    playMove(game, move1);
    move1.action = END_TURN;
    assert(isValidMove(game, move1) == TRUE);
    playMove(game, move1);
    printf("Player 1 moves are valid\n");
    playerMove move2;
    Card card2;
    card2 = find_card_in_hand(game, 2, DRAW_TWO, RED, HEARTS);
    move2.action = PLAY_CARD;
    move2.card = card2;
    assert(isValidMove(game, move2) == TRUE);    
    playMove(game, move2);
    move2.action = END_TURN;
    assert(isValidMove(game, move2) == TRUE);
    printf("Player 2 moves are valid\n");
    playMove(game, move2);
}

// Check the player3 can draw right number of cards
static void sub_poor_player3(Game game) {
    //check the player can draw 6 cards;
    playerMove move;
    Card card;
    printf("There are 3 DRAW_TWOS at the top \n");
    assert(getNumberOfTwoCardsAtTop(game) == 4);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Player 3 moves are valid\n");
}

// Check the case one there is consetructive DRAW_TWOS on the top, but 
// there is only one is active
static void sub_active(Game game) {
    //Player 0 plays a draw two again
    playerMove move;
    Card card;
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, DRAW_TWO, RED, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Player 0 played a DRAW_TWO, RED, HEARTS\n");
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = DRAW_CARD;
    playMove(game, move);
    move.action = END_TURN;
    assert(getActiveDrawTwos(game) == 1);
    assert(isValidMove(game, move) == TRUE);
    printf("Player 1 have to draw 2 cards\n");
}

// Check when one player has an empty hand, the game finish and the 
// gameWinner function can return to the right game winner.
// Also, check the discard pile will be moved to the deckpile correct 
// when there is no card on the deckcard pile.
static void win_the_game() {
    printf("CASE 3: WIN THE GAME\n");
    int decksize = 30;
    value values[] = {
        A, B, A, C, A,
        ONE, A, DRAW_TWO, A, E, 
        A, THREE, A, B, A,
        FOUR, A, ZERO, A, ZERO,
        A, C, C, F,    A, 
        B, FOUR, D,    THREE, A
    };
    
    color colors[] = {
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE, 
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE,
        RED, GREEN, YELLOW, BLUE, PURPLE
    };
    
    suit suits[] = { 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, 
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS 
    };
    
    Game game = newGame(decksize, values, colors, suits);
    sub_keep_playing_card(game);
    sub_repeated(game);
    sub_repeated_again(game);
    sub_update_deckcards(game);
    sub_PLAYER0_WIN(game);
    printf("Try to destroy the game\n");
    destroyGame(game);
    printf("-------------------------------------------\n");
}

//Playing cards until no card to play
static void sub_keep_playing_card(Game game) {
    playerMove move0;
    Card card0;
    move0.action = PLAY_CARD;
    assert(find_card_in_hand(game, 0, A, BLUE, SPADES) != NULL);
    card0 = find_card_in_hand(game, 0,  A, BLUE, SPADES);
    move0.card = card0;
    assert(isValidMove(game, move0) == TRUE);
    printf("Player 0 PLAY_CARD  A, BLUE, SPADES is valid\n");
    playMove(game, move0);
    move0.action = END_TURN;
    assert(isValidMove(game, move0) == TRUE);
    playMove(game, move0);
    printf("END TURN is valid\n");
    
    playerMove move1;
    Card card1;
    move1.action = PLAY_CARD;
    assert(find_card_in_hand(game, 2, A, YELLOW, CLUBS) != NULL);
    card1 = find_card_in_hand(game, 2,  A, YELLOW, CLUBS);
    move1.card = card1;
    assert(isValidMove(game, move1) == TRUE);
    printf("Player 2 PLAY_CARD  A, YELLOW, CLUBS is valid\n");
    playMove(game, move1);
    move1.action = END_TURN;
    assert(isValidMove(game, move1) == TRUE);
    playMove(game, move1);
    printf("END TURN is valid\n");
}

// Repeat the same process
static void sub_repeated(Game game) {
    playerMove move;
    Card card;
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, RED, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 2, A, GREEN, DIAMONDS);
    move.card = card;
    playMove(game, move);
    move.action = END_TURN;
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, PURPLE, QUESTIONS);
    move.card = card;
    playMove(game, move);
    move.action = END_TURN;
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 2, A, RED, HEARTS);
    move.card = card;
    playMove(game, move);
    move.action = END_TURN;
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, YELLOW, CLUBS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Now player 0 has %d cards in hand\n", playerCardCount(game, 0));
}

// Repeat again
static void sub_repeated_again(Game game) {
    playerMove move;
    Card card;
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 2, A, PURPLE, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, GREEN, DIAMONDS);
    move.card = card;
    playMove(game, move);
    move.action = END_TURN;
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 2, A, BLUE, SPADES);
    move.card = card;
    playMove(game, move);
    move.action = END_TURN;
    playMove(game, move);
    
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, RED, HEARTS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);    
    printf("Now player 0 has %d cards in hand\n", playerCardCount(game, 0));
}

// Now player 2 has no card to play and he has to draw a card, after this,
// the deckcard pile is empty
static void sub_update_deckcards(Game game) {
    printf("Checking current state\n");
    check_state(game, 11, 2, 0, 0, 10);

    playerMove move;
    move.card = NULL;
    move.action = DRAW_CARD;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Now the deck pile is updated\n");
    printf("The first card in new deck pile is the same as ");
    printf("last card in previous discard pile\n");
    Card c = getDeckCard(game, 0);
    assert(cardValue(c) == THREE);
    assert(cardColor(c) == BLUE);
    assert(cardSuit(c) == SPADES);
    assert(checkdiscard(game, A, RED, HEARTS) == 1);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Checking there is only one card on the discard pile\n");
    assert(getDiscardPileCard(game, 0) != NULL);
    assert(getDiscardPileCard(game, 1) == NULL);
}

// Check the game winner
static void sub_PLAYER0_WIN(Game game) {
    // This player 3's turn
    check_state(game, 12, 3, 0, 2, 10);
    playerMove move;
    Card card;
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 3, ZERO, PURPLE, QUESTIONS); 
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    move.action = END_TURN;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Player 3 played a ZERO, PURPLE, QUESTIONS\n");
    check_state(game, 13, 0, 0, 3, 12);
    // This is player 0's turn
    move.action = PLAY_CARD;
    card = find_card_in_hand(game, 0, A, PURPLE, QUESTIONS);
    move.card = card;
    assert(isValidMove(game, move) == TRUE);
    playMove(game, move);
    printf("Now player 0 has %d cards in hand\n", playerCardCount(game, 0));
    assert(handCard(game, 0) == NULL);
    //Game Over, player 0 win
    assert(gameWinner(game) == 0);
    printf(">>>>>>>>>>> PLAYER 0 WIN THE GAME <<<<<<<<<<<\n");
}
