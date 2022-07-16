#include "s21_string.h"

#include <math.h>
#include <stdlib.h>

int s21_number(char c) {
  int result = 0;
  if (c > 47 && c < 58) {
    result = 1;
  }
  return result;
}

int s21_letter(char c) {
  int result = 0;
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
    result = 1;
  }
  return result;
}

int s21_double_to_char(char *str, long double a, int n, int sys) {
    int X = 87;
    if (sys == 17) {
        sys = 16;
        X = 55;
    }
    long double d = sys, r;
    int i = 0;
    char buff[400];
    if (a == 0) {
        str[n] = '0';
        n++;
    }
    while (a >= 1) {
        r = roundl(fmodl(a, d));
        buff[i + 1] = buff[i];
        if (r < 10) {
            buff[i] = (int)r + 48;
        } else {
            buff[i] = (int)r + X;
        }
        a = roundl((a - r) / d);
        i++;
    }
    i += n;
    for (int k = n; k < i; k++) {
        str[k] = buff[i - k - 1];
    }
    str[i] = '\0';
    return i;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *point = s21_NULL;

    for (s21_size_t i = 0; i < n; i++) {
        if (((char *)str)[i] == c) {
            point = ((char *)(str + i));
            break;
        }
    }
    return point;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int check = 0;
    char *str1_s = (char *)str1;
    char *str2_s = (char *)str2;
    for (s21_size_t i = 0; i < n; i++) {
        if (str1_s[i] != str2_s[i]) {
            check = str1_s[i] - str2_s[i];
            break;
        }
    }
    return check;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *dest_s = (char *)dest;
    const char *src_s = (char *)src;
    for (s21_size_t i = 0; i < n; i++) {
        *dest_s++ = *src_s++;
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *dest_s = (char *)dest;
    const char *src_s = (char *)src;
    char *buf = s21_calloc(n * sizeof(char));
    for (s21_size_t i = 0; i < n; i++) {
        buf[i] = src_s[i];
    }
    for (s21_size_t i = 0; i < n; i++) {
        dest_s[i] = buf[i];
    }
    free(buf);
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *str_s = (char *)str;
    for (s21_size_t i = 0; i < n; i++) {
        str_s[i] = c;
    }
    return str;
}

char *s21_strcat(char *data1, const char *data2) {
    s21_size_t len = s21_strlen(data1);
    s21_size_t i;
    for (i = 0; data2[i] != '\0'; i++) data1[len + i] = data2[i];
    data1[len + i] = '\0';
    return data1;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t len = s21_strlen(dest);
    s21_size_t i;
    for (i = 0; i <= n && src[i] != '\0'; i++) dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
  char *soul = s21_NULL;
  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
      if (str[i] == c) {
          soul = ((char*)str) + i;
          break;
      }
  }
  return soul;
}

int s21_strcmp(const char *data1, const char *data2) {
    int soul = 0;
    for (; *data1 == *data2; ++data1, ++data2) {
        if (*data2 == '\0') break;
    }
    soul = (unsigned char)*data1 - (unsigned char)*data2;
    return soul;
}

char *s21_strcpy(char *new, const char *data) {
    char *p = new;
    while ((*p++ = *data++) != '\0') {}
    return new;
}

s21_size_t s21_strlen(const char *str) {
    char *s = (char *)str;
    while (*s) {
        s++;
    }
    return (s - str);
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t soul = 0;
  int flag = 0;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        soul = i;
        flag = 1;
        break;
      }
    }
    if (flag == 1) break;
  }
  if (!flag)
    soul = (s21_strlen(str1));
  return soul;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *str = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        str = (char *)&str1[i];
        break;
      }
    }
    if (str != s21_NULL) break;
  }
  return str;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t soul = s21_strlen(str1);
  int check = 0;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    check = 0;
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) check = 1;
    }
    if (check == 0) {
      soul = i;
      break;
    }
  }

  return soul;
}

char *s21_strstr(const char *data1, const char *data2) {
  int i = 0;
  char *soul = s21_NULL;
  if (s21_strlen(data2) == 0) soul = (char *)data1;
  while (data1[i] != '\0') {
    if (data1[i] == data2[0]) {
      int p = 0;
      while (data1[i + p] != '\0' && data1[i + p] == data2[p]) {
        p++;
      }
      if (data2[p] == '\0') {
        soul = (char *)&data1[i];
        break;
      }
    }
    i++;
    if (soul != s21_NULL) break;
  }
  return soul;
}

char *s21_strerror(int errnum) {
    static char e[100];
    char s[5];
    char *err[] = ERROR;
    int check = 0;
    if (errnum >= 0 && errnum <= NUM) {
        s21_strcpy(e, err[errnum]);
    } else {
        if (errnum < 0) {
            errnum = -errnum;
            s[0] = '-';
            check++;
        }
        s21_double_to_char(s, (long double)errnum, check, 10);
        s21_strcpy(e, ER);
        s21_strcat(e, s);
    }
  return e;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i <= n - 1) {
    dest[i] = src[i];
    i++;
    if (src[i] == '\0') {
      while (i <= n - 1) {
        dest[i] = '\0';
        i++;
      }
    }
  }
  return dest;
}

char *s21_chrstr(const char *str, int c) {
  char *soul = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (str[i] == c) {
          soul = ((char*)str) + i;
          break;
      }
  }
  return soul;
}

char *s21_strrchr(const char *str, int c) {
  s21_size_t i = 0, j = 0;
  int flag = 0;
  char *soul = s21_NULL;
  while (str[i] != '\0') {
    if (str[i] == c) {
      j = i;
      flag = 1;
    }
    i++;
  }
  if (flag) soul = ((char *)str + j);
  if (c == 0) {
    soul = ((char *)str + i);
  }
  return soul;
}

int s21_strncmp(const char *data1, const char *data2, s21_size_t n) {
  int soul = 0;
  s21_size_t nn = n;
  for (; *data1 == *data2; ++data1, ++data2) {
    n--;
    if (*data2 == '\0' || n == 0) break;
  }
  soul = (unsigned char)*data1 - (unsigned char)*data2;
  return (nn <= 0) ? 0 : soul;
}

char *s21_strtok(char *str, const char *delim) {
  static char *buffer;
  char *ret;
  if (str != s21_NULL) buffer = str;
  if (*buffer == '\0') {
    ret = s21_NULL;
  } else {
    if (*delim == '\0') {
      char *begin = buffer;
      buffer += s21_strlen(buffer);
      ret = begin;
    } else {
      char *b = buffer;
      while (s21_chrstr((char*)delim, (int)*b)) {
        b++;
      }
      if (*b == '\0') {
        ret = s21_NULL;
      } else {
        ret = b;
        for ( ; ; b++) {
          if (s21_chrstr((char*)delim, (int)*b) || *b == '\0') {
            char *ff = b;
            while (s21_chrstr((char*)delim, (int)*b)) {
              b++;
            }
            *ff = '\0';
            buffer = b;
            break;
          }
        }
      }
    }
  }
  return ret;
}


void* s21_to_upper(const char* str) {
    s21_size_t i = 0;
    char* new = s21_calloc(s21_strlen(str));
    s21_strcpy(new, str);
    while (new[i] != '\0') {
        if ((int)new[i] >= 97 && (int)new[i] <= 122)
            new[i] = (char)((int)new[i] - 32);
        i++;
    }
    return new;
}

void* s21_to_lower(const char *str) {
    s21_size_t i = 0;
    char* new = s21_calloc(s21_strlen(str));
    s21_strcpy(new, str);
    while (new[i] != '\0') {
        if ((int)new[i] >= 65 && (int)new[i] <= 90)
            new[i] = (char)((int)new[i] + 32);
        i++;
    }
    return new;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t i = 0, j = 0;
  char *new = s21_calloc(s21_strlen(str) + s21_strlen(src));
  if (!(s21_strlen(str) + s21_strlen(src))) {
    free(new);
    new = NULL;
  }
  while (src[i] != '\0') {
    if (i == start_index) {
      while (str[j] != '\0') {
        new[i + j] = str[j];
        j++;
      }
    }
    new[i + j] = src[i];
    i++;
  }
  new[i + j] = '\0';
  return new;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *soul;
    char * trim_char = s21_NULL;
    if (trim_chars) {
      trim_char = s21_calloc(s21_strlen(trim_chars));
      s21_strcpy(trim_char, trim_chars);
      trim_char = s21_strcat(trim_char, " ");
    }
    if (trim_chars == s21_NULL) {
      trim_char = s21_calloc(5);
      trim_char = " ";
    }
    int i = 0, ii = (s21_strlen(src) - 1);
    for (; src[i] != '\0'; i++) {
        if  (!s21_chrstr(trim_char, src[i])) break;
    }
    for (; ii > i; ii--) {
        if  (!s21_chrstr(trim_char, src[ii])) break;
    }
    soul = s21_calloc(ii-i);
    for (int j = 0; j <= (ii-i); j++) {
        soul[j] = src[i+j];
    }
    if (s21_strlen(trim_char) == 0) {
        free(soul);
        soul = s21_calloc(s21_strlen(src));
        s21_strcpy(soul, src);
    }
    if (trim_chars) free(trim_char);
    return soul;
}

void *s21_calloc(s21_size_t size) {
  char *mas = malloc(size + 5);
  if (mas == s21_NULL) {
    exit(1);
  }
  for (int k = 0; k < (int)size + 5; k++) {
    mas[k] = '\0';
  }
  return mas;
}
