#include "myrecord.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* comparator for RECORD, sort by score descending for qsort */
static int cmp_score_desc(const void *x, const void *y) {
  float sx = ((const RECORD *)x)->score;
  float sy = ((const RECORD *)y)->score;

  if (sx < sy)
    return 1; // x should come after y (descending)
  else if (sx > sy)
    return -1; // x should come before y
  else
    return 0;
}

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77), B-=[70, 73),
 * C+=[67, 70), C=[63, 67), C-=[60, 63), D+=[57,60), D=[53,57), D-=[50,53),
 * F=[0,50). Use binary search algorithm to find the corresponding letter grade.
 */
GRADE grade(float score) {
  static const float bounds[] = {0,  50, 53, 57, 60, 63, 67,
                                 70, 73, 77, 80, 85, 90, 101};
  static const char *letters[] = {"F",  "D-", "D",  "D+", "C-", "C", "C+",
                                  "B-", "B",  "B+", "A-", "A",  "A+"};
  const int N = (int)(sizeof(letters) / sizeof(letters[0]));

  int left = 0, right = N - 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (score < bounds[mid + 1]) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  GRADE g;
  snprintf(g.letter_grade, sizeof(g.letter_grade), "%s", letters[left]);
  return g;
}

/*
 * Import record data from file and store all record entries
 * in the RECORD array passed by dataset, return the number of records.
 */
int import_data(FILE *fp, RECORD *dataset) {
  char line[64];
  int count = 0;

  if (fp == NULL || dataset == NULL)
    return 0;

  while (fgets(line, sizeof(line), fp)) {
    /* Remove newline characters (both \n and \r\n cases) */
    line[strcspn(line, "\r\n")] = '\0';

    /* Parse name and score from comma-separated line */
    if (sscanf(line, "%19[^,],%f", dataset[count].name,
               &dataset[count].score) == 2) {
      count++;
    }
  }
  return count;
}

/*
 * Compute count, mean, stddev, and median from dataset.
 */
STATS process_data(RECORD *dataset, int count) {
  STATS stats = {0, 0.0f, 0.0f, 0.0f};

  if (dataset == NULL || count <= 0)
    return stats;

  /* mean */
  float total = 0.0f;
  for (int i = 0; i < count; i++) {
    total += dataset[i].score; // use float, not int
  }
  float mean = total / count;

  /* standard deviation (population version, divide by count) */
  float variance_sum = 0.0f;
  for (int i = 0; i < count; i++) {
    float diff = dataset[i].score - mean;
    variance_sum += diff * diff;
  }
  float std = sqrtf(variance_sum / count);

  /* median: need a sorted copy (order doesn't matter for median) */
  RECORD *temp = malloc(count * sizeof(RECORD));
  if (temp == NULL) {
    stats.count = count;
    stats.mean = mean;
    stats.stddev = std;
    stats.median = 0.0f;
    return stats;
  }

  for (int i = 0; i < count; i++) {
    temp[i] = dataset[i];
  }
  qsort(temp, count, sizeof(RECORD), cmp_score_desc);

  float median;
  if (count % 2 == 0) {
    median = (temp[count / 2 - 1].score + temp[count / 2].score) / 2.0f;
  } else {
    median = temp[count / 2].score;
  }

  free(temp);

  stats.count = count;
  stats.mean = mean;
  stats.stddev = std;
  stats.median = median;

  return stats;
}

/*
 * Write stats and grade report to fp.
 * Records are sorted by score in decreasing order.
 */
int report_data(FILE *fp, RECORD *dataset, STATS stats) {
  if (fp == NULL || dataset == NULL || stats.count < 1)
    return 0;

  /* Make a sorted copy of dataset */
  RECORD *sorted = malloc(stats.count * sizeof(RECORD));
  if (sorted == NULL)
    return 0;

  for (int i = 0; i < stats.count; i++) {
    sorted[i] = dataset[i];
  }
  qsort(sorted, stats.count, sizeof(RECORD), cmp_score_desc);

  /* Statistics header – matches style used in the test driver */
  fprintf(fp, "Stats     value\n");
  fprintf(fp, "%-10s%-6d\n", "count", stats.count);
  fprintf(fp, "%-10s%-6.1f\n", "mean", stats.mean);
  fprintf(fp, "%-10s%-6.1f\n", "stddev", stats.stddev);
  fprintf(fp, "%-10s%-6.1f\n", "median", stats.median);

  /* Records: name, score %, grade */
  fprintf(fp, "\nname:score,grade\n");

  for (int i = 0; i < stats.count; i++) {
    GRADE g = grade(sorted[i].score);
    fprintf(fp, "%s:%6.1f,%s\n", sorted[i].name, sorted[i].score,
            g.letter_grade);
  }

  free(sorted);
  return 1;
}