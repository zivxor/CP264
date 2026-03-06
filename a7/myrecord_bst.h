#include "bst.h"
/* Define structure data type BSTSD contains pointer to the BSTNODE root
 * and count, mean, and stddev fields for stats of record data stored in
 * the BSTDS.
 */
typedef struct {
  BSTNODE *root;
  int count;
  float mean;
  float stddev;   
} BSTDS;

/* Add a record data into the BSTDS and update its statistic fields 
 * using incremental/online algorithm.
 * @parame dsp - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *dsp, RECORD record);

/* Delete a node from BSTDA with data.name matching with the given name
 * and stats fields using incremental/online algorithm.
 * @parame dsp - pointer to the BSTDS.
 * @parama name - node data.name to be removed.
 */
void remove_record(BSTDS *dsp, char *name);

/* Clean the BSTDS and reset count, mean, stddev
 * @parame dsp - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *dsp);