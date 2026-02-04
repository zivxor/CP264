/**
 * -------------------------------------
 * @file  myword.c
 * -------------------------------------
 * @author Luka Zivkovic, 169102858, zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */

#include "myword.h"
#include <ctype.h>
#include <string.h>

/*
 * Load word data from file, and insert words a directory represented by char
 * array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are
 * stored. It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */
int create_dictionary(FILE *fp, char *dictionary) {
  int count = 0;
  char word[20];
  char *ptr = dictionary;
  int i = 0;
  int c;

  // Read comma-separated words from file
  while ((c = fgetc(fp)) != EOF) {
    if (c == ',' || c == '\n' || c == '\r') {
      if (i > 0) {
        word[i] = '\0';
        strcpy(ptr, word);
        ptr += strlen(word) + 1;
        count++;
        i = 0;
      }
    } else if (i < 19) {
      word[i++] = c;
    }
  }

  // Handle last word if file doesn't end with comma/newline
  if (i > 0) {
    word[i] = '\0';
    strcpy(ptr, word);
    ptr += strlen(word) + 1;
    count++;
  }

  *ptr = '\0'; // Mark end of dictionary

  return count;
}

/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */
BOOLEAN contain_word(char *dictionary, char *word) {
  char *ptr = dictionary;

  while (*ptr != '\0') {
    if (strcmp(ptr, word) == 0) {
      return TRUE;
    }
    ptr += strlen(ptr) + 1;
  }

  return FALSE;
}

/*
 * Process text data from a file for word statistic information of line count,
 * word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
  WORDSTATS stats = {0, 0, 0};
  char line[1000];
  char word[20];
  int i, j, found;

  while (fgets(line, sizeof(line), fp) != NULL) {
    stats.line_count++;

    // Parse words from line
    i = 0;
    while (line[i] != '\0') {
      // Skip non-alphabetic characters
      while (line[i] != '\0' && !isalpha(line[i])) {
        i++;
      }

      if (line[i] == '\0')
        break;

      // Extract word
      j = 0;
      while (line[i] != '\0' && isalpha(line[i]) && j < 19) {
        word[j++] = tolower(line[i++]);
      }
      word[j] = '\0';

      if (j > 0) {
        stats.word_count++;

        // Check if it's not a common word (not in dictionary)
        if (!contain_word(dictionary, word)) {
          // Check if word already exists in words array
          found = 0;
          for (int k = 0; k < stats.keyword_count; k++) {
            if (strcmp(words[k].word, word) == 0) {
              words[k].count++;
              found = 1;
              break;
            }
          }

          // Add new keyword
          if (!found) {
            strcpy(words[stats.keyword_count].word, word);
            words[stats.keyword_count].count = 1;
            stats.keyword_count++;
          }
        }
      }
    }
  }

  return stats;
}