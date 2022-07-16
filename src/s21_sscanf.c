#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>

#include "s21_string.h"

int s21_d_sscanf(int star, int k, const char *str, va_list factor, int length, int sys, int *warning);
int s21_un_sscanf(int star, int k, const char *str, va_list factor, int length, int sys, int *warning);
int s21_f_sscanf(int star, int k, const char *str, va_list factor, int length, int *warning);
int s21_c_sscanf(int star, int k, const char *str, va_list factor, int length);
int s21_length_sscanf(const char *format, int i, int *length);
int s21_s_sscanf(int star, int k, const char *str, va_list factor, int length);
int s21_spase(int k, const char *str);
char *s21_width_sscanf(int *i, const char *format, char *copy, const char *str, int k, int *wid);
int s21_specs(int star, int k, char *copy, va_list factor, int length, \
              char format_i, int *warning, int *result);

int s21_sscanf(const char *str, const char *format, ...) {
    int result = 0, i = 0, k = 0, warning = 0, stop = 1, star = 0;
    va_list factor;
    va_start(factor, format);
    while (format[i] && stop) {
        if (format[i] == '%') {
            char *copy = (char*)str;
            int width = 0, length = 0;
            star = 0;
            i++;
            if (format[i] == '*') {
                star = 1;
                i++;
            } else {
                result++;
                copy = s21_width_sscanf(&i, format, copy, str, k, &width);
                i = s21_length_sscanf(format, i, &length);
            }
            k = s21_specs(star, k, copy, factor, length, format[i], &warning, &result);
            if (k == -1) {
                break;
            }
            if (width != 0) {
                free(copy);
            }
            if (warning != 0) {
                stop = 0;
            }
        }
        i++;
    }
    if (warning == 1 && star != 1) {
        result--;
    }
    va_end(factor);
    return result;
}

int s21_specs(int star, int k, char *copy, va_list factor, \
              int length, char format_i, int *warning, int *result) {
    if (format_i == 'd') {
        k = s21_d_sscanf(star, k, copy, factor, length, 10, warning);
    } else if (format_i == 'i') {
        k = s21_d_sscanf(star, k, copy, factor, length, 0, warning);
    } else if (format_i == 'x' || format_i == 'X') {
        k = s21_un_sscanf(star, k, copy, factor, length, 16, warning);
    } else if (format_i == 'o') {
        k = s21_un_sscanf(star, k, copy, factor, length, 8, warning);
    } else if (format_i == 'u') {
        k = s21_un_sscanf(star, k, copy, factor, length, 10, warning);
    } else if (format_i == 'c') {
        k = s21_c_sscanf(star, k, copy, factor, length);
    } else if (format_i == 'p') {
        k = s21_un_sscanf(star, k, copy, factor, length, 15, warning);
    } else if (format_i == 's') {
        k = s21_s_sscanf(star, k, copy, factor, length);
    } else if (format_i == 'f' || format_i == 'e' || format_i == 'E' || format_i == 'g' || format_i == 'G') {
        k = s21_f_sscanf(star, k, copy, factor, length, warning);
    } else if (format_i == 'n' && star != 1) {
        *(int*)va_arg(factor, int*) = k;
        *result = *result - 1;
    } else {
        k = -1;
    }
    return k;
}

char *s21_width_sscanf(int *i, const char *format, char *copy, const char *str, int k, int *wid) {
    k = s21_spase(k, str);
    if (s21_number(format[*i])) {
        char *endptr;
        int width = s21_strtol(&format[*i], &endptr, 10);
        wchar_t buff;
        mbstowcs(&buff, &str[k + width - 1], 1);
        if (format[*i + 1] == 'l' && (format[*i + 2] == 'c' || format[*i + 2] == 's') && (int)buff > 127) {
            width++;
        }
        *i += endptr - &format[*i];
        copy = s21_calloc(k + width + 1);
        s21_strncpy(copy, str, k + width);
        copy[k + width] = '\0';
        *wid = 1;
    }
    return copy;
}

int s21_spase(int k, const char *str) {
    while (str[k] == ' ') {
        k++;
    }
    return k;
}

int s21_length_sscanf(const char *format, int i, int *length) {
    if (format[i] == 'h') {
        *length = 1;
        i++;
    } else if (format[i] == 'l') {
        *length = 2;
        i++;
        if (format[i] == 'l') {
            *length = 3;
            i++;
        }
    } else if (format[i] == 'L') {
        *length = 3;
        i++;
    }
    return i;
}

int s21_d_sscanf(int star, int k, const char *str, va_list factor, int length, int sys, int *warning) {
    k = s21_spase(k, str);
    char *endptr;
    if (length == 0) {
        int e = (int)s21_strtol(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(int*)va_arg(factor, int*) = e;
        }
    } else if (length == 1) {
        short int e = (short int)s21_strtol(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(short int*)va_arg(factor, short int*) = e;
        }
    } else if (length == 2) {
        long int e = s21_strtol(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(long int*)va_arg(factor, long int*) = e;
        }
    } else if (length == 3) {
        long long int e = s21_strtol(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(long long int*)va_arg(factor, long long int*) = e;
        }
    }
    if (str[k] == *endptr) {
        *warning = 1;
    }
    k += endptr - &str[k];
    return k;
}

int s21_un_sscanf(int star, int k, const char *str, va_list factor, int length, int sys, int *warning) {
    k = s21_spase(k, str);
    char *endptr;
    if (sys == 15 && (void*)s21_strtoul(&str[k], &endptr, sys)) {
        sys = 16;
        *(void**)va_arg(factor, void**) = (void*)s21_strtoul(&str[k], &endptr, sys);
    } else if (length == 0) {
        unsigned int e = (unsigned int)s21_strtoul(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(unsigned int*)va_arg(factor, unsigned int*) = e;
        }
    } else if (length == 1) {
        unsigned short int e = (unsigned short int)s21_strtoul(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(unsigned short int*)va_arg(factor, unsigned short int*) = e;
        }
    } else if (length == 2) {
        unsigned long int e = s21_strtoul(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(unsigned long int*)va_arg(factor, unsigned long int*) = e;
        }
    } else if (length == 3) {
        unsigned long long int e = s21_strtoul(&str[k], &endptr, sys);
        if (star != 1 && str[k] != *endptr) {
            *(unsigned long long int*)va_arg(factor, unsigned long long int*) = e;
        }
    }
    if (str[k] == *endptr) {
        *warning = 1;
    }
    k += endptr - &str[k];
    return k;
}

int s21_c_sscanf(int star, int k, const char *str, va_list factor, int length) {
    if (length == 0) {
        if (star != 1) {
            *(char*)va_arg(factor, char*) = str[k];
        }
    } else if (length == 2) {
        wchar_t new;
        mbstowcs(&new, &str[k], 1);
        if (star != 1) {
            *(wchar_t*)va_arg(factor, wchar_t*) = new;
        }
        if ((int)new > 127) {
            k++;
        }
    }
    k++;
    k = s21_spase(k, str);
    return k;
}

int s21_s_sscanf(int star, int k, const char *str, va_list factor, int length) {
    k = s21_spase(k, str);
    int as = k;
    while (str[as] != ' ' && str[as] != '\n' && str[as]) {
        as++;
    }
    if (star == 1) {
        k = as;
    } else {
        if (length == 0) {
            char *buff = (char*)va_arg(factor, char*);
            int r = 0;
            while (str[k] != ' ' && str[k] != '\n' && str[k] && str[k] != '\0') {
                buff[r] = str[k];
                k++;
                r++;
            }
            buff[r] = '\0';
        } else if (length == 2) {
            wchar_t *buff = (wchar_t*)va_arg(factor, wchar_t*);
            int r = 0;
            while (str[k] != ' ' && str[k] != '\n' && str[k] && str[k] != '\0') {
                mbstowcs(&buff[r], &str[k], 1);
                if ((int)buff[r] > 127) {
                    k++;
                }
                k++;
                r++;
            }
            buff[r] = '\0';
        }
    }
    return k;
}

int s21_f_sscanf(int star, int k, const char *str, va_list factor, int length, int *warning) {
    k = s21_spase(k, str);
    char *endptr;
    if (length == 0) {
        float e = s21_strtof(&str[k], &endptr);
        if (star != 1 && str[k] != *endptr) {
            *(float*)va_arg(factor, float*) = e;
        }
    } else if (length == 2) {
        double e = s21_strtod(&str[k], &endptr);
        if (star != 1 && str[k] != *endptr) {
            *(double*)va_arg(factor, double*) = e;
        }
    } else if (length == 3) {
        long double e = s21_strtold(&str[k], &endptr);
        if (star != 1 && str[k] != *endptr) {
            *(long double*)va_arg(factor, long double*) = e;
        }
    }
    if (str[k] == *endptr) {
        *warning = 1;
    }
    k += endptr - &str[k];
    return k;
}
