#include "s21_string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>

#include <check.h>

START_TEST(s21_strlen_test) {
    char * a = "123456789";
    char * b = "";
    char * c = "123/0000000";
    char * d = "wefафуцкппЙЙЙЙЙЙжж;;";
    ck_assert_int_eq(s21_strlen(a), strlen(a));
    ck_assert_int_eq(s21_strlen(b), strlen(b));
    ck_assert_int_eq(s21_strlen(c), strlen(c));
    ck_assert_int_eq(s21_strlen(d), strlen(d));
}
END_TEST

START_TEST(s21_memchr_test) {
    char * a = "1234567\009";
    char * b = "";
    char * c = "123/00000000";
    ck_assert_pstr_eq(s21_memchr(a, 52, 6), memchr(a, 52, 6));
    ck_assert_pstr_eq(s21_memchr(a, '2', 2), memchr(a, '2', 2));
    ck_assert_pstr_eq(s21_memchr(b, 52, 0), memchr(b, 52, 0));
    ck_assert_pstr_eq(s21_memchr(a, 1, 2), memchr(a, 1, 2));
    ck_assert_pstr_eq(s21_memchr(c, 1, 2), memchr(c, 1, 2));
    ck_assert_pstr_eq(s21_memchr(c, 0, 100), memchr(c, 0, 100));
}
END_TEST

START_TEST(s21_memcmp_test) {
    char * a = "123456789";
    char * b = "1233456799";
    char * c = "";
    char * d = "wergwertbg";
    char * e = "\0";
    ck_assert_int_eq(s21_memcmp(a, b, 6), memcmp(a, b, 6));
    ck_assert_int_eq(s21_memcmp(a, b, 9), memcmp(a, b, 9));
    ck_assert_int_eq(s21_memcmp(a, b, 0), memcmp(a, b, 0));
    ck_assert_int_eq(s21_memcmp(a, b, 100), memcmp(a, b, 100));
    ck_assert_int_eq(s21_memcmp(a, c, 3), memcmp(a, c, 3));
    ck_assert_int_eq(s21_memcmp(d, d, 10), memcmp(d, d, 10));
    ck_assert_int_eq(s21_memcmp(c, e, 4), memcmp(c, e, 4));
}
END_TEST

START_TEST(s21_memcpy_test) {
    char b[100] = "123456";
    char a[100] = "";
    char c[100] = "\0";
    ck_assert_pstr_eq(s21_memcpy(a, b, 1), memcpy(a, b, 1));
    ck_assert_pstr_eq(s21_memcpy(a, b, 2), memcpy(a, b, 2));
    ck_assert_pstr_eq(s21_memcpy(a, b, 10), memcpy(a, b, 10));
    ck_assert_pstr_eq(s21_memcpy(a, b, 0), memcpy(a, b, 0));
    ck_assert_pstr_eq(s21_memcpy(a, c, 10), memcpy(a, c, 10));
}
END_TEST

START_TEST(s21_memset_test) {
    char b[100] = "123456789";
    ck_assert_pstr_eq(s21_memset(b, 200, 3), memset(b, 200, 3));
    ck_assert_pstr_eq(s21_memset(b, 50, 0), memset(b, 50, 0));
    ck_assert_pstr_eq(s21_memset(b, 50, 10), memset(b, 50, 10));
}
END_TEST

START_TEST(s21_memmove_test) {
    char b[100] = "1234567890";
    char a[100] = "";
    ck_assert_pstr_eq(s21_memmove(a, b, 6), memmove(a, b, 6));
    ck_assert_pstr_eq(s21_memmove(&a[4], &a[3], 3), memmove(&a[4], &a[3], 3));
    ck_assert_pstr_eq(s21_memmove(&a[3], &a[4], 4), memmove(&a[3], &a[4], 4));
}
END_TEST

START_TEST(s21_strcat_test) {
    char b[1024] = "первая строка ";
    char a[1024] = "вторая ст\0рока";
    ck_assert_pstr_eq(s21_strcat(a, b), strcat(a, b));
    ck_assert_pstr_eq(s21_strcat(a, ""), strcat(a, ""));
}
END_TEST

START_TEST(s21_strncat_test) {
    char b[1024] = "первая строка ";
    char a[1024] = "вторая строка";
    ck_assert_pstr_eq(s21_strncat(a, b, 3), strncat(a, b, 3));
    ck_assert_pstr_eq(s21_strncat(a, b, 50), strncat(a, b, 50));
    ck_assert_pstr_eq(s21_strncat(a, b, 0), strncat(a, b, 0));
}
END_TEST


START_TEST(s21_strchr_test) {
    char a[1024] = "123456789";
    ck_assert_pstr_eq(s21_strchr(a, '\0'), strchr(a, '\0'));
    ck_assert_pstr_eq(s21_strchr(a, 80), strchr(a, 80));
    ck_assert_pstr_eq(s21_strchr(a, ' '), strchr(a, ' '));
    ck_assert_pstr_eq(s21_strchr("", 80), strchr("", 80));
}

END_TEST

START_TEST(s21_strcmp_test) {
    char * a = "123456789";
    char * b = "123456799";

    ck_assert_int_eq(s21_strcmp(a, b), strcmp(a, b));
    ck_assert_int_eq(s21_strcmp(b, b), strcmp(b, b));
    ck_assert_int_eq(s21_strcmp(a, b), strcmp(a, b));
    ck_assert_int_eq(s21_strcmp(a, a), strcmp(a, a));
}
END_TEST

START_TEST(s21_strncmp_test) {
    char * a = "123456789";
    char * b = "123456799";
    char * c = "";

    ck_assert_int_eq(s21_strncmp(a, b, 6), strncmp(a, b, 6));
    ck_assert_int_eq(s21_strncmp(c, b, 9), strncmp(c, b, 9));
    ck_assert_int_eq(s21_strncmp(a, c, 0), strncmp(a, c, 0));
    ck_assert_int_eq(s21_strncmp(a, a, 60), strncmp(a, a, 60));
    ck_assert_int_eq(s21_strncmp(c, c, 6), strncmp(c, c, 6));
}
END_TEST

START_TEST(s21_strcpy_test) {
    char a[1024] = "123456789";
    char b[1024] = "987654321";
    ck_assert_pstr_eq(s21_strcpy(a, b), strcpy(a, b));
}
END_TEST

START_TEST(s21_strncpy_test) {
    char a[1024] = "123456789";
    char b[1024] = "98765";
    ck_assert_pstr_eq(s21_strncpy(a, b, 6), strncpy(a, b, 6));
    ck_assert_pstr_eq(s21_strncpy(a, b, 1), strncpy(a, b, 1));
    ck_assert_pstr_eq(s21_strncpy(a, b, 18), strncpy(a, b, 18));
}
END_TEST

START_TEST(s21_strcspn_test) {
    char a[100] = "0123456789";
    char b[100] = "9876";
    ck_assert_int_eq(s21_strcspn(a, b), strcspn(a, b));
    ck_assert_int_eq(s21_strcspn(a, ""), strcspn(a, ""));
    ck_assert_int_eq(s21_strcspn("", b), strcspn("", b));
    ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
}
END_TEST

START_TEST(s21_strpbrk_test) {
    char a[100] = "0123456789";
    char b[100] = "9876";
    ck_assert_pstr_eq(s21_strpbrk(a, b), strpbrk(a, b));
    ck_assert_pstr_eq(s21_strpbrk(a, a), strpbrk(a, a));
    ck_assert_pstr_eq(s21_strpbrk(a, ""), strpbrk(a, ""));
    ck_assert_pstr_eq(s21_strpbrk(b, a), strpbrk(b, a));
}
END_TEST

START_TEST(s21_strrchr_test) {
    char a[100] = "0123456789";
    ck_assert_pstr_eq(s21_strrchr(a, 54), strrchr(a, 54));
    ck_assert_pstr_eq(s21_strrchr(a, 10), strrchr(a, 10));
    ck_assert_pstr_eq(s21_strrchr(a, 0), strrchr(a, 0));
}
END_TEST

START_TEST(s21_strspn_test) {
    char a[100] = "0123456789";
    char b[100] = "54321";
    ck_assert_int_eq(s21_strspn(a, b), strspn(a, b));
    ck_assert_int_eq(s21_strspn(a, "e"), strspn(a, "e"));
    ck_assert_int_eq(s21_strspn(a, a), strspn(a, a));
}
END_TEST

START_TEST(s21_strstr_test) {
    char a[100] = "0123456789";
    ck_assert_pstr_eq(s21_strstr(a, "456"), strstr(a, "456"));
    ck_assert_pstr_eq(s21_strstr(a, ""), strstr(a, ""));
    ck_assert_pstr_eq(s21_strstr(a, "e"), strstr(a, "e"));
}
END_TEST

START_TEST(s21_strtok_test) {
    char a[50]= "test1//test2/test3/test";
    for (int k = 0; k < 3; k++) {
        ck_assert_pstr_eq(s21_strtok(a, "/"), strtok(a, "/"));
    }
    ck_assert_pstr_eq(s21_strtok(a, "/"), strtok(a, "/"));
    ck_assert_pstr_eq(s21_strtok(a, "e"), strtok(a, "e"));
    ck_assert_pstr_eq(s21_strtok(a, "es"), strtok(a, "es"));
}
END_TEST

START_TEST(s21_sprintf_test_1) {
    char c[1590];
    char C[1590];
    ck_assert_int_eq(s21_sprintf(c, "%d", 15), sprintf(C, "%d", 15));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_2) {
    char c[1590];
    char C[1590];
    long long int b = 5;
    float a = 1234.6789;
    char x = 'w';
    const char format[] = "%-13.*lld %.6f %-2c %s !!!";
    ck_assert_int_eq(s21_sprintf(c, format, 6, b, a,  x, "qwerty"), \
                     sprintf(C, format, 6, b, a,  x, "qwerty"));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_3) {
    char c[1590];
    char C[1590];
    long double d = 12.32e30;
    long int li = -123456789;
    short int si = 123;
    int j = 0, J = 1;
    const char format[] = "%20.15ld %- 10hd %#+0*.5Lg ..%n.. ";
    ck_assert_int_eq(s21_sprintf(c, format, li, si, 19, d, &j), \
                     sprintf(C, "%20.15ld %- 10hd %#+0*.5Lg ..%n.. ", li, si, 19, d, &J));
    ck_assert_pstr_eq(c, C);
    ck_assert_int_eq(j, J);
}
END_TEST

START_TEST(s21_sprintf_test_4) {
    char c[1590];
    char C[1590];
    float ff = FLT_MAX, FF = FLT_MIN_10_EXP;
    unsigned int ui = 1239465;
    const char format[] = "%.*E %f %#15.4x";
    ck_assert_int_eq(s21_sprintf(c, format, 3, ff, FF, ui), sprintf(C, format, 3, ff, FF, ui));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_5) {
    char c[1590];
    char C[1590];
    char s[10] = "qwerЙuio";
    float fff = 401.12634e-2;
    float a = 1234.6789;
    const char format[] = " -%12.15s %.2s %g %p";
    ck_assert_int_eq(s21_sprintf(c, format, s, s, fff, &a), sprintf(C, format, s, s, fff, &a));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_6) {
    char c[1590];
    char C[1590];
    const char format[] = " ";
    ck_assert_int_eq(s21_sprintf(c, format), sprintf(C, format));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_7) {
    char c[1590];
    char C[1590];
    float a = -123.09876544;
    double b = 0.00023;
    long double q = -33e-5;
    int k = 4;
    int l = 5;
    const char format[] = "qwe%f%-4.4lftr%#*.*Le";
    ck_assert_int_eq(s21_sprintf(c, format, a, b, k, l, q), sprintf(C, format, a, b, k, l, q));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_8) {
    char c[1590];
    char C[1590];
    float a = -123.09876544;
    double b = 0.0023;
    long double q = -36e-3;
    float w = 0;
    const char format[] = "%g%045lg %+.3Lg %#g";
    ck_assert_int_eq(s21_sprintf(c, format, a, b, q, w), sprintf(C, format, a, b, q, w));
    ck_assert_pstr_eq(c, C);
}
END_TEST

START_TEST(s21_sprintf_test_9) {
    char c[1590];
    char C[1590];
    unsigned short x = 9045;
    char s[16] = "ç∂ƒe\n rty";
    int n = 0, N = 0;
    const char format[] = "%-13s  %*.*hX \n%n\n 7&";
    ck_assert_int_eq(s21_sprintf(c, format, s, 11, 9, x, &n), \
                     sprintf(C, "%-13s  %*.*hX \n%n\n 7&", s, 11, 9, x, &N));
    ck_assert_pstr_eq(c, C);
    ck_assert_int_eq(n, N);
}
END_TEST

START_TEST(s21_sprintf_test_10) {
    char c[1590];
    char C[1590];
    float d = -12.99999;
    long double ld = INFINITY;
    long double z = -0;
    const char format[] = "%.15f %.15Lf %+Lf";
    s21_sprintf(c, format, d, ld, z);
    sprintf(C, format, d, ld, z);
    ck_assert_pstr_eq(c, C);
    ck_assert_int_eq(s21_sprintf(c, format, d, ld, z), sprintf(C, format, d, ld, z));
}
END_TEST

START_TEST(s21_sprintf_test_11) {
    char t[1590];
    char T[1590];
    unsigned short int g = -123;
    unsigned int a = 1230;
    unsigned long int b = 123654;
    unsigned long long int c = 7;
    const char format[] = "%u%hu%lu%llu %o%ho%lo%llo %x%hx%lx%llx %#X%hX%lX%llX";
    int i = s21_sprintf(t, format, a, g, b, c, a, g, b, c, a, g, b, c, a, g, b, c);
    int I = sprintf(T, format, a, g, b, c, a, g, b, c, a, g, b, c, a, g, b, c);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_12) {
    char t[1590];
    char T[1590];
    float f = -INFINITY, ff = -0, fff = NAN;
    double d = -40000000003e-0, dd = -0.003e+10;
    long double ld = -NAN, lld = -0;
    const char format[] = "%%%%%+#6.5f%% %+f %+0#10.10lf %-#+9.9lf %+.0Lf %+.0Lf %+07f %-+10f";
    int i = s21_sprintf(t, format, f, ff, d, dd, ld, lld, fff, f);
    int I = sprintf(T, format, f, ff, d, dd, ld, lld, fff, f);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_13) {
    char t[1590];
    char T[1590];
    float a1 = 1e-1;
    float a2 = 2e-2;
    float a3 = 3e-3;
    float a4 = 4e-4;
    float a5 = 5e-5;
    float a6 = 6e-6;
    float a7 = 7e-7;
    float a8 = 8e-8;
    float a9 = 9e-1;
    float a10 = 10e-10;
    float a11 = 11e-11;
    float a12 = 12e-12;
    float a13 = 13e-13;
    float a14 = 14e-14;
    float a15 = 15e-15;
    float a16 = 16e-16;
    const char format[] = "%f %f %f %f %f %f %.7f %.8f%.8f %.9f %.10f %.12f %.13f %.14f %.15f %.16f";
    int i = s21_sprintf(t, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    int I = sprintf(T, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_14) {
    char t[1590];
    char T[1590];
    double a1 = 1.01e-1;
    double a2 = 0.99e-2;
    double a3 = 3.33e-3;
    double a4 = 0.1e-4;
    double a5 = -12e-5;
    double a6 = 4e-6;
    double a7 = 4e-7;
    double a8 = 4e-8;
    const char format[] = "%lf %lf %lf %lf %lf %lf %lf %lf";
    int i = s21_sprintf(t, format, a1, a2, a3, a4, a5, a6, a7, a8);
    int I = sprintf(T, format, a1, a2, a3, a4, a5, a6, a7, a8);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_15) {
    char t[1590];
    char T[1590];
    long double a1 = 87.78e1;
    long double a2 = 99e2;
    long double a3 = -33.33e3;
    long double a4 = -100e4;
    long double a5 = -1e5;
    long double a6 = 3333e6;
    long double a7 = 0.003e7;
    long double a8 = 0.1001e8;
    const char format[] = "%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf";
    int i = s21_sprintf(t, format, a1, a2, a3, a4, a5, a6, a7, a8);
    int I = sprintf(T, format, a1, a2, a3, a4, a5, a6, a7, a8);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_16) {
    char t[1590];
    char T[1590];
    float a1 = 0.101;
    float a2 = -1.00101;
    float a3 = 2.0202;
    float a4 = 0.0002002;
    float a5 = -11.0011;
    float a6 = 0.0000000101;
    float a7 = -100000;
    float a8 = 1000000;
    float a9 = 10000000;
    float a10 = 100000000;
    const char format[] = "%f %f %f %f %f %f %f %f %f %f";
    int i = s21_sprintf(t, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    int I = sprintf(T, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_17) {
    char t[1590];
    char T[1590];
    float a1 = 9e1;
    float a2 = 8e2;
    float a3 = 7e3;
    float a4 = 6e4;
    float a5 = 5e5;
    float a6 = 4e6;
    float a7 = 3e7;
    float a8 = 2e8;
    float a9 = 1e9;
    float a10 = -1e10;
    float a11 = -2e11;
    float a12 = -3e12;
    float a13 = -4e13;
    float a14 = -5e14;
    float a15 = -7e15;
    float a16 = -8e16;
    const char format[] = "%f %f %f %f %f %f %f %f%f %f %f %f %f %f %f %f";
    int i = s21_sprintf(t, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    int I = sprintf(T, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_18) {
    char t[1590];
    char T[1590];
    char *c = NULL;
    const char format[] = "%s %10s %7.10s %2.2s %-8s";
    int i = s21_sprintf(t, format, c, c, c, c, c);
    int I = sprintf(T, format, c, c, c, c, c);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sprintf_test_19) {
    char t[1590];
    char T[1590];
    char c1[] = "1234\t456";
    char c2[] = "d\new";
    char c3[] = "qwerfdsa";
    char c4[] = "7777";
    char c5[] = "q\t\n\0";
    const char format[100] = "%s %11s %8.9s %3.2s %-166s";
    int i = s21_sprintf(t, format, c1, c2, c3, c4, c5);
    int I = sprintf(T, format, c1, c2, c3, c4, c5);
    ck_assert_pstr_eq(t, T);
    ck_assert_int_eq(i, I);
}
END_TEST

START_TEST(s21_sscanf_test_1) {
    const char srt[] = "0.45Щ5ČйxЦ44qwerЩЩЩ-1   5.511W    rwerfds r";
    const char format[] = "%hd%lc%ls%d%Lf%c%5s%n";
    short int a = 0, A = 0;
    wchar_t wc = 123, WC = 123;
    wchar_t ww[40];
    wchar_t WW[40];
    int u = 0, n = 0, U = 0, N = 0;
    long double b = 0, B = 0;
    char c = 't', C = 't';
    char s[12] = "123";
    char S[12] = "123";
    ck_assert_int_eq(s21_sscanf(srt, format, &a, &wc, ww, &u, &b, &c, s, &n), \
                     sscanf(srt, format, &A, &WC, WW, &U, &B, &C, S, &N));
    ck_assert_int_eq(a, A);
    ck_assert_int_eq(n, N);
    ck_assert_int_eq(u, U);
    ck_assert_int_eq(wc, WC);
    ck_assert_int_eq(c, C);
    ck_assert_str_eq(s, S);
    ck_assert_double_eq(b, B);
    ck_assert_str_eq((char*)ww, (char*)WW);
}
END_TEST

START_TEST(s21_sscanf_test_2) {
    const char srt[100] = "123.123  -44%";
    const char format[30] = "%5Lf%1hd%n%lc%hx%c";
    short int a = 0, A = 0, q = 0, Q = 0;
    wchar_t wc = 123, WC = 123;
    int  n = 1, N = 0;
    long double b = 0, B = 0;
    char c = 't', C = 't';
    ck_assert_int_eq(s21_sscanf(srt, format, &b, &q, &n, &wc, &a, &c), \
                     sscanf(srt, format, &B, &Q, &N, &WC, &A, &C));
    ck_assert_int_eq(a, A);
    ck_assert_int_eq(n, N);
    ck_assert_int_eq(q, Q);
    ck_assert_int_eq(wc, WC);
    ck_assert_ldouble_eq(b, B);
    ck_assert_int_eq(c, C);
}
END_TEST

START_TEST(s21_sscanf_test_3) {
    setlocale(LC_ALL, "");
    const char srt[100] = "1qqwereЦ йцукке1 055";
    const char format[30] = "%f%c%5s%1ls%n%*d%n%lf";
    float rr = 0, RR = 0;
    char cc = 'q', CC = 'q';
    char s[6] = "123";
    char S[6] = "123";
    int nn = 0, NN = 0, aa = 0, AA = 0;
    double d = 0, D = 0;
    wchar_t ss[10];
    ss[0] = '\0';
    wchar_t SS[10];
    SS[0] = '\0';
    ck_assert_int_eq(s21_sscanf(srt, format, &rr, &cc, s, ss, &nn, &aa, &d), \
                     sscanf(srt, format, &RR, &CC, S, SS, &NN, &AA, &D));
    ck_assert_float_eq(rr, RR);
    ck_assert_str_eq(s, S);
    ck_assert_int_eq(aa, AA);
    ck_assert_int_eq(nn, NN);
    ck_assert_double_eq(d, D);
    ck_assert_int_eq(cc, CC);
    ck_assert_str_eq((char*)ss, (char*)SS);
}
END_TEST

START_TEST(s21_sscanf_test_4) {
    setlocale(LC_ALL, "");
    const char srt[100] = "1-m14 -300 -556 111 3add56abc4";
    const char format[30] = "%u%i%o%*c%*s%5lx%n";
    int z = 0, Z = 0, x = 0, X = 0, v = 0, V = 0, n = 0, N = 0;
    long int m = 0, M = 0;
    ck_assert_int_eq(s21_sscanf(srt, format, &z, &x, &v, &m, &n), sscanf(srt, format, &Z, &X, &V, &M, &N));
    ck_assert_int_eq(z, Z);
    ck_assert_int_eq(x, X);
    ck_assert_int_eq(v, V);
    ck_assert_int_eq(m, M);
    ck_assert_int_eq(n, N);
}
END_TEST

START_TEST(s21_sscanf_test_5) {
    setlocale(LC_ALL, "");
    const char srt[100] = "q  5 4";
    const char format[30] = "%*c%d%c%f";
    int nn = 0, NN = 0;
    float rr = 0, RR = 0;
    char c = 'q', C = 'q';
    ck_assert_int_eq(s21_sscanf(srt, format, &nn, &c, &rr), sscanf(srt, format, &NN, &C, &RR));
    ck_assert_int_eq(nn, NN);
    ck_assert_float_eq(rr, RR);
    ck_assert_int_eq(c, C);
}
END_TEST

START_TEST(s21_sscanf_test_6) {
    setlocale(LC_ALL, "");
    const char srt[100] = "--я345.";
    const char format[30] = "%Lf%15ls%*d%*d%n";
    wchar_t ss[20];
    ss[0] = '\0';
    wchar_t SS[20];
    SS[0] = '\0';
    long double b = 0, B = 0;
    int n = 0, N = 0;
    ck_assert_int_eq(s21_sscanf(srt, format, &b, ss, &n), sscanf(srt, format, &B, SS, &N));
    ck_assert_int_eq(n, N);
    ck_assert_ldouble_eq(b, B);
    ck_assert_str_eq((char*)ss, (char*)SS);
}
END_TEST

START_TEST(s21_sscanf_test_7) {
    double f = 0, F = 0;
    float r = 0, R = 0, e = 0, E = 0;
    long double l = 0, L = 0, t = 0, T = 0;
    const char srt[100] = "12e4 .0 -43e-3  5e+1 7 .4e-4 0.0.0 r";
    const char format[30] = "%lf%f%f%*d%*c%*c%Lf%Lf";
    ck_assert_int_eq(s21_sscanf(srt, format, &f, &r, &e, &l, &t), sscanf(srt, format, &F, &R, &E, &L, &T));
    ck_assert_float_eq(r, R);
    ck_assert_float_eq(E, e);
    ck_assert_double_eq(l, L);
    ck_assert_ldouble_eq(t, T);
    ck_assert_double_eq(f, F);
}
END_TEST

START_TEST(s21_sscanf_test_8) {
    int n = 0, N = 0;
    float k = 0, K = 0;
    long double l = 0, L = 0;
    const char srt[100] = ".e+ -.e-4";
    const char format[30] = "%f%n%Lf";
    ck_assert_int_eq(s21_sscanf(srt, format, &k, &n, &l), sscanf(srt, format, &K, &N, &L));
    ck_assert_ldouble_eq(l, L);
    ck_assert_float_eq(k, K);
    ck_assert_int_eq(n, N);
    const char srt2[100] = "-.5 0e-4";
    ck_assert_int_eq(s21_sscanf(srt2, format, &k, &n, &l), sscanf(srt2, format, &k, &N, &L));
    ck_assert_ldouble_eq(l, L);
    ck_assert_int_eq(n, N);
}
END_TEST

START_TEST(s21_sscanf_test_9) {
    long double l = 0, L = 0;
    const char srt[100] = "4e- 5";
    const char format[30] = "%*f%*c%*c%Lf";
    ck_assert_int_eq(s21_sscanf(srt, format, &l), sscanf(srt, format, &L));
    ck_assert_ldouble_eq(l, L);
}
END_TEST

START_TEST(s21_sscanf_test_10) {
    float l = 0, L = 0;
    const char srt[100] = "12345678909876544332234653482354624564273568357836584769845673511134e100";
    const char format[30] = "%f";
    ck_assert_int_eq(s21_sscanf(srt, format, &l), sscanf(srt, format, &L));
    ck_assert_float_eq(l, L);
}
END_TEST

START_TEST(s21_sscanf_test_11) {
    long double l = 0, L = 0;
    const char srt[100] = "123456789098";
    const char format[30] = "%Lf";
    ck_assert_int_eq(s21_sscanf(srt, format, &l), sscanf(srt, format, &L));
    ck_assert_double_eq(l, L);
}
END_TEST

START_TEST(s21_sscanf_test_12) {
    long double l = 0, L = 0;
    void *a = &l;
    void *A = &L;
    void *T = &L;
    void *t = &L;
    const char srt[100] = "123654a";
    const char format[30] = "%p %p";
    ck_assert_int_eq(s21_sscanf(srt, format, &a, &t), sscanf(srt, format, &A, &T));
    ck_assert_ptr_eq(a, A);
    ck_assert_ptr_eq(t, T);
}
END_TEST

START_TEST(s21_sscanf_test_13) {
    long int a = 0, A = 0, c = 0, C = 0;
    long long int b = 0, B = 0, d = 0, D = 0;
    unsigned long int e = 0, f = 0, E = 0, F = 0;
    unsigned long long int g = 0, G = 0, h = 0, H = 0;
    const char srt[200] = "1234 765 -0345 -65425476 123 65646 -0X56456 0x5453456";
    const char format[50] = "%ld %lld %lo %5llo %lu %llu %*u %lx %llX";
    int r = s21_sscanf(srt, format, &a, &b, &c, &d, &e, &g, &f, &h);
    int R = sscanf(srt, format, &A, &B, &C, &D, &E, &G, &F, &H);
    ck_assert_int_eq(r, R);
    ck_assert_int_eq(a, A);
    ck_assert_int_eq(b, B);
    ck_assert_int_eq(c, C);
    ck_assert_int_eq(d, D);
    ck_assert_int_eq(E, e);
    ck_assert_int_eq(F, f);
    ck_assert_int_eq(G, g);
    ck_assert_int_eq(H, h);
}
END_TEST

START_TEST(s21_sscanf_test_14) {
    short int q = 0, Q = 0;
    long int a = 0, A = 0;
    long long int b = 0, B = 0;
    unsigned long int e = 0, E = 0;
    unsigned long long int g = 0, G = 0;
    const char srt[200] = "-0X123 0 01234 12 0xaB4 -0X -1 33";
    const char format[50] = "%li %lli %*i %4li %7lli %hi";
    int r = s21_sscanf(srt, format, &a, &b, &e, &g, &q);
    int R = sscanf(srt, format, &A, &B, &E, &G, &Q);
    ck_assert_int_eq(r, R);
    ck_assert_int_eq(a, A);
    ck_assert_int_eq(b, B);
    ck_assert_int_eq(q, Q);
    ck_assert_int_eq(E, e);
    ck_assert_int_eq(G, g);
}
END_TEST

START_TEST(s21_sscanf_sprinf_test) {
    wchar_t c1[30];
    wchar_t a1;
    wchar_t s1[30];
    wchar_t c2[30];
    wchar_t a2;
    wchar_t s2[30];
    char pr[1024];
    char PR[1024];
    unsigned int u, U;
    const char srt[] = "123 укай我爱菠ЙЦВ Й цкаwrfwцу";
    const char format_s[] = "%x %ls %lc %ls";
    const char format_p[] = "%x reere %3.3ls %-3lc %-18ls";
    int r = sscanf(srt, format_s, &u, c1, &a1, s1);
    int R = sscanf(srt, format_s, &U, c2, &a2, s2);
    int p = s21_sprintf(pr, format_p, u, c1, a1, s1);
    int P = sprintf(PR, format_p, U, c2, a2, s2);
    ck_assert_int_eq(r, R);
    ck_assert_pstr_eq(pr, PR);
    ck_assert_int_eq(p, P);
}
END_TEST


START_TEST(s21_to_upper_test) {
    ck_assert_str_eq(s21_to_upper("qwertyGTREvc"), "QWERTYGTREVC");
    ck_assert_str_eq(s21_to_upper(""), "");
    ck_assert_str_eq(s21_to_upper("123\n0gtGT"), "123\n0GTGT");
}
END_TEST

START_TEST(s21_to_lower_test) {
    ck_assert_str_eq(s21_to_lower("qwertyGTREvc"), "qwertygtrevc");
    ck_assert_str_eq(s21_to_lower(""), "");
    ck_assert_str_eq(s21_to_lower("123\n0gtGT"), "123\n0gtgt");
}
END_TEST

START_TEST(s21_insert_test) {
    ck_assert_str_eq(s21_insert("12345", "ty", 2), "12ty345");
    ck_assert_str_eq(s21_insert("qwe", "1", 5), "qwe");
    ck_assert_str_eq(s21_insert("\n\n45t", "0", 0), "0\n\n45t");
    ck_assert_str_eq(s21_insert(" ", "", 0), " ");
}
END_TEST

START_TEST(s21_trim_test) {
    ck_assert_str_eq(s21_trim("**.*123456789**.*", "*."), "123456789");
    ck_assert_str_eq(s21_trim("**.*12345\0006789**.*", "*."), "12345");
    ck_assert_str_eq(s21_trim("**.*123456789", "*."), "123456789");
    ck_assert_str_eq(s21_trim("123456789**.*", "*."), "123456789");
    ck_assert_str_eq(s21_trim("123456789", "6"), "123456789");
    ck_assert_str_eq(s21_trim("\\\\\\\\\\", "\0"), "\\\\\\\\\\");
    ck_assert_str_eq(s21_trim(" ", "123234234"), "");
}
END_TEST

START_TEST(s21_strerror_test) {
    ck_assert_str_eq(s21_strerror(4), strerror(4));
    ck_assert_str_eq(s21_strerror(0), strerror(0));
    ck_assert_str_eq(s21_strerror(400), strerror(400));
    ck_assert_str_eq(s21_strerror(-4), strerror(-4));
}
END_TEST

START_TEST(all_empty) {
    char str[] = "";
    char trim_ch[] = "";
    char expected[] = "";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(str_empty) {
    char str[] = "";
    char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
    char expected[] = "";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_empty) {
    char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
    char trim_ch[] = "";
    char expected[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_and_str_eq) {
    char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
    char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
    char expected[] = "";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_test1) {
    char str[] = "+!!++Abo+ba++00";
    char trim_ch[] = "+!0-";
    char expected[] = "Abo+ba";
    char *got = (char *)s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_test2) {
    char str[] = "Ab000cd0";
    char trim_ch[] = "003";
    char expected[] = "Ab000cd";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_test3) {
    char str[] = "DoNotTouch";
    char trim_ch[] = "Not";
    char expected[] = "DoNotTouch";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_test4) {
    char str[] = "&* !!sc21 * **";
    char trim_ch[] = "&!* ";
    char expected[] = "sc21";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(trim_test5) {
    char str[] = " Good morning!    ";
    char trim_ch[] = " ";
    char expected[] = "Good morning!";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(empty_spaces) {
    char str[] = "        abc         ";
    char trim_ch[] = " ";
    char expected[] = "abc";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(null_ptr_trim_chars) {
    char str[] = "        abc         ";
    char *trim_ch = NULL;
    char expected[] = "abc";
    char *got = s21_trim(str, trim_ch);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
}
END_TEST

START_TEST(correct_token_string) {
    char str1[] = "Aboba++Floppa_! Kotya====!Shleppa";
    char str2[] = "Aboba++Floppa_! Kotya====!Shleppa";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_uint_eq(strlen(got), strlen(expected));
    ck_assert_str_eq(got, expected);


    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(hard_token_string) {
    char str1[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
    char str2[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(unary_delimiters) {
    char str1[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
    char str2[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(no_delims) {
    char str1[] = "AbobaHasNoDelims";
    char str2[] = "AbobaHasNoDelims";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(only_delims) {
    char str1[] = "++++++++";
    char str2[] = "++++++++";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_ptr_null(got);
    ck_assert_ptr_null(expected);
} END_TEST


START_TEST(too_many_uses_non_segfault) {
    char str1[] = "Aboba_Floppa_Roba";
    char str2[] = "Aboba_Floppa_Roba";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    int i = 5;
    while (i) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);
        i--;

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(even_n_of_delims) {
    char str1[] = "Roba++++Kepa++A++++B__V";
    char str2[] = "Roba++++Kepa++A++++B__V";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(odd_n_of_delims) {
    char str1[] = "Aboba__+Floppa_  Roba";
    char str2[] = "Aboba__+Floppa_  Roba";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(mixed_n_of_delims) {
    char str1[] = "Aboba__Floppa_+++Roba_Kepa";
    char str2[] = "Aboba__Floppa_+++Roba_Kepa";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got && expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(hard_mixed) {
    char str1[] = "     Aboba__+ Flo!ppa_   Roba+";
    char str2[] = "     Aboba__+ Flo!ppa_   Roba+";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got || expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(mixed_hard_incorrect) {
    char str1[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
    char str2[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
    const char delims[] = "+_! =";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got || expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

START_TEST(very_hard_mixed) {
    char str1[] = "!       A!B!C!D!E!!F!!G";
    char str2[] = "!       A!B!C!D!E!!F!!G";
    const char delims[] = "";

    char *got = s21_strtok(str1, delims);
    char *expected = strtok(str2, delims);

    ck_assert_str_eq(got, expected);

    while (got || expected) {
        got = s21_strtok(NULL, delims);
        expected = strtok(NULL, delims);

        if (got || expected) {
            ck_assert_str_eq(got, expected);
        } else {
            ck_assert_ptr_null(got);
            ck_assert_ptr_null(expected);
        }
    }
} END_TEST

// Функция создания набора тестов.
Suite *s21_string_suite(void) {
    Suite *suite;

    suite = suite_create("s21_string");
    TCase *tcase_core = tcase_create("Core");
    TCase *tc = tcase_create("trim_tc");

    tcase_add_test(tcase_core, s21_strlen_test);
    tcase_add_test(tcase_core, s21_memchr_test);
    tcase_add_test(tcase_core, s21_memcmp_test);
    tcase_add_test(tcase_core, s21_memcpy_test);
    tcase_add_test(tcase_core, s21_memmove_test);
    tcase_add_test(tcase_core, s21_memset_test);
    tcase_add_test(tcase_core, s21_strcat_test);
    tcase_add_test(tcase_core, s21_strncat_test);
    tcase_add_test(tcase_core, s21_strchr_test);
    tcase_add_test(tcase_core, s21_strcmp_test);
    tcase_add_test(tcase_core, s21_strncmp_test);
    tcase_add_test(tcase_core, s21_strcpy_test);
    tcase_add_test(tcase_core, s21_strncpy_test);
    tcase_add_test(tcase_core, s21_strcspn_test);
    tcase_add_test(tcase_core, s21_strpbrk_test);
    tcase_add_test(tcase_core, s21_strrchr_test);
    tcase_add_test(tcase_core, s21_strspn_test);
    tcase_add_test(tcase_core, s21_strstr_test);
    tcase_add_test(tcase_core, s21_strtok_test);
    tcase_add_test(tcase_core, s21_sprintf_test_1);
    tcase_add_test(tcase_core, s21_sprintf_test_2);
    tcase_add_test(tcase_core, s21_sprintf_test_3);
    tcase_add_test(tcase_core, s21_sprintf_test_4);
    tcase_add_test(tcase_core, s21_sprintf_test_5);
    tcase_add_test(tcase_core, s21_sprintf_test_6);
    tcase_add_test(tcase_core, s21_sprintf_test_7);
    tcase_add_test(tcase_core, s21_sprintf_test_8);
    tcase_add_test(tcase_core, s21_sprintf_test_9);
    tcase_add_test(tcase_core, s21_sprintf_test_10);
    tcase_add_test(tcase_core, s21_sprintf_test_11);
    tcase_add_test(tcase_core, s21_sprintf_test_12);
    tcase_add_test(tcase_core, s21_sprintf_test_13);
    tcase_add_test(tcase_core, s21_sprintf_test_14);
    tcase_add_test(tcase_core, s21_sprintf_test_15);
    tcase_add_test(tcase_core, s21_sprintf_test_16);
    tcase_add_test(tcase_core, s21_sprintf_test_17);
    tcase_add_test(tcase_core, s21_sprintf_test_18);
    tcase_add_test(tcase_core, s21_sprintf_test_19);
    tcase_add_test(tcase_core, s21_sscanf_test_1);
    tcase_add_test(tcase_core, s21_sscanf_test_2);
    tcase_add_test(tcase_core, s21_sscanf_test_3);
    tcase_add_test(tcase_core, s21_sscanf_test_4);
    tcase_add_test(tcase_core, s21_sscanf_test_5);
    tcase_add_test(tcase_core, s21_sscanf_test_6);
    tcase_add_test(tcase_core, s21_sscanf_test_7);
    tcase_add_test(tcase_core, s21_sscanf_test_8);
    tcase_add_test(tcase_core, s21_sscanf_test_9);
    tcase_add_test(tcase_core, s21_sscanf_test_10);
    tcase_add_test(tcase_core, s21_sscanf_test_11);
    tcase_add_test(tcase_core, s21_sscanf_test_12);
    tcase_add_test(tcase_core, s21_sscanf_test_13);
    tcase_add_test(tcase_core, s21_sscanf_test_14);
    tcase_add_test(tcase_core, s21_sscanf_sprinf_test);
    tcase_add_test(tcase_core, s21_to_upper_test);
    tcase_add_test(tcase_core, s21_to_lower_test);
    tcase_add_test(tcase_core, s21_insert_test);
    tcase_add_test(tcase_core, s21_trim_test);
    tcase_add_test(tcase_core, s21_strerror_test);

    tcase_add_test(tc, all_empty);
    tcase_add_test(tc, str_empty);
    tcase_add_test(tc, trim_empty);
    tcase_add_test(tc, trim_and_str_eq);

    tcase_add_test(tc, trim_test1);
    tcase_add_test(tc, trim_test2);
    tcase_add_test(tc, trim_test3);
    tcase_add_test(tc, trim_test4);
    tcase_add_test(tc, trim_test5);
    tcase_add_test(tc, empty_spaces);
    tcase_add_test(tc, null_ptr_trim_chars);

    tcase_add_test(tc, correct_token_string);
    tcase_add_test(tc, hard_token_string);
    tcase_add_test(tc, only_delims);
    tcase_add_test(tc, even_n_of_delims);
    tcase_add_test(tc, odd_n_of_delims);
    tcase_add_test(tc, mixed_n_of_delims);
    tcase_add_test(tc, too_many_uses_non_segfault);
    tcase_add_test(tc, hard_mixed);
    tcase_add_test(tc, mixed_hard_incorrect);
    tcase_add_test(tc, very_hard_mixed);
    tcase_add_test(tc, unary_delimiters);
    tcase_add_test(tc, no_delims);

    suite_add_tcase(suite, tcase_core);
    suite_add_tcase(suite, tc);

    return suite;
}

int main(void) {
    Suite *suite = s21_string_suite();
    SRunner *suite_runner = srunner_create(suite);
    srunner_run_all(suite_runner, CK_VERBOSE);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
