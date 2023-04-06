#ifndef _FONT_H_
#define _FONT_H_

#pragma GCC diagnostic ignored "-Wmissing-braces"

#define USE_ONCHIP_FLASH_FONT 1
#define hz16_num 50

struct typFNT_GB162
{
    unsigned char Index[2];
    char Msk[32];
};

struct typFNT_GB242
{
    unsigned char Index[2];
    char Msk[72];
};

extern const unsigned char asc16[];
extern const unsigned char sz32[];
extern const struct typFNT_GB162 hz16[];

#endif
