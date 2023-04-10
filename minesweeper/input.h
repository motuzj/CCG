#ifndef INPUT_H
#define INPUT_H

#include "game.h"

int process_input();
int getch();
int command_guess(long x, long y);
int command_flag(long x, long y);
int command_status();
int command_restart();
int command_quit();
int command_help();

#endif
