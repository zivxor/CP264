#include "avl_myrecord.h"
#include "avl.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Helper: recursively insert all nodes from source tree into dest tree */
static void avl_merge_helper(AVLNODE **rootp_dest, AVLNODE *source) {
  if (!source)
    return;
  avl_insert(rootp_dest, source->data);
  avl_merge_helper(rootp_dest, source->left);
  avl_merge_helper(rootp_dest, source->right);
}

void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source) {
  if (!rootp_dest || !rootp_source)
    return;
  avl_merge_helper(rootp_dest, *rootp_source);
}

void avlds_merge(AVLDS *dest, AVLDS *source) {
  if (!dest || !source)
    return;

  int n1 = dest->count;
  int n2 = source->count;
  int n = n1 + n2;

  if (n == 0)
    return;

  float mean1 = dest->mean;
  float mean2 = source->mean;
  float var1 = dest->stddev * dest->stddev;
  float var2 = source->stddev * source->stddev;

  float new_mean = (n1 * mean1 + n2 * mean2) / n;
  float new_var = (n1 * (var1 + (mean1 - new_mean) * (mean1 - new_mean)) +
                   n2 * (var2 + (mean2 - new_mean) * (mean2 - new_mean))) /
                  n;

  avl_merge(&dest->root, &source->root);
  dest->count = n;
  dest->mean = new_mean;
  dest->stddev = sqrtf(new_var);

  avlds_clean(source);
}

void avlds_clean(AVLDS *ds) {
  if (!ds)
    return;
  avl_clean(&ds->root);
  ds->count = 0;
  ds->mean = 0.0f;
  ds->stddev = 0.0f;
}

void add_record(AVLDS *ds, RECORD data) {
  if (!ds)
    return;
  if (avl_search(ds->root, data.name))
    return;

  avl_insert(&ds->root, data);

  int n = ds->count;
  if (n <= 0) {
    ds->count = 1;
    ds->mean = data.score;
    ds->stddev = 0.0f;
    return;
  }

  float old_mean = ds->mean;
  float old_var = ds->stddev * ds->stddev;
  int new_n = n + 1;

  float new_mean = old_mean + (data.score - old_mean) / new_n;
  float new_var =
      (n * old_var + (data.score - old_mean) * (data.score - new_mean)) / new_n;

  ds->count = new_n;
  ds->mean = new_mean;
  ds->stddev = sqrtf(new_var);
}

void remove_record(AVLDS *ds, char *name) {
  if (!ds || !name || !ds->root || ds->count <= 0)
    return;

  AVLNODE *node = avl_search(ds->root, name);
  if (!node)
    return;

  float x = node->data.score;
  int n = ds->count;

  if (n == 1) {
    avl_delete(&ds->root, name);
    ds->count = 0;
    ds->mean = 0.0f;
    ds->stddev = 0.0f;
    return;
  }

  float old_mean = ds->mean;
  float old_var = ds->stddev * ds->stddev;
  int new_n = n - 1;

  float new_mean = (old_mean * n - x) / new_n;
  float new_var = (n * old_var - (x - old_mean) * (x - new_mean)) / new_n;
  if (new_var < 0.0f)
    new_var = 0.0f;

  avl_delete(&ds->root, name);

  ds->count = new_n;
  ds->mean = new_mean;
  ds->stddev = sqrtf(new_var);
}
