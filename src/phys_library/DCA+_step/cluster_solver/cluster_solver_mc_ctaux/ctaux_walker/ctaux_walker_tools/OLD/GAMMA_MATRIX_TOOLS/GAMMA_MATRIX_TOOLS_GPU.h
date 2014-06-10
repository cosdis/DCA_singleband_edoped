//-*-C++-*-

#ifndef GAMMA_MATRIX_TOOLS_GPU_H
#define GAMMA_MATRIX_TOOLS_GPU_H

namespace QMC {
  
  namespace GAMMA_MATRIX_TOOLS_GPU_KERNELS {

    void compute_beta(int N, double* Gamma_LU_ptr, int LD_Gamma_LU, double  corr_term);
  }

  /*! 
   *  \ingroup CT-AUX-WALKER
   *
   *  \author Peter Staar
   *  \brief  This class contains all the data needed in the GAMMA_TOOLS class. 
   *          Depending on the template, the data will be situated in the host or device.
   */
  template<>
  class GAMMA_MATRIX_TOOLS<LIN_ALG::GPU>
  {
  public:

    GAMMA_MATRIX_TOOLS(int id, int n):
      thread_id(id),

      indices_up(0, n),
      indices_dn(0, n),

      exp_V_up  (0, n),
      exp_V_dn  (0, n),

      i_indices(0,n),
      j_indices(0,n),
      
      is_Bennett(0,n),
      
      exp_Vi(0,n),
      exp_Vj(0,n),
      
      r    (0,n),
      c    (0,n),
      delta(0,n)
    {}    

    ~GAMMA_MATRIX_TOOLS() 
    {}

    void initialize(){
      indices_up.resize(0);
      indices_dn.resize(0);

      exp_V_up.resize(0);
      exp_V_dn.resize(0);
    }

    void resize(int n, e_spin_states_type e_spin){

      if(e_spin == e_UP)
	{
	  indices_up.resize(n);
	  exp_V_up  .resize(n);
	}
      else
	{
	  indices_dn.resize(n);
	  exp_V_dn  .resize(n);
	}
    }

    void push_back_new_values(int j, double exp_Vj, e_spin_states_type e_spin){
      
      if(e_spin == e_UP)
	{
	  indices_up.push_back(j);
	  exp_V_up  .push_back(exp_Vj);
	}
      else
	{
    	  indices_dn.push_back(j);
	  exp_V_dn  .push_back(exp_Vj);
	}
    }

    LIN_ALG::vector<int, LIN_ALG::GPU>& get_indices(e_spin_states_type e_spin){
      if(e_spin == e_UP)
	return indices_up;
      else
	return indices_dn;
    }

    LIN_ALG::vector<double, LIN_ALG::GPU>& get_exp_V(e_spin_states_type e_spin){
      if(e_spin == e_UP)
	return exp_V_up;
      else
	return exp_V_dn;
    }

    void set_delta(int index, double val){
      LIN_ALG::MEMORY_MANAGEMENT<LIN_ALG::GPU>::set_to_zero(delta.get_ptr(), delta.size());
      LIN_ALG::MEMORY_MANAGEMENT<LIN_ALG::GPU>::set(delta.get_ptr(index), val);
    }

    static void compute_beta(LIN_ALG::matrix<double, LIN_ALG::GPU>& Gamma_LU, double gamma_k){
      
      int n = Gamma_LU.get_number_of_rows();
      GAMMA_MATRIX_TOOLS_GPU_KERNELS::compute_beta(n, Gamma_LU.get_ptr(), Gamma_LU.get_leading_dimension(), (gamma_k)/(gamma_k-1.));

//       Gamma_LU(n-1, n-1) -= (gamma_k)/(gamma_k-1.);
//       Gamma_LU(n-1, n-1) -= LIN_ALG::DOT<LIN_ALG::CPU>::execute(n-1, Gamma_LU.get_ptr(n-1,0), Gamma_LU.get_leading_dimension(), Gamma_LU.get_ptr(0,n-1), 1);
    }

  protected:

    int thread_id;

    LIN_ALG::vector<int   , LIN_ALG::GPU> indices_up, indices_dn;
    LIN_ALG::vector<double, LIN_ALG::GPU> exp_V_up, exp_V_dn;

    LIN_ALG::vector<int   , LIN_ALG::CPU> i_indices, j_indices;
    LIN_ALG::vector<bool  , LIN_ALG::CPU> is_Bennett;
    LIN_ALG::vector<double, LIN_ALG::CPU> exp_Vi, exp_Vj;
    LIN_ALG::vector<double, LIN_ALG::GPU> r, c, delta;
  };

}

#endif
