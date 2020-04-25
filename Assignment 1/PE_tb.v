`timescale 1ns/1ps

// testbench for processing element
module PE_tb ();
	localparam CLK_PERIOD = 20; //ns
	parameter block_size = 16;
	parameter pixel_width = 8;
	
	reg clk, reset;
	reg [3:0] pixel_valid;
	reg[7:0] p0, p1, p2, p3, c0, c1, c2, c3;
	wire SAD_valid;
	wire [15:0] SAD;	// 8 bits for one AD, number of ADs: block_size*block_size
	reg [15:0] SAD_data;
	reg[7:0] current_pixel_data [255:0];
	reg[7:0] previous_pixel_data [255:0];
	reg success;
	
	initial begin 
		clk <= 0;
		forever  #(CLK_PERIOD/2) clk = ~clk;
	end

	integer i;

	initial begin
		SAD_data = 0;
		for(i = 0; i < 256; i = i + 1) begin
			current_pixel_data[i] = $urandom(i);
			previous_pixel_data[i] = $urandom(i*i+20);
			SAD_data = SAD_data + ((current_pixel_data[i] > previous_pixel_data[i]) ? (current_pixel_data[i] - previous_pixel_data[i]) : (previous_pixel_data[i] - current_pixel_data[i]));
		end
		$display("Precalculated SAD result: %d", SAD_data);
		
		#0 reset = 1;	
		pixel_valid = 0;
		success = 0;
		#(CLK_PERIOD) reset = 0;
		for(i = 0; i < block_size*block_size/4; i = i + 1) begin			
			#(CLK_PERIOD) 
			pixel_valid = 4'b1111;
			c0 = current_pixel_data[4*i];
			c1 = current_pixel_data[4*i+1];
			c2 = current_pixel_data[4*i+2];
			c3 = current_pixel_data[4*i+3];
			p0 = previous_pixel_data[4*i];
			p1 = previous_pixel_data[4*i+1];
			p2 = previous_pixel_data[4*i+2];
			p3 = previous_pixel_data[4*i+3];		
		end

		for(i = 0; i < 3; i = i + 1) begin
			#(CLK_PERIOD);
			if(SAD_valid == 1) begin
				$display("SAD result calculated by PE: %d", SAD);
				if(SAD == SAD_data)
					success = 1;
			end
		end
		if(success)
			$display("Simulation result: Succeeded!");
		else
			$display("Simulation result: Failed...");

		$stop;
	end

	PE PE1(clk, reset, pixel_valid, p0, p1, p2, p3, c0, c1, c2, c3, 
SAD_valid, SAD); 




endmodule
