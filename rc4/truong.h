#ifndef TRUONG_H
#define TRUONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <termios.h>

#if defined(__GNUC__)
#define export __attribute__((visibility("default")))
#else
#define export
#endif

export void usage(const char *);
export bool echo(bool);
export char *readkey(const char *prompt);

#endif