//-*-C++-*-

#ifndef BASIS_TRANSFORMATION_CD_TO_ED_H
#define BASIS_TRANSFORMATION_CD_TO_ED_H

namespace MATH_ALGORITHMS
{
  /*!
   *  \ingroup
   *
   *  \brief
   *  \author Peter Staar
   *
   *  \version 1.0
   *  \date    2013
   */
  template<typename input_type, typename output_type>
  class basis_transformation<input_type, CONTINUOUS, output_type, EXPANSION>
  {
  public:

    typedef input_type  rh_dmn_type;
    typedef output_type lh_dmn_type;

    typedef typename lh_dmn_type::dmn_specifications_type lh_spec_dmn_type;
    typedef typename rh_dmn_type::dmn_specifications_type rh_spec_dmn_type;

    typedef typename lh_spec_dmn_type::scalar_type lh_scalar_type;
    typedef typename rh_spec_dmn_type::scalar_type rh_scalar_type;

    typedef typename lh_spec_dmn_type::element_type lh_element_type;
    typedef typename rh_spec_dmn_type::element_type rh_element_type;

    //typedef rh_scalar_type                               f_scalar_type;
    typedef std::complex<double>                         f_scalar_type;
    typedef LIN_ALG::matrix<f_scalar_type, LIN_ALG::CPU> matrix_type;

    typedef inner_product_domain<input_type> inner_product_dmn;

    typedef basis_transformation<input_type       , CONTINUOUS, inner_product_dmn, DISCRETE > input_transform_type;
    typedef basis_transformation<inner_product_dmn, DISCRETE  , output_type      , EXPANSION> output_transform_type;

    typedef typename input_transform_type ::matrix_type input_matrix_type;
    typedef typename output_transform_type::matrix_type output_matrix_type;

  public:

    static bool& is_initialized()
    {
      static bool initialized = false;
      return initialized;
    }

    static std::string& get_name()
    {
      static std::string name = "basis-transformation-matrix ( " + input_type::get_name() + " --> "+ output_type::get_name() + " )";
      return name;
    }

    static matrix_type& get_transformation_matrix()
    {
      static matrix_type T(get_name());

      if(not is_initialized())
        initialize_transformation_matrix();

      return T;
    }

    static double& get_matrix_accuracy()
    {
      static double accuracy = 1.e-6;
      return accuracy;
    }

    static int get_matrix_iterations()
    {
      static int itr = 4;
      return itr;
    }

    static void initialize_transformation_matrix()
    {
      GENERIC_ASSERT<CONTINUOUS == rh_spec_dmn_type::DOMAIN_REPRESENTATION>::execute();
      GENERIC_ASSERT<EXPANSION  == lh_spec_dmn_type::DOMAIN_REPRESENTATION>::execute();

      is_initialized() = true;

      int M = lh_dmn_type::get_size();
      int N = rh_dmn_type::get_size();

      assert(M>0 and N>0);

      LIN_ALG::matrix<f_scalar_type, LIN_ALG::CPU>& T = get_transformation_matrix();

      T.resize_no_copy(std::pair<int, int>(M, N));

      matrix_type T_cpy("T", std::pair<int, int>(M, N));

      for(int l=1; l<get_matrix_iterations(); l++){

        T_cpy.copy_from(T);

        inner_product_dmn::initialize(l);

        input_transform_type ::is_initialized() = false;
        output_transform_type::is_initialized() = false;

        input_matrix_type&  A = input_transform_type ::get_transformation_matrix();
        output_matrix_type& B = output_transform_type::get_transformation_matrix();

        for(int j=0; j<A.get_current_size().second; j++)
          for(int i=0; i<A.get_current_size().first; i++)
            A(i,j) *= inner_product_dmn::get_weights()[i];

        LIN_ALG::GEMM<LIN_ALG::CPU>::execute('N', 'N', B, A, T);

        double max=0;
        for(int j=0; j<N; j++)
          for(int i=0; i<M; i++)
            max = max<abs(T(i,j))? abs(T(i,j)) : max;

        double diff=0;
        for(int j=0; j<N; j++)
          for(int i=0; i<M; i++)
            diff = diff<abs(T(i,j)-T_cpy(i,j))? abs(T(i,j)-T_cpy(i,j)) : diff;

        cout << diff << "\t" << max << endl;

        if(diff<get_matrix_accuracy()*max)
          break;
      }
    }

  };

}

#endif
