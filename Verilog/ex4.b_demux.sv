// Experiment 4B: Development of Verilog modules for a 1x4 DEMUX.
// Design
module demux(I, Y0, Y1, Y2, Y3, S1, S0);
  input I, S1, S0;
  output Y0, Y1, Y2, Y3;
  assign Y0 = ~S1&~S0&I;
  assign Y1 = ~S1&S0&I;
  assign Y2 = S1&~S0&I;
  assign Y3 = S1&S0&I;
endmodule

// Testbench
module main;
  reg i, s1, s0;
  reg [4:0]acc;
  wire y0, y1, y2, y3;
  
  demux demux_test(i, y0, y1, y2, y3, s1, s0);
  initial begin
    $display("I | S1 S0 | Y0 Y1 Y2 Y3");
    #5; {i, s1, s0} = 3'b100;
    $monitor("%b |  %b  %b |  %b  %b  %b  %b", i, s1, s0, y0, y1, y2, y3);
    #5; {i, s1, s0} = 3'b101;
    #5; {i, s1, s0} = 3'b110;
    #5; {i, s1, s0} = 3'b111;
  end
endmodule

// Output
// I | S1 S0 | Y0 Y1 Y2 Y3
// 1 |  0  0 |  1  0  0  0
// 1 |  0  1 |  0  1  0  0
// 1 |  1  0 |  0  0  1  0
// 1 |  1  1 |  0  0  0  1
// Done