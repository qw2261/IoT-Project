#ifndef _PATH_H
#define _PATH_H
#include "chassis.h"
#include "path0.h"

#define PATH_NUM   6

extern PathInfoTypedef PathInforms[PATH_NUM];

extern bool USE_RED ;
extern bool USE_BLUE;

void PathInit();

#endif