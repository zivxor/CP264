#include "myrecord_bst.h"
#include <math.h>
#include <string.h>

/* Add a record data into the BSTDS and update its statistic fields
 * using incremental/online algorithm.
 * @parame dsp - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *dsp, RECORD record) {
  if (dsp == NULL) {
    return;
  }

  /* Keep stats unchanged when the name already exists. */
  if (bst_search(dsp->root, record.name) != NULL) {
    return;
  }

  bst_insert(&dsp->root, record);

  int n = dsp->count;
  if (n <= 0) {
    dsp->count = 1;
    dsp->mean = record.score;
    dsp->stddev = 0.0f;
    return;
  }

  float old_mean = dsp->mean;
  float old_var = dsp->stddev * dsp->stddev;
  int new_n = n + 1;

  float new_mean = old_mean + (record.score - old_mean) / new_n;
  float new_var = (n * old_var + (record.score - old_mean) * (record.score - new_mean)) / new_n;

  dsp->count = new_n;
  dsp->mean = new_mean;
  dsp->stddev = sqrtf(new_var);
}

/* Delete a node from BSTDA with data.name matching with the given name
 * and stats fields using incremental/online algorithm.
 * @parame dsp - pointer to the BSTDS.
 * @parama name - node data.name to be removed.
 */
void remove_record(BSTDS *dsp, char *name) {
  if (dsp == NULL || name == NULL || dsp->root == NULL || dsp->count <= 0) {
    return;
  }

  BSTNODE *node = bst_search(dsp->root, name);
  if (node == NULL) {
    return;
  }

  float x = node->data.score;
  int n = dsp->count;

  if (n == 1) {
    bst_delete(&dsp->root, name);
    dsp->count = 0;
    dsp->mean = 0.0f;
    dsp->stddev = 0.0f;
    return;
  }

  float old_mean = dsp->mean;
  float old_var = dsp->stddev * dsp->stddev;
  int new_n = n - 1;

  float new_mean = (old_mean * n - x) / new_n;
  float new_var = (n * old_var - (x - old_mean) * (x - new_mean)) / new_n;
  if (new_var < 0.0f) {
    new_var = 0.0f;
  }

  bst_delete(&dsp->root, name);

  dsp->count = new_n;
  dsp->mean = new_mean;
  dsp->stddev = sqrtf(new_var);
}

/* Clean the BSTDS and reset count, mean, stddev
 * @parame dsp - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *dsp) {
  if (dsp == NULL) {
    return;
  }

  bst_clean(&dsp->root);
  dsp->count = 0;
  dsp->mean = 0.0f;
  dsp->stddev = 0.0f;
}
