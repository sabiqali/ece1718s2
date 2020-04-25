__kernel void mult(__global float *A, __global float *B, __global float *C) {
    
    // Get the index of the current element
    int i = get_global_id(0);
    int j = get_global_id(1);

    // Do the operation
    //C[j][i] -= 0.01 * B[j][i];
    C[i*120 + j] -= 0.01 * B[i*120 + j];
}
