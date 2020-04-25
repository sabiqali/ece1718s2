__kernel void vector_addv7(__global float *A, __global float *B, __global float *C) {
    
    // Get the index of the current element
    int i = get_global_id(0);
    int j = get_global_id(1);

    // Do the operation
    //C[i][j] = A[i] * B[j];
    C[i*120+j] = A[i] * B[j];
}
