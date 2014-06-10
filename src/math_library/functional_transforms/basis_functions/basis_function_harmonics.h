//-*-C++-*-

#ifndef BASIS_FUNCTION_HARMONICS_H
#define BASIS_FUNCTION_HARMONICS_H

namespace MATH_ALGORITHMS
{
  template<typename lhs_dmn_type, typename rhs_dmn_type>
  class basis_function<lhs_dmn_type, KRONECKER_DELTA, rhs_dmn_type, HARMONICS>
  {
  public:

    typedef typename lhs_dmn_type::dmn_specifications_type lhs_spec_dmn_type;
    typedef typename rhs_dmn_type::dmn_specifications_type rhs_spec_dmn_type;

    typedef typename lhs_spec_dmn_type::scalar_type lhs_scalar_type;
    typedef typename rhs_spec_dmn_type::scalar_type rhs_scalar_type;

    typedef typename lhs_spec_dmn_type::element_type lhs_element_type;
    typedef typename rhs_spec_dmn_type::element_type rhs_element_type;
    
    typedef std::complex<lhs_scalar_type> f_scalar_type;

  public:

    static f_scalar_type execute(int i, int j)
    {
      return execute(lhs_dmn_type::get_elements()[i], rhs_dmn_type::get_elements()[j]);
    }

    static f_scalar_type execute(lhs_element_type& lh_elem, rhs_element_type& rh_elem)
    {
      const static f_scalar_type I(0,1);

      f_scalar_type phase = dot_prod(lh_elem, rh_elem);

      return std::exp(I*phase);
    }

  private:
    
    template<typename scalartype>
    inline static scalartype dot_prod(scalartype x, scalartype y)
    {
      return x*y;
    }

    template<typename scalartype>
    inline static scalartype dot_prod(std::vector<scalartype> x, std::vector<scalartype> y)
    {
      scalartype result=0;
      for(size_t l=0; l<x.size(); l++)
	result += x[l]*y[l];
      return result;
    }
  };


  template<typename lhs_dmn_type, typename rhs_dmn_type>
  class basis_function<lhs_dmn_type, HERMITE_CUBIC_SPLINE, rhs_dmn_type, HARMONICS>
  {
  public:

    typedef typename lhs_dmn_type::dmn_specifications_type lhs_spec_dmn_type;
    typedef typename rhs_dmn_type::dmn_specifications_type rhs_spec_dmn_type;

    typedef typename lhs_spec_dmn_type::scalar_type lhs_scalar_type;
    typedef typename rhs_spec_dmn_type::scalar_type rhs_scalar_type;

    typedef typename lhs_spec_dmn_type::element_type lhs_element_type;
    typedef typename rhs_spec_dmn_type::element_type rhs_element_type;
    
    typedef std::complex<lhs_scalar_type> f_scalar_type;

  public:

    static f_scalar_type execute(int i, int j)
    {
      return execute(lhs_dmn_type::get_elements()[i], rhs_dmn_type::get_elements()[j]);
    }

    static f_scalar_type execute(lhs_element_type& lh_elem, rhs_element_type& rh_elem)
    {
      const static f_scalar_type I(0,1);

      f_scalar_type phase = dot_prod(lh_elem, rh_elem);

      //return std::exp(I*phase)/lhs_dmn_type::get_volume();
      return std::exp(-I*phase)/lhs_dmn_type::get_volume();
    }

  private:
    
    template<typename scalartype>
    inline static scalartype dot_prod(scalartype x, scalartype y)
    {
      return x*y;
    }

    template<typename scalartype>
    inline static scalartype dot_prod(std::vector<scalartype> x, std::vector<scalartype> y)
    {
      scalartype result=0;
      for(size_t l=0; l<x.size(); l++)
	result += x[l]*y[l];
      return result;
    }
  };

}

#endif
