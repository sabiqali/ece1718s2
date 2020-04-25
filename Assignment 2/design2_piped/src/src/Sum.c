// Source file is "L/design2_piped/src/Sum.cal"

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
extern actor_t Sum;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *Sum_Abs_diff;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Abs_diff;
static unsigned int numTokens_Abs_diff;
#define SIZE_Abs_diff 8388608
#define tokens_Abs_diff Sum_Abs_diff->contents

extern connection_t connection_Sum_Abs_diff;
#define rate_Abs_diff connection_Sum_Abs_diff.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Abs_Diff;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Sum_Sad_vals;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Sad_vals;
#define NUM_READERS_Sad_vals 1
#define SIZE_Sad_vals 8388608
#define tokens_Sad_vals Sum_Sad_vals->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Printer;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 i = 0;
static i32 sum = 0;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Abs_diff() {
	index_Abs_diff = Sum_Abs_diff->read_inds[0];
	numTokens_Abs_diff = index_Abs_diff + fifo_u8_get_num_tokens(Sum_Abs_diff, 0);
}

static void read_end_Abs_diff() {
	Sum_Abs_diff->read_inds[0] = index_Abs_diff;
}

static void write_Sad_vals() {
	index_Sad_vals = Sum_Sad_vals->write_ind;
}

static void write_end_Sad_vals() {
	Sum_Sad_vals->write_ind = index_Sad_vals;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;
	i32 local_i;

	local_i = i;
	result = local_i < 2560;
	return result;
}

static void untagged_0() {
	u8 a;
	i32 local_sum;
	i32 local_i;
	a = tokens_Abs_diff[(index_Abs_diff + (0)) % SIZE_Abs_diff];
	local_sum = sum;
	sum = local_sum + a;
	local_i = i;
	i = local_i + 1;
	// Update ports indexes
	index_Abs_diff += 1;
	rate_Abs_diff += 1;
}
static i32 isSchedulable_untagged_1() {
	i32 result;
	i32 local_i;

	local_i = i;
	result = local_i == 2560;
	return result;
}

static void untagged_1() {
	u8 out1;
	i32 local_sum;
	local_sum = sum;
	out1 = local_sum;
	tokens_Sad_vals[(index_Sad_vals + (0)) % SIZE_Sad_vals] = out1;
	// Update ports indexes
	index_Sad_vals += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Sum_initialize(schedinfo_t *si) {
	int i = 0;
	write_Sad_vals();
finished:
	write_end_Sad_vals();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void Sum_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Abs_diff();
	write_Sad_vals();

	while (1) {
		if (numTokens_Abs_diff - index_Abs_diff >= 1 && isSchedulable_untagged_0()) {
			untagged_0();
			i++;
		} else if (isSchedulable_untagged_1()) {
			int stop = 0;
			if (1 > SIZE_Sad_vals - index_Sad_vals + Sum_Sad_vals->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_1();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Abs_diff();
	write_end_Sad_vals();
}
