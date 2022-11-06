// Experiment 2B: Development of Verilog modules for full adder
//                in structural modeling using half adder
module structural_ha(SUM, COUT, A, B);
  input A, B;
  output SUM, COUT;
  xor(SUM, A, B);
  and(COUT, A, B);
endmodule

module fa(SUM, COUT, A, B, CIN);
  input A, B, CIN;
  output SUM, COUT;
  wire s1, s2, c1, c2;
  ha ha1(s1, c1, A, B);
  ha ha2(s2, c2, s1, CIN);
  assign SUM = s2;
  or(COUT,c1,c2);
endmodule

// Testbench
module main;
  reg in1, in2, in3, z;
  reg [4:0]acc;
  wire s, c;
  
  fa fa_test(s, c, in1, in2, in3);
  initial begin
    $display("A\tB\tC | SUM\tCARRY");
    for(acc=0; acc<8; acc=acc+1) begin
      assign in1 = acc[2];
      assign in2 = acc[1];
      assign in3 = acc[0];
      #5; $display("%b\t%b\t%b |  %b\t %b", in1, in2, in3, s, c);
    end
  end
endmodule

// Output
// A	B	C | SUM	CARRY
// 0	0	0 |  0	 0
// 0	0	1 |  1	 0
// 0	1	0 |  1	 0
// 0	1	1 |  0	 1
// 1	0	0 |  1	 0
// 1	0	1 |  0	 1
// 1	1	0 |  0	 1
// 1	1	1 |  1	 1
// Done