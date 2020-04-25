// Source file is "L/ece1718_milestone3/src/decrypt.cal"

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
extern actor_t decrypt;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Input FIFOs
extern fifo_u8_t *decrypt_encrypted_img;
extern fifo_u8_t *decrypt_key;

////////////////////////////////////////////////////////////////////////////////
// Input Fifo control variables
static unsigned int index_encrypted_img;
static unsigned int numTokens_encrypted_img;
#define SIZE_encrypted_img 8192
#define tokens_encrypted_img decrypt_encrypted_img->contents

extern connection_t connection_decrypt_encrypted_img;
#define rate_encrypted_img connection_decrypt_encrypted_img.rate

static unsigned int index_key;
static unsigned int numTokens_key;
#define SIZE_key 8192
#define tokens_key decrypt_key->contents

extern connection_t connection_decrypt_key;
#define rate_key connection_decrypt_key.rate

////////////////////////////////////////////////////////////////////////////////
// Predecessors
extern actor_t encrypt;
extern actor_t encrypt;

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *decrypt_decrypted_img;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_decrypted_img;
#define NUM_READERS_decrypted_img 1
#define SIZE_decrypted_img 8192
#define tokens_decrypted_img decrypt_decrypted_img->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t printer;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static u8 temp;
static u8 temp_key;



////////////////////////////////////////////////////////////////////////////////
// Token functions
static void read_encrypted_img() {
	index_encrypted_img = decrypt_encrypted_img->read_inds[0];
	numTokens_encrypted_img = index_encrypted_img + fifo_u8_get_num_tokens(decrypt_encrypted_img, 0);
}

static void read_end_encrypted_img() {
	decrypt_encrypted_img->read_inds[0] = index_encrypted_img;
}
static void read_key() {
	index_key = decrypt_key->read_inds[0];
	numTokens_key = index_key + fifo_u8_get_num_tokens(decrypt_key, 0);
}

static void read_end_key() {
	decrypt_key->read_inds[0] = index_key;
}

static void write_decrypted_img() {
	index_decrypted_img = decrypt_decrypted_img->write_ind;
}

static void write_end_decrypted_img() {
	decrypt_decrypted_img->write_ind = index_decrypted_img;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_decrypt() {
	i32 result;

	result = 1;
	return result;
}

static void decrypt() {
	u8 in1;
	u8 in2;
	u8 out1;
	u8 local_temp_key;
	u8 local_temp;
	in1 = tokens_encrypted_img[(index_encrypted_img + (0)) % SIZE_encrypted_img];
	in2 = tokens_key[(index_key + (0)) % SIZE_key];
	temp_key = in2;
	local_temp_key = temp_key;
	if (in1 >= local_temp_key) {
		local_temp_key = temp_key;
		out1 = in1 - local_temp_key;
		printf("decrypt:%u %u", in1, out1);
	} else {
		local_temp_key = temp_key;
		temp = local_temp_key - in1;
		local_temp = temp;
		out1 = 256 - local_temp;
		printf("decrypt:%u %u", in1, out1);
	}
	tokens_decrypted_img[(index_decrypted_img + (0)) % SIZE_decrypted_img] = out1;
	// Update ports indexes
	index_encrypted_img += 1;
	index_key += 1;
	index_decrypted_img += 1;
	rate_encrypted_img += 1;
	rate_key += 1;
}

////////////////////////////////////////////////////////////////////////////////
// Initializes

void decrypt_initialize(schedinfo_t *si) {
	int i = 0;
	write_decrypted_img();
finished:
	write_end_decrypted_img();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler
void decrypt_scheduler(schedinfo_t *si) {
	int i = 0;
	si->ports = 0;

	read_encrypted_img();
	read_key();
	write_decrypted_img();

	while (1) {
		if (numTokens_encrypted_img - index_encrypted_img >= 1 && numTokens_key - index_key >= 1 && isSchedulable_decrypt()) {
			int stop = 0;
			if (1 > SIZE_decrypted_img - index_decrypted_img + decrypt_decrypted_img->read_inds[0]) {
				stop = 1;
			}
			if (stop != 0) {
				si->num_firings = i;
				si->reason = full;
				goto finished;
			}
			decrypt();
			i++;
		} else {
			si->num_firings = i;
			si->reason = starved;
			goto finished;
		}
	}

finished:

	read_end_encrypted_img();
	read_end_key();
	write_end_decrypted_img();
}
