#include "../headers/misc.h"
#include <stdio.h>
#include <sys/time.h>

int get_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec*1000 + t.tv_usec/1000;
}