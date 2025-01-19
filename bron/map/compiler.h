
#ifndef __WACHTER_COMPILER_H
#define __WACHTER_COMPILER_H

#include <stdint.h>


#define MAP_START_POORTEN 0x25


#define ONGEDEFINEERD 0XFF
static const uint8_t ascii_naar_waarde[] = {[0 ... 47] = ONGEDEFINEERD,
                                     [58 ... 64] = ONGEDEFINEERD,
                                     [91 ... 96] = ONGEDEFINEERD,
                                     [123 ... 127] = ONGEDEFINEERD,
                                     [48] = 0x00, // 0 -> 9
                                     [49] = 0x01,
                                     [50] = 0x02,
                                     [51] = 0x03,
                                     [52] = 0x04,
                                     [53] = 0x05,
                                     [54] = 0x06,
                                     [55] = 0x07,
                                     [56] = 0x08,
                                     [57] = 0x09,
                                     [65] = 0x0A, // A -> Z
                                     [66] = 0x0B,
                                     [67] = 0x0C,
                                     [68] = 0x0D,
                                     [69] = 0x0E,
                                     [70] = 0x0F,
                                     [71] = 0x10,
                                     [72] = 0x11,
                                     [73] = 0x12,
                                     [74] = 0x13,
                                     [75] = 0x14,
                                     [76] = 0x15,
                                     [77] = 0x16,
                                     [78] = 0x17,
                                     [79] = 0x18,
                                     [80] = 0x19,
                                     [81] = 0x1A,
                                     [82] = 0x1B,
                                     [83] = 0x1C,
                                     [84] = 0x1D,
                                     [85] = 0x1E,
                                     [86] = 0x1F,
                                     [87] = 0x20,
                                     [88] = 0x21,
                                     [89] = 0x23,
                                     [90] = 0x24,
                                     [97] = 0x25, // a -> z
                                     [98] = 0x26,
                                     [99] = 0x27,
                                     [100] = 0x28,
                                     [101] = 0x29,
                                     [102] = 0x2A,
                                     [103] = 0x2B,
                                     [104] = 0x2C,
                                     [105] = 0x2D,
                                     [106] = 0x2E,
                                     [107] = 0x2F,
                                     [108] = 0x30,
                                     [109] = 0x31,
                                     [110] = 0x32,
                                     [111] = 0x33,
                                     [112] = 0x34,
                                     [113] = 0x35,
                                     [114] = 0x36,
                                     [115] = 0x37,
                                     [116] = 0x38,
                                     [117] = 0x39,
                                     [118] = 0x3A,
                                     [119] = 0x3B,
                                     [120] = 0x3C,
                                     [121] = 0x3D,
                                     [122] = 0x3E};

#endif // __WACHTER_COMPILER_H
