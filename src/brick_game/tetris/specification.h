#ifndef SPECIFICATION_H_
#define SPECIFICATION_H_

#include <stdbool.h>

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

#endif  // SPECIFICATION_H_
