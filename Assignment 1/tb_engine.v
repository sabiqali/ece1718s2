`timescale 1ns/10ps 

`define NULL 0    
module engine_tb();

localparam CLK_PERIOD = 4;
  integer               config_file    ; // file handler
  integer               config_scan_file    ; // file handler
  integer               cur_file    ; // file handler
  integer               cur_scan_file    ; // file handler
  integer               ref_file    ; // file handler
  integer               ref_scan_file    ; // file handler
  
  integer mv_write;
  
  reg  [5:0]config_captured_data;
  reg  [8:0]cur_captured_data;
  reg  [8:0]slidewindow_captured_data;
  reg           dut_clk;
  reg           dut_rst_n;
  /*come from config file*/
  reg [5:0]dut_ref_width;
  reg [5:0]dut_ref_height;
  reg [5:0]dut_cur_size;
  reg [5:0]dut_search_range;
  reg [5:0]dut_reuse_ctr;
  reg [5:0]dut_validTop;
  reg [5:0]dut_validBottom;
  reg [5:0]dut_validLeft;
  reg [5:0]dut_validRight;
  /*come from cur block file, fixed size 256 datapoints each has 8 bits*/
  reg [8:0]dut_cur_data;
  /*come from ref block file, fixed size has 9 bits*/
  reg [8:0]dut_ref_data;
    
  //reg me_busy;//signal that marks the me engine finishes,write  results==1
  reg read_finish;//complete read sliding window
  reg signed [2:0]fake_result1,fake_result2;
  
  reg [31:0]slide_counter;
  reg [63:0]slide_uplimit;
  
reg [8:0]slid_matrix[0:19][0:19];
reg [8:0]curblock_matrix[0:15][0:15];

	reg clk;
	reg reset;
	reg reuse;
	reg [4:0] valid_left, valid_right, valid_top, valid_bottom;
	reg [3:0] pixel_valid_in; 
	reg [7:0]  p0, p1, p2, p3, c0, c1, c2, c3;
	wire mv_valid; 
	wire signed [2:0] mv_x, mv_y;
reg write_to_file;
reg written;
//wire [15:0]  dut_res_mv;
  
 
// instantiate ME engine
	ME_engine dut (dut_clk, reset, reuse, valid_left, valid_right, valid_top, valid_bottom, pixel_valid_in, p0, p1, p2, p3, c0, c1, c2, c3, mv_valid, mv_x, mv_y);



  
  initial begin
    config_file = $fopen("configure.txt", "r");
    if (config_file == `NULL) begin
      $display("data_file handle was NULL");
      $finish;
    end
  end
  initial begin
    //me_busy=1;
    read_finish=1'd0;
    fake_result1=2'b01;
    fake_result2=2'b00;
    slide_counter=0;
    
    dut_validTop=0;
    dut_validBottom=19;
    dut_validLeft=0;
    dut_validRight=19;
    
    
    
    dut_clk   = 1'b0;
    /*dut_rst_n = 1'b1;
    repeat(1) @(negedge dut_clk);
    dut_rst_n = 1'b0;
    repeat(1) @(posedge dut_clk);
    #1;
    dut_rst_n = 1'b1;*/
  end
  always #2 dut_clk = ~dut_clk;

initial begin
    cur_file = $fopen("cur_block.txt", "r");
    if (cur_file == `NULL) begin
      $display("data_file handle was NULL");
      $finish;
    end
  end

reg [20:0]curblock_uplimit;
always @(posedge dut_clk) begin
  if (dut_cur_size!=0 )begin
    curblock_uplimit=dut_cur_size*dut_cur_size+9;
  end
end  
  
reg [4:0]curblock_x;
reg [4:0]curblock_y;
reg [7:0]slide_x;
reg [7:0]slide_y;
initial begin
  curblock_x=0;
  curblock_y=0;
  slide_x=0;
  slide_y=0;
end
always @(posedge dut_clk) begin
  
  if (slide_counter<=curblock_uplimit &&slide_counter>4'd9 /*&&read_finish==0 */)begin
    cur_scan_file = $fscanf(cur_file, "%d\n", cur_captured_data);
    dut_cur_data=cur_captured_data;
    if (curblock_y<dut_cur_size)begin
      curblock_matrix[curblock_x][curblock_y]<=dut_cur_data;
      curblock_y=curblock_y+1;
    end
  else begin
    curblock_matrix[curblock_x+1][0]<=dut_cur_data;
    curblock_y<=1;
    curblock_x=curblock_x+1;
  end
  end
else begin 
  curblock_x<=0;
  curblock_y<=0;
end

end  
  
  
  
always @(posedge dut_clk) begin
  if (dut_ref_width!=0 && dut_ref_height!=0)begin
    slide_uplimit=dut_ref_width*dut_ref_height+8;
  end
end  

always @(posedge dut_clk) begin
   
  if (slide_counter<4'd9 )begin
    config_scan_file = $fscanf(config_file, "%d\n", config_captured_data);
    if (slide_counter==4'd0)begin
      dut_ref_width=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd1)begin
      dut_ref_height=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd2)begin
      dut_cur_size=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd3)begin
      dut_search_range=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    
    if (slide_counter==4'd4)begin
      dut_validTop=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd5)begin
      dut_validBottom=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd6)begin
      dut_validLeft=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd7)begin
      dut_validRight=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    if (slide_counter==4'd8)begin
      dut_reuse_ctr=config_captured_data;
      slide_counter<=slide_counter+1;
    end
    
  end
    
end


initial begin
    ref_file = $fopen("slide_window.txt", "r");
    if (ref_file == `NULL) begin
      $display("data_file handle was NULL");
      $finish;
    end
  end
  
always @(posedge dut_clk) begin
  if (slide_counter==4'd7)begin
    slide_x<=dut_validTop;
    slide_y<=dut_validLeft;
    
  end

end  
  
always @(posedge dut_clk) begin
  
  if (slide_counter>=4'd8 && slide_counter<=slide_uplimit &&!read_finish)begin
    ref_scan_file <= $fscanf(ref_file, "%d\n", slidewindow_captured_data);
    dut_ref_data=slidewindow_captured_data;
    slide_counter=slide_counter+1;
    if (slide_y<=dut_validRight)begin
      slid_matrix[slide_x][slide_y]<=dut_ref_data;
      if (slide_y==dut_validRight)begin
        slide_y<=dut_validLeft;
        if (slide_x==dut_validBottom)begin
          slide_x<=0;
          slide_y<=0;
          slide_counter<=0;
          read_finish<=1;
        end
      else begin
        slide_x<=slide_x+1;
      end
      end
      else begin
        
        slide_y<=slide_y+1;
        end
    end
  end
end  

	reg [15:0] pre_SAD;
	reg [15:0] pre_best_SAD;	
	reg [2:0] pre_x_length, pre_y_length;
	reg [2:0] pre_best_x_length, pre_best_y_length;
	reg signed [2:0] pre_best_mv_x ;
	reg signed [2:0] pre_best_mv_y ;

integer i, j, k, l;
initial begin
	//start sending signal to dut
	while(1) begin		
		if(!read_finish) begin
			#(CLK_PERIOD) reuse = dut_reuse_ctr;
			#(CLK_PERIOD) reset = 1;	
			pixel_valid_in = 0;
		end
		else begin
			#(CLK_PERIOD) reuse = dut_reuse_ctr;
			#(CLK_PERIOD) reset = 1;	
			pixel_valid_in = 0;
			#(CLK_PERIOD) reset = 0;
			#(CLK_PERIOD);

			valid_left = dut_validLeft;
			valid_right = dut_validRight;
			valid_top = dut_validTop;
			valid_bottom = dut_validBottom;

			
			/*
			// precalculation of best motion vector
			for(i = valid_top; i <= valid_bottom-15; i = i + 1) begin
				for(j = valid_left; j <= valid_right-15; j = j + 1) begin
					pre_SAD = 0;
					for(k = 0; k < 16; k = k + 1) begin
						for(l = 0; l < 16; l = l + 1) begin						
							pre_SAD = pre_SAD + ((curblock_matrix[k][l] > slid_matrix[i+k][j+l]) ? (curblock_matrix[k][l] - slid_matrix[i+k][j+l]) : (slid_matrix[i+k][j+l] - curblock_matrix[k][l]));
							
						end
					end
					pre_x_length = ((j > 2) ? (j - 2) : (2 - j));
					pre_y_length = ((i > 2) ? (i - 2) : (2 - i));
					// decide whether to update global best
					if((i == valid_top && j == valid_left) || 
					(pre_SAD < pre_best_SAD) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length < pre_best_x_length + pre_best_y_length)) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length < pre_best_x_length)) ||
					((pre_SAD == pre_best_SAD) && (pre_x_length + pre_y_length == pre_best_x_length + pre_best_y_length) && (pre_x_length == pre_best_x_length) && (pre_y_length < pre_best_y_length)) ) begin
						pre_best_SAD = pre_SAD;
						pre_best_x_length = pre_x_length;
						pre_best_y_length = pre_y_length;
						pre_best_mv_x = j - 2;
						pre_best_mv_y = i - 2;
					end
				end
			end
				
			$display("Precalculated motion vector result: %d, %d, best SAD %d", pre_best_mv_x, pre_best_mv_y, pre_best_SAD);
			*/
			//  generate inputs to ME_engine
			for(i = 0; i < 20; i = i + 1) begin		
				for(j = 0; j < 5; j = j + 1) begin		
					#(CLK_PERIOD) 
					pixel_valid_in = 4'b1111;
					// decide which three pixel data to send in each cycle
					if(reuse) begin
						p0 = ((j>0) ? slid_matrix[i][j*4] : 0); 
						p1 = ((j>0) ? slid_matrix[i][j*4+1] : 0); 
						p2 = ((j>0) ? slid_matrix[i][j*4+2]: 0); 
						p3 = ((j>0) ? slid_matrix[i][j*4+3] : 0); 
					end
					else begin
						p0 = slid_matrix[i][j*4]; 
						p1 = slid_matrix[i][j*4+1]; 
						p2 = slid_matrix[i][j*4+2]; 
						p3 = slid_matrix[i][j*4+3]; 
					end
					if(i < 16 && j < 4) begin
						c0 = curblock_matrix[i][j*4];
						c1 = curblock_matrix[i][j*4+1];
						c2 = curblock_matrix[i][j*4+2];
						c3 = curblock_matrix[i][j*4+3];
					end
					else begin 
						c0 = 8'd0;
						c1 = 8'd0;
						c2 = 8'd0;
						c3 = 8'd0;
					end
				end
			end
			#(CLK_PERIOD) pixel_valid_in = 0;
			while(read_finish == 1) begin
				#(CLK_PERIOD);
			end
		end
		
	end	// while loop 
end		
			
			
		



always @(posedge dut_clk) begin
  if (read_finish && mv_valid)begin
    read_finish<=0;
  end

end 



//write results to file
initial begin
    mv_write=$fopen("mv_results.txt","w"); 
  end



always @(posedge dut_clk) begin
	if(reset) begin
		written <= 0;
		write_to_file <= 0;
	end
else begin
  	if (mv_valid==1'd1)begin
		written <= 0;
  		write_to_file <= ((written || write_to_file) ? 0 : 1);
	end
	else
 		write_to_file <= 0;
	if(write_to_file) begin
		$display("SAD result calculated by ME_engine: %d, %d", mv_x, mv_y);
    	$fwrite(mv_write,"%d %d\n", mv_x, mv_y) ;
		written <= 1;
 	end
end
end
  
  

    
  
  
  
initial begin 
  #10000000
  $stop;
end
endmodule