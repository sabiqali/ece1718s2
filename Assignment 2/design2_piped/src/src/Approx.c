// Source file is "L/design2_piped/src/Approx.cal"

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
#define SIZE_Data_To_Be_Manipulated 8388608
#define tokens_Data_To_Be_Manipulated Approx_Data_To_Be_Manipulated->contents

extern connection_t connection_Approx_Data_To_Be_Manipulated;
#define rate_Data_To_Be_Manipulated connection_Approx_Data_To_Be_Manipulated.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Duplicate;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Approx_Approxed_Data;
extern fifo_u8_t *Approx_input_flag;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Approxed_Data;
#define NUM_READERS_Approxed_Data 1
#define SIZE_Approxed_Data 8388608
#define tokens_Approxed_Data Approx_Approxed_Data->contents

static unsigned int index_input_flag;
#define NUM_READERS_input_flag 1
#define SIZE_input_flag 8388608
#define tokens_input_flag Approx_input_flag->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Abs_Diff;
extern actor_t Duplicate;


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
static u8 M[2560];
static u8 N[2560];

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_s_first,
	my_state_s_fourth,
	my_state_s_second,
	my_state_s_third
};

static char *stateNames[] = {
	"s_first",
	"s_fourth",
	"s_second",
	"s_third"
};

static enum states _FSM_state;



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
static void write_input_flag() {
	index_input_flag = Approx_input_flag->write_ind;
}

static void write_end_input_flag() {
	Approx_input_flag->write_ind = index_input_flag;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_build_list() {
	i32 result;
	i32 local_i;

	local_i = i;
	result = local_i < 2560;
	return result;
}

static void build_list() {
	u8 In1;
	u8 flag;
	i32 local_i;
	u8 tmp_M;
	In1 = tokens_Data_To_Be_Manipulated[(index_Data_To_Be_Manipulated + (0)) % SIZE_Data_To_Be_Manipulated];
	flag = 0;
	local_i = i;
	M[local_i] = In1;
	local_i = i;
	tmp_M = M[local_i];
	printf("Approx: %u\n", tmp_M);
	local_i = i;
	i = local_i + 1;
	local_i = i;
	if (local_i == 2560) {
		flag = 1;
	}
	tokens_input_flag[(index_input_flag + (0)) % SIZE_input_flag] = flag;
	// Update ports indexes
	index_Data_To_Be_Manipulated += 1;
	index_input_flag += 1;
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
	result = ((((local_i == 2560 && local_o < 2560) && local_p < 1920) && local_k < 1280) && local_j < 640);
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
	u8 tmp_N;
	u8 tmp_N0;
	u8 tmp_N1;
	u8 tmp_N2;
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
	tmp_N = N[local_j];
	local_j = j;
	tmp_N0 = N[local_j + 1];
	local_k = k;
	tmp_N1 = N[local_k];
	local_k = k;
	tmp_N2 = N[local_k + 1];
	local_j = j;
	local_k = k;
	printf("Approx2: %u %u %u %u %i %i \n", tmp_N, tmp_N0, tmp_N1, tmp_N2, local_j, local_k);
	local_j = j;
	j = local_j + 4;
	local_k = k;
	k = local_k + 4;
	local_o = o;
	o = local_o + 4;
	local_p = p;
	p = local_p + 4;
	// Update ports indexes
}
static i32 isSchedulable_send_list() {
	i32 result;
	i32 local_p;
	i32 local_l;

	local_p = p;
	local_l = l;
	result = (local_p == 2560 && local_l < 2560);
	return result;
}

static void send_list() {
	u8 Out1;
	i32 local_l;
	local_l = l;
	Out1 = N[local_l];
	local_l = l;
	l = local_l + 1;
	tokens_Approxed_Data[(index_Approxed_Data + (0)) % SIZE_Approxed_Data] = Out1;
	// Update ports indexes
	index_Approxed_Data += 1;
}
static i32 isSchedulable_init() {
	i32 result;

	result = 1;
	return result;
}

static void init() {
	u8 flag;
	flag = 1;
	i = 0;
	j = 0;
	k = 640;
	o = 1280;
	p = 1920;
	l = 0;
	k = 1280;
	tokens_input_flag[(index_input_flag + (0)) % SIZE_input_flag] = flag;
	// Update ports indexes
	index_input_flag += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void Approx_initialize(schedinfo_t *si) {
	int i = 0;
	write_Approxed_Data();
	write_input_flag();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_s_first;
finished:
	write_end_Approxed_Data();
	write_end_input_flag();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void Approx_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Data_To_Be_Manipulated();
	write_Approxed_Data();
	write_input_flag();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_s_first:
		goto l_s_first;
	case my_state_s_fourth:
		goto l_s_fourth;
	case my_state_s_second:
		goto l_s_second;
	case my_state_s_third:
		goto l_s_third;
	default:
		printf("unknown state in Approx.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_s_first:
	if (numTokens_Data_To_Be_Manipulated - index_Data_To_Be_Manipulated >= 1 && isSchedulable_build_list()) {
		int stop = 0;
		if (1 > SIZE_input_flag - index_input_flag + Approx_input_flag->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_s_first;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		build_list();
		i++;
		goto l_s_second;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_s_first;
		goto finished;
	}
l_s_fourth:
	if (isSchedulable_init()) {
		int stop = 0;
		if (1 > SIZE_input_flag - index_input_flag + Approx_input_flag->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_s_fourth;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		init();
		i++;
		goto l_s_first;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_s_fourth;
		goto finished;
	}
l_s_second:
	if (isSchedulable_read_list()) {
		read_list();
		i++;
		goto l_s_third;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_s_second;
		goto finished;
	}
l_s_third:
	if (isSchedulable_send_list()) {
		int stop = 0;
		if (1 > SIZE_Approxed_Data - index_Approxed_Data + Approx_Approxed_Data->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_s_third;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		send_list();
		i++;
		goto l_s_fourth;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_s_third;
		goto finished;
	}
finished:
	read_end_Data_To_Be_Manipulated();
	write_end_Approxed_Data();
	write_end_input_flag();
}
