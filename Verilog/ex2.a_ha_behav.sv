// Experiment 2A: Behavioural Model Half Adder
// Behavioural Level Design
module behavioural_ha(SUM, COUT, A, B);
  input A, B;
  output reg SUM, COUT;
  always @(A,B) begin
    SUM =  A ^ B;
  	COUT = A & B;
  end
endmodule

// Testbench
module main;
  reg in1, in2;
  wire s, c;
  
  behavioural_ha ha_bv(s, c, in1, in2);
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