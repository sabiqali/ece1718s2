`timescale 1ns/10ps 
// test bench for ME_engine 
module ME_engine_tb();
	localparam CLK_PERIOD = 20; //ns	

	reg [7:0] current_block [15:0][15:0][2:0];
	reg [7:0] search_window [19:0][19:0][2:0];
	
	reg clk;
	reg reset;
	reg reuse;
	reg [4:0] valid_left, valid_right, valid_top, valid_bottom;
	reg [3:0] pixel_valid_in; 
	reg [7:0]  p0, p1, p2, p3, c0, c1, c2, c3;
	wire mv_valid; 
	wire signed [2:0] mv_x, mv_y;
	
	reg [15:0] pre_SAD;
	reg [15:0] pre_best_SAD;	
	reg [2:0] pre_x_length, pre_y_length;
	reg [2:0] pre_best_x_length, pre_best_y_length;
	reg signed [2:0] pre_best_mv_x [2:0];
	reg signed [2:0] pre_best_mv_y [2:0];
	reg [2:0] success;
	reg [4:0] valid_left_reg[2:0];
	reg [4:0] valid_right_reg[2:0];	
	reg [4:0] valid_top_reg[2:0];
	reg [4:0] valid_bottom_reg[2:0];
	reg reuse_reg [2:0];
	
	integer i, j, k, l, idx;
	
	initial begin 
		clk <= 0;
		forever  #(CLK_PERIOD/2) clk = ~clk;
	end

	initial begin
		for( idx = 0; idx < 3; idx = idx + 1) begin 
			reuse_reg[idx] = ((idx > 0) ? 1'b1 : 1'b0);
			valid_left_reg[idx] = ((idx > 0) ? 0 : 2);
			valid_right_reg[idx] = 19;
			valid_top_reg[idx] = 2;
			valid_bottom_reg[idx] = 19;
		end
		//generate random data in current block and search_window		
		for( idx = 0; idx < 3; idx = idx + 1) begin 
			pre_best_SAD = -1;
			for(i = 0; i < 16; i = i + 1) begin
				for(j = 0; j < 16; j = j + 1) begin
					current_block[i][j][idx] = $urandom(i*j*j+idx+6);
				
				end
			end
			if(reuse_reg[idx]) begin //reuse
				for(i = 0; i < 20; i = i + 1) begin
					for(j = 0; j < 4; j = j + 1) begin
						search_window[i][j][idx] = search_window[i][j+16][idx-1];			
					end
					for(j = 4; j < 20; j = j + 1) begin
						search_window[i][j][idx] = $urandom(i*j*j+idx+16);			
					end
				end
			end
			else begin // no reuse
				for(i = 0; i < 20; i = i + 1) begin
					for(j = 0; j < 20; j = j + 1) begin
						search_window[i][j][idx] = $urandom((j+idx)*i*i+16);
					
					end
				end
			end
			// precalculation of best motion vector
			for(i = valid_top_reg[idx]; i <= valid_bottom_reg[idx]-15; i = i + 1) begin
				for(j = valid_left_reg[idx]; j <= valid_right_reg[idx]-15; j = j + 1) begin
					pre_SAD = 0;
					for(k = 0; k < 16; k = k + 1) begin
						for(l = 0; l < 16; l = l + 1) begin						
							pre_SAD = pre_SAD + ((current_block[k][l][idx] > search_window[i+k][j+l][idx]) ? (current_block[k][l][idx] - search_window[i+k][j+l][idx]) : (search_window[i+k][j+l][idx] - current_block[k][l][idx]));
							/*if(l % 3 == 0) begin							
								#(CLK_PERIOD) ;
							end*/
						end
					end
					pre_x_length = ((j > 2) ? (j - 2) : (2 - j));
					pre_y_length = ((i > 2) ? (i - 2) : (2 - i));
					// decide whether to update global best
					if((i == valid_top_reg[idx] && j == valid_left_reg[idx]) || 
					(pre_SAD < pre_best_SAD) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length < pre_best_x_length + pre_best_y_length)) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length < pre_best_x_length)) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length == pre_best_x_length) && (pre_y_length < pre_best_y_length)) ) begin
						pre_best_SAD = pre_SAD;
						pre_best_x_length = pre_x_length;
						pre_best_y_length = pre_y_length;
						pre_best_mv_x[idx] = j - 2;
						pre_best_mv_y[idx] = i - 2;
					end
				end
			end
				
			$display("Precalculated motion vector result%d: %d, %d, best SAD %d", idx, pre_best_mv_x[idx], pre_best_mv_y[idx], pre_best_SAD);
		end
		
		
		//start sending signal to dut
		for( idx = 0; idx < 3; idx = idx + 1) begin 
			#(CLK_PERIOD) reuse = reuse_reg[idx];
			#(CLK_PERIOD)reset = 1;	
			pixel_valid_in = 0;
			success[idx] = 0;
			#(CLK_PERIOD) reset = 0;
			#(CLK_PERIOD);

			valid_left = valid_left_reg[idx];
			valid_right = valid_right_reg[idx];
			valid_top = valid_top_reg[idx];
			valid_bottom = valid_bottom_reg[idx];
			
			//  generate inputs to ME_engine
			for(i = 0; i < 20; i = i + 1) begin		
				for(j = 0; j < 5; j = j + 1) begin		
					#(CLK_PERIOD) 
					pixel_valid_in = 4'b1111;
					// decide which three pixel data to send in each cycle
					if(reuse) begin
						p0 = ((j>0) ? search_window[i][j*4][idx] : 0); 
						p1 = ((j>0) ? search_window[i][j*4+1][idx] : 0); 
						p2 = ((j>0) ? search_window[i][j*4+2][idx] : 0); 
						p3 = ((j>0) ? search_window[i][j*4+3][idx] : 0); 
					end
					else begin
						p0 = search_window[i][j*4][idx]; 
						p1 = search_window[i][j*4+1][idx]; 
						p2 = search_window[i][j*4+2][idx]; 
						p3 = search_window[i][j*4+3][idx]; 
					end
					if(i < 16 && j < 4) begin
						c0 = current_block[i][j*4][idx];
						c1 = current_block[i][j*4+1][idx];
						c2 = current_block[i][j*4+2][idx];
						c3 = current_block[i][j*4+3][idx];
					end
					else begin 
						c0 = 8'd0;
						c1 = 8'd0;
						c2 = 8'd0;
						c3 = 8'd0;
					end
				end
			end
			
			
			
			// judge whether mv result from ME engine is the same as precalculated
			while(mv_valid != 1) begin
				#(CLK_PERIOD);
				if(mv_valid == 1) begin
					$display("SAD result calculated by ME_engine: %d, %d", mv_x, mv_y);
					if(mv_x == pre_best_mv_x[idx] && mv_y == pre_best_mv_y[idx])
						success[idx] = 1;
					
				end
			end
			
		end
		
		
		if(&success)
			$display("Simulation result: Succeeded!");
		else
			$display("Simulation result: Failed...");

		$stop;
	end

	// instantiate ME engine
	ME_engine ME1 (clk, reset, reuse, valid_left, valid_right, valid_top, valid_bottom, pixel_valid_in, p0, p1, p2, p3, c0, c1, c2, c3, mv_valid, mv_x, mv_y);

endmodule
