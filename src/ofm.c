#include <stdlib.h>
#include <stdio.h>

#include "ofm.h"
#include "ofm_helper.h"
#include "math_helper.h"

ofm_t *ofm_init(image_t *img1, image_t *img2, uint32_t width, uint32_t height) {
    ofm_t *ofm = calloc(1, sizeof(ofm_t));
    ofm->u_field = calloc(width * height, sizeof(float));
    ofm->v_field = calloc(width * height, sizeof(float));

    ofm->E_x = intensity_partial_derivative_field(img1, img2, 'x', 20.0f);
    ofm->E_y = intensity_partial_derivative_field(img1, img2, 'y', 20.0f);
    ofm->E_t = intensity_partial_derivative_field(img1, img2, 't', 20.0f);

    float temp = 1.0f / 12.0f;
    float *weights = calloc(9, sizeof(float));

    for (int i = 0; i < 9; i++) {
        weights[i] = temp;
        temp += i % 2 == 0 ? 1.0f / 12.0f : -1.0f / 12.0f;
    }

    weights[4] = 0.0f;

    ofm->local_velocity_weights = weights;

    ofm->field_width = width;
    ofm->field_height = height;
    ofm->field_area = width * height;

    return ofm;
}

void ofm_free(ofm_t **ofm) {
    ofm_t *temp = *ofm;

    free(temp->u_field);
    free(temp->v_field);

    free(temp->E_x);
    free(temp->E_y);
    free(temp->E_t);

    free(temp->local_velocity_weights);

    free(temp);
    *ofm = NULL;
}

float local_u(ofm_t *ofm, int x, int y) {
    if (x < 0 || y < 0 || x >= (int) ofm->field_width - (int) ofm->weight_width || y >= (int) ofm->field_height - (int) ofm->weight_height) {
        fprintf(stderr, "DEBUG: calculating local u requires indexing out of \
                bounds");
        return 0.0f;
    }

    float out = weighted_avg(ofm->u_field, ofm->local_velocity_weights, ofm->field_width, ofm->field_height, ofm->weight_width, ofm->weight_height, x, y);

    return out;
}

float local_v(ofm_t *ofm, int x, int y) {
    if (x < 0 || y < 0 || x >= (int) ofm->field_width - (int) ofm->weight_width || y >= (int) ofm->field_height - (int) ofm->weight_height) {
        fprintf(stderr, "DEBUG: calculating local u requires indexing out of \
                bounds");
        return 0.0f;
    }

    float out = weighted_avg(ofm->v_field, ofm->local_velocity_weights, ofm->field_width, ofm->field_height, ofm->weight_width, ofm->weight_height, x, y);

    return out;
}

void iterate(ofm_t *ofm) {
    uint32_t area = ofm->field_width * ofm->field_height;

    for (uint32_t i = 0; i < area; i++) {
        ofm->u_field[i] = 0.0f;
    }
}
