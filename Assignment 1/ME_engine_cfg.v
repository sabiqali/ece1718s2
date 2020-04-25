//main module
module ME_engine_cfg (clk, reset, pixel_valid_in, pixel_data0, pixel_data1, pixel_data2, mv_valid, mv_x, mv_y);
	parameter block_size = 16;
	parameter pixel_width = 8;
	parameter search_range = 2;
	
	input clk;
	input reset;
	input [2:0] pixel_valid_in;	// valid bits for pixel data2,1&0
	input [pixel_width-1:0] pixel_data0, pixel_data1, pixel_data2; 
	
	output reg mv_valid;
	output reg signed [$clog2(search_range+1):0] mv_x;
	output reg signed [$clog2(search_range+1):0] mv_y;
		
	reg [1:0] pixel_valid [search_range*2:0][search_range*2:0];
	reg [pixel_width-1:0] current_pixel [search_range*2:0][search_range*2:0];
	reg [pixel_width-1:0] previous_pixel [search_range*2:0][search_range*2:0];
	wire SAD_valid [search_range*2:0][search_range*2:0];
	wire [$clog2(block_size*block_size)+pixel_width-1:0] SAD [search_range*2:0][search_range*2:0];
	
	integer i, j, k, l, left, right, top, bottom, left1, right1, top1, bottom1;
	integer counter_y, counter_x;	// to record number of cycles and determine which status the engine is in
	integer i_cycle = ((2*search_range+1 > block_size) ? (2*search_range+1) : block_size);	// cycles in a inner loop
	integer o_cycle = 2*search_range + block_size + 1;	// cycles in a outer loop
	reg [pixel_width-1:0] current_block [block_size-1:0][block_size-1:0];
	
	always@(posedge clk)begin
		if(reset) begin
			mv_valid <= 0;
			mv_x <= 0;
			mv_y <= 0;
			counter_x <= 0;
			counter_y <= 0;
			for(i = 0; i < search_range*2+1; i = i + 1) begin
				for(j = 0; j < search_range*2+1; j = j + 1) begin
					pixel_valid[i][j] <= 0;
					current_pixel[i][j] <= 0;
					previous_pixel[i][j] <= 0;
				end
			end
		end
		else begin	
			// default
			for(i = 0; i < search_range*2+1; i = i + 1) begin
				for(j = 0; j < search_range*2+1; j = j + 1) begin
					pixel_valid[i][j] <= 0;
					current_pixel[i][j] <= 0;
					previous_pixel[i][j] <= 0;
				end
			end
			// decide which PE should the input pixel data be sent to
			if(counter_x == i_cycle - 1) begin
				counter_x = 0;
				if(counter_y == o_cycle - 1) begin
					// the final cycle
				end
				else
					counter_y = counter_y + 1;
			
			end
			else
				counter_x = counter_x + 1;
			// store current block data
			if(counter_x < block_size && counter_y < block_size) begin
				if(pixel_valid_in[0])
					current_block[counter_y][counter_x] <= pixel_data[0];
			end
			// broadcast current block data
			for(i = 0; i < block_size; i = i + 1) begin
				for(j = 0; j < block_size; j = j + 1) begin					
					if(counter_y-i >=0 && counter_x-j >= 0 && counter_y-i <= 2*search_range && counter_x-j <= 2*search_range) begin
						if(i == counter_y && j == counter_x) begin // the new one
							current_pixel[0][0] <= pixel_data[0];
							pixel_valid[0][0][1] <= pixel_valid_in[0];
						end
						else begin	// already stored
							current_pixel[counter_y-i][counter_x-j] <=  current_block[i][j];
							pixel_valid[counter_y-i][counter_x-j][1] <= 1;
						end
					end					
				end			
			end
			// broadcast previous block data
			if(block_size - 1 >= 2 * search_range) begin	// one case
				if(counter_y < block_size+2*search_range) begin  // deal with pixel_data1
					if(counter_x < ((block_size-1<2*search_range)?(block_size-1<2):(2*search_range))) begin
						left = 0;
						right = counter_x;
					end
					else begin
						left = 0;
						right = 2*search_range;
					end
					top = ((counter_y-block_size+1 > 0) ? (counter_y-block_size+1) : 0);
					down = (y+1<2*search_range) ? (y+1) : (2*search_range);
				end
				if(counter_y > 0) begin	// deal with pixel_data2
					left1 = 2*search_range-(block_size-counter_x-1);
					right1 = 2*search_range;					
					top1 = ((counter_y-block_size > 0) ? (counter_y-block_size) : 0);
					down1 = (y<2*search_range) ? y : (2*search_range);
				end
			end
			else begin	// the other case
			
			end
						
		end	
	end
	
	// instantiate Processing Elements
	genvar gi, gj;
	generate
		for(gi = 0; gi < search_range*2+1; gi = gi + 1) begin: l1
			for(gj = 0; gj < search_range*2+1; gj = gj + 1) begin: l2
				PE #(block_size, pixel_width)  PE1(
				clk, 
				reset, 
				pixel_valid[gi][gj], 
				current_pixel[gi][gj], 
				previous_pixel[gi][gj], 
				SAD_valid[gi][gj], 
				SAD[gi][gj]
				); 
			end
		end	
	endgenerate
	
	

endmodule

