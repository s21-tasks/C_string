#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <wchar.h>
#include <stdlib.h>

#include "s21_string.h"

static int s21_spec(char form, int n, char *str, va_list factor, \
                    int length, int precision, int width, char *flags);
static int s21_d_sprintf(char *str, va_list factor, int n, \
                         int length, int precision, int width, char *flags);
static int s21_f_sprintf(char *str, va_list factor, int n, int length, \
                  int precision, int width, char *flags, char e);
static int s21_s_sprintf(char *str, va_list factor, int n, \
                         int precision, int width, char *flags, int length);
static int s21_c_sprintf(char *str, va_list factor, int n, int width, char *flags, int length);
static int s21_length_sprintf(const char *format, int i, int *length);
static int s21_precision_sprintf(int *precision, const char *format, int i, va_list factor);
static int s21_width_sprintf(int *width, const char *format, int i, va_list factor);
static int s21_shift(char *str, int minus, int i, int n, int width, char c, char *flags);
static int s21_flags_sprintf(const char *format, char *flags, int i);
static int s21_minus_sprintf(int *n, int *minus, char *str, long double a, char *flags);
static int s21_e_sprintf(long double bb, char *str, int precision, int n, char e, char *flags);
static int s21_g_sprintf(char *str, va_list factor, int n, int length, \
                         int precision, int width, char *flags, char form);
static int s21_un_sprintf(char *str, va_list factor, int n, int length, \
                   int precision, int width, char *flags, int sys);
static int s21_f_precision(int *precision, int der, long double *bb, long double *aa, char *flags);
static int s21_inf_nan(int *i, int *n, char *str, int *inf, long double bb, char *flags);
static int s21_e_to_char(char *flags, int E, char *str, int i, char e);
static int s21_e_precision(char e, long double *bb, int E);
static long long int s21_pyramid_d(va_list factor, int length);
static unsigned long long int s21_pyramid_un(va_list factor, int length, int sys);
static int s21_char(char *str, va_list factor, int n, int precision, int width, char *flags);
static int s21_wchart(char *str, va_list factor, int n, int precision, int width, char *flags);
static int s21_string_null(int precision, char * str, int n);

int s21_sprintf(char *str, const char *format, ...) {
    int i = 0, n = 0, stop = 0;
    va_list factor;
    va_start(factor, format);
    while (format[i] && n != -1) {
        if (format[i] == '%') {
            int length = 0, precision = -1, width = 0;
            char flags[6];
            i++;
            if (format[i] == '%') {
                str[n] = format[i];
                n++;
                str[n] = '\0';
            }
            i = s21_flags_sprintf(format, flags, i);
            i = s21_width_sprintf(&width, format, i, factor);
            i = s21_precision_sprintf(&precision, format, i, factor);
            i = s21_length_sprintf(format, i, &length);
            n = s21_spec(format[i], n, str, factor, length, precision, width, flags);
            if (flags[5] == 'S') {
                str[stop] = '\0';
                n = -1;
            }
            i++;
        } else {
            stop = n;
            while (format[i] != '%' && format[i]) {
                str[n] = format[i];
                n++;
                i++;
            }
            str[n] = '\0';
        }
    }
    va_end(factor);
    return n;
}

static int s21_flags_sprintf(const char *format, char *flags, int i) {
    int t = 1;
    for (int k = 0; k < 6; k++) flags[k] = '\0';
    while (t != 0 && t < 6) {
        char form = format[i];
        if (form == '-' || form == '+' || form == ' ' || form == '#' || form == '0') {
            flags[t - 1] = form;
            i++;
            t++;
        } else {
            t = 0;
        }
    }
    return i;
}

static int s21_width_sprintf(int *width, const char *format, int i, va_list factor) {
    if (s21_number(format[i])) {
        char *endptr;
        *width = s21_strtol(&format[i], &endptr, 10);
        i += endptr - &format[i];
    } else if (format[i] == '*') {
        *width = va_arg(factor, int);
        i++;
    }
    return i;
}

static int s21_precision_sprintf(int *precision, const char *format, int i, va_list factor) {
    if (format[i] == '.') {
        i++;
        if (format[i] == '*') {
            *precision = va_arg(factor, int);
            i++;
        } else {
            char *endptr;
            *precision = s21_strtol(&format[i], &endptr, 10);
            i += endptr - &format[i];
        }
    }
    return i;
}

static int s21_length_sprintf(const char *format, int i, int *length) {
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

static int s21_spec(char form, int n, char *str, va_list factor, int length, \
                    int precision, int width, char *flags) {
    if (form == 'd' || form == 'i') {
        n = s21_d_sprintf(str, factor, n, length, precision, width, flags);
    } else if (form == 'f') {
        n = s21_f_sprintf(str, factor, n, length, precision, width, flags, 'T');
    } else if (form == 'e') {
        n = s21_f_sprintf(str, factor, n, length, precision, width, flags, 'e');
    } else if (form == 'E') {
        n = s21_f_sprintf(str, factor, n, length, precision, width, flags, 'E');
    } else if (form == 'g' || form == 'G') {
        n = s21_g_sprintf(str, factor, n, length, precision, width, flags, form);
    } else if (form == 'u') {
        n = s21_un_sprintf(str, factor, n, length, precision, width, flags, 10);
    } else if (form == 'o') {
        n = s21_un_sprintf(str, factor, n, length, precision, width, flags, 8);
    } else if (form == 'x') {
        n = s21_un_sprintf(str, factor, n, length, precision, width, flags, 16);
    } else if (form == 'X') {
        n = s21_un_sprintf(str, factor, n, length, precision, width, flags, 16 + 1);
    } else if (form == 'c') {
        n = s21_c_sprintf(str, factor, n, width, flags, length);
    } else if (form == 's') {
        n = s21_s_sprintf(str, factor, n, precision, width, flags, length);
    } else if (form == 'n') {
        *va_arg(factor, int*) = n;
    } else if (form == 'p') {
        n = s21_un_sprintf(str, factor, n, length, precision, width, flags, 18);
    }
    return n;
}

static int s21_d_sprintf(char *str, va_list factor, int n, int length, \
                         int precision, int width, char *flags) {
    int minus = 0, i = 0;
    long long int a = s21_pyramid_d(factor, length);
    if (a == -9223372036854775807 - 1) {
        const char buf[] = "-9223372036854775808";
        s21_strcat(str, buf);
        i = n + 1;
        n += 20;
    } else {
        a *= s21_minus_sprintf(&n, &minus, str, (long double)a, flags);
        i = n;
        if (precision != 0 || a != 0) {
            n = s21_double_to_char(str, (long double)a, n, 10);
        }
    }
    n = s21_shift(str, 0, i, n, precision, '0', s21_NULL);
    if (precision != width && width != n - i) {
        n = s21_shift(str, minus, i, n, width, ' ', flags);
    }
    str[n] = '\0';
    return n;
}

static long long int s21_pyramid_d(va_list factor, int length) {
    long long int a = 0;
    if (length == 0) {
        a = (long long int)va_arg(factor, int);
    } else if (length == 1) {
        a = (long long int)(short int)va_arg(factor, int);
    } else if (length == 2) {
        a = (long long int)va_arg(factor, long int);
    } else if (length == 3) {
        a = (long long int)va_arg(factor, long long int);
    }
    return a;
}

static int s21_un_sprintf(char *str, va_list factor, int n, int length, \
                          int precision, int width, char *flags, int sys) {
    int i = n;
    int k = n;
    unsigned long long int a = s21_pyramid_un(factor, length, sys);
    if ((s21_strchr(flags, (int)'#') && (sys == 17 || sys == 16) && a != 0)) {
        str[n] = '0';
        if (sys == 17) {
            str[n + 1] = 'X';
        } else if (sys == 16) {
            str[n + 1] = 'x';
        }
        n += 2;
        i = n;
    } else if (s21_strchr(flags, (int)'#') && sys == 8 && a != 0) {
        str[n] = '0';
        n++;
        i = n;
    } else if (sys == 18) {
        str[n] = '0';
        str[n + 1] = 'x';
        n += 2;
        i = n;
        sys = 16;
    }
    if (precision != 0 || a != 0) {
        n = s21_double_to_char(str, (long double)a, n, sys);
    }
    n = s21_shift(str, 0, i, n, precision, '0', s21_NULL);
    n = s21_shift(str, 0, k, n, width, ' ', flags);
    str[n] = '\0';
    return n;
}

static unsigned long long int s21_pyramid_un(va_list factor, int length, int sys) {
    unsigned long long int a = 0;
    if (sys == 18) {
        a = (unsigned long long int)va_arg(factor, void*);
    } else if (length == 0) {
        a = (unsigned long long int)va_arg(factor, unsigned int);
    } else if (length == 1) {
        a = (unsigned long long int)(unsigned short int)va_arg(factor, int);
    } else if (length == 2) {
        a = (unsigned long long int)va_arg(factor, unsigned long int);
    } else if (length == 3) {
        a = (unsigned long long int)va_arg(factor, unsigned long long int);
    }
    return a;
}

static int s21_minus_sprintf(int *n, int *minus, char *str, long double a, char *flags) {
    int c = 1;
    if (a < 0) {
        c = -1;
        str[*n] = '-';
        *n = *n + 1;
        *minus = -1;
    } else if (flags && s21_strchr(flags, (int)'+')) {
        str[*n] = '+';
        *n = *n + 1;
        *minus = -1;
    } else if (flags && s21_strchr(flags, (int)' ')) {
        str[*n] = ' ';
        *n = *n + 1;
        *minus = -1;
    }
    return c;
}

static int s21_shift(char *str, int minus, int i, int n, int width, char c, char *flags) {
    if (flags) {
        flags[5] = '\0';
    }
    int z = 0;
    if (flags && s21_strchr(flags, (int)'0')) {
        c = '0';
        if (minus == -1) {
            minus = 0;
            z = 1;
        }
    }
    if (width > n - i + minus) {
        if (flags && s21_strchr(flags, (int)'-')) {
            while (n < width + i + minus) {
                str[n] = c;
                n++;
            }
        } else {
            i += minus;
            for (int k = 0; k < n - i + 1; k++) {
                str[i + width - k - z] = str[n - k];
            }
            for (int k = 0; k < width - n + i - z; k++) {
                str[i + k] = c;
            }
            n = i + width - z;
        }
        str[n] = '\0';
    }
    return n;
}

static int s21_f_sprintf(char *str, va_list factor, int n, int length, \
                  int precision, int width, char *flags, char e) {
    int minus = 0, i;
    if (precision != -2 && flags[4] == 'g' && e == 'T') {
        precision = 6;
    }
    if (precision == -1) {
        precision = 6;
    }
    long double bb;
    if (length == 3) {
        bb = va_arg(factor, long double);
    } else {
        bb = (long double)va_arg(factor, double);
    }
    if (!isnan(bb)) {
        bb *= s21_minus_sprintf(&n, &minus, str, bb, flags);
    }
    i = s21_e_sprintf(bb, str, precision, n, e, flags);
    if (width != i - n) {
        i = s21_shift(str, minus, n, i, width, ' ', flags);
    }
    str[i] = '\0';
    return i;
}

static int s21_e_sprintf(long double bb, char *str, int precision, int n, char e, char *flags) {
    int E = 0, der = 0, inf = 1, i = 0;
    long double aa = 0;
    E = s21_e_precision(e, &bb, E);
    if (s21_inf_nan(&i, &n, str, &inf, bb, flags)) {
        der = s21_f_precision(&precision, der, &bb, &aa, flags);
        i = s21_double_to_char(str, bb, n, 10);
    }
    if (((precision == 0 && s21_strchr(flags, (int)'#')) || precision != 0) && inf) {
        str[i] = '.';
        i++;
        for (int k = 0; k < der; k++) {
            str[i] = '0';
            i++;
        }
    }
    if (precision != 0 && inf) {
        if (aa != 0) {
            i = s21_double_to_char(str, aa, i, 10);
        }
        if (flags[4] == 'g' && s21_strchr(flags, (int)'#') == 0) {
            while (str[i - 1] == '0') {
                str[i - 1] = '\0';
                i--;
            }
            if (str[i - 1] == '.') {
                str[i - 1] = '\0';
                i--;
            }
        }
    }
    i = s21_e_to_char(flags, E, str, i, e);
    return i;
}

static int s21_e_precision(char e, long double *bb, int E) {
    if ((e == 'E' || e == 'e') && *bb != 0) {
        if (*bb > 1) {
            while (*bb > 10) {
                *bb = *bb / 10;
                E++;
            }
        } else {
            while (*bb < 1) {
                *bb = *bb * 10;
                E--;
            }
        }
    }
    return E;
}

static int s21_e_to_char(char *flags, int E, char *str, int i, char e) {
    if (flags[4] == 'g' && E == 0) {
    } else if (e == 'e' || e == 'E') {
        str[i] = e;
        if (E >= 0) {
            str[i + 1] = '+';
        } else {
            str[i + 1] = '-';
            E *= -1;
        }
        i += 2;
        int g = i;
        i = s21_double_to_char(str, (long double)E, i, 10);
        i = s21_shift(str, 0, g, i, 2, '0', s21_NULL);
    }
    return i;
}

static int s21_inf_nan(int *i, int *n, char *str, int *inf, long double bb, char *flags) {
    if (bb == INFINITY || isnan(bb)) {
        if (bb == INFINITY) {
            str[*n] = 'i'; str[*n + 1] = 'n'; str[*n + 2] = 'f';
        } else {
            str[*n] = 'n'; str[*n + 1] = 'a'; str[*n + 2] = 'n';
        }
        *n = 3 + *n;
        *i = *n;
        *inf = 0;
        if (s21_strchr(flags, (int)'0')) {
            *s21_strchr(flags, (int)'0') = 'T';
        }
    }
    return *inf;
}

static int s21_f_precision(int *precision, int der, long double *bb, long double *aa, char *flags) {
    long double dre = 0, pres = 0, l;
    if (*precision == 0) {
        *bb = roundl(*bb);
    } else {
        *aa = modfl(*bb, &l);
        if (*bb != l) {
            *aa = modfl(*bb + 1e-8, bb);
            *aa = *aa - 1e-8;
        } else {
            *aa = modfl(*bb, bb);
        }
        if (*precision == -2) {
            pres = *bb;
            while (pres > 1) {
                pres /= 10;
                der++;
            }
            *precision -= der - 8;
            if (*precision < 0) {
                *precision = 0;
            }
        }
        der = 0;
        dre = *aa;
        if (dre != 0) {
            while (dre < 0.1 - 0.0005 && der < *precision) {
                dre *= 10;
                der++;
            }
        } else {
            if (flags[4] == 'g') {
                der = *precision - 1;
            } else {
                der = *precision;
            }
        }
        *aa = roundl((*aa * powl(10, *precision)));
    }
    return der;
}

static int s21_s_sprintf(char *str, va_list factor, int n, int precision, \
                         int width, char *flags, int length) {
    if (length == 0) {
        n = s21_char(str, factor, n, precision, width, flags);
    } else {
        n = s21_wchart(str, factor, n, precision, width, flags);
    }
    return n;
}

static int s21_char(char *str, va_list factor, int n, int precision, int width, char *flags) {
    int begin = n;
    char *buff = va_arg(factor, char*);
    if (buff == s21_NULL) {
        n = s21_string_null(precision, str, n);
    } else {
        str[n] = '\0';
        if (precision == -1 || (int)s21_strlen(buff) < precision) {
            s21_strcat(str, buff);
            n += s21_strlen(buff);
            str[n] = '\0';
        } else {
            s21_strncat(str, buff, precision - 1);
            n += precision;
            str[n] = '\0';
        }
    }
    n = s21_shift(str, 0, begin, n, width, ' ', flags);
    return n;
}

static int s21_wchart(char *str, va_list factor, int n, int precision, int width, char *flags) {
    int begin = n;
    const wchar_t *buff = va_arg(factor, wchar_t*);
    if (buff == s21_NULL) {
        n = s21_string_null(precision, str, n);
    } else {
        int i = wcstombs(&str[n], buff, (s21_size_t)1024);
        str[i + n] = '\0';
        if (precision == -1 || i < precision) {
            n += i;
            str[n] = '\0';
        } else {
            n += precision;
            str[n] = '\0';
        }
    }
    n = s21_shift(str, 0, begin, n, width, ' ', flags);
    return n;
}

static int s21_string_null(int precision, char * str, int n) {
    char buff_null[7] = "(null)";
    if (precision == - 1) {
        precision = 6;
    }
    str[n] = '\0';
    s21_strncat(str, buff_null, precision - 1);
    n = s21_strlen(str);
    return n;
}

static int s21_c_sprintf(char *str, va_list factor, int n, int width, char *flags, int length) {
    if (length != 0) {
        const wchar_t buff = (wchar_t)va_arg(factor, wchar_t);
        int i = (int)wcstombs(&str[n], &buff, (s21_size_t)1024);
        n += i;
        n = s21_shift(str, 0, n - 1, n, width, ' ', flags);
    } else {
        str[n] = va_arg(factor, int);
        n++;
        n = s21_shift(str, 0, n - 1, n, width, ' ', flags);
        str[n] = '\0';
    }
    return n;
}

static int s21_g_sprintf(char *str, va_list factor, int n, int length, \
                         int precision, int width, char *flags, char form) {
    if (form == 'g') {
        form = 'e';
    } else {
        form = 'E';
    }
    if (precision == 0) {
        precision = 2;
    }
    flags[4] = 'g';
    int i = n, zero = 1;
    va_list copy;
    va_copy(copy, factor);
    n = s21_f_sprintf(str, copy, n, length, precision - 1, 0, flags, 'T');
    int f = n - i;
    if (f == 1 && str[i] == '0') {
        zero = 0;
    }
    n = i;
    va_end(copy);
    va_copy(copy, factor);
    n = s21_f_sprintf(str, copy, n, length, precision - 1, 0, flags, form);
    int e = n - i;
    n = i;
    va_end(copy);
    if (f <= e && zero) {
        n = s21_f_sprintf(str, factor, n, length, precision - 1, width, flags, 'T');
    } else {
        n = s21_f_sprintf(str, factor, n, length, precision - 1, width, flags, form);
    }
    return n;
}
