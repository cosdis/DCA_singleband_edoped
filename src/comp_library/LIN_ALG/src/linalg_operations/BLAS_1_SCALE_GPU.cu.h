//-*-C++-*-

#ifndef LINALG_SCALE_GPU_CU_H
#define LINALG_SCALE_GPU_CU_H

namespace LIN_ALG {

  namespace GPU_KERNEL_SCALE {

    void dscale(int length, double f, double* a, int inc_a)
    {
      cublasStatus_t status = cublasDscal(get_thread_handle(0), length, &f, a, inc_a);
      
      if(status != CUBLAS_STATUS_SUCCESS)
	  cublas_error_msg(status, __FUNCTION__, __FILE__, __LINE__);

#ifdef DEBUG_CUDA
      cuda_check_for_errors_end(__FUNCTION__, __FILE__, __LINE__);
#endif
    }

    void dscale(int length, double f, double* a, int inc_a, int id)
    {
      cublasStatus_t status = cublasDscal(get_thread_handle(id), length, &f, a, inc_a);
      
      if(status != CUBLAS_STATUS_SUCCESS)
	  cublas_error_msg(status, __FUNCTION__, __FILE__, __LINE__);

#ifdef DEBUG_CUDA
      cuda_check_for_errors_end(__FUNCTION__, __FILE__, __LINE__);
#endif
    }
        
    const static int BLOCK_SIZE_x = 32;
    const static int BLOCK_SIZE_y = 8;

    __global__ void many_rows_kernel(int Nc, int Ni, int* r_i, double* alpha, double* A, int LD)
    {
      int index = threadIdx.x + blockIdx.x*BLOCK_SIZE_x;
	  
      int l_MIN = BLOCK_SIZE_y*(blockIdx.y+0);
      int l_MAX = BLOCK_SIZE_y*(blockIdx.y+1);
      
      l_MIN = max(l_MIN, 0);
      l_MAX = min(l_MAX, Nc);
      
      if(index < Ni)
	{
	  int row_index = r_i[index];
	  assert(row_index>-1);
	  assert(row_index<Nc);

	  for(int l=l_MIN; l<l_MAX; ++l)
	    A[row_index+l*LD] *= alpha[index]; 
	}
    }

    void many_rows(int Nc, int Ni, int* r_i, double* alpha, double* A, int LD, int thread_id, int stream_id)
    {
      if(Ni>0 and Nc>0)
	{
#ifdef DEBUG_CUDA
	  //CUBLAS_THREAD_MANAGER<device_t>::synchronize_streams(thread_id, stream_id);
	  cuda_check_for_errors_bgn(__FUNCTION__, __FILE__, __LINE__);
#endif

	  int bl_x = get_number_of_blocks(Ni, BLOCK_SIZE_x);
	  int bl_y = get_number_of_blocks(Nc, BLOCK_SIZE_y);
	  
	  dim3 threads(BLOCK_SIZE_x);
	  dim3 blocks (bl_x, bl_y);

	  cudaStream_t& stream_handle = LIN_ALG::get_stream_handle(thread_id, stream_id);
	  
	  many_rows_kernel<<<blocks, threads, 0, stream_handle>>>(Nc, Ni, r_i, alpha, A, LD);

#ifdef DEBUG_CUDA
	  //CUBLAS_THREAD_MANAGER<device_t>::synchronize_streams(thread_id, stream_id);
	  cuda_check_for_errors_end(__FUNCTION__, __FILE__, __LINE__);
#endif
	}
    }

  }

}

#endif



