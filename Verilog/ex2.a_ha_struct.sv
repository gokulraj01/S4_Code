// Experiment 2A: Structural Model Half Adder
// Structural or Gate Level Design
module structural_ha(SUM, COUT, A, B);
  input A, B;
  output SUM, COUT;
  xor(SUM, A, B);
  and(COUT, A, B);
endmodule

// Testbench
module main;
  reg in1, in2;
  wire s, c;
  
  structural_ha ha_str(s, c, in1, in2);
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