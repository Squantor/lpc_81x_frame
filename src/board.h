/*
    Main board definitions include
*/
#ifndef BOARD_H_
#define BOARD_H_

#if defined(lpcxpresso)
    #include "lpcxpresso.h"
#elif defined(breadboard)
    #include "breadboard.h"
#else
    #error Unknown board!
#endif

#endif
