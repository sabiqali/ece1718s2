// Processing Element in the ME engine
// calculate the absolute difference between 2 pixel data and accumulate SAD
module PE (clk, reset, pixel_valid, p0, p1, p2, p3, c0, c1, c2, c3, 
SAD_valid, SAD
);	
	input clk;
	input reset;
	input [3:0] pixel_valid;	// one for each pair
	input [7:0]  p0, p1, p2, p3, c0, c1, c2, c3;
	output SAD_valid;
	output reg [15:0] SAD;	
	
	wire [7:0] AD_wire [3:0];
	reg [7:0] AD_reg [3:0];
	reg [8:0] AD_counter;
	wire [8:0] add_wire [1:0];
	reg [8:0] add_reg [1:0];
	wire [15:0] SAD_wire;
	wire [2:0] valid_count;
	reg [2:0] SAD_valid_reg [1:0];
	
	integer i;
	
	assign valid_count = pixel_valid[3] + pixel_valid[2] + pixel_valid[1] + pixel_valid[0];
	
	assign AD_wire[3] = ((c3>p3) ? (c3-p3) : (p3-c3));
	assign AD_wire[2] = ((c2>p2) ? (c2-p2) : (p2-c2));
	assign AD_wire[1] = ((c1>p1) ? (c1-p1) : (p1-c1));
	assign AD_wire[0] = ((c0>p0) ? (c0-p0) : (p0-c0));
	
	assign add_wire[1] = AD_reg[3] + AD_reg[2];
	assign add_wire[0] = AD_reg[1] + AD_reg[0];
	
	assign SAD_wire = SAD + add_reg[1] + add_reg[0];
	
	assign SAD_valid = (AD_counter == 256);
	
	always@(posedge clk)begin
		if(reset) begin
			for(i = 0; i < 4; i = i + 1) begin
				AD_reg[i] <= 0;				
			end
			SAD_valid_reg[0] <= 0;
			
			for(i = 0; i < 2; i = i + 1) begin
				add_reg[i] <= 0;				
			end
			SAD_valid_reg[1] <= 0;
			
			SAD <= 0;			
			AD_counter <= 0;
		end
		else begin
			for(i = 0; i < 4; i = i + 1) begin
				AD_reg[i] <= ((pixel_valid[i]) ? AD_wire[i] : 8'd0);				
			end
			SAD_valid_reg[0] <= valid_count;
			
			for(i = 0; i < 2; i = i + 1) begin
				add_reg[i] <= add_wire[i];				
			end
			SAD_valid_reg[1] <= SAD_valid_reg[0];
			
			if(AD_counter < 256) begin
				SAD <= SAD_wire;
				AD_counter <= AD_counter + SAD_valid_reg[1];
			end
			else begin
				SAD <= SAD;
				AD_counter <= AD_counter;
			end			
			
		end
	end

endmodule       

                           