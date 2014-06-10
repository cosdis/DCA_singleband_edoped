//-*-C++-*-

#ifndef WANNIER_INTERPOLATION_KERNEL_NU_NU_K_TO_NU_NU_k_NFFT_H
#define WANNIER_INTERPOLATION_KERNEL_NU_NU_K_TO_NU_NU_k_NFFT_H

/*! \class   wannier_interpolation_kernel
 *  \ingroup INTERPOLATION
 *
 *  \author  Peter Staar
 *  \brief   This class implements a Wannier interpolation technique, using the nfft library.
 */
template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
class wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>, 
				   dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >
{
#include "type_definitions.h"

  typedef typename source_k_dmn_type::parameter_type source_k_cluster_type;
  typedef typename target_k_dmn_type::parameter_type target_k_cluster_type;

  //typedef typename source_k_cluster_type::base_cluster source_base_cluster_type;
  //typedef typename target_k_cluster_type::base_cluster target_base_cluster_type;

  typedef wannier_interpolation_kernel<source_k_cluster_type, target_k_cluster_type> wannier_interpolation_kernel_type;
  //typedef wannier_interpolation_kernel<source_base_cluster_type, target_k_cluster_type> wannier_interpolation_kernel_type;

  typedef typename wannier_interpolation_kernel_type::centered_r_cluster_dmn_t centered_r_dmn_t;
  //typedef dmn_0<centered_r_LDA> centered_r_dmn_t;

  typedef dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type> input_dmn_t;
  typedef dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> output_dmn_t;

public:

  wannier_interpolation_kernel();
  ~wannier_interpolation_kernel();
  
  void reset();

  void reset_functions();

  void set(function<std::complex<double>, input_dmn_t >& H_K);
  void get(function<std::complex<double>, output_dmn_t>& H_k);

private:
  
  b_dmn_t dmn;

  wannier_interpolation_kernel_type wannier_kernel_object;

  //function<std::complex<double>, centered_r_dmn_t>  in;
  function<std::complex<double>, source_k_dmn_type> in;
  function<std::complex<double>, target_k_dmn_type> out;

  function<std::complex<double>, dmn_3<b_dmn_t, b_dmn_t, centered_r_dmn_t> > F_R;
};

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>, 
			     dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::wannier_interpolation_kernel():
  wannier_kernel_object(),

  F_R("wannier_interpolation_kernel__F_r")
{}

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>, 
			     dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::~wannier_interpolation_kernel()
{}

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
void wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>,
				  dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::reset()
{
  wannier_kernel_object.reset_output();
}

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
void wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>,
				  dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::reset_functions()
{
  in .reset();
  out.reset();

  F_R.reset();
}

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
void wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>,
				  dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::set(function<std::complex<double>, input_dmn_t>& H_K)
{
  for(int i=0; i<dmn.get_size(); ++i){
    for(int j=0; j<dmn.get_size(); ++j){
      
      for(int k=0; k<source_k_cluster_type::get_size(); ++k)
	in(k) = H_K(i,j,k);

      wannier_kernel_object.set(&in(0));

      for(int r=0; r<centered_r_dmn_t::dmn_size(); ++r)
	F_R(i,j,r) = wannier_kernel_object.get_F_r(r);
    }
  }
}

template<typename b_dmn_t, typename source_k_dmn_type, typename target_k_dmn_type>
void wannier_interpolation_kernel<dmn_3<b_dmn_t, b_dmn_t, source_k_dmn_type>, 
				  dmn_3<b_dmn_t, b_dmn_t, target_k_dmn_type> >::get(function<std::complex<double>, output_dmn_t>& H_k)
{
  for(int i=0; i<dmn.get_size(); ++i){
    for(int j=0; j<dmn.get_size(); ++j){

      for(int r=0; r<centered_r_dmn_t::dmn_size(); ++r)
	wannier_kernel_object.get_F_r(r) = F_R(i,j,r);
      
      wannier_kernel_object.get(&out(0));
      
      for(int k=0; k<target_k_cluster_type::get_size(); ++k)
	H_k(i,j,k) = out(k);  
    }
  }
}

#endif
