/**
 * -------------------------------------
 * @file  mystring.c
 * -------------------------------------
 * @author Luka Zivkovic, 169102858, zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */

#include "mystring.h"
#include <stdio.h>
#include <string.h>

/**
 * Count the number words of given simple string. A word starts with an English
 * charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */
int str_words(char *s) {
  int count = 0;
  int in_word = 0;

  while (*s) {
    if ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
      if (!in_word) {
        in_word = 1;
        count++;
      }
    } else {
      in_word = 0;
    }
    s++;
  }
  return count;
}

/**
 * Change every upper case English letter to its lower case of string passed by
 * s.
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */
int str_lower(char *s) {
  int flips = 0;

  while (*s) {
    if (*s >= 'A' && *s <= 'Z') {
      *s += ('a' - 'A'); // Convert to lower case
      flips++;
    }
    s++;
  }
  return flips;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s) {
  char *src = s;
  char *dst = s;
  int in_space = 0;

  // Skip leading spaces
  while (*src == ' ' || *src == '\t') {
    src++;
  }

  while (*src) {
    if (*src == ' ' || *src == '\t') {
      if (!in_space) {
        *dst++ = ' ';
        in_space = 1;
      }
    } else {
      *dst++ = *src;
      in_space = 0;
    }
    src++;
  }

  // Remove trailing space if exists
  if (dst > s && *(dst - 1) == ' ') {
    dst--;
  }

  *dst = '\0';
}