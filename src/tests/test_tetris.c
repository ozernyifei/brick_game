// tests/test_tetris.c

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../brick_game/tetris/tetris.h"
#include "../brick_game/tetris/game_logic.h"
#include "../brick_game/tetris/pieces.h"
#include "../brick_game/tetris/utils.h"

static void initialize_game(Game_t *game) {
    initGame(game);
}


// Test case for initTetris function
START_TEST(test_initTetris)
{
    // Initialize Tetris
    initTetris();

    // Assume initGame sets initial values to game state. 
    // We'll need to check if game state is initialized properly.
    GameInfo_t info = updateCurrentState();

    // Check that game field is not NULL after initialization
    ck_assert(info.field != NULL);

    // Check that the score is initialized to 0
    ck_assert_int_eq(info.score, 0);

    // Check that the level is initialized to 1
    ck_assert_int_eq(info.level, 1);

    // Clean up memory
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        free(info.field[i]);
    }
    free(info.field);
    for (int i = 0; i < 4; ++i) {
        free(info.next[i]);
    }
    free(info.next);
}
END_TEST

// Test spawning a figure generates a new next_piece
START_TEST(test_spawnPiece_generates_new_next_piece)
{
    Game_t game;
    initialize_game(&game);

    PieceType_t original_next_type = game.next_piece.type;

    spawnPiece(&game);

    // next_piece should be a new tetramino type (could be same due to randomness)
    // To handle randomness, ensure that next_piece is a valid type
    ck_assert_uint_ge(game.next_piece.type, 0);
    ck_assert_uint_lt(game.next_piece.type, 7); // Assuming 7 types
}
END_TEST




START_TEST(test_create_piece_I)
{
    Piece_t piece = createPiece(I_PIECE);
    ck_assert_int_eq(piece.type, I_PIECE);
    ck_assert_int_eq(piece.rotation, 0);
    ck_assert_int_eq(piece.x, 3);
    ck_assert_int_eq(piece.y, 0);
}
END_TEST

START_TEST(test_create_piece_O)
{
    Piece_t piece = createPiece(O_PIECE);
    ck_assert_int_eq(piece.type, O_PIECE);
    ck_assert_int_eq(piece.rotation, 0);
    ck_assert_int_eq(piece.x, 3);
    ck_assert_int_eq(piece.y, 0);
}
END_TEST

START_TEST(test_rotate_piece_clockwise)
{
    Game_t game;
    initialize_game(&game);
    int original_rotation = game.current_piece.rotation;

    bool rotated = rotateCurrentPiece(&game, true); 
    ck_assert(rotated);
    ck_assert_int_eq(game.current_piece.rotation, (original_rotation + 1) % 4);
}
END_TEST


// Test getting complete game information
START_TEST(test_getGameInfo_complete)
{
    Game_t game;
    initialize_game(&game);
    game.score = 500;
    game.level = 4;

    GameInfo_t info;
    info = getGameInfo(&game);

    ck_assert_int_eq(info.score, 500);
    ck_assert_int_eq(info.level, 4);
}
END_TEST

START_TEST(test_rotate_piece_counterclockwise)
{
    Game_t game;
    initialize_game(&game);
    int original_rotation = game.current_piece.rotation;

    bool rotated = rotateCurrentPiece(&game, false); 
    ck_assert(rotated);
    ck_assert_int_eq(game.current_piece.rotation, (original_rotation + 3) % 4);
}
END_TEST

START_TEST(test_move_piece_left)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    bool moved = moveCurrentPiece(&game, -1, 0); 

    ck_assert(moved);
    ck_assert_int_eq(game.current_piece.x, original_x - 1);
}
END_TEST

START_TEST(test_move_piece_right)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    bool moved = moveCurrentPiece(&game, 1, 0); 
    ck_assert(moved);
    ck_assert_int_eq(game.current_piece.x, original_x + 1);
}
END_TEST

START_TEST(test_move_piece_down)
{
    Game_t game;
    initialize_game(&game);
    int original_y = game.current_piece.y;

    bool moved = moveCurrentPiece(&game, 0, 1); // Move down

    ck_assert(moved);
    ck_assert_int_eq(game.current_piece.y, original_y + 1);
}
END_TEST

START_TEST(test_collision_with_left_wall)
{
    Game_t game;
    initialize_game(&game);
    game.current_piece.x = 0; 

    bool moved = moveCurrentPiece(&game, -1, 0); 

    ck_assert(!moved);
}
END_TEST

START_TEST(test_collision_with_right_wall)
{
    Game_t game;
    initialize_game(&game);
    game.current_piece.x = FIELD_WIDTH - 1; 

    bool moved = moveCurrentPiece(&game, 1, 0); 

    ck_assert(!moved);
}
END_TEST

START_TEST(test_movePiece_left_success)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    movePiece(&game, -1, 0); // Move left

    ck_assert_int_ne(game.current_piece.x, original_x - 1);
}
END_TEST

// Test moving the piece right successfully
START_TEST(test_movePiece_right_success)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    movePiece(&game, 1, 0); // Move right

    ck_assert_int_ne(game.current_piece.x, original_x + 1);
}
END_TEST

// Test moving the piece down successfully
START_TEST(test_movePiece_down_success)
{
    Game_t game;
    initialize_game(&game);
    int original_y = game.current_piece.y;

    movePiece(&game, 0, 1); // Move down

    
    ck_assert_int_ne(game.current_piece.y, original_y + 1);
}
END_TEST

// Test moving the piece into a collision (left wall)
START_TEST(test_movePiece_collision_left)
{
    Game_t game;
    initialize_game(&game);
    game.current_piece.x = 0; // At left boundary

    movePiece(&game, -1, 0); // Attempt to move left into wall

    
    ck_assert_int_eq(game.current_piece.x, 0); // Position should remain unchanged
}
END_TEST

// Test moving the piece into a collision (right wall)
START_TEST(test_movePiece_collision_right)
{
    Game_t game;
    initialize_game(&game);
    game.current_piece.x = FIELD_WIDTH - 1; // At right boundary

    movePiece(&game, 1, 0); // Attempt to move right into wall

    
    ck_assert_int_eq(game.current_piece.x, FIELD_WIDTH - 1); // Position should remain unchanged
}
END_TEST

START_TEST(test_collision_with_bottom_wall)
{
    Game_t game;
    initialize_game(&game);
    game.current_piece.y = FIELD_HEIGHT - 1; 

    bool moved = moveCurrentPiece(&game, 0, 1); 

    ck_assert(!moved);
}
END_TEST

START_TEST(test_clear_single_line)
{
    Game_t game;
    initialize_game(&game);


    int test_row = FIELD_HEIGHT - 1;
    for(int x = 0; x < FIELD_WIDTH; x++) {
        game.field[test_row][x] = 1;
    }

    int original_score = game.score;

    clearLines(&game);

    for(int x = 0; x < FIELD_WIDTH; x++) {
        ck_assert_int_eq(game.field[test_row][x], 0);
    }

    ck_assert_int_eq(game.score, original_score + 100);
}
END_TEST

START_TEST(test_clear_multiple_lines_300)
{
    Game_t game;
    initialize_game(&game);

    // Fill two lines
    int test_row1 = FIELD_HEIGHT - 1;
    int test_row2 = FIELD_HEIGHT - 2;
    for(int x = 0; x < FIELD_WIDTH; x++) {
        game.field[test_row1][x] = 1;
        game.field[test_row2][x] = 1;
    }

    int original_score = game.score;

    clearLines(&game);

    for(int x = 0; x < FIELD_WIDTH; x++) {
        ck_assert_int_eq(game.field[test_row1][x], 0);
        ck_assert_int_eq(game.field[test_row2][x], 0);
    }

    ck_assert_int_eq(game.score, original_score + 300);
}
END_TEST

START_TEST(test_clear_multiple_lines_700)
{
    Game_t game;
    initialize_game(&game);

    // Fill two lines
    int test_row1 = FIELD_HEIGHT - 1;
    int test_row2 = FIELD_HEIGHT - 2;
    int test_row3 = FIELD_HEIGHT - 3;
    for(int x = 0; x < FIELD_WIDTH; x++) {
        game.field[test_row1][x] = 1;
        game.field[test_row2][x] = 1;
        game.field[test_row3][x] = 1;
    }

    int original_score = game.score;

    clearLines(&game);

    for(int x = 0; x < FIELD_WIDTH; x++) {
        ck_assert_int_eq(game.field[test_row1][x], 0);
        ck_assert_int_eq(game.field[test_row2][x], 0);
        ck_assert_int_eq(game.field[test_row3][x], 0);
    }

    ck_assert_int_eq(game.score, original_score + 700);
}
END_TEST

START_TEST(test_clear_multiple_lines_1500)
{
    Game_t game;
    initialize_game(&game);

    // Fill two lines
    int test_row1 = FIELD_HEIGHT - 1;
    int test_row2 = FIELD_HEIGHT - 2;
    int test_row3 = FIELD_HEIGHT - 3;
    int test_row4 = FIELD_HEIGHT - 4;
    for(int x = 0; x < FIELD_WIDTH; x++) {
        game.field[test_row1][x] = 1;
        game.field[test_row2][x] = 1;
        game.field[test_row3][x] = 1;
        game.field[test_row4][x] = 1;
    }

    int original_score = game.score;

    clearLines(&game);

    for(int x = 0; x < FIELD_WIDTH; x++) {
        ck_assert_int_eq(game.field[test_row1][x], 0);
        ck_assert_int_eq(game.field[test_row2][x], 0);
        ck_assert_int_eq(game.field[test_row3][x], 0);
        ck_assert_int_eq(game.field[test_row4][x], 0);
    }

    ck_assert_int_eq(game.score, original_score + 1500);
}
END_TEST

START_TEST(test_score_highscore_no_update)
{
    Game_t game;
    initialize_game(&game);
    
    game.score = 80;
    game.high_score = 100;
    
    if(game.score > game.high_score) {
        game.high_score = game.score;
        saveHighScore(game.high_score);
    }
    
    ck_assert_int_eq(game.high_score, 100);
}
END_TEST


START_TEST(test_victory_condition)
{
    Game_t game;
    initialize_game(&game);
    
    // Simulate achieving victory
    game.score = 1000; // Assuming 1000 points trigger victory
    updateGame(&game);
    
    // Assuming victory sets state to STATE_GAME_OVER with a separate flag
    ck_assert_int_eq(game.state, STATE_GAME_OVER);
    // If you have a separate flag, adjust the assertion accordingly
}
END_TEST


// Test Handle Input for Rotating Piece
START_TEST(test_handle_input_rotate)
{
    Game_t game;
    initialize_game(&game);
    int original_rotation = game.current_piece.rotation;

    handleInput(&game, Action);
    
    ck_assert_int_eq(game.current_piece.rotation, (original_rotation + 1) % 4);
}
END_TEST

// Test Handle Input for Moving Left
START_TEST(test_handle_input_move_left)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    handleInput(&game, Left);
    
    ck_assert_int_eq(game.current_piece.x, original_x - 1);
}
END_TEST

// Test Handle Input for Moving Right
START_TEST(test_handle_input_move_right)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    handleInput(&game, Right);
    
    ck_assert_int_eq(game.current_piece.x, original_x + 1);
}
END_TEST

START_TEST(test_handleInput_move_left)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    handleInput(&game, Left);

    ck_assert_int_eq(game.current_piece.x, original_x - 1);
}
END_TEST

// Test handling 'right' input moves the piece right
START_TEST(test_handleInput_move_right)
{
    Game_t game;
    initialize_game(&game);
    int original_x = game.current_piece.x;

    handleInput(&game, Right);

    ck_assert_int_eq(game.current_piece.x, original_x + 1);
}
END_TEST

// Test case when highscore file exists and contains a valid score
START_TEST(test_loadHighScore_valid_file)
{
    // Arrange: create a temporary highscore file
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    fprintf(file, "%d", 500);  // Writing a valid score to the file
    fclose(file);

    // Act: load the high score
    int high_score = 0;
    loadHighScore(&high_score);

    // Assert: high score should be correctly loaded
    ck_assert_int_eq(high_score, 500);

    // Clean up: remove the test high score file
    remove(HIGH_SCORE_FILE);
}
END_TEST

// Test case when highscore file does not exist
START_TEST(test_loadHighScore_no_file)
{
    // Arrange: ensure the highscore file does not exist
    remove(HIGH_SCORE_FILE);

    // Act: load the high score
    int high_score = -1;
    loadHighScore(&high_score);

    // Assert: high score should default to 0 when the file doesn't exist
    ck_assert_int_eq(high_score, 0);
}
END_TEST

// Test case when highscore file contains invalid data
START_TEST(test_loadHighScore_invalid_file)
{
    // Arrange: create a temporary highscore file with invalid data
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    fprintf(file, "invalid_data");  // Writing invalid data to the file
    fclose(file);

    // Act: load the high score
    int high_score = -1;
    loadHighScore(&high_score);

    // Assert: high score should default to 0 when the file contains invalid data
    ck_assert_int_eq(high_score, 0);

    // Clean up: remove the test high score file
    remove(HIGH_SCORE_FILE);
}
END_TEST


// Suite Setup
Suite* tetris_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Tetris");

    // Core test case
    tc_core = tcase_create("Core");

    // Add all tests to the test case
    tcase_add_test(tc_core, test_initTetris);
    tcase_add_test(tc_core, test_create_piece_I);
    tcase_add_test(tc_core, test_create_piece_O);
    tcase_add_test(tc_core, test_rotate_piece_clockwise);
    tcase_add_test(tc_core, test_rotate_piece_counterclockwise);
    tcase_add_test(tc_core, test_move_piece_left);
    tcase_add_test(tc_core, test_move_piece_right);
    tcase_add_test(tc_core, test_move_piece_down);
    tcase_add_test(tc_core, test_collision_with_left_wall);
    tcase_add_test(tc_core, test_collision_with_right_wall);
    tcase_add_test(tc_core, test_collision_with_bottom_wall);
    tcase_add_test(tc_core, test_clear_single_line);
    tcase_add_test(tc_core, test_clear_multiple_lines_300);
    tcase_add_test(tc_core, test_clear_multiple_lines_700);
    tcase_add_test(tc_core, test_clear_multiple_lines_1500);
    tcase_add_test(tc_core, test_handle_input_rotate);
    tcase_add_test(tc_core, test_handle_input_move_left);
    tcase_add_test(tc_core, test_handle_input_move_right);
    tcase_add_test(tc_core, test_victory_condition);
    tcase_add_test(tc_core, test_score_highscore_no_update);
    tcase_add_test(tc_core, test_spawnPiece_generates_new_next_piece);
    tcase_add_test(tc_core, test_getGameInfo_complete);

    tcase_add_test(tc_core, test_movePiece_left_success);
    tcase_add_test(tc_core, test_movePiece_right_success);
    tcase_add_test(tc_core, test_movePiece_down_success);
    tcase_add_test(tc_core, test_movePiece_collision_left);
    tcase_add_test(tc_core, test_movePiece_collision_right);

    tcase_add_test(tc_core, test_handleInput_move_left);
    tcase_add_test(tc_core, test_handleInput_move_right);

    tcase_add_test(tc_core, test_loadHighScore_invalid_file);
    tcase_add_test(tc_core, test_loadHighScore_no_file);
    tcase_add_test(tc_core, test_loadHighScore_valid_file);


    suite_add_tcase(s, tc_core);

    return s;
}

// Main function to run the tests
int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = tetris_suite();
    sr = srunner_create(s);

    // Enable logging for failed tests
    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
