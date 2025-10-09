#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

void velocity_field_normalize(ofm_t *ofm) {
    uint32_t area = ofm->field_area;

    float max_velo = 0.0f;
    float curr_velo = 0.0f;

    float *u_field = ofm->u_field;
    float *v_field = ofm->v_field;

    for (uint32_t i = 0; i < area; i ++) {
        curr_velo = u_field[i]*u_field[i] + v_field[i]*v_field[i];
        max_velo = curr_velo > max_velo ? curr_velo : max_velo;
    }

    max_velo = sqrtf(max_velo);

    for (uint32_t i = 0; i < area; i ++) {
        u_field[i] /= max_velo;
        v_field[i] /= max_velo;
    }
}

void iterate(ofm_t *ofm, float alpha) {
    float *E_x = ofm->E_x;
    float *E_y = ofm->E_y;
    float *E_t = ofm->E_t;

    float *u_field = ofm->u_field;
    float *v_field = ofm->v_field;

    float *u_field_new = calloc(ofm->field_area, sizeof(float));
    memcpy(u_field_new, ofm->u_field, ofm->field_area);

    float *v_field_new = calloc(ofm->field_area, sizeof(float));
    memcpy(v_field_new, ofm->v_field, ofm->field_area);

    float bracketed_term;
    for (int y = 0; y < (int) ofm->field_height; y++) {
        for (int x = 0; x < (int) ofm->field_width; x++) {
            int i = get_index(ofm->field_width, ofm->field_height, x, y);
            float u_avg = local_u(ofm, x, y);
            float v_avg = local_v(ofm, x, y);

            bracketed_term = (E_x[i] * u_avg + E_y[i] * v_avg + E_t[i]) / (alpha*alpha + E_x[i]*E_x[i] + E_y[i]*E_y[i]);
            u_field_new[i] = u_field[i] - E_x[i] * bracketed_term;
            v_field_new[i] = v_field[i] - E_y[i] * bracketed_term;
        }
    }

    free(ofm->u_field);
    free(ofm->v_field);

    ofm->u_field = u_field_new;
    ofm->v_field = v_field_new;
}
