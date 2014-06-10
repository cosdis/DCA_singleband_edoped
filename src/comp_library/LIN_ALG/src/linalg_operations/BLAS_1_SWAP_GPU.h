//-*-C++-*-                                                                                                                                                                                                                                                                                                                                                        

#ifndef LINALG_SWAP_GPU_H
#define LINALG_SWAP_GPU_H

namespace LIN_ALG {

  namespace GPU_KERNEL_SWAP {

    void dswap(int length, double* a, int inc_a, double* b, int inc_b);
    void dswap(int length, double* a, int inc_a, double* b, int inc_b, int id);

    void swap_many_rows(int M_r, int M_c, double* M_ptr, int M_LD, 
			int N_s, int* i_s_ptr, int* i_t_ptr,
			int thread_id, int stream_id);		     

    void swap_many_cols(int M_r, int M_c, double* M_ptr, int M_LD, 
			int N_s, int* i_s_ptr, int* i_t_ptr,
			int thread_id, int stream_id);		     
    
  }

  template<>
  class SWAP<GPU>
  {
  public:
    
    template<typename scalartype>
    static void row(matrix<scalartype, GPU>& M, int i, int j, int thread_id, int stream_id)
    {
      
      assert(i>-1 && i<M.get_current_size().first);
      assert(j>-1 && j<M.get_current_size().first);
      
      execute(M.get_current_size().second, M.get_ptr(i,0), M.get_global_size().first, M.get_ptr(j,0), M.get_global_size().first, thread_id, stream_id);
    }
    
    template<typename scalartype>
    static void col(matrix<scalartype, GPU>& M, int i, int j, int thread_id, int stream_id)
    {

      assert(i>-1 && i<M.get_current_size().second);
      assert(j>-1 && j<M.get_current_size().second);
	  
      execute(M.get_current_size().first, M.get_ptr(0,i), 1, M.get_ptr(0,j), 1, thread_id, stream_id);
    }
	
    template<typename scalartype>
    static void row_and_column(matrix<scalartype, GPU>& M, int i, int j, int thread_id, int stream_id)
    {
      SWAP<GPU>::row( M, i, j, thread_id, stream_id);
      SWAP<GPU>::col( M, i, j, thread_id, stream_id);
    }

    template<typename scalartype>
    static void many_rows(matrix<scalartype, GPU>& M, 
			  vector<int       , GPU>& index_source,
			  vector<int       , GPU>& index_target,
			  int thread_id, int stream_id)
    {      
      assert(index_source.size() == index_target.size());
      
      int M_r = M.get_current_size().first;
      int M_c = M.get_current_size().second;

      scalartype* M_ptr =  M.get_ptr();

      int M_LD = M.get_global_size().first;

      int N_s = index_source.size();

      int* i_s_ptr = index_source.get_ptr();
      int* i_t_ptr = index_target.get_ptr();

      GPU_KERNEL_SWAP::swap_many_rows(M_r, M_c, M_ptr, M_LD, 
				      N_s, i_s_ptr, i_t_ptr,
				      thread_id, stream_id);		     
    }
    
    template<typename scalartype>
    static void many_cols(matrix<scalartype, GPU>& M, 
			  vector<int       , GPU>& index_source,
			  vector<int       , GPU>& index_target,
			  int thread_id, int stream_id)
    {
      assert(index_source.size() == index_target.size());
      
      int M_r = M.get_current_size().first;
      int M_c = M.get_current_size().second;

      scalartype* M_ptr =  M.get_ptr();

      int M_LD = M.get_global_size().first;

      int N_s = index_source.size();

      int* i_s_ptr = index_source.get_ptr();
      int* i_t_ptr = index_target.get_ptr();

      GPU_KERNEL_SWAP::swap_many_cols(M_r, M_c, M_ptr, M_LD, 
				      N_s, i_s_ptr, i_t_ptr,
				      thread_id, stream_id);		     
    }

    /*	
    inline static void execute(int length, float* a, int inc_a, float* b, int inc_b){
      GPU_KERNEL_SWAP::sswap(length, a, inc_a, b, inc_b);
    }
    */
	
    inline static void execute(int length, double* a, int inc_a, double* b, int inc_b,
			       int thread_id, int stream_id)
    {
      assert(stream_id==0);
      GPU_KERNEL_SWAP::dswap(length, a, inc_a, b, inc_b, thread_id);
    }
	
    /*
    inline static void execute(int length, cuComplex* a, int inc_a, cuComplex* b, int inc_b){
      cublasCswap(length, a, inc_a, b, inc_b);
    }
	
    inline static void execute(int length, cuDoubleComplex* a, int inc_a, cuDoubleComplex* b, int inc_b){
      cublasZswap(length, a, inc_a, b, inc_b);
    }
    */
  };

}

#endif
