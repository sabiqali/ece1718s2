// Source file is "L/design2_piped/src/Printer.cal"

#include <stdio.h>
#include <stdlib.h>
#include "orcc_config.h"

#include "types.h"
#include "fifo.h"
#include "util.h"
#include "scheduler.h"
#include "dataflow.h"
#include "cycle.h"


////////////////////////////////////////////////////////////////////////////////
// Instance
extern actor_t Printer;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u32_t *Printer_Sad_vals;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Sad_vals;
static unsigned int numTokens_Sad_vals;
#define SIZE_Sad_vals 8388608
#define tokens_Sad_vals Printer_Sad_vals->contents

extern connection_t connection_Printer_Sad_vals;
#define rate_Sad_vals connection_Printer_Sad_vals.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Sum;




////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Sad_vals() {
	index_Sad_vals = Printer_Sad_vals->read_inds[0];
	numTokens_Sad_vals = index_Sad_vals + fifo_u32_get_num_tokens(Printer_Sad_vals, 0);
}

static void read_end_Sad_vals() {
	Printer_Sad_vals->read_inds[0] = index_Sad_vals;
}


////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0() {
	u32 a;
	a = tokens_Sad_vals[(index_Sad_vals + (0)) % SIZE_Sad_vals];
	// Update ports indexes
	index_Sad_vals += 1;
	rate_Sad_vals += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Printer_initialize(schedinfo_t *si) {
	int i = 0;
finished:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void Printer_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Sad_vals();

	while (1) {
		if (numTokens_Sad_vals - index_Sad_vals >= 1 && isSchedulable_untagged_0()) {
			untagged_0();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Sad_vals();
}
