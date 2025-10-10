#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdint.h>

typedef struct {
    double x;
    double y;
} particle_t;

particle_t *particle_init(double x, double y);

#endif
