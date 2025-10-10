#include <stdlib.h>

#include "particle.h"

particle_t *particle_init(double x, double y) {
    particle_t *particle = calloc(1, sizeof(particle_t));
    particle->x = x;
    particle->y = y;

    return particle;
}
