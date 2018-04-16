/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#pragma once
#include <stdio.h>
#include <matrix_core.h>
#include <math.h>
#include <Testy/assert.h>
#include <Testy/testy.h>
#include <vector.h>

TESTY_INIT

double func(double x, double y) {
  return 6*sin(x) - y*y;
}

void fill_matrix(SL_m_Matrix *matrix) {
  for (int y = 0; y < matrix->height; y++) {
    for (int x = 0; x < matrix->width; x++) {
      SL_m_setElementDouble(matrix, x, y, func(x, y));
    }
  }
}

void print_matrix(SL_m_Matrix *matrix) {
  for (int y = 0; y < matrix->height; y++) {
    for (int x = 0; x < matrix->width; x++) {
      printf("%f ", SL_m_getElementDouble(matrix, x, y));
    }
    printf("\n");
  }
  printf("\n");
}

void base_check_matrix(SL_m_Matrix *matrix) {
  for (int y = 0; y < matrix->height; y++) {
    for (int x = 0; x < matrix->width; x++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, x, y), func(x, y));
    }
  }
}

void print_vector(SL_v_Vector *v) {
  for (size_t i = 0; i < v->size; i++) {
    printf("%f ", SL_v_getElementDouble(v, i));
  }
  printf("\n");
}
