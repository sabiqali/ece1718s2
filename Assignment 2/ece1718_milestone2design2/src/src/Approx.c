// Source file is "L/ece1718_milestone2design2/src/Approx6.cal"

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
#define SIZE_Data_To_Be_Manipulated 4194304
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
#define SIZE_Approxed_Data 4194304
#define tokens_Approxed_Data Approx_Approxed_Data->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Abs_Diff;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 i = 0;
static i32 j = 0;
static i32 l = 0;
static i32 jcount = 0;
static i32 k = 640;
static i32 a = 0;
static i8 h = 0;
static i32 compute_flag = 0;
static i32 send_flag = 0;
static i32 m = 640;
static i32 n = 576;
static i32 sum = 0;
static i32 diff = 0;
static i32 o = 1280;
static i32 p = 1920;
static u8 M[368640];
static u8 N[368640];



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
	In1 = tokens_Data_To_Be_Manipulated[(index_Data_To_Be_Manipulated + (0)) % SIZE_Data_To_Be_Manipulated];
	local_i = i;
	M[local_i] = In1;
	local_i = i;
	i = local_i + 1;
	// Update ports indexes
	index_Data_To_Be_Manipulated += 1;
	rate_Data_To_Be_Manipulated += 1;
}
static i32 isSchedulable_read_list() {
	i32 result;
	i32 local_i;
	i32 local_o;
	i32 local_p;
	i32 local_k;
	i32 local_j;

	local_i = i;
	local_o = o;
	local_p = p;
	local_k = k;
	local_j = j;
	result = ((((local_i == 368640 && local_o < 368000) && local_p < 368640) && local_k < 367360) && local_j < 366720);
	return result;
}

static void read_list() {
	i32 local_j;
	u8 tmp_M;
	u8 tmp_M0;
	u8 tmp_M1;
	u8 tmp_M2;
	i32 local_k;
	u8 tmp_M3;
	u8 tmp_M4;
	u8 tmp_M5;
	u8 tmp_M6;
	i32 local_o;
	u8 tmp_M7;
	u8 tmp_M8;
	u8 tmp_M9;
	u8 tmp_M10;
	i32 local_p;
	u8 tmp_M11;
	u8 tmp_M12;
	u8 tmp_M13;
	u8 tmp_M14;
	i8 local_h;
	u8 tmp_M15;
	u8 tmp_N;
	u8 tmp_M16;
	u8 tmp_N0;
	u8 tmp_M17;
	u8 tmp_N1;
	u8 tmp_M18;
	u8 tmp_N2;
	u8 tmp_M19;
	u8 tmp_N3;
	u8 tmp_M20;
	u8 tmp_N4;
	u8 tmp_M21;
	u8 tmp_N5;
	u8 tmp_M22;
	u8 tmp_N6;
	u8 tmp_M23;
	u8 tmp_N7;
	u8 tmp_M24;
	u8 tmp_N8;
	u8 tmp_M25;
	u8 tmp_N9;
	u8 tmp_M26;
	u8 tmp_N10;
	u8 tmp_M27;
	u8 tmp_N11;
	u8 tmp_M28;
	u8 tmp_N12;
	u8 tmp_M29;
	u8 tmp_N13;
	u8 tmp_M30;
	u8 tmp_N14;
	i32 local_sum;
	i32 local_diff;
	u8 tmp_N15;
	u8 tmp_N16;
	u8 tmp_N17;
	u8 tmp_N18;
	i32 local_jcount;
	local_j = j;
	tmp_M = M[local_j];
	local_j = j;
	tmp_M0 = M[local_j + 1];
	local_j = j;
	tmp_M1 = M[local_j + 2];
	local_j = j;
	tmp_M2 = M[local_j + 3];
	local_k = k;
	tmp_M3 = M[local_k];
	local_k = k;
	tmp_M4 = M[local_k + 1];
	local_k = k;
	tmp_M5 = M[local_k + 2];
	local_k = k;
	tmp_M6 = M[local_k + 3];
	local_o = o;
	tmp_M7 = M[local_o];
	local_o = o;
	tmp_M8 = M[local_o + 1];
	local_o = o;
	tmp_M9 = M[local_o + 2];
	local_o = o;
	tmp_M10 = M[local_o + 3];
	local_p = p;
	tmp_M11 = M[local_p];
	local_p = p;
	tmp_M12 = M[local_p + 1];
	local_p = p;
	tmp_M13 = M[local_p + 2];
	local_p = p;
	tmp_M14 = M[local_p + 3];
	h = (tmp_M + tmp_M0 + tmp_M1 + tmp_M2 + tmp_M3 + tmp_M4 + tmp_M5 + tmp_M6 + tmp_M7 + tmp_M8 + tmp_M9 + tmp_M10 + tmp_M11 + tmp_M12 + tmp_M13 + tmp_M14) / 16;
	local_j = j;
	local_h = h;
	N[local_j] = local_h;
	local_j = j;
	local_h = h;
	N[local_j + 1] = local_h;
	local_j = j;
	local_h = h;
	N[local_j + 2] = local_h;
	local_j = j;
	local_h = h;
	N[local_j + 3] = local_h;
	local_k = k;
	local_h = h;
	N[local_k] = local_h;
	local_k = k;
	local_h = h;
	N[local_k + 1] = local_h;
	local_k = k;
	local_h = h;
	N[local_k + 2] = local_h;
	local_k = k;
	local_h = h;
	N[local_k + 3] = local_h;
	local_o = o;
	local_h = h;
	N[local_o] = local_h;
	local_o = o;
	local_h = h;
	N[local_o + 1] = local_h;
	local_o = o;
	local_h = h;
	N[local_o + 2] = local_h;
	local_o = o;
	local_h = h;
	N[local_o + 3] = local_h;
	local_p = p;
	local_h = h;
	N[local_p] = local_h;
	local_p = p;
	local_h = h;
	N[local_p + 1] = local_h;
	local_p = p;
	local_h = h;
	N[local_p + 2] = local_h;
	local_p = p;
	local_h = h;
	N[local_p + 3] = local_h;
	local_j = j;
	tmp_M15 = M[local_j];
	local_j = j;
	tmp_N = N[local_j];
	local_j = j;
	tmp_M16 = M[local_j + 1];
	local_j = j;
	tmp_N0 = N[local_j + 1];
	local_j = j;
	tmp_M17 = M[local_j + 2];
	local_j = j;
	tmp_N1 = N[local_j + 2];
	local_j = j;
	tmp_M18 = M[local_j + 3];
	local_j = j;
	tmp_N2 = N[local_j + 3];
	local_k = k;
	tmp_M19 = M[local_k];
	local_k = k;
	tmp_N3 = N[local_k];
	local_k = k;
	tmp_M20 = M[local_k + 1];
	local_k = k;
	tmp_N4 = N[local_k - 1];
	local_k = k;
	tmp_M21 = M[local_k + 2];
	local_k = k;
	tmp_N5 = N[local_k + 2];
	local_k = k;
	tmp_M22 = M[local_k + 3];
	local_k = k;
	tmp_N6 = N[local_k + 3];
	local_o = o;
	tmp_M23 = M[local_o];
	local_o = o;
	tmp_N7 = N[local_o];
	local_o = o;
	tmp_M24 = M[local_o + 1];
	local_o = o;
	tmp_N8 = N[local_o + 1];
	local_o = o;
	tmp_M25 = M[local_o + 2];
	local_o = o;
	tmp_N9 = N[local_o + 2];
	local_o = o;
	tmp_M26 = M[local_o + 3];
	local_o = o;
	tmp_N10 = N[local_o + 3];
	local_p = p;
	tmp_M27 = M[local_p];
	local_p = p;
	tmp_N11 = N[local_p];
	local_p = p;
	tmp_M28 = M[local_p + 1];
	local_p = p;
	tmp_N12 = N[local_p + 1];
	local_p = p;
	tmp_M29 = M[local_p + 2];
	local_p = p;
	tmp_N13 = N[local_p + 2];
	local_p = p;
	tmp_M30 = M[local_p + 3];
	local_p = p;
	tmp_N14 = N[local_p + 3];
	diff = tmp_M15 - tmp_N + (tmp_M16 - tmp_N0) + (tmp_M17 - tmp_N1) + (tmp_M18 - tmp_N2) + (tmp_M19 - tmp_N3) + (tmp_M20 - tmp_N4) + (tmp_M21 - tmp_N5) + (tmp_M22 - tmp_N6) + (tmp_M23 - tmp_N7) + (tmp_M24 - tmp_N8) + (tmp_M25 - tmp_N9) + (tmp_M26 - tmp_N10) + (tmp_M27 - tmp_N11) + (tmp_M28 - tmp_N12) + (tmp_M29 - tmp_N13) + (tmp_M30 - tmp_N14);
	local_sum = sum;
	local_diff = diff;
	sum = local_sum + local_diff;
	local_j = j;
	tmp_N15 = N[local_j];
	local_j = j;
	tmp_N16 = N[local_j + 1];
	local_k = k;
	tmp_N17 = N[local_k];
	local_k = k;
	tmp_N18 = N[local_k + 1];
	local_j = j;
	local_k = k;
	local_sum = sum;
	printf("Approx2: %u %u %u %u %i %i %i\n", tmp_N15, tmp_N16, tmp_N17, tmp_N18, local_j, local_k, local_sum);
	local_j = j;
	j = local_j + 4;
	local_k = k;
	k = local_k + 4;
	local_o = o;
	o = local_o + 4;
	local_p = p;
	p = local_p + 4;
	local_j = j;
	local_k = k;
	printf(" %i %i\n", local_j, local_k);
	local_j = j;
	if (local_j % 640 == 0) {
		local_jcount = jcount;
		jcount = local_jcount + 4;
		local_jcount = jcount;
		j = 640 * local_jcount;
		local_j = j;
		k = local_j + 640;
		local_k = k;
		o = local_k + 640;
		local_o = o;
		p = local_o + 640;
	}
	// Update ports indexes
}
static i32 isSchedulable_send_list() {
	i32 result;
	i32 local_p;
	i32 local_l;

	local_p = p;
	local_l = l;
	result = (local_p == 370560 && local_l < 368640);
	return result;
}

static void send_list() {
	u8 Out1;
	i32 local_l;
	local_l = l;
	Out1 = N[local_l];
	local_l = l;
	printf("Approx2: %i %u\n", local_l, Out1);
	local_l = l;
	l = local_l + 1;
	tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data] = Out1;
	// Update ports indexes
	index_Approxed_Data += 1;
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
		if (numTokens_Data_To_Be_Manipulated - index_Data_To_Be_Manipulated >= 1 && isSchedulable_build_list()) {
			build_list();
			i++;
		} else if (isSchedulable_read_list()) {
			read_list();
			i++;
		} else if (isSchedulable_send_list()) {
			int stop = 0;
			if (1 > SIZE_Approxed_Data - index_Approxed_Data + Approx_Approxed_Data->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			send_list();
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
