#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

long int s21_strtol(const char *string, char **endptr, int basis) {
  long int soul = 0, znak = 1, q = 0;
  int flag = 0;
  char *ptr = (char *)string;
  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '-') {
    znak = -1;
    ptr++;
  } else if (*ptr == '+') {
    ptr++;
  }
  if (basis == 0) {
    if (*ptr == '0') {
      if (*(ptr + 1) == 'x' || *(ptr + 1) == 'X') {
        if (s21_number(*(ptr + 2)) || s21_letter(*(ptr + 2))) {
          basis = 16;
          ptr += 2;
        }
      } else if (s21_number(*(ptr + 1))) {
        basis = 8;
        ptr += 1;
      }
    } else {
      basis = 10;
    }
  }
  while (s21_number(*ptr) || s21_letter(*ptr)) {
    flag = 1;
    if (s21_number(*ptr)) {
      q = (*ptr - 48);
    } else if (*ptr >= 'a') {
      q = (*ptr + 10 - 97);
      if (q >= basis) break;
    } else {
      q = (*ptr + 10 - 65);
      if (q >= basis) break;
    }
    soul = soul * basis + q;
    ptr++;
  }
  if (*(ptr - 1) == '-') {
    ptr--;
  }
  *endptr = (flag) ? ptr : (char *)string;
  return soul * znak;
}

unsigned long int s21_strtoul(const char *string, char **endptr, int basis) {
  unsigned long int soul = 0, znak = 1, q = 0;
  int flag = 0;
  char *ptr = (char *)string;

  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '-') {
    znak = -1;
    ptr++;
  } else if (*ptr == '+') {
    ptr++;
  }
  if (basis == 16) {
    if (*ptr == '0' && (*(ptr + 1) == 'x' || *(ptr + 1) == 'X')) {
      if (s21_number(*(ptr + 2)) || s21_letter(*(ptr + 2))) {
        ptr += 2;
      }
    }
  }
  if (basis == 8) {
    if (*ptr == '0' && s21_number(*(ptr + 1))) {
      ptr++;
    }
  }
  while (s21_number(*ptr) || s21_letter(*ptr)) {
    flag = 1;
    if (s21_number(*ptr)) {
      q = (*ptr - 48);
    } else if (*ptr >= 'a') {
      q = (*ptr + 10 - 97);
      if ((int)q >= basis) break;
    } else {
      q = (*ptr + 10 - 65);
      if ((int)q >= basis) break;
    }
    soul = soul * basis + q;
    ptr++;
  }
  if (*(ptr - 1) == '-') {
    ptr--;
  }
  *endptr = (flag) ? ptr : (char *)string;
  return soul * znak;
}

long double s21_strtold(const char *str, char **end) {
  long double result = 0;
  int k = 0, e = 0;
  int znak = 1, znake = 1, flag = 0;;
  while (str[k] == ' ') {
    k++;
  }
  if (str[k] == '-' && (s21_number(str[k + 1]) || str[k + 1] == '.')) {
    znak = -1;
    k++;
    flag = 1;
  } else if (str[k] == '+' && (s21_number(str[k + 1]) || str[k + 1] == '.')) {
    k++;
    flag = 1;
  }
  if (s21_number(str[k]) || str[k] == '.') {
    while (s21_number(str[k])) {
      result = result * 10 + (str[k] - 48);
      k++;
      flag = 0;
    }
    if (str[k] == '.' && s21_number(str[k + 1])) {
      k++;
      int mnoj = 0;
      while (s21_number(str[k])) {
        result = result * 10 + (str[k] - 48);
        mnoj++;
        k++;
      }
      for (int n = 0; n < mnoj; n++) {
        result /= 10;
      }
    }
    if (str[k] == '.' && flag == 1) {
      k--;
    }
    if ((str[k] == 'e' || str[k] == 'E') && (str[k + 1] == '-' \
    || str[k + 1] == '+' || s21_number(str[k + 1]))) {
      k++;
      flag = 0;
      if (str[k] == '-' && s21_number(str[k + 1])) {
        znake = -1;
        k++;
      } else if (str[k] == '+' && s21_number(str[k + 1])) {
        k++;
      }
      if (s21_number(str[k])) {
        while (s21_number(str[k])) {
          e = e * 10 + (str[k] - 48);
          k++;
          flag = 1;
        }
      }
      for (int n = 0; n < e; n++) {
        if (znake == 1) {
          result *= 10;
        } else {
          result /= 10;
        }
      }
      if (flag == 0) {
        k--;
      }
    }
  }
  *end = (char*)&str[k];
  return result * znak;
}

float s21_strtof(const char *str, char **end) {
  float result = (float)s21_strtold(str, end);
  return result;
}

double s21_strtod(const char *str, char **end) {
  double result = (double)s21_strtold(str, end);
  return result;
}
