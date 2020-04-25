// Source file is "L/ece1718_milestone3/src/printer.cal"

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
extern actor_t printer;

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *printer_data;
fifo_u8_t *printer_data2;
fifo_u8_t *printer_data3;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_data;
static unsigned int numTokens_data;
#define SIZE_data 8192
#define tokens_data printer_data->contents

extern connection_t connection_printer_data;
#define rate_data connection_printer_data.rate

static unsigned int index_data2;
static unsigned int numTokens_data2;
#define SIZE_data2 8192
#define tokens_data2 printer_data2->contents

connection_t connection_printer_data2;
#define rate_data2 connection_printer_data2.rate

static unsigned int index_data3;
static unsigned int numTokens_data3;
#define SIZE_data3 8192
#define tokens_data3 printer_data3->contents

connection_t connection_printer_data3;
#define rate_data3 connection_printer_data3.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t decrypt;




////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_data() {
	index_data = printer_data->read_inds[0];
	numTokens_data = index_data + fifo_u8_get_num_tokens(printer_data, 0);
}

static void read_end_data() {
	printer_data->read_inds[0] = index_data;
}
static void read_data2() {
	/* Input port printer_data2 not connected */
	index_data2 = 0;
	numTokens_data2 = 0;
}

static void read_end_data2() {
	/* Input port printer_data2 not connected */
}
static void read_data3() {
	/* Input port printer_data3 not connected */
	index_data3 = 0;
	numTokens_data3 = 0;
}

static void read_end_data3() {
	/* Input port printer_data3 not connected */
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
	u8 in1;
	u8 in2;
	u8 in3;
	in1 = tokens_data[(index_data + (0)) % SIZE_data];
	in2 = tokens_data2[(index_data2 + (0)) % SIZE_data2];
	in3 = tokens_data3[(index_data3 + (0)) % SIZE_data3];
	// Update ports indexes
	index_data += 1;
	index_data2 += 1;
	index_data3 += 1;
	rate_data += 1;
	rate_data2 += 1;
	rate_data3 += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void printer_initialize(schedinfo_t *si) {
	int i = 0;
finished:
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void printer_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_data();
	read_data2();
	read_data3();

	while (1) {
		if (numTokens_data - index_data >= 1 && numTokens_data2 - index_data2 >= 1 && numTokens_data3 - index_data3 >= 1 && isSchedulable_untagged_0()) {
			untagged_0();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_data();
	read_end_data2();
	read_end_data3();
}
