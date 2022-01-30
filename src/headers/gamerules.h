#ifndef GAMERULES_H_INCLUDE
#define GAMERULES_H_INCLUDE

#define RED 0x52
#define GREEN 0x47
#define BLUE 0x42
#define YELLOW 0x59
#define VIOLET 0x56
#define ORANGE 0x4F
#define PINK 0x50
#define TURQUOISE 0x54

#define PLAYER_LIVES 10
#define CODE_LENGTH 4

/* 8 for super mastermind or 6 */
#define C_PEGS 6

/* this char indicates, that this peg has been accounted for during comparison for black pegs */
#define USED_A 'q'

/* this char indicates, that this peg has been accounted for during comparison for white pegs two different are necessary as otherwise false positives will be indicated */
#define USED_B 'a' 

#define OS "Windows"

extern int available_colors[8];

#endif
