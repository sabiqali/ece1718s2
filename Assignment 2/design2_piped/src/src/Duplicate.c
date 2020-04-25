// Source file is "L/design2_piped/src/Duplicate.cal"

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
extern fifo_u8_t *Duplicate_send_flag;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Stream;
static unsigned int numTokens_Stream;
#define SIZE_Stream 8388608
#define tokens_Stream Duplicate_Stream->contents

extern connection_t connection_Duplicate_Stream;
#define rate_Stream connection_Duplicate_Stream.rate

static unsigned int index_send_flag;
static unsigned int numTokens_send_flag;
#define SIZE_send_flag 8388608
#define tokens_send_flag Duplicate_send_flag->contents

extern connection_t connection_Duplicate_send_flag;
#define rate_send_flag connection_Duplicate_send_flag.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Source;
extern actor_t Approx;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Duplicate_Actual_data;
extern fifo_u8_t *Duplicate_Data_To_Be_Manipulated;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Actual_data;
#define NUM_READERS_Actual_data 1
#define SIZE_Actual_data 8388608
#define tokens_Actual_data Duplicate_Actual_data->contents

static unsigned int index_Data_To_Be_Manipulated;
#define NUM_READERS_Data_To_Be_Manipulated 1
#define SIZE_Data_To_Be_Manipulated 8388608
#define tokens_Data_To_Be_Manipulated Duplicate_Data_To_Be_Manipulated->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Abs_Diff;
extern actor_t Approx;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 i = 0;
static i32 j = 0;
static i32 k = 0;
static u8 M[2560];



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Stream() {
	index_Stream = Duplicate_Stream->read_inds[0];
	numTokens_Stream = index_Stream + fifo_u8_get_num_tokens(Duplicate_Stream, 0);
}

static void read_end_Stream() {
	Duplicate_Stream->read_inds[0] = index_Stream;
}
static void read_send_flag() {
	index_send_flag = Duplicate_send_flag->read_inds[0];
	numTokens_send_flag = index_send_flag + fifo_u8_get_num_tokens(Duplicate_send_flag, 0);
}

static void read_end_send_flag() {
	Duplicate_send_flag->read_inds[0] = index_send_flag;
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
	u8 flag;
	i32 local_i;

	flag = tokens_send_flag[(index_send_flag + (0)) % SIZE_send_flag];
	local_i = i;
	result = (local_i < 368640 && flag == 0);
	return result;
}

static void build_list() {
	u8 In1;
	u8 flag;
	u8 out1;
	u8 out2;
	i32 local_j;
	i32 local_i;
	i32 local_k;
	In1 = tokens_Stream[(index_Stream + (0)) % SIZE_Stream];
	flag = tokens_send_flag[(index_send_flag + (0)) % SIZE_send_flag];
	local_j = j;
	M[local_j] = In1;
	printf("flag: %u\n", flag);
	local_i = i;
	i = local_i + 1;
	local_j = j;
	j = local_j + 1;
	local_j = j;
	if (local_j % 2560 == 0) {
		local_k = k;
		while (local_k < 2560) {
			local_k = k;
			out1 = M[local_k];
			local_k = k;
			out2 = M[local_k];
			local_k = k;
			k = local_k + 1;
			local_k = k;
			printf("Duplicate2: %u %u %i\n", out1, out2, local_k);
			local_k = k;
		}
		j = 0;
	}
	k = 0;
	tokens_Actual_data[(index_Actual_data + (0)) % SIZE_Actual_data] = out1;
	tokens_Data_To_Be_Manipulated[(index_Data_To_Be_Manipulated + (0)) % SIZE_Data_To_Be_Manipulated] = out2;
	// Update ports indexes
	index_Stream += 1;
	index_send_flag += 1;
	index_Actual_data += 1;
	index_Data_To_Be_Manipulated += 1;
	rate_Stream += 1;
	rate_send_flag += 1;
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
	read_send_flag();
	write_Actual_data();
	write_Data_To_Be_Manipulated();

	while (1) {
		if (numTokens_Stream - index_Stream >= 1 && numTokens_send_flag - index_send_flag >= 1 && isSchedulable_build_list()) {
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
	read_end_send_flag();
	write_end_Actual_data();
	write_end_Data_To_Be_Manipulated();
}
