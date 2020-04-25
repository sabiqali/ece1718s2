//main module
module ME_engine (clk, reset, i_reuse, i_left, i_right, i_top, i_bottom, i_pixel_valid, i_p0, i_p1, i_p2, i_p3, i_c0, i_c1, i_c2, i_c3, o_mv_valid, o_mv_x, o_mv_y);
	
	input clk;
	input reset;
	input i_reuse;	// reset while reuse == 1 will not clear search window data
	input [4:0] i_left, i_right, i_top, i_bottom;	// legal range []
	input i_pixel_valid;	// 8 input pixel data are all valid
	input [7:0] i_p0, i_p1, i_p2, i_p3, i_c0, i_c1, i_c2, i_c3; 
	
	output reg o_mv_valid;
	output reg signed [2:0] o_mv_x;
	output reg signed [2:0] o_mv_y;
	
	// signal from and to PEs
	reg [3:0] pixel_valid [4:0][4:0];
	reg [7:0] p0 [4:0][4:0];
	reg [7:0] p1 [4:0][4:0];
	reg [7:0] p2 [4:0][4:0];
	reg [7:0] p3 [4:0][4:0];
	reg [7:0] c0 [4:0][4:0];
	reg [7:0] c1 [4:0][4:0];
	reg [7:0] c2 [4:0][4:0];
	reg [7:0] c3 [4:0][4:0];
	wire SAD_valid [4:0][4:0];
	wire [15:0] SAD [4:0][4:0];
	
	wire [7:0] i_c [3:0];
	
	integer i, j, k, l;
	// counters to record number of cycles and determine which status the engine is in
	reg [2:0] counter_x;	// 0-4  ( 16 + 4 ) / 4
	reg [4:0] counter_y;	// 0-19 ( 16 + 4 ) 
	// store data in the current block and search window for reuse
	reg [7:0] current_block [15:0][15:0];
	reg [7:0] previous_window [19:0][19:0];
	
	reg [4:0] sliding_index;
	wire [4:0] new_sliding_index;
	
	assign new_sliding_index = ((i_reuse) ? ((sliding_index + 16) % 20) : 0) ;						
	
	// put i_c0 ~ i_c1 into i_c vector
	assign i_c[3] = i_c3;
	assign i_c[2] = i_c2;
	assign i_c[1] = i_c1;
	assign i_c[0] = i_c0;
	
	// generate SAD in each PE
	always@(posedge clk)begin
		if(reset) begin
			for(i = 0; i < 5; i = i + 1) begin
				for(j = 0; j < 5; j = j + 1) begin
					pixel_valid[i][j] <= 0;
					p0[i][j] <= 0;
					p1[i][j] <= 0;
					p2[i][j] <= 0;
					p3[i][j] <= 0;
					c0[i][j] <= 0;
					c1[i][j] <= 0;
					c2[i][j] <= 0;
					c3[i][j] <= 0;
				end
			end
			for(i = 0; i <= 15; i = i + 1) begin
				for(j = 0; j <= 15; j = j + 1) begin
					current_block[i][j] <= 0;
				end
			end
			for(i = 0; i <= 19; i = i + 1) begin
				for(j = 0; j <= 19; j = j + 1) begin					
					previous_window[i][j] <= ((i_reuse == 0) ? 8'd0 : previous_window[i][j]);
				end
			end			
			counter_x <= 0;
			counter_y <= 0;
			sliding_index <= ((i_reuse == 0) ? 8'd0 : sliding_index);			
		end
		else begin
			// set default value
			for(i = 0; i < 5; i = i + 1) begin
				for(j = 0; j < 5; j = j + 1) begin
					pixel_valid[i][j] <= 0;
					p0[i][j] <= 0;
					p1[i][j] <= 0;
					p2[i][j] <= 0;
					p3[i][j] <= 0;
					c0[i][j] <= 0;
					c1[i][j] <= 0;
					c2[i][j] <= 0;
					c3[i][j] <= 0;
				end
			end
			for(i = 0; i < 15; i = i + 1) begin
				for(j = 0; j < 15; j = j + 1) begin
					current_block[i][j] <= current_block[i][j];
				end
			end
			for(i = 0; i < 19; i = i + 1) begin
				for(j = 0; j < 19; j = j + 1) begin
					previous_window[i][j] <= previous_window[i][j];
				end
			end
			counter_x <= counter_x;
			counter_y <= counter_y;
			sliding_index <= sliding_index;
			
			// if inputs are valid
			if(i_pixel_valid) begin
				// keep record of counter
				if(counter_x == 4) begin
					if(counter_y == 19) begin
						// update sliding index in the last cycle of the block
						if(i_reuse) begin
							sliding_index <= new_sliding_index;
						end
					end
					if(counter_y <= 19) begin
						counter_y <= counter_y + 1'b1;
						counter_x <= 0;
					end
					else begin
						counter_y <= counter_y;
						counter_x <= 0;
					end
				end
				else begin
					counter_x <= counter_x + 1'b1;
					counter_y <= counter_y;
				end
				// broadcast previous frame pixel data to PE
				for(i = 0; i < 5; i = i + 1) begin
					for(j = 0; j < 5; j = j + 1) begin
						if(counter_y < 20) begin						
							if(i_reuse) begin
								p0[i][j] <= (counter_x > 0) ? i_p0 : previous_window[counter_y][new_sliding_index%20];
								p1[i][j] <= (counter_x > 0) ? i_p1 : previous_window[counter_y][new_sliding_index%20+1];
								p2[i][j] <= (counter_x > 0) ? i_p2 : previous_window[counter_y][new_sliding_index%20+2];
								p3[i][j] <= (counter_x > 0) ? i_p3 : previous_window[counter_y][new_sliding_index%20+3];
							end
							else begin
								p0[i][j] <= i_p0;
								p1[i][j] <= i_p1;
								p2[i][j] <= i_p2;
								p3[i][j] <= i_p3;
							end
						end
						else begin
							p0[i][j] <= 8'd0;
							p1[i][j] <= 8'd0;
							p2[i][j] <= 8'd0;
							p3[i][j] <= 8'd0;
						end
					end
				end
				// store previous frame pixel data to memory
				if(counter_y < 20) begin
					if(i_reuse) begin
						if(counter_x > 0) begin	// reuse the right stripe of previous search window as left stripe of current window
							previous_window[counter_y][(counter_x*4+new_sliding_index)%20] <= i_p0;
							previous_window[counter_y][(counter_x*4+1+new_sliding_index)%20] <= i_p1;
							previous_window[counter_y][(counter_x*4+2+new_sliding_index)%20] <= i_p2;
							previous_window[counter_y][(counter_x*4+3+new_sliding_index)%20] <= i_p3;
						end
					end
					else begin
						previous_window[counter_y][counter_x*4] <= i_p0;
						previous_window[counter_y][counter_x*4+1] <= i_p1;
						previous_window[counter_y][counter_x*4+2] <= i_p2;
						previous_window[counter_y][counter_x*4+3] <= i_p3;					
					end
				end
				// determine valid and current frame pixel data
				for(i = 0; i < 5; i = i + 1) begin
					for(j = 0; j < 5; j = j + 1) begin
						// determine valid signal to PE
						if((counter_y - i >= 0) && (counter_y - i <= 15)) begin
							pixel_valid[i][j] <= {
							(((counter_x*4-j+3>=0) && (counter_x*4-j+3<=15)) ? 1'b1 : 1'b0), 
							(((counter_x*4-j+2>=0) && (counter_x*4-j+2<= 15)) ? 1'b1 : 1'b0), 
							(((counter_x*4-j+1>=0) && (counter_x*4-j+1<= 15)) ? 1'b1 : 1'b0), 
							(((counter_x*4-j>=0) && (counter_x*4-j<= 15)) ? 1'b1 : 1'b0) 
							};
						end
						else 						
							pixel_valid[i][j] <= 0;
						// store current block pixel data to memory
						if((counter_y <= 15) && (counter_x <= 3)) begin
							current_block[counter_y][counter_x*4] <= i_c0;							
							current_block[counter_y][counter_x*4+1] <= i_c1;
							current_block[counter_y][counter_x*4+2] <= i_c2;
							current_block[counter_y][counter_x*4+3] <= i_c3;							
						end
						// send current block pixel data to PE						
						c0[i][j] <= (i == 0 && j == 0) ? i_c[0] : ( ((counter_x*4-j>=0) && (counter_x*4-j<=15) && (counter_y-i>=0) && (counter_y-i<=15)) ? current_block[counter_y-i][counter_x*4-j] : 8'd0);
						c1[i][j] <= (i == 0 && j <= 1) ? i_c[1-j] : ( ((counter_x*4-j+1>=0) && (counter_x*4-j+1<=15) && (counter_y-i>=0) && (counter_y-i<=15)) ? current_block[counter_y-i][counter_x*4-j+1] : 8'd0);
						c2[i][j] <= (i == 0 && j <= 2) ? i_c[2-j] : ( ((counter_x*4-j+2>=0) && (counter_x*4-j+2<=15) && (counter_y-i>=0) && (counter_y-i<=15)) ? current_block[counter_y-i][counter_x*4-j+2] : 8'd0);
						c3[i][j] <= (i == 0 && j <= 3) ? i_c[3-j] : ( ((counter_x*4-j+3>=0) && (counter_x*4-j+3<=15) && (counter_y-i>=0) && (counter_y-i<=15)) ? current_block[counter_y-i][counter_x*4-j+3] : 8'd0);
					end
				end
			end
			
		end
		
	end
	
	
	// counter to record number of SAD compared
	reg [4:0] counter_SAD;	// 0-24 ( 5 * 5 )
	// record the temporary best motion vector and SAD
	reg [15:0] best_SAD;
	wire [2:0] x_length, y_length, best_x_length, best_y_length;
	
	assign y_length = ( (counter_SAD/5 > 2) ? (counter_SAD/5 - 2) : (2 - counter_SAD/5) );
	assign x_length = ( (counter_SAD%5 > 2) ? (counter_SAD%5 - 2) : (2 - counter_SAD%5) );
	assign best_y_length = ( (o_mv_y > 0) ? o_mv_y : -o_mv_y );
	assign best_x_length = ( (o_mv_x > 0) ? o_mv_x : -o_mv_x );
	// compare SAD generated by each PE
	always@(posedge clk)begin
		if(reset) begin
			counter_SAD <= 0;
			o_mv_valid <= 0;
			o_mv_x <= 0;
			o_mv_y <= 0;
			best_SAD <= 0;
		end
		else begin
			// set default			
			counter_SAD <= counter_SAD;
			o_mv_valid <= o_mv_valid;			
			best_SAD <= best_SAD;
			o_mv_x <= o_mv_x;
			o_mv_y <= o_mv_y;
			// judge whether or not to update global best
			if((counter_SAD < 25) && SAD_valid[counter_SAD/5][counter_SAD%5]) begin
				counter_SAD <= counter_SAD + 1'b1;
				o_mv_valid <= ((counter_SAD == 24) ? 1'b1 : 1'b0);				
				if((counter_SAD == (i_top*5+i_left)) || 
				(SAD[counter_SAD/5][counter_SAD%5] < best_SAD) ||
				((SAD[counter_SAD/5][counter_SAD%5] == best_SAD) && (y_length + x_length < best_y_length + best_x_length)) ||
				((SAD[counter_SAD/5][counter_SAD%5] == best_SAD) && (y_length + x_length == best_y_length + best_x_length) && (x_length < best_x_length)) ||
				((SAD[counter_SAD/5][counter_SAD%5] == best_SAD) && (y_length + x_length == best_y_length + best_x_length) && (x_length == best_x_length) && (y_length < best_y_length))
				) begin
					if(((counter_SAD/5) >= i_top) && ((counter_SAD/5) <= (i_bottom-15)) && ((counter_SAD%5) >= i_left) && ((counter_SAD%5) <= (i_right-15))) begin
						best_SAD <= SAD[counter_SAD/5][counter_SAD%5];				
						o_mv_y <= counter_SAD/5 - 2;
						o_mv_x <= counter_SAD%5 - 2;	
					end
				end
			end
			else if(counter_SAD == 25)
				o_mv_valid <= 1'b1;
		end
	end
	
	// instantiate Processing Elements
	genvar gi, gj;
	generate
		for(gi = 0; gi < 5; gi = gi + 1) begin: l1
			for(gj = 0; gj < 5; gj = gj + 1) begin: l2
				PE PE1(
				clk, 
				reset, 
				pixel_valid[gi][gj], 
				p0[gi][gj], 
				p1[gi][gj], 
				p2[gi][gj], 
				p3[gi][gj], 
				c0[gi][gj], 
				c1[gi][gj], 
				c2[gi][gj], 
				c3[gi][gj], 
				SAD_valid[gi][gj], 
				SAD[gi][gj]
				); 
			end
		end	
	endgenerate
	
	

endmodule

