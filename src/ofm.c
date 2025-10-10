#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "ofm.h"
#include "ofm_helper.h"
#include "math_helper.h"

ofm_t *ofm_init(image_t *img1, image_t *img2, uint32_t width, uint32_t height) {
    ofm_t *ofm = calloc(1, sizeof(ofm_t));
    ofm->u_field = calloc(width * height, sizeof(double));
    ofm->v_field = calloc(width * height, sizeof(double));

    ofm->E_x = intensity_partial_derivative_field(img1, img2, 'x', 20.0f);
    ofm->E_y = intensity_partial_derivative_field(img1, img2, 'y', 20.0f);
    ofm->E_t = intensity_partial_derivative_field(img1, img2, 't', 20.0f);

    double temp = 1.0f / 12.0f;
    double *weights = calloc(9, sizeof(double));

    for (int i = 0; i < 9; i++) {
        weights[i] = temp;
        temp += i % 2 == 0 ? 1.0f / 12.0f : -1.0f / 12.0f;
    }

    weights[4] = 0.0f;

    ofm->local_velocity_weights = weights;
    ofm->weight_width = 3;
    ofm->weight_height = 3;

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

double local_u(ofm_t *ofm, int x, int y) {
    if (x < 0 || y < 0 || x >= (int) ofm->field_width - (int) ofm->weight_width || y >= (int) ofm->field_height - (int) ofm->weight_height) {
        return 0.0f;
    }

    double out = weighted_avg(ofm->u_field, ofm->local_velocity_weights, ofm->field_width, ofm->field_height, ofm->weight_width, ofm->weight_height, x - (int) ofm->weight_width / 2, y - (int) ofm->weight_height / 2);

    return out;
}

double local_v(ofm_t *ofm, int x, int y) {
    if (x < 0 || y < 0 || x >= (int) ofm->field_width - (int) ofm->weight_width || y >= (int) ofm->field_height - (int) ofm->weight_height) {
        return 0.0f;
    }

    double out = weighted_avg(ofm->v_field, ofm->local_velocity_weights, ofm->field_width, ofm->field_height, ofm->weight_width, ofm->weight_height, x - (int) ofm->weight_width / 2, y - (int) ofm->weight_height / 2);

    return out;
}

void velocity_field_normalize(ofm_t *ofm) {
    uint32_t area = ofm->field_area;

    double max_velo = 0.0f;
    double curr_velo = 0.0f;

    double *u_field = ofm->u_field;
    double *v_field = ofm->v_field;

    for (uint32_t i = 0; i < area; i ++) {
        curr_velo = u_field[i]*u_field[i] + v_field[i]*v_field[i];
        max_velo = curr_velo > max_velo ? curr_velo : max_velo;
    }

    max_velo = sqrt(max_velo);

    for (uint32_t i = 0; i < area; i ++) {
        u_field[i] /= max_velo;
        v_field[i] /= max_velo;
    }
}

void iterate(ofm_t *ofm, double alpha) {
    double *E_x = ofm->E_x;
    double *E_y = ofm->E_y;
    double *E_t = ofm->E_t;

    double *u_field = ofm->u_field;
    double *v_field = ofm->v_field;

    double *u_field_new = calloc(ofm->field_area, sizeof(double));
    memcpy(u_field_new, u_field, ofm->field_area * sizeof(double));

    double *v_field_new = calloc(ofm->field_area, sizeof(double));
    memcpy(v_field_new, v_field, ofm->field_area * sizeof(double));

    double frac_numerator;
    double frac_denominator;
    double frac_term;
    for (int y = 0; y < (int) ofm->field_height; y++) {
        for (int x = 0; x < (int) ofm->field_width; x++) {
            int i = get_index(ofm->field_width, ofm->field_height, x, y);

            double u_avg = local_u(ofm, x, y);
            double v_avg = local_v(ofm, x, y);

            frac_numerator = E_x[i] * u_avg + E_y[i] * v_avg + E_t[i];
            frac_denominator = alpha*alpha + E_x[i]*E_x[i] + E_y[i]*E_y[i];
            frac_term = frac_numerator / frac_denominator;

            u_field_new[i] = u_avg - E_x[i] * frac_term;
            v_field_new[i] = v_avg - E_y[i] * frac_term;
        }
    }

    free(ofm->u_field);
    free(ofm->v_field);

    ofm->u_field = u_field_new;
    ofm->v_field = v_field_new;
}
