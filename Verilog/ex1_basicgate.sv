// Experiment 1: Development of Verilog modules for basic gates
//               and to verify truth tables.
module gates(AND, OR, XOR, NOT, a, b);
  input a, b;
  output AND, OR, XOR, NOT;
  assign AND = a & b;
  assign OR = a | b;
  assign XOR = a ^ b;
  assign NOT = ~a;
endmodule

// Testbench
module main;
  reg in1, in2;
  wire a, o, x, n;
  
  gates gates_test(.AND(a), .OR(o), .XOR(x), .NOT(n), .a(in1), .b(in2));
  initial begin
    $display("A\tB | AND\tOR\tXOR\tNOT");
    {in1, in2} = 2'b00;
    #2; $display("%b\t%d |  %b\t %b\t %b\t %b\t", in1, in2, a, o, x, n);
    {in1, in2} = 2'b01;
    #2; $display("%b\t%d |  %b\t %b\t %b\t %b\t", in1, in2, a, o, x, n);
    {in1, in2} = 2'b10;
    #2; $display("%b\t%d |  %b\t %b\t %b\t %b\t", in1, in2, a, o, x, n);
    {in1, in2} = 2'b11;
    #2; $display("%b\t%d |  %b\t %b\t %b\t %b\t", in1, in2, a, o, x, n);
  end
endmodule

// Output
// A	B | AND	OR	XOR	NOT
// 0	0 |  0	 0	 0	 1	
// 0	1 |  0	 1	 1	 1	
// 1	0 |  0	 1	 1	 0	
// 1	1 |  1	 1	 0	 0
// Done