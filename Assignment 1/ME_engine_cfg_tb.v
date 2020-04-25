`timescale 1ns/10ps 
// test bench for ME_engine 
module ME_engine_cfg_tb();
	localparam CLK_PERIOD = 20; //ns	
	parameter block_size = 16;
	parameter pixel_width = 8;
	parameter search_range = 2;

	reg [pixel_width-1:0] current_block [block_size-1:0][block_size-1:0];
	reg [pixel_width-1:0] search_window [block_size+2*search_range-1:0][block_size+2*search_range-1:0];
	
	reg clk;
	reg reset;
	reg [2:0] pixel_valid_in; 
	reg [pixel_width-1:0] pixel_data0, pixel_data1, pixel_data2;
	wire mv_valid; 
	wire signed [$clog2(search_range+1):0] mv_x, mv_y;
	
	reg [$clog2(block_size*block_size)+pixel_width-1:0] pre_SAD;
	reg [$clog2(block_size*block_size)+pixel_width-1:0] pre_best_SAD;	
	reg [$clog2(search_range+1):0] pre_x_length, pre_y_length;
	reg [$clog2(search_range+1):0] pre_best_x_length, pre_best_y_length;
	reg signed [$clog2(search_range+1):0] pre_best_mv_x, pre_best_mv_y;
	reg success;
	
	initial begin 
		clk <= 0;
		forever  #(CLK_PERIOD/2) clk = ~clk;
	end

	integer i, j, k, l;

	initial begin
		//generate random data in current block and search_window
		pre_best_SAD = -1;
		for(i = 0; i < block_size; i = i + 1) begin
			for(j = 0; j < block_size; j = j + 1) begin
				current_block[i][j] = $urandom(i*j+2*i);
			
			end
		end
		for(i = 0; i < block_size+2*search_range; i = i + 1) begin
			for(j = 0; j < block_size+2*search_range; j = j + 1) begin
				search_window[i][j] = $urandom(i+j*i*i);
			
			end
		end
		// precalculation of best motion vector
		for(i = 0; i <= search_range*2; i = i + 1) begin
			for(j = 0; j <= search_range*2; j = j + 1) begin
				pre_SAD = 0;
				for(k = 0; k < block_size; k = k + 1) begin
					for(l = 0; l < block_size; l = l + 1) begin
						pre_SAD = pre_SAD + ((current_block[k][l] > search_window[i+k][j+l]) ? (current_block[k][l] - search_window[i+k][j+l]) : (search_window[i+k][j+l] - current_block[k][l]));
					
					end
				end
				pre_x_length = ((j > search_range) ? (j - search_range) : (search_range - j));
				pre_y_length = ((i > search_range) ? (i - search_range) : (search_range - i));
				// decide whether to update global best
				if((i == 0 && j == 0) || 
				(pre_SAD < pre_best_SAD) ||
				((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length < pre_best_x_length + pre_best_y_length)) ||
				((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length < pre_best_x_length)) ||
				((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length == pre_best_x_length) && (pre_y_length < pre_best_y_length)) ) begin
					pre_best_SAD = pre_SAD;
					pre_best_x_length = pre_x_length;
					pre_best_y_length = pre_y_length;
					pre_best_mv_x = j - search_range;
					pre_best_mv_y = i - search_range;
				end
			end
		end
			
		$display("Precalculated motion vector result: %d, %d", pre_best_mv_x, pre_best_mv_y);
		
		#0 reset = 1;	
		pixel_valid_in = 0;
		success = 0;
		#(CLK_PERIOD) reset = 0;
		
		//  generate inputs to ME_engine
		for(i = 0; i <= block_size*block_size; i = i + 1) begin			
			#(CLK_PERIOD) 
			pixel_valid_in = 3'b111;
			// decide which three pixel data to send in each cycle
			pixel_data0 = 0;
			pixel_data1 = 0;
			pixel_data2 = 0;
		
		end
		
		// judge whether mv result from ME engine is the same as precalculated
		while(mv_valid != 1) begin
			#(CLK_PERIOD);
			if(mv_valid == 1) begin
				$display("SAD result calculated by ME_engine: %d, %d", mv_x, mv_y);
				if(mv_x == pre_best_mv_x && mv_y == pre_best_mv_y)
					success = 1;
				
			end
		end
		if(mv_valid == 1) begin
			$display("SAD result calculated by ME_engine: %d, %d", mv_x, mv_y);
			if(mv_x == pre_best_mv_x && mv_y == pre_best_mv_y)
				success = 1;
		end
		if(success)
			$display("Simulation result: Succeeded!");
		else
			$display("Simulation result: Failed...");

		$stop;
	end

	// instantiate ME engine
	ME_engine_cfg #(block_size, pixel_width, search_range) ME1(clk, reset, pixel_valid_in, pixel_data0, pixel_data1, pixel_data2, mv_valid, mv_x, mv_y); 


endmodule
