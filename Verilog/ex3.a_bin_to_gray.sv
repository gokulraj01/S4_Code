// Experiment 3A: 4-bit Binary to Gray code converter
// Design
module bin2gray(g3, g2, g1, g0, b3, b2, b1, b0);
    input b3, b2, b1, b0;
    output g3, g2, g1, g0;
    assign g3 = b3;
    assign g2 = b3 ^ b2;
    assign g1 = b2 ^ b1;
    assign g0 = b1 ^ b0;
endmodule

// Testbench
module main;
    reg b3, b2, b1, b0;
    wire g3, g2, g1, g0;
    reg [5:0]acc;

    bin2gray b2g(g3, g2, g1, g0, b3, b2, b1, b0);
    initial begin
        $display("B3\tB2\tB1\tB0 | G3\tG2\tG1\tG0");
        for(acc=0; acc<16; acc=acc+1) begin
            assign b3 = acc[3];
            assign b2 = acc[2];
            assign b1 = acc[1];
            assign b0 = acc[0];
            #5; $display("%b\t%b\t%b\t%b  |  %b\t %b\t %b\t %b", b3, b2, b1, b0, g3, g2, g1, g0);
        end
    end
endmodule

// Output
// B3	B2	B1	B0 | G3	G2	G1	G0
// 0	0	0	0  |  0	 0	 0	 0
// 0	0	0	1  |  0	 0	 0	 1
// 0	0	1	0  |  0	 0	 1	 1
// 0	0	1	1  |  0	 0	 1	 0
// 0	1	0	0  |  0	 1	 1	 0
// 0	1	0	1  |  0	 1	 1	 1
// 0	1	1	0  |  0	 1	 0	 1
// 0	1	1	1  |  0	 1	 0	 0
// 1	0	0	0  |  1	 1	 0	 0
// 1	0	0	1  |  1	 1	 0	 1
// 1	0	1	0  |  1	 1	 1	 1
// 1	0	1	1  |  1	 1	 1	 0
// 1	1	0	0  |  1	 0	 1	 0
// 1	1	0	1  |  1	 0	 1	 1
// 1	1	1	0  |  1	 0	 0	 1
// 1	1	1	1  |  1	 0	 0	 0
// Done