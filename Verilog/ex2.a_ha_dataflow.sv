// Experiment 2A: Dataflow Model Half Adder
// Dataflow Level Design
module dataflow_ha(SUM, COUT, A, B);
  input A, B;
  output SUM, COUT;
  assign SUM =  A ^ B;
  assign COUT = A & B;
endmodule

// Testbench
module main;
  reg in1, in2;
  wire s, c;
  
  dataflow_ha ha_df(s, c, in1, in2);
  initial begin
    $display("A\tB | SUM\tCARRY");
    {in1, in2} = 2'b00;
    #2; $display("%b\t%d |  %b\t %b\t", in1, in2, s, c);
    {in1, in2} = 2'b01;
    #2; $display("%b\t%d |  %b\t %b\t", in1, in2, s, c);
    {in1, in2} = 2'b10;
    #2; $display("%b\t%d |  %b\t %b\t", in1, in2, s, c);
    {in1, in2} = 2'b11;
    #2; $display("%b\t%d |  %b\t %b\t", in1, in2, s, c);
  end
endmodule

// Output
// A	B | SUM	CARRY
// 0	0 |  0	 0	
// 0	1 |  1	 0	
// 1	0 |  1	 0	
// 1	1 |  0	 1	
// Done