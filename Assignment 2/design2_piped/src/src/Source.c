// Source file is "L/design2_piped/src/Source.cal"

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
extern actor_t Source;

////////////////////////////////////////////////////////////////////////////////
// Shared Variables

////////////////////////////////////////////////////////////////////////////////
// Output FIFOs
extern fifo_u8_t *Source_Stream;

////////////////////////////////////////////////////////////////////////////////
// Output Fifo control variables
static unsigned int index_Stream;
#define NUM_READERS_Stream 1
#define SIZE_Stream 8388608
#define tokens_Stream Source_Stream->contents

////////////////////////////////////////////////////////////////////////////////
// Successors
extern actor_t Duplicate;


////////////////////////////////////////////////////////////////////////////////
// State variables of the actor
static i32 DEBUG = 0;
#define NB_TOKEN_TO_SENT 2
static u8 bytesRead[2];
static u32 iterationLoop = 0;
static u32 nbByteLeft;
static u16 nbByteToSend = 0;
static u16 nbByteSent = 0;
static u32 nbIteration;
static i32 lastIterationDone = 0;
static i32 endOfFile = 0;

////////////////////////////////////////////////////////////////////////////////
// Initial FSM state of the actor
enum states {
	my_state_ReadFile,
	my_state_ReadFileDone,
	my_state_ReadInit,
	my_state_SendData,
	my_state_SendLastData
};

static char *stateNames[] = {
	"ReadFile",
	"ReadFileDone",
	"ReadInit",
	"SendData",
	"SendLastData"
};

static enum states _FSM_state;



////////////////////////////////////////////////////////////////////////////////
// Token functions

static void write_Stream() {
	index_Stream = Source_Stream->write_ind;
}

static void write_end_Stream() {
	Source_Stream->write_ind = index_Stream;
}

////////////////////////////////////////////////////////////////////////////////
// Functions/procedures
extern i32 source_sizeOfFile();
extern u32 source_getNbLoop();
extern void source_init();
extern void source_readNBytes(u8 outTable[2], u16 nbTokenToRead);
extern void source_rewind();
extern void source_close();


////////////////////////////////////////////////////////////////////////////////
// Actions
static i32 isSchedulable_getFileSize() {
	i32 result;
	i32 tmp_source_sizeOfFile;

	tmp_source_sizeOfFile = source_sizeOfFile();
	result = tmp_source_sizeOfFile > 0;
	return result;
}

static void getFileSize() {
	u32 nbBytes;
	u32 local_NB_TOKEN_TO_SENT;
	i32 local_DEBUG;
	nbBytes = source_sizeOfFile();
	local_NB_TOKEN_TO_SENT = NB_TOKEN_TO_SENT;
	nbIteration = nbBytes / local_NB_TOKEN_TO_SENT;
	local_NB_TOKEN_TO_SENT = NB_TOKEN_TO_SENT;
	nbByteLeft = nbBytes % local_NB_TOKEN_TO_SENT;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: getFileSize\n");
		printf("Source STATE: ReadFile\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
}
static i32 isSchedulable_readNBytes() {
	i32 result;
	u32 local_iterationLoop;
	u32 local_nbIteration;

	local_iterationLoop = iterationLoop;
	local_nbIteration = nbIteration;
	result = local_iterationLoop < local_nbIteration;
	return result;
}

static void readNBytes() {
	u32 local_NB_TOKEN_TO_SENT;
	u32 local_iterationLoop;
	i32 local_DEBUG;
	local_NB_TOKEN_TO_SENT = NB_TOKEN_TO_SENT;
	source_readNBytes(bytesRead, local_NB_TOKEN_TO_SENT);
	local_NB_TOKEN_TO_SENT = NB_TOKEN_TO_SENT;
	nbByteToSend = local_NB_TOKEN_TO_SENT;
	nbByteSent = 0;
	local_iterationLoop = iterationLoop;
	iterationLoop = local_iterationLoop + 1;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: readNbytes\n");
		printf("Source STATE: SendData\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
}
static i32 isSchedulable_readEndOfFile() {
	i32 result;
	u32 local_nbByteLeft;

	local_nbByteLeft = nbByteLeft;
	result = local_nbByteLeft > 0;
	return result;
}

static void readEndOfFile() {
	u32 local_nbByteLeft;
	i32 local_DEBUG;
	local_nbByteLeft = nbByteLeft;
	source_readNBytes(bytesRead, local_nbByteLeft);
	local_nbByteLeft = nbByteLeft;
	nbByteToSend = local_nbByteLeft;
	nbByteSent = 0;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: readEndOfFile\n");
		printf("Source STATE: SendLastData\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
}
static i32 isSchedulable_closeFile() {
	i32 result;
	i32 local_endOfFile;

	local_endOfFile = endOfFile;
	result = local_endOfFile == 0;
	return result;
}

static void closeFile() {
	i32 local_DEBUG;
	i32 local_endOfFile;
	source_close();
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: closeFile\n");
		printf("Source STATE: ReadFileDone\n");
		printf("-------------------------\n");
	}
	endOfFile = 1;
	local_endOfFile = endOfFile;
	// Update ports indexes
}
static i32 isSchedulable_sendData_launch() {
	i32 result;
	u16 local_nbByteToSend;
	u16 local_nbByteSent;

	local_nbByteToSend = nbByteToSend;
	local_nbByteSent = nbByteSent;
	result = local_nbByteToSend > local_nbByteSent;
	return result;
}

static void sendData_launch() {
	u8 Out;
	u16 local_nbByteSent;
	i32 local_DEBUG;
	u32 local_iterationLoop;
	u32 local_nbIteration;
	i32 local_lastIterationDone;
	i32 local_endOfFile;
	local_nbByteSent = nbByteSent;
	Out = bytesRead[local_nbByteSent];
	local_nbByteSent = nbByteSent;
	nbByteSent = local_nbByteSent + 1;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: sendData.launch\n");
		local_iterationLoop = iterationLoop;
		local_nbIteration = nbIteration;
		local_lastIterationDone = lastIterationDone;
		if ((local_iterationLoop == local_nbIteration && local_lastIterationDone)) {
			printf("Source STATE: SendLastData\n");
			printf("-------------------------\n");
		} else {
			printf("Source STATE: SendData\n");
			printf("-------------------------\n");
		}
	}
	tokens_Stream[(index_Stream + (0)) % SIZE_Stream] = Out;
	local_endOfFile = endOfFile;
	// Update ports indexes
	index_Stream += 1;
}
static i32 isSchedulable_sendData_done() {
	i32 result;
	u16 local_nbByteToSend;
	u16 local_nbByteSent;

	local_nbByteToSend = nbByteToSend;
	local_nbByteSent = nbByteSent;
	result = local_nbByteToSend == local_nbByteSent;
	return result;
}

static void sendData_done() {
	i32 local_DEBUG;
	u32 local_iterationLoop;
	u32 local_nbIteration;
	i32 local_lastIterationDone;
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: sendData.done\n");
		local_iterationLoop = iterationLoop;
		local_nbIteration = nbIteration;
		local_lastIterationDone = lastIterationDone;
		if ((local_iterationLoop == local_nbIteration && local_lastIterationDone)) {
			printf("Source STATE: ReadFileDone\n");
			printf("-------------------------\n");
		} else {
			printf("Source STATE: ReadFile\n");
			printf("-------------------------\n");
			local_iterationLoop = iterationLoop;
			local_nbIteration = nbIteration;
			if (local_iterationLoop == local_nbIteration) {
				lastIterationDone = 1;
			}
		}
	}
	// Update ports indexes
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
	source_init();
	local_DEBUG = DEBUG;
	if (local_DEBUG) {
		printf("Source ACTION: initialize\n");
		printf("Source STATE: ReadInit\n");
		printf("-------------------------\n");
	}
	// Update ports indexes
}

void Source_initialize(schedinfo_t *si) {
	int i = 0;
	write_Stream();
	/* Set initial state to current FSM state */
	_FSM_state = my_state_ReadInit;
	if(isSchedulable_untagged_0()) {
		untagged_0();
	}
finished:
	write_end_Stream();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Action scheduler

void Source_scheduler(schedinfo_t *si) {
	int i = 0;

	write_Stream();

	// jump to FSM state
	switch (_FSM_state) {
	case my_state_ReadFile:
		goto l_ReadFile;
	case my_state_ReadFileDone:
		goto l_ReadFileDone;
	case my_state_ReadInit:
		goto l_ReadInit;
	case my_state_SendData:
		goto l_SendData;
	case my_state_SendLastData:
		goto l_SendLastData;
	default:
		printf("unknown state in Source.c : %s\n", stateNames[_FSM_state]);
		exit(1);
	}

	// FSM transitions
l_ReadFile:
	if (isSchedulable_readNBytes()) {
		readNBytes();
		i++;
		goto l_SendData;
	} else if (isSchedulable_readEndOfFile()) {
		readEndOfFile();
		i++;
		goto l_SendLastData;
	} else if (isSchedulable_sendData_done()) {
		sendData_done();
		i++;
		goto l_ReadFileDone;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_ReadFile;
		goto finished;
	}
l_ReadFileDone:
	if (isSchedulable_closeFile()) {
		closeFile();
		i++;
		goto l_ReadFileDone;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_ReadFileDone;
		goto finished;
	}
l_ReadInit:
	if (isSchedulable_getFileSize()) {
		getFileSize();
		i++;
		goto l_ReadFile;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_ReadInit;
		goto finished;
	}
l_SendData:
	if (isSchedulable_sendData_launch()) {
		int stop = 0;
		if (1 > SIZE_Stream - index_Stream + Source_Stream->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendData_launch();
		i++;
		goto l_SendData;
	} else if (isSchedulable_sendData_done()) {
		sendData_done();
		i++;
		goto l_ReadFile;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendData;
		goto finished;
	}
l_SendLastData:
	if (isSchedulable_sendData_launch()) {
		int stop = 0;
		if (1 > SIZE_Stream - index_Stream + Source_Stream->read_inds[0]) {
			stop = 1;
		}
		if (stop != 0) {
			_FSM_state = my_state_SendLastData;
			si->num_firings = i;
			si->reason = full;
			goto finished;
		}
		sendData_launch();
		i++;
		goto l_SendLastData;
	} else if (isSchedulable_sendData_done()) {
		sendData_done();
		i++;
		goto l_ReadFileDone;
	} else {
		si->num_firings = i;
		si->reason = starved;
		_FSM_state = my_state_SendLastData;
		goto finished;
	}
finished:
	write_end_Stream();
}
