// Source file is "L/ece1718_milestone2/src/Abs_Diff2.cal"

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
extern actor_t Abs_Diff;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *Abs_Diff_Approxed_Data;
extern fifo_u8_t *Abs_Diff_Actual_data;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Approxed_Data;
static unsigned int numTokens_Approxed_Data;
#define SIZE_Approxed_Data 8192
#define tokens_Approxed_Data Abs_Diff_Approxed_Data->contents

extern connection_t connection_Abs_Diff_Approxed_Data;
#define rate_Approxed_Data connection_Abs_Diff_Approxed_Data.rate

static unsigned int index_Actual_data;
static unsigned int numTokens_Actual_data;
#define SIZE_Actual_data 8192
#define tokens_Actual_data Abs_Diff_Actual_data->contents

extern connection_t connection_Abs_Diff_Actual_data;
#define rate_Actual_data connection_Abs_Diff_Actual_data.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Approx;
extern actor_t Duplicate;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Abs_Diff_Abs_diff;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Abs_diff;
#define NUM_READERS_Abs_diff 1
#define SIZE_Abs_diff 8192
#define tokens_Abs_diff Abs_Diff_Abs_diff->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Sum;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 temp;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Approxed_Data() {
	index_Approxed_Data = Abs_Diff_Approxed_Data->read_inds[0];
	numTokens_Approxed_Data = index_Approxed_Data + fifo_u8_get_num_tokens(Abs_Diff_Approxed_Data, 0);
}

static void read_end_Approxed_Data() {
	Abs_Diff_Approxed_Data->read_inds[0] = index_Approxed_Data;
}
static void read_Actual_data() {
	index_Actual_data = Abs_Diff_Actual_data->read_inds[0];
	numTokens_Actual_data = index_Actual_data + fifo_u8_get_num_tokens(Abs_Diff_Actual_data, 0);
}

static void read_end_Actual_data() {
	Abs_Diff_Actual_data->read_inds[0] = index_Actual_data;
}

static void write_Abs_diff() {
	index_Abs_diff = Abs_Diff_Abs_diff->write_ind;
}

static void write_end_Abs_diff() {
	Abs_Diff_Abs_diff->write_ind = index_Abs_diff;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_untagged_0() {
	i32 result;
	u8 b;
	u8 a;

	b = tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data];
	a = tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data];
	result = a > b;
	return result;
}

static void untagged_0() {
	u8 a;
	u8 b;
	u8 out1;
	i32 local_temp;
	a = tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data];
	b = tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data];
	temp = a - b;
	local_temp = temp;
	if (local_temp >= 1) {
		local_temp = temp;
		out1 = 2 - local_temp;
	} else {
		local_temp = temp;
		out1 = local_temp;
	}
	printf("Abs-Diff1 %u %u %u\n", a, b, out1);
	tokens_Abs_diff[(index_Abs_diff + (0)) % SIZE_Abs_diff] = out1;
	// Update ports indexes
	index_Actual_data += 1;
	index_Approxed_Data += 1;
	index_Abs_diff += 1;
	rate_Actual_data += 1;
	rate_Approxed_Data += 1;
}
static i32 isSchedulable_untagged_1() {
	i32 result;
	u8 b;
	u8 a;

	b = tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data];
	a = tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data];
	result = a < b;
	return result;
}

static void untagged_1() {
	u8 a;
	u8 b;
	u8 out1;
	i32 local_temp;
	a = tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data];
	b = tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data];
	temp = b - a;
	local_temp = temp;
	if (local_temp >= 1) {
		local_temp = temp;
		out1 = 2 - local_temp;
	} else {
		local_temp = temp;
		out1 = local_temp;
	}
	printf("Abs-Diff2 %u %u %u\n", a, b, out1);
	tokens_Abs_diff[(index_Abs_diff + (0)) % SIZE_Abs_diff] = out1;
	// Update ports indexes
	index_Actual_data += 1;
	index_Approxed_Data += 1;
	index_Abs_diff += 1;
	rate_Actual_data += 1;
	rate_Approxed_Data += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Abs_Diff_initialize(schedinfo_t *si) {
	int i = 0;
	write_Abs_diff();
finished:
	write_end_Abs_diff();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void Abs_Diff_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Approxed_Data();
	read_Actual_data();
	write_Abs_diff();

	while (1) {
		if (numTokens_Actual_data - index_Actual_data >= 1 && numTokens_Approxed_Data - index_Approxed_Data >= 1 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (1 > SIZE_Abs_diff - index_Abs_diff + Abs_Diff_Abs_diff->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_0();
			i++;
		} else if (numTokens_Actual_data - index_Actual_data >= 1 && numTokens_Approxed_Data - index_Approxed_Data >= 1 && isSchedulable_untagged_1()) {
			int stop = 0;
			if (1 > SIZE_Abs_diff - index_Abs_diff + Abs_Diff_Abs_diff->read_inds[0]) {
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

	read_end_Approxed_Data();
	read_end_Actual_data();
	write_end_Abs_diff();
}
