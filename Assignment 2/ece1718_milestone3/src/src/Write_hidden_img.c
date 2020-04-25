// Source file is "L/ece1718_milestone3/src/Write_hidden_img.cal"

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
extern actor_t Write_hidden_img;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *Write_hidden_img_Byte;
extern fifo_i32_t *Write_hidden_img_pEOF;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Byte;
static unsigned int numTokens_Byte;
#define SIZE_Byte 8388608
#define tokens_Byte Write_hidden_img_Byte->contents

extern connection_t connection_Write_hidden_img_Byte;
#define rate_Byte connection_Write_hidden_img_Byte.rate

static unsigned int index_pEOF;
static unsigned int numTokens_pEOF;
#define SIZE_pEOF 8388608
#define tokens_pEOF Write_hidden_img_pEOF->contents

extern connection_t connection_Write_hidden_img_pEOF;
#define rate_pEOF connection_Write_hidden_img_pEOF.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Source_host;
extern actor_t Source_host;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 DEBUG = 1;
static i32 peof = 0;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_ReadEOF,
	my_state_WriteFile
};

static char *stateNames[] = {
	"ReadEOF",
	"WriteFile"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Byte() {
	index_Byte = Write_hidden_img_Byte->read_inds[0];
	numTokens_Byte = index_Byte + fifo_u8_get_num_tokens(Write_hidden_img_Byte, 0);
}

static void read_end_Byte() {
	Write_hidden_img_Byte->read_inds[0] = index_Byte;
}
static void read_pEOF() {
	index_pEOF = Write_hidden_img_pEOF->read_inds[0];
	numTokens_pEOF = index_pEOF + fifo_i32_get_num_tokens(Write_hidden_img_pEOF, 0);
}

static void read_end_pEOF() {
	Write_hidden_img_pEOF->read_inds[0] = index_pEOF;
}


////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
extern void Writer_init();
extern void Writer_write(u8 byte);
extern void Writer_close();


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getEOF() {
	i32 result;

	result = 1;
	return result;
}

static void getEOF() {
	i32 p;
	i32 local_DEBUG;
	i32 local_peof;
	p = tokens_pEOF[(index_pEOF + (0)) % SIZE_pEOF];
	peof = p;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Writer ACTION: getEOF\n");
		local_peof = peof;
		if (local_peof) {
			printf("Writer: File is close\n");
		}
		printf("Writer STATE: ReadEOF\n");
		printf("-------------------------\n");
	}
	local_peof = peof;
	if (local_peof) {
		Writer_close();
	}
	// Update ports indexes
	index_pEOF += 1;
	rate_pEOF += 1;
}
static i32 isSchedulable_writeData() {
	i32 result;
	i32 local_peof;

	local_peof = peof;
	result = !local_peof;
	return result;
}

static void writeData() {
	u8 b;
	i32 local_DEBUG;
	b = tokens_Byte[(index_Byte + (0)) % SIZE_Byte];
	Writer_write(b);
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Writer ACTION: writeData\n");
		printf("Writer STATE: WriteFile\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
	index_Byte += 1;
	rate_Byte += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes
static i32 isSchedulable_untagged_0() {
	i32 result;

	result = 1;
	return result;
}

static void untagged_0() {
	i32 local_DEBUG;
	Writer_init();
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Writer ACTION: initialize\n");
		printf("Writer STATE: WriteFile\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
}

void Write_hidden_img_initialize(schedinfo_t *si) {
	int i = 0;
	/* Set initial state to current FSM state */
	_FSM_state = my_state_WriteFile;
	if(isSchedulable_untagged_0()) {
		untagged_0();
	}
finished:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void Write_hidden_img_scheduler(schedinfo_t *si) {
	int i = 0;

	read_Byte();
	read_pEOF();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_ReadEOF:
		goto l_ReadEOF;
	case my_state_WriteFile:
		goto l_WriteFile;
	default:
		printf("unknown state in Write_hidden_img.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_ReadEOF:
	if (numTokens_Byte - index_Byte >= 1 && isSchedulable_writeData()) {
		writeData();
		i++;
		goto l_WriteFile;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_ReadEOF;
		goto finished;
	}
l_WriteFile:
	if (numTokens_pEOF - index_pEOF >= 1 && isSchedulable_getEOF()) {
		getEOF();
		i++;
		goto l_ReadEOF;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_WriteFile;
		goto finished;
	}
finished:
	read_end_Byte();
	read_end_pEOF();
}
