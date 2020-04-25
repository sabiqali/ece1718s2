// Source file is "L/ece1718_milestone2/src/Approx.cal"

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
extern actor_t Approx;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *Approx_Data_To_Be_Manipulated;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Data_To_Be_Manipulated;
static unsigned int numTokens_Data_To_Be_Manipulated;
#define SIZE_Data_To_Be_Manipulated 8192
#define tokens_Data_To_Be_Manipulated Approx_Data_To_Be_Manipulated->contents

extern connection_t connection_Approx_Data_To_Be_Manipulated;
#define rate_Data_To_Be_Manipulated connection_Approx_Data_To_Be_Manipulated.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Duplicate;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Approx_Approxed_Data;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Approxed_Data;
#define NUM_READERS_Approxed_Data 1
#define SIZE_Approxed_Data 8192
#define tokens_Approxed_Data Approx_Approxed_Data->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Abs_Diff;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 divi = 0;
static i32 new_num = 0;
static i32 diff1 = 0;
static i32 diff2 = 0;
static i32 temp = 0;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Data_To_Be_Manipulated() {
	index_Data_To_Be_Manipulated = Approx_Data_To_Be_Manipulated->read_inds[0];
	numTokens_Data_To_Be_Manipulated = index_Data_To_Be_Manipulated + fifo_u8_get_num_tokens(Approx_Data_To_Be_Manipulated, 0);
}

static void read_end_Data_To_Be_Manipulated() {
	Approx_Data_To_Be_Manipulated->read_inds[0] = index_Data_To_Be_Manipulated;
}

static void write_Approxed_Data() {
	index_Approxed_Data = Approx_Approxed_Data->write_ind;
}

static void write_end_Approxed_Data() {
	Approx_Approxed_Data->write_ind = index_Approxed_Data;
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
	u8 a;
	u8 out1;
	i32 local_divi;
	i32 local_new_num;
	i32 local_temp;
	i32 local_diff2;
	i32 local_diff1;
	a = tokens_Data_To_Be_Manipulated[(index_Data_To_Be_Manipulated + (0)) % SIZE_Data_To_Be_Manipulated];
	divi = a / 2;
	local_divi = divi;
	new_num = local_divi * 2;
	local_divi = divi;
	temp = (local_divi + 1) * 2;
	local_new_num = new_num;
	diff1 = a - local_new_num;
	local_temp = temp;
	diff2 = local_temp - a;
	local_diff2 = diff2;
	local_diff1 = diff1;
	if (local_diff2 >= local_diff1) {
		local_temp = temp;
		out1 = local_temp;
	} else {
		local_new_num = new_num;
		out1 = local_new_num;
	}
	tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data] = out1;
	// Update ports indexes
	index_Data_To_Be_Manipulated += 1;
	index_Approxed_Data += 1;
	rate_Data_To_Be_Manipulated += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Approx_initialize(schedinfo_t *si) {
	int i = 0;
	write_Approxed_Data();
finished:
	write_end_Approxed_Data();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void Approx_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Data_To_Be_Manipulated();
	write_Approxed_Data();

	while (1) {
		if (numTokens_Data_To_Be_Manipulated - index_Data_To_Be_Manipulated >= 1 && isSchedulable_untagged_0()) {
			int stop = 0;
			if (1 > SIZE_Approxed_Data - index_Approxed_Data + Approx_Approxed_Data->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_0();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Data_To_Be_Manipulated();
	write_end_Approxed_Data();
}
