#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"

int process_command();
int command_guess(long x, long y);
int command_mark(long x, long y);
int command_status();
int command_restart();
int command_quit();
int command_help();

#endif
