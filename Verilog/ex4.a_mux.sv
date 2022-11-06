// Experiment 4A: Development of Verilog modules for a 4x1 MUX.
// Design
module mux(OUT, I0, I1, I2, I3, S1, S0);
  input I0, I1, I2, I3, S1, S0;
  output OUT;
  assign OUT = ~S1&~S0&I0 | ~S1&S0&I1 | S1&~S0&I2 | S1&S0&I3;
endmodule

// Testbench
module main;
  reg i0, i1, i2, i3, s1, s0;
  reg [4:0]acc;
  wire y;
  
  mux mux_test(y, i0, i1, i2, i3, s1, s0);
  initial begin
    $display("S1 S0 | I0 I1 I2 I3 | Y");
    #5; {i0, i1, i2, i3, s1, s0} = 6'b100000;
    $monitor(" %b  %b |  %b  %b  %b  %b | %b", s1, s0, i0, i1, i2, i3, y);
    #5; {i0, i1, i2, i3, s1, s0} = 6'b010001;
    #5; {i0, i1, i2, i3, s1, s0} = 6'b001010;
    #5; {i0, i1, i2, i3, s1, s0} = 6'b000111;
  end
endmodule

// Output
// S1 S0 | I0 I1 I2 I3 | Y
//  0  0 |  1  0  0  0 | 1
//  0  1 |  0  1  0  0 | 1
//  1  0 |  0  0  1  0 | 1
//  1  1 |  0  0  0  1 | 1
// Done