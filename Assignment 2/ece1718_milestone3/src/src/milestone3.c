// Generated from ".milestone3"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "fifo.h"
#include "util.h"
#include "dataflow.h"
#include "serialize.h"
#include "options.h"
#include "scheduler.h"

/////////////////////////////////////////////////
// FIFO allocation
DECLARE_FIFO(u8, 8192, 0, 1)
DECLARE_FIFO(u8, 8192, 1, 1)
DECLARE_FIFO(u8, 8192, 2, 1)
DECLARE_FIFO(u8, 8192, 3, 1)

/////////////////////////////////////////////////
// FIFO pointer assignments
fifo_u8_t *Source_host_Stream = &fifo_0;
fifo_u8_t *encrypt_Stream = &fifo_0;

fifo_u8_t *encrypt_key = &fifo_1;
fifo_u8_t *decrypt_key = &fifo_1;

fifo_u8_t *encrypt_encrypted_img = &fifo_2;
fifo_u8_t *decrypt_encrypted_img = &fifo_2;

fifo_u8_t *decrypt_decrypted_img = &fifo_3;
fifo_u8_t *printer_data = &fifo_3;


/////////////////////////////////////////////////
// Actor functions
extern void Source_host_initialize(schedinfo_t *si);
extern void Source_host_scheduler(schedinfo_t *si);
extern void encrypt_initialize(schedinfo_t *si);
extern void encrypt_scheduler(schedinfo_t *si);
extern void decrypt_initialize(schedinfo_t *si);
extern void decrypt_scheduler(schedinfo_t *si);
extern void printer_initialize(schedinfo_t *si);
extern void printer_scheduler(schedinfo_t *si);

/////////////////////////////////////////////////
// Declaration of the actors array
actor_t Source_host = {"Source_host", Source_host_initialize, Source_host_scheduler, 0, 0, 0, 0, NULL, -1, 0, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t encrypt = {"encrypt", encrypt_initialize, encrypt_scheduler, 0, 0, 0, 0, NULL, -1, 1, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t decrypt = {"decrypt", decrypt_initialize, decrypt_scheduler, 0, 0, 0, 0, NULL, -1, 2, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t printer = {"printer", printer_initialize, printer_scheduler, 0, 0, 0, 0, NULL, -1, 3, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};

actor_t *actors[] = {
	&Source_host,
	&encrypt,
	&decrypt,
	&printer
};

/////////////////////////////////////////////////
// Declaration of the connections array
connection_t connection_encrypt_Stream = {&Source_host, &encrypt, 0, 0};
connection_t connection_decrypt_encrypted_img = {&encrypt, &decrypt, 0, 0};
connection_t connection_decrypt_key = {&encrypt, &decrypt, 0, 0};
connection_t connection_printer_data = {&decrypt, &printer, 0, 0};

connection_t *connections[] = {
	&connection_encrypt_Stream,
	&connection_decrypt_encrypted_img,
	&connection_decrypt_key,
	&connection_printer_data
};

/////////////////////////////////////////////////
// Declaration of the network
network_t network = {".milestone3", actors, connections, 4, 4};

////////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char *argv[]) {
	
	options_t *opt = init_orcc(argc, argv);
	set_scheduling_strategy("RR", opt);
	
	launcher(opt, &network);
	
	return compareErrors;
}
