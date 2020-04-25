// Source file is "L/ece1718_milestone3/src/encrypt.cal"

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
extern actor_t encypt;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *encypt_Stream;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_Stream;
static unsigned int numTokens_Stream;
#define SIZE_Stream 8192
#define tokens_Stream encypt_Stream->contents

extern connection_t connection_encypt_Stream;
#define rate_Stream connection_encypt_Stream.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t Source_host;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *encypt_encrypted_img;
extern fifo_u8_t *encypt_key;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_encrypted_img;
#define NUM_READERS_encrypted_img 1
#define SIZE_encrypted_img 8192
#define tokens_encrypted_img encypt_encrypted_img->contents

static unsigned int index_key;
#define NUM_READERS_key 1
#define SIZE_key 8192
#define tokens_key encypt_key->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t printer;
extern actor_t printer;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static u8 temp;
static u8 temp_key = 40;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_Stream() {
	index_Stream = encypt_Stream->read_inds[0];
	numTokens_Stream = index_Stream + fifo_u8_get_num_tokens(encypt_Stream, 0);
}

static void read_end_Stream() {
	encypt_Stream->read_inds[0] = index_Stream;
}

static void write_encrypted_img() {
	index_encrypted_img = encypt_encrypted_img->write_ind;
}

static void write_end_encrypted_img() {
	encypt_encrypted_img->write_ind = index_encrypted_img;
}
static void write_key() {
	index_key = encypt_key->write_ind;
}

static void write_end_key() {
	encypt_key->write_ind = index_key;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_encrypt_img() {
	i32 result;

	result = 1;
	return result;
}

static void encrypt_img() {
	u8 in1;
	u8 out1;
	u8 out2;
	u8 local_temp_key;
	u8 local_temp;
	in1 = tokens_Stream[(index_Stream + (0)) % SIZE_Stream];
	local_temp_key = temp_key;
	temp = in1 + local_temp_key;
	local_temp = temp;
	if (local_temp >= 256) {
		local_temp = temp;
		out1 = local_temp - 256;
		local_temp_key = temp_key;
		out2 = local_temp_key;
		printf("encrypt: %u %u %u\n", in1, out1, out2);
	} else {
		local_temp = temp;
		out1 = local_temp;
		local_temp_key = temp_key;
		out2 = local_temp_key;
		printf("encrypt: %u %u %u\n", in1, out1, out2);
	}
	tokens_encrypted_img[(index_encrypted_img + (0)) % SIZE_encrypted_img] = out1;
	tokens_key[(index_key + (0)) % SIZE_key] = out2;
	// Update ports indexes
	index_Stream += 1;
	index_encrypted_img += 1;
	index_key += 1;
	rate_Stream += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void encypt_initialize(schedinfo_t *si) {
	int i = 0;
	write_encrypted_img();
	write_key();
finished:
	write_end_encrypted_img();
	write_end_key();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void encypt_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_Stream();
	write_encrypted_img();
	write_key();

	while (1) {
		if (numTokens_Stream - index_Stream >= 1 && isSchedulable_encrypt_img()) {
			int stop = 0;
			if (1 > SIZE_encrypted_img - index_encrypted_img + encypt_encrypted_img->read_inds[0]) {
				stop = 1;
			}
			if (1 > SIZE_key - index_key + encypt_key->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			encrypt_img();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_Stream();
	write_end_encrypted_img();
	write_end_key();
}
