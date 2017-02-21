#ifndef ARIA_MODE_H

#define ARIA_MODE_H

#include "aria.h"
#include <stdio.h>

#define CtoH(x) x>='a'?(x-0x57):(x>='A'?(x-0x37):(x-0x30))

void CBCKat();
void CBCMct();
void CBCMmt();

void ECBKat();
void ECBMct();
void ECBMmt();

void CTRKat();
void CTRMct();
void CTRMmt();

#endif