#include "Halide.h"
#include "wrapper_tutorial_03.h"
#include <tiramisu/utils.h>
#include <cstdlib>
#include <iostream>

#define NN 1000

int main(int, char **)
{
    Halide::Buffer<uint8_t> A_buf(NN, NN);
    init_buffer(A_buf, (uint8_t)1);
    Halide::Buffer<uint8_t> B_buf(NN, NN);
    init_buffer(B_buf, (uint8_t)1);

    // Output
    Halide::Buffer<uint8_t> C1_buf(NN, NN);

    matmul(A_buf.raw_buffer(), B_buf.raw_buffer(), C1_buf.raw_buffer());

    // Reference matrix multiplication
    Halide::Buffer<uint8_t> C2_buf(NN, NN);
    init_buffer(C2_buf, (uint8_t)0);

    for (int i = 0; i < NN; i++)
        for (int j = 0; j < NN; j++)
            for (int k = 0; k < NN; k++)
            {
                C2_buf(i, j) += A_buf(i, k) * B_buf(k, j);
            }

    compare_buffers("matmul", C1_buf, C2_buf);

    return 0;
}
