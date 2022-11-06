// Experiment 3B: 4-bit Gray to Binary code converter
// Design
module gray2bin(b3, b2, b1, b0, g3, g2, g1, g0);
    input g3, g2, g1, g0;
    output b3, b2, b1, b0;
    assign b3 = g3;
    assign b2 = b3 ^ g2;
    assign b1 = b2 ^ g1;
    assign b0 = b1 ^ g0;
endmodule

// Testbench
module main;
    reg g3, g2, g1, g0;
    wire b3, b2, b1, b0;
    reg [5:0]acc;

    gray2bin g2b(b3, b2, b1, b0, g3, g2, g1, g0);
    initial begin
        $display("G3\tG2\tG1\tG0 | B3\tB2\tB1\tB0");
        for(acc=0; acc<16; acc=acc+1) begin
            assign g3 = acc[3];
            assign g2 = acc[2];
            assign g1 = acc[1];
            assign g0 = acc[0];
            #5; $display("%b\t%b\t%b\t%b  |  %b\t %b\t %b\t %b", g3, g2, g1, g0, b3, b2, b1, b0);
        end
    end
endmodule

// Output
// G3	G2	G1	G0 | B3	B2	B1	B0
// 0	0	0	0  |  0	 0	 0	 0
// 0	0	0	1  |  0	 0	 0	 1
// 0	0	1	0  |  0	 0	 1	 1
// 0	0	1	1  |  0	 0	 1	 0
// 0	1	0	0  |  0	 1	 1	 1
// 0	1	0	1  |  0	 1	 1	 0
// 0	1	1	0  |  0	 1	 0	 0
// 0	1	1	1  |  0	 1	 0	 1
// 1	0	0	0  |  1	 1	 1	 1
// 1	0	0	1  |  1	 1	 1	 0
// 1	0	1	0  |  1	 1	 0	 0
// 1	0	1	1  |  1	 1	 0	 1
// 1	1	0	0  |  1	 0	 0	 0
// 1	1	0	1  |  1	 0	 0	 1
// 1	1	1	0  |  1	 0	 1	 1
// 1	1	1	1  |  1	 0	 1	 0
// Done