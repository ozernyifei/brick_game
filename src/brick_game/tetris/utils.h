#ifndef TETRIS_UTILS_H_
#define TETRIS_UTILS_H_

#define HIGH_SCORE_FILE "highscore.dat"

/**
 * @brief Loads the high score from a file.
 *
 * @param high_score Pointer to store the loaded high score.
 */
void loadHighScore(int* high_score);

/**
 * @brief Saves the high score to a file.
 *
 * @param high_score The high score to save.
 */
void saveHighScore(int high_score);

/**
 * @brief Generates a random number between min and max (inclusive).
 *
 * @param min Minimum value.
 * @param max Maximum value.
 * @return Random integer between min and max.
 */
int getRandomNumber(int min, int max);

unsigned long getCurrentTime();

#endif  // TETRIS_UTILS_H_
