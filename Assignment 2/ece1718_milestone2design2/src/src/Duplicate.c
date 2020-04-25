// Source file is "L/ece1718_milestone2design2/src/Duplicate.cal"

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
extern actor_t Duplicate;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *Duplicate_Stream;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Stream;
static unsigned int numTokens_Stream;
#define SIZE_Stream 4194304
#define tokens_Stream Duplicate_Stream->contents

extern connection_t connection_Duplicate_Stream;
#define rate_Stream connection_Duplicate_Stream.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Source;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Duplicate_Actual_data;
extern fifo_u8_t *Duplicate_Data_To_Be_Manipulated;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Actual_data;
#define NUM_READERS_Actual_data 1
#define SIZE_Actual_data 4194304
#define tokens_Actual_data Duplicate_Actual_data->contents

static unsigned int index_Data_To_Be_Manipulated;
#define NUM_READERS_Data_To_Be_Manipulated 1
#define SIZE_Data_To_Be_Manipulated 4194304
#define tokens_Data_To_Be_Manipulated Duplicate_Data_To_Be_Manipulated->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Abs_Diff;
extern actor_t Approx;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 i = 0;
static i32 j = 0;
static u8 M[368640];



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Stream() {
	index_Stream = Duplicate_Stream->read_inds[0];
	numTokens_Stream = index_Stream + fifo_u8_get_num_tokens(Duplicate_Stream, 0);
}

static void read_end_Stream() {
	Duplicate_Stream->read_inds[0] = index_Stream;
}

static void write_Actual_data() {
	index_Actual_data = Duplicate_Actual_data->write_ind;
}

static void write_end_Actual_data() {
	Duplicate_Actual_data->write_ind = index_Actual_data;
}
static void write_Data_To_Be_Manipulated() {
	index_Data_To_Be_Manipulated = Duplicate_Data_To_Be_Manipulated->write_ind;
}

static void write_end_Data_To_Be_Manipulated() {
	Duplicate_Data_To_Be_Manipulated->write_ind = index_Data_To_Be_Manipulated;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_build_list() {
	i32 result;
	i32 local_i;

	local_i = i;
	result = local_i < 368640;
	return result;
}

static void build_list() {
	u8 In1;
	i32 local_i;
	u8 tmp_M;
	In1 = tokens_Stream[(index_Stream + (0)) % SIZE_Stream];
	local_i = i;
	M[local_i] = In1;
	local_i = i;
	tmp_M = M[local_i];
	printf("Duplicate: %u\n", tmp_M);
	local_i = i;
	i = local_i + 1;
	// Update ports indexes
	index_Stream += 1;
	rate_Stream += 1;
}
static i32 isSchedulable_untagged_0() {
	i32 result;
	i32 local_i;
	i32 local_j;

	local_i = i;
	local_j = j;
	result = (local_i == 368640 && local_j < 368640);
	return result;
}

static void untagged_0() {
	u8 out1;
	u8 out2;
	i32 local_j;
	local_j = j;
	out1 = M[local_j];
	local_j = j;
	out2 = M[local_j];
	local_j = j;
	j = local_j + 1;
	tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data] = out1;
	tokens_Data_To_Be_Manipulated[(index_Data_To_Be_Manipulated + (0)) % SIZE_Data_To_Be_Manipulated] = out2;
	// Update ports indexes
	index_Actual_data += 1;
	index_Data_To_Be_Manipulated += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Duplicate_initialize(schedinfo_t *si) {
	int i = 0;
	write_Actual_data();
	write_Data_To_Be_Manipulated();
finished:
	write_end_Actual_data();
	write_end_Data_To_Be_Manipulated();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void Duplicate_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Stream();
	write_Actual_data();
	write_Data_To_Be_Manipulated();

	while (1) {
		if (isSchedulable_untagged_0()) {
			int stop = 0;
			if (1 > SIZE_Actual_data - index_Actual_data + Duplicate_Actual_data->read_inds[0]) {
				stop = 1;
			}
			if (1 > SIZE_Data_To_Be_Manipulated - index_Data_To_Be_Manipulated + Duplicate_Data_To_Be_Manipulated->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			untagged_0();
			i++;
		} else if (numTokens_Stream - index_Stream >= 1 && isSchedulable_build_list()) {
			build_list();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Stream();
	write_end_Actual_data();
	write_end_Data_To_Be_Manipulated();
}
