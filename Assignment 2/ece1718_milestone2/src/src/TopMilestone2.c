// Generated from ".TopMilestone2"

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
DECLARE_FIFO(u8, 8192, 4, 1)
DECLARE_FIFO(u32, 8192, 5, 1)

/////////////////////////////////////////////////
// FIFO pointer assignments
fifo_u8_t *Source_Stream = &fifo_0;
fifo_u8_t *Duplicate_Stream = &fifo_0;

fifo_u8_t *Duplicate_Actual_data = &fifo_1;
fifo_u8_t *Abs_Diff_Actual_data = &fifo_1;

fifo_u8_t *Duplicate_Data_To_Be_Manipulated = &fifo_2;
fifo_u8_t *Approx_Data_To_Be_Manipulated = &fifo_2;

fifo_u8_t *Approx_Approxed_Data = &fifo_3;
fifo_u8_t *Abs_Diff_Approxed_Data = &fifo_3;

fifo_u8_t *Abs_Diff_Abs_diff = &fifo_4;
fifo_u8_t *Sum_Abs_diff = &fifo_4;

fifo_u32_t *Sum_Sad_vals = &fifo_5;
fifo_u32_t *Printer_Sad_vals = &fifo_5;


/////////////////////////////////////////////////
// Actor functions
extern void Source_initialize(schedinfo_t *si);
extern void Source_scheduler(schedinfo_t *si);
extern void Duplicate_initialize(schedinfo_t *si);
extern void Duplicate_scheduler(schedinfo_t *si);
extern void Approx_initialize(schedinfo_t *si);
extern void Approx_scheduler(schedinfo_t *si);
extern void Abs_Diff_initialize(schedinfo_t *si);
extern void Abs_Diff_scheduler(schedinfo_t *si);
extern void Sum_initialize(schedinfo_t *si);
extern void Sum_scheduler(schedinfo_t *si);
extern void Printer_initialize(schedinfo_t *si);
extern void Printer_scheduler(schedinfo_t *si);

/////////////////////////////////////////////////
// Declaration of the actors array
actor_t Source = {"Source", Source_initialize, Source_scheduler, 0, 0, 0, 0, NULL, -1, 0, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t Duplicate = {"Duplicate", Duplicate_initialize, Duplicate_scheduler, 0, 0, 0, 0, NULL, -1, 1, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t Approx = {"Approx", Approx_initialize, Approx_scheduler, 0, 0, 0, 0, NULL, -1, 2, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t Abs_Diff = {"Abs_Diff", Abs_Diff_initialize, Abs_Diff_scheduler, 0, 0, 0, 0, NULL, -1, 3, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t Sum = {"Sum", Sum_initialize, Sum_scheduler, 0, 0, 0, 0, NULL, -1, 4, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};
actor_t Printer = {"Printer", Printer_initialize, Printer_scheduler, 0, 0, 0, 0, NULL, -1, 5, 0, 1, 0, 0, 0, NULL, 0, 0, "", 0, 0, 0};

actor_t *actors[] = {
	&Source,
	&Duplicate,
	&Approx,
	&Abs_Diff,
	&Sum,
	&Printer
};

/////////////////////////////////////////////////
// Declaration of the connections array
connection_t connection_Approx_Data_To_Be_Manipulated = {&Duplicate, &Approx, 0, 0};
connection_t connection_Abs_Diff_Actual_data = {&Duplicate, &Abs_Diff, 0, 0};
connection_t connection_Abs_Diff_Approxed_Data = {&Approx, &Abs_Diff, 0, 0};
connection_t connection_Sum_Abs_diff = {&Abs_Diff, &Sum, 0, 0};
connection_t connection_Printer_Sad_vals = {&Sum, &Printer, 0, 0};
connection_t connection_Duplicate_Stream = {&Source, &Duplicate, 0, 0};

connection_t *connections[] = {
	&connection_Approx_Data_To_Be_Manipulated,
	&connection_Abs_Diff_Actual_data,
	&connection_Abs_Diff_Approxed_Data,
	&connection_Sum_Abs_diff,
	&connection_Printer_Sad_vals,
	&connection_Duplicate_Stream
};

/////////////////////////////////////////////////
// Declaration of the network
network_t network = {".TopMilestone2", actors, connections, 6, 6};

////////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char *argv[]) {
	
	options_t *opt = init_orcc(argc, argv);
	set_scheduling_strategy("RR", opt);
	
	launcher(opt, &network);
	
	return compareErrors;
}
