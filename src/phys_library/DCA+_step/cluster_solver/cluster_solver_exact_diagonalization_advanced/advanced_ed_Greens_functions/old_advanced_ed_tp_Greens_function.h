//-*-C++-*-

#ifndef ADVANCED_FERMIONIC_SP_GREENS_FUNCTION_H
#define ADVANCED_FERMIONIC_SP_GREENS_FUNCTION_H

namespace DCA
{
  namespace ADVANCED_EXACT_DIAGONALIZATION
  {
    template<typename parameter_type, typename ed_options>
    class fermionic_sp_Greens_function
    {
#include "type_definitions.h"

      //typedef ED_type_definitions<parameter_type, b_dmn, s_dmn, r_dmn> ED_type_def;

      typedef typename ed_options::b_dmn b_dmn;
      typedef typename ed_options::s_dmn s_dmn;
      typedef typename ed_options::r_dmn r_dmn;
      typedef typename ed_options::k_dmn k_dmn;

      typedef typename ed_options::profiler_t       profiler_t;
      typedef typename ed_options::concurrency_type concurrency_type;

      typedef typename ed_options::scalar_type  scalar_type;
      typedef typename ed_options::complex_type complex_type;

      typedef typename ed_options::vector_type         vector_type;
      typedef typename ed_options::matrix_type         matrix_type;
      typedef typename ed_options::int_matrix_type int_matrix_type;

      typedef typename ed_options::nu_dmn nu_dmn;
      typedef typename ed_options::b_s_r  b_s_r_dmn_type;

      typedef typename ed_options::bs_dmn_type  bs_dmn_type;
      typedef typename ed_options::bsr_dmn_type bsr_dmn_type;

      typedef fermionic_Hamiltonian     <parameter_type, ed_options> fermionic_Hamiltonian_type;
      typedef fermionic_overlap_matrices<parameter_type, ed_options> fermionic_overlap_type;

      typedef Fock_space   <parameter_type, ed_options> fermionic_Fock_space_type;
      typedef Hilbert_space<parameter_type, ed_options> Hilbert_space_type;

      typedef dmn_0<fermionic_Fock_space_type>          fermionic_Fock_dmn_type;

    public:

      fermionic_sp_Greens_function(parameter_type&             parameters_ref,
                                   fermionic_Hamiltonian_type& Hamiltonian_ref,
                                   fermionic_overlap_type&     overlap_ref);

      ~fermionic_sp_Greens_function();

      template<typename MOMS_w_imag_type, typename MOMS_w_real_type>
      void compute_all_sp_functions(MOMS_w_imag_type& MOMS_imag, MOMS_w_real_type& MOMS_real, bool interacting);

      template<typename w_dmn>
      void compute_S_k_w(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& G_k_w,
                         function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& G0_k_w,
                         function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& S_k_w);

      //template<typename MOMS_type>
      //void print_G_k_w(MOMS_type& MOMS, bool interacting);

    private:

      void compute_Greens_functions_main(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                         function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                         function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t,
                                         function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w     > >& G_k_w,
                                         function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_REAL> >& G_k_w_real,
                                         function<             double , dmn_4<nu_dmn, nu_dmn, k_dmn, t     > >& G_k_t);


      void compute_Greens_functions_st   (function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                          function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                          function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t);

      void compute_Greens_functions_ac_st(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                          function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                          function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t);

      void compute_Greens_functions_ac_translation(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                   function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                   function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t);

      void compute_Greens_functions_ca_st(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                          function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                          function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t);

      void compute_Greens_functions_ca_translation(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                   function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                   function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t);

    private:

      parameter_type&   parameters;
      concurrency_type& concurrency;

      double CUT_OFF;

      fermionic_Hamiltonian_type& Hamiltonian;
      fermionic_overlap_type&     overlap;

      function<vector_type, fermionic_Fock_dmn_type >& eigen_energies;
      function<matrix_type, fermionic_Fock_dmn_type >& eigen_states;

      function<int, dmn_3<fermionic_Fock_dmn_type, fermionic_Fock_dmn_type, b_s_r_dmn_type> >& creation_set_all;
      function<int, dmn_3<fermionic_Fock_dmn_type, fermionic_Fock_dmn_type, b_s_r_dmn_type> >& annihilation_set_all;

      function<int, dmn_2<r_dmn, r_dmn> > rj_minus_ri;

    };

    template<typename parameter_type, typename ed_options>
    fermionic_sp_Greens_function<parameter_type, ed_options>::fermionic_sp_Greens_function(parameter_type&             parameters_ref,
                                                                                           fermionic_Hamiltonian_type& Hamiltonian_ref,
                                                                                           fermionic_overlap_type&     overlap_ref):
      parameters(parameters_ref),
      concurrency(parameters.get_concurrency()),

      CUT_OFF(parameters.get_eigenvalue_cut_off()),//1.e-6),

      Hamiltonian(Hamiltonian_ref),
      overlap(overlap_ref),

      eigen_energies(Hamiltonian.get_eigen_energies()),
      eigen_states  (Hamiltonian.get_eigen_states()),

      creation_set_all    (overlap.get_creation_set_all()),
      annihilation_set_all(overlap.get_annihilation_set_all()),

      rj_minus_ri("rj_minus_ri")
    {
      for(int ri=0; ri<r_dmn::dmn_size(); ri++)
        for(int rj=0; rj<r_dmn::dmn_size(); rj++)
          rj_minus_ri(ri, rj) = r_dmn::parameter_type::subtract(ri, rj);
    }

    template<typename parameter_type, typename ed_options>
    fermionic_sp_Greens_function<parameter_type, ed_options>::~fermionic_sp_Greens_function()
    {}


    template<typename parameter_type, typename ed_options>
    template<typename w_dmn>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_S_k_w(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& G_k_w,
                                                                                 function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& G0_k_w,
                                                                                 function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_dmn> >& S_k_w)
    {
      if(concurrency.id()==0)
        cout << "\n\t" << __FUNCTION__ << endl;

      int matrix_size = b::dmn_size()*s::dmn_size()*b::dmn_size()*s::dmn_size();
      int matrix_dim  = b::dmn_size()*s::dmn_size();

      std::complex<double>* G_inverted_matrix                   = new std::complex<double>[matrix_size];
      std::complex<double>* G0_cluster_excluded_inverted_matrix = new std::complex<double>[matrix_size];
      std::complex<double>* Sigma_matrix                        = new std::complex<double>[matrix_size];

      // Sigma = 1/G0 - 1/G

      for(int k_ind=0; k_ind<k_dmn::dmn_size(); k_ind++){
        for(int w_ind=0; w_ind<w_dmn::dmn_size(); w_ind++){

          {
            invert_plan<std::complex<double> > invert_pln(matrix_dim);
            memcpy(invert_pln.Matrix, &G_k_w(0,0,0,0,k_ind,w_ind), sizeof(std::complex<double>)*matrix_size);
            invert_pln.execute_plan();
            memcpy(G_inverted_matrix, invert_pln.inverted_matrix, sizeof(std::complex<double>)*matrix_size);
          }

          {
            invert_plan<std::complex<double> > invert_pln(matrix_dim);
            memcpy(invert_pln.Matrix, &G0_k_w(0,0,0,0,k_ind,w_ind), sizeof(std::complex<double>)*matrix_size);
            invert_pln.execute_plan();
            memcpy(G0_cluster_excluded_inverted_matrix, invert_pln.inverted_matrix, sizeof(std::complex<double>)*matrix_size);
          }

          for(int l=0; l<matrix_size; ++l)
            Sigma_matrix[l] = (G0_cluster_excluded_inverted_matrix[l] - G_inverted_matrix[l]);

          memcpy(&S_k_w(0,0,0,0,k_ind,w_ind), Sigma_matrix, sizeof(std::complex<double>)*matrix_size);
        }
      }

      //SHOW::execute(S_k_w);

      delete [] G_inverted_matrix;
      delete [] G0_cluster_excluded_inverted_matrix;
      delete [] Sigma_matrix;

      if(concurrency.id()==0)
        {
          cout << "\n";
          for(int w_i=w_dmn::dmn_size()/2-16; w_i<w_dmn::dmn_size()/2+16; w_i++){
            cout << w_dmn::get_elements()[w_i] << "\t";
            for(int k_i=0; k_i<k_dmn::dmn_size(); k_i++)
              cout << real(S_k_w(0,0,0,0,k_i,w_i)) << "\t" << imag(S_k_w(0,0,0,0,k_i,w_i)) << "\t";
            cout << "\n";
          }
          cout << "\n";
        }

    }

    template<typename parameter_type, typename ed_options>
    template<typename MOMS_w_imag_type, typename MOMS_w_real_type>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_all_sp_functions(MOMS_w_imag_type& MOMS_imag,
                                                                                            MOMS_w_real_type& MOMS_real,
                                                                                            bool interacting)
    {
      if(interacting){
        compute_Greens_functions_main(MOMS_imag.G_r_w , MOMS_real.G_r_w , MOMS_imag.G_r_t,
                                      MOMS_imag.G_k_w , MOMS_real.G_k_w , MOMS_imag.G_k_t);
      }
      else{
        compute_Greens_functions_main(MOMS_imag.G0_r_w , MOMS_real.G0_r_w , MOMS_imag.G0_r_t,
                                      MOMS_imag.G0_k_w , MOMS_real.G0_k_w , MOMS_imag.G0_k_t);
      }
    }

    template<typename parameter_type, typename ed_options>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_Greens_functions_main(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                                                                 function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                                                                 function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t,
                                                                                                 function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w     > >& G_k_w,
                                                                                                 function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, k_dmn, w_REAL> >& G_k_w_real,
                                                                                                 function<             double , dmn_4<nu_dmn, nu_dmn, k_dmn, t     > >& G_k_t)
    {
      if(concurrency.id()==0)
        cout << "\n\t" << __FUNCTION__ << endl;

      G_r_w = 0;
      G_k_w = 0;

      G_r_t = 0;
      G_k_t = 0;

      int start = clock();

      //compute_Greens_functions_st(G_r_w, G_r_w_real, G_r_t);

      if(false)
        {
          compute_Greens_functions_ac_st(G_r_w, G_r_w_real, G_r_t);
          compute_Greens_functions_ca_st(G_r_w, G_r_w_real, G_r_t);

          G_r_w      *= double(1)/double(r_dmn::dmn_size());
          G_r_w_real *= double(1)/double(r_dmn::dmn_size());
          G_r_t      *= double(1)/double(r_dmn::dmn_size());
        }
      else
        {
          compute_Greens_functions_ac_translation(G_r_w, G_r_w_real, G_r_t);
          compute_Greens_functions_ca_translation(G_r_w, G_r_w_real, G_r_t);
        }

      concurrency.sum(G_r_t);
      concurrency.sum(G_r_w);
      concurrency.sum(G_r_w_real);

      int end = clock();

      if(concurrency.id()==0)
        cout << "\t total time : " << double(end-start)/double(CLOCKS_PER_SEC) << "\n\n";

      {
        for(int t_i=t::dmn_size()/2; t_i<t::dmn_size(); t_i++)
          for(int r_i=0; r_i<r_dmn::dmn_size(); r_i++)
            for(int nu_j=0; nu_j<2*b_dmn::dmn_size(); nu_j++)
              for(int nu_i=0; nu_i<2*b_dmn::dmn_size(); nu_i++)
                G_r_t(nu_i, nu_j, r_i, t_i-t::dmn_size()/2) = -G_r_t(nu_i, nu_j, r_i, t_i);
      }

      std::vector< Hilbert_space_type >& Hilbert_spaces = fermionic_Fock_dmn_type::get_elements();

      {
        double beta = parameters.get_beta();

        double Z = 0;
        for(int HS_i = 0; HS_i < Hilbert_spaces.size(); ++HS_i)
          for(int n = 0; n < Hilbert_spaces[HS_i].size(); ++n)
            Z += std::exp(-beta*eigen_energies(HS_i)[n]);

        //double factor = 1./(Z*r_dmn::dmn_size());
        double factor = 1./Z;

        G_r_w      *= factor;
        G_r_w_real *= factor;
        G_r_t      *= -factor;

        //       FT<r_dmn, k_dmn>::execute(G_r_w     , G_k_w);
        //       FT<r_dmn, k_dmn>::execute(G_r_w_real, G_k_w_real);
        //       FT<r_dmn, k_dmn>::execute(G_r_t     , G_k_t);
        MATH_ALGORITHMS::TRANSFORM<r_dmn, k_dmn>::execute(G_r_w     , G_k_w);
        MATH_ALGORITHMS::TRANSFORM<r_dmn, k_dmn>::execute(G_r_w_real, G_k_w_real);
        MATH_ALGORITHMS::TRANSFORM<r_dmn, k_dmn>::execute(G_r_t     , G_k_t);

        SHOW::execute(G_r_t);
        SHOW::execute(G_k_t);

        SHOW::execute(G_r_w);
        SHOW::execute(G_k_w);
      }
    }

    template<typename parameter_type, typename ed_options>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_Greens_functions_ac_st(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                                                                  function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                                                                  function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t)
    {
      cout << "\n\n\t" << __FUNCTION__ << "\n\n";

      std::vector< Hilbert_space_type >& Hilbert_spaces = fermionic_Fock_dmn_type::get_elements();

      matrix_type annihilation_bsr_i;
      matrix_type creation_bsr_j;

      scalar_type beta    = parameters.get_beta();
      scalar_type off_set = parameters.get_real_frequencies_off_set();

      scalar_type  ONE(1);
      complex_type I(0,1);

      b_s_r_dmn_type bsr_dmn;
      std::vector<int> bsr_i_index(3,0);
      std::vector<int> bsr_j_index(3,0);

      double zero=0, nonzero=0;

      for(int bsr_i = 0; bsr_i < b_s_r_dmn_type::dmn_size(); ++bsr_i)
        {
          for(int bsr_j = 0; bsr_j < b_s_r_dmn_type::dmn_size(); ++bsr_j)
            {
              cout << "bsr_i : " << bsr_i
                   << "\t bsr_j : " << bsr_j
                   << "\t" << print_time()
                   << endl;

              bsr_dmn.linind_2_subind(bsr_i, &bsr_i_index[0]);
              int b_i = bsr_i_index[0];
              int s_i = bsr_i_index[1];
              int r_i = bsr_i_index[2];
              int nu_i = b_i + s_i*b::dmn_size();

              bsr_dmn.linind_2_subind(bsr_j, &bsr_j_index[0]);
              int b_j = bsr_j_index[0];
              int s_j = bsr_j_index[1];
              int r_j = bsr_j_index[2];
              int nu_j = b_j + s_j*b::dmn_size();

              int delta_r = rj_minus_ri(r_i, r_j);

              for(int HS_0 = 0; HS_0 < Hilbert_spaces.size(); ++HS_0)
                {
                  for(int HS_1 = 0; HS_1 < Hilbert_spaces.size(); ++HS_1)
                    {
                      bool done = false;

                      if(annihilation_set_all(HS_0, HS_1, bsr_i) != -1 &&
                         creation_set_all    (HS_1, HS_0, bsr_j) != -1)
                        {
                          for(int n0 = 0; n0 < Hilbert_spaces[HS_0].size(); ++n0)
                            {
                              scalar_type E_n0 = eigen_energies(HS_0)[n0];
                              scalar_type w_e  = std::exp(-beta*E_n0);

                              if(w_e > CUT_OFF)
                                {
                                  for(int n1 = 0; n1 < Hilbert_spaces[HS_1].size(); ++n1)
                                    {
                                      if(not done)
                                        {
                                          overlap.compute_annihilation_matrix(HS_0, HS_1, bsr_i, annihilation_bsr_i);
                                          overlap.compute_creation_matrix    (HS_1, HS_0, bsr_j, creation_bsr_j);

                                          done = true;
                                        }

                                      scalar_type E_n1 = eigen_energies(HS_1)[n1];

                                      complex_type factor = w_e * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);

                                      if(abs(factor) > CUT_OFF)
                                        {
                                          nonzero += 1;

                                          scalar_type  factor_re = real(factor);

                                          for(int t_i = t::dmn_size()/2; t_i < t::dmn_size(); ++t_i)
                                            {
                                              scalar_type tau   = t::get_elements()[t_i];
                                              scalar_type G_tau = 1./(std::exp((beta-tau)*(E_n0 - E_n1)) + std::exp(-tau*(E_n0 - E_n1)));

                                              //G_r_t(nu_i, nu_j, delta_r, t_i) += w_e * G_tau * real(annihilation_bsr_i(n0,n1)) * real(creation_bsr_j(n1,n0));
                                              G_r_t(nu_i, nu_j, delta_r, t_i) += factor_re * G_tau;// * real(annihilation_bsr_i(n0,n1)) * real(creation_bsr_j(n1,n0));
                                            }

                                          for(int w_i = 0; w_i < w::dmn_size(); ++w_i)
                                            {
                                              scalar_type w_im = w::get_elements()[w_i];

                                              complex_type iw   = I*w_im;
                                              complex_type G_w  = ONE/(iw + E_n0 - E_n1);

                                              //G_r_w(nu_i, nu_j, delta_r, w_i) += w_e * G_w * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                              G_r_w(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                            }

                                          for(int w_i = 0; w_i < w_REAL::dmn_size(); ++w_i)
                                            {
                                              scalar_type w_re = w_REAL::get_elements()[w_i];

                                              complex_type iw  = w_re + I*off_set;
                                              complex_type G_w = ONE/(iw + E_n0 - E_n1);

                                              //G_r_w_real(nu_i, nu_j, delta_r, w_i) += w_e * G_w * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                              G_r_w_real(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                            }
                                        }
                                      else
                                        {
                                          zero += 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

      cout << "\n\t nonzero/total : " << nonzero/(zero+nonzero) << "\n";
    }

    template<typename parameter_type, typename ed_options>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_Greens_functions_ac_translation(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                                                                           function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                                                                           function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t)
    {
      cout << "\n\n\t" << __FUNCTION__ << "\n\n";

      std::vector< Hilbert_space_type >& Hilbert_spaces = fermionic_Fock_dmn_type::get_elements();

//       matrix_type annihilation_bsr_i;
//       matrix_type creation_bsr_j;

      scalar_type beta    = parameters.get_beta();
      scalar_type off_set = parameters.get_real_frequencies_off_set();

      scalar_type  ONE(1);
      complex_type I(0,1);

//       bs_dmn_type  bs_dmn;
//       bsr_dmn_type bsr_dmn;

      double zero=0, nonzero=0;

      for(int b_i=0; b_i<b_dmn::dmn_size(); b_i++){
        for(int s_i=0; s_i<s_dmn::dmn_size(); s_i++){

          int r_i = r_dmn::parameter_type::origin_index();

          for(int b_j=0; b_j<b_dmn::dmn_size(); b_j++){
            for(int s_j=0; s_j<s_dmn::dmn_size(); s_j++){

#ifdef USE_OPENMP_DIRECTIVES
 	      //omp_set_num_threads(4);
#pragma omp parallel for
#endif
              for(int r_j=0; r_j<r_dmn::dmn_size(); r_j++){

		bs_dmn_type  bs_dmn;
		bsr_dmn_type bsr_dmn;

		matrix_type tmp("tmp", 128);

		matrix_type annihilation_bsr_i;
		matrix_type creation_bsr_j;

                int delta_r = r_j;

                int nu_i = bs_dmn(b_i, s_i);
                int nu_j = bs_dmn(b_j, s_j);

                int bsr_i = bsr_dmn(b_i, s_i, r_i);
                int bsr_j = bsr_dmn(b_j, s_j, r_j);

		{
		  stringstream ss;
		  ss << "\nbsr_i : " << bsr_i
                     << "\t bsr_j : " << bsr_j
                     << "\t" << print_time()
                     << "\n";
		  cout << ss.str();
		}

                for(int HS_0 = 0; HS_0 < Hilbert_spaces.size(); ++HS_0)
                  {
                    for(int HS_1 = 0; HS_1 < Hilbert_spaces.size(); ++HS_1)
                      {
                        bool done = false;

                        if(annihilation_set_all(HS_0, HS_1, bsr_i) != -1 &&
                           creation_set_all    (HS_1, HS_0, bsr_j) != -1)
                          {
                            for(int n0 = 0; n0 < Hilbert_spaces[HS_0].size(); ++n0)
                              {
                                scalar_type E_n0 = eigen_energies(HS_0)[n0];
                                scalar_type w_e  = std::exp(-beta*E_n0);

                                if(w_e > CUT_OFF)
                                  {
                                    for(int n1 = 0; n1 < Hilbert_spaces[HS_1].size(); ++n1)
                                      {
                                        if(not done)
                                          {
                                            overlap.compute_annihilation_matrix_fast(HS_0, HS_1, bsr_i, annihilation_bsr_i, tmp);
                                            overlap.compute_creation_matrix_fast    (HS_1, HS_0, bsr_j, creation_bsr_j    , tmp);

                                            done = true;
                                          }

                                        scalar_type E_n1 = eigen_energies(HS_1)[n1];

                                        complex_type factor = w_e * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);

                                        if(abs(factor) > CUT_OFF)
                                          {
                                            nonzero += 1;

                                            scalar_type  factor_re = real(factor);

                                            for(int t_i = t::dmn_size()/2; t_i < t::dmn_size(); ++t_i)
                                              {
                                                scalar_type tau   = t::get_elements()[t_i];
                                                scalar_type G_tau = 1./(std::exp((beta-tau)*(E_n0 - E_n1)) + std::exp(-tau*(E_n0 - E_n1)));

                                                //G_r_t(nu_i, nu_j, delta_r, t_i) += w_e * G_tau * real(annihilation_bsr_i(n0,n1)) * real(creation_bsr_j(n1,n0));
                                                G_r_t(nu_i, nu_j, delta_r, t_i) += factor_re * G_tau;// * real(annihilation_bsr_i(n0,n1)) * real(creation_bsr_j(n1,n0));
                                              }

                                            for(int w_i = 0; w_i < w::dmn_size(); ++w_i)
                                              {
                                                scalar_type w_im = w::get_elements()[w_i];

                                                complex_type iw   = I*w_im;
                                                complex_type G_w  = ONE/(iw + E_n0 - E_n1);

                                                //G_r_w(nu_i, nu_j, delta_r, w_i) += w_e * G_w * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                                G_r_w(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                              }

                                            for(int w_i = 0; w_i < w_REAL::dmn_size(); ++w_i)
                                              {
                                                scalar_type w_re = w_REAL::get_elements()[w_i];

                                                complex_type iw  = w_re + I*off_set;
                                                complex_type G_w = ONE/(iw + E_n0 - E_n1);

                                                //G_r_w_real(nu_i, nu_j, delta_r, w_i) += w_e * G_w * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                                G_r_w_real(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * annihilation_bsr_i(n0,n1) * creation_bsr_j(n1,n0);
                                              }
                                          }
                                        else
                                          {
                                            zero += 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
            }
          }
        }
      }

      cout << "\n\t nonzero/total : " << nonzero/(zero+nonzero) << "\n";
    }

    template<typename parameter_type, typename ed_options>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_Greens_functions_ca_st(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                                                                  function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                                                                  function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t)
    {
      cout << "\n\n\t" << __FUNCTION__ << "\n\n";

      std::vector< Hilbert_space_type >& Hilbert_spaces = fermionic_Fock_dmn_type::get_elements();

      matrix_type annihilation_bsr_i;
      matrix_type creation_bsr_j;

      scalar_type beta    = parameters.get_beta();
      scalar_type off_set = parameters.get_real_frequencies_off_set();

      scalar_type  ONE(1);
      complex_type I(0,1);

      b_s_r_dmn_type bsr_dmn;
      std::vector<int> bsr_i_index(3,0);
      std::vector<int> bsr_j_index(3,0);

      double zero=0, nonzero=0;

      for(int bsr_i = 0; bsr_i < b_s_r_dmn_type::dmn_size(); ++bsr_i)
        {
          for(int bsr_j = 0; bsr_j < b_s_r_dmn_type::dmn_size(); ++bsr_j)
            {
              cout << "bsr_i : " << bsr_i
                   << "\t bsr_j : " << bsr_j
                   << "\t" << print_time()
                   << endl;

              bsr_dmn.linind_2_subind(bsr_i, &bsr_i_index[0]);
              int b_i = bsr_i_index[0];
              int s_i = bsr_i_index[1];
              int r_i = bsr_i_index[2];
              int nu_i = b_i + s_i*b::dmn_size();

              bsr_dmn.linind_2_subind(bsr_j, &bsr_j_index[0]);
              int b_j = bsr_j_index[0];
              int s_j = bsr_j_index[1];
              int r_j = bsr_j_index[2];
              int nu_j = b_j + s_j*b::dmn_size();

              int delta_r = rj_minus_ri(r_i, r_j);

              for(int HS_0 = 0; HS_0 < Hilbert_spaces.size(); ++HS_0)
                {
                  for(int HS_1 = 0; HS_1 < Hilbert_spaces.size(); ++HS_1)
                    {
                      bool done = false;

                      if(annihilation_set_all(HS_1, HS_0, bsr_i) != -1 &&
                         creation_set_all    (HS_0, HS_1, bsr_j) != -1)
                        {
                          for(int n0 = 0; n0 < Hilbert_spaces[HS_0].size(); ++n0)
                            {
                              scalar_type E_n0 = eigen_energies(HS_0)[n0];
                              scalar_type w_e  = std::exp(-beta*E_n0);

                              if(w_e > CUT_OFF)
                                {
                                  for(int n1 = 0; n1 < Hilbert_spaces[HS_1].size(); ++n1)
                                    {
                                      if(not done)
                                        {
                                          overlap.compute_annihilation_matrix(HS_1, HS_0, bsr_i, annihilation_bsr_i);
                                          overlap.compute_creation_matrix    (HS_0, HS_1, bsr_j, creation_bsr_j);

                                          done = true;
                                        }

                                      scalar_type E_n1 = eigen_energies(HS_1)[n1];

                                      complex_type factor = w_e * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);

                                      if(abs(factor) > CUT_OFF)
                                        {
                                          nonzero += 1;

                                          scalar_type  factor_re  = real(factor);

                                          for(int t_i = t::dmn_size()/2; t_i < t::dmn_size(); ++t_i)
                                            {
                                              scalar_type tau   = t::get_elements()[t_i];
                                              scalar_type G_tau = 1./(std::exp((beta-tau)*(E_n1 - E_n0)) + std::exp(-tau*(E_n1 - E_n0)));

                                              //                                               G_r_t(nu_i, nu_j, delta_r, t_i) += w_e * G_tau * real(creation_bsr_j(n0,n1))
                                              //                                                 * real(annihilation_bsr_i(n1,n0));
                                              G_r_t(nu_i, nu_j, delta_r, t_i) += factor_re * G_tau;
                                            }

                                          for(int w_i = 0; w_i < w::dmn_size(); ++w_i)
                                            {
                                              scalar_type w_im = w::get_elements()[w_i];

                                              complex_type iw   = I*w_im;
                                              complex_type G_w  = ONE/(iw - E_n0 + E_n1);

                                              //                                               G_r_w(nu_i, nu_j, delta_r, w_i) += w_e * G_w * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                              G_r_w(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                            }

                                          for(int w_i = 0; w_i < w_REAL::dmn_size(); ++w_i)
                                            {
                                              scalar_type w_re = w_REAL::get_elements()[w_i];

                                              complex_type iw  = w_re + I*off_set;
                                              complex_type G_w = ONE/(iw - E_n0 + E_n1);

                                              //                                               G_r_w_real(nu_i, nu_j, delta_r, w_i) += w_e * G_w * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                              G_r_w_real(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                            }
                                        }
                                      else
                                        {
                                          zero += 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

      cout << "\n\t nonzero/total : " << nonzero/(zero+nonzero) << "\n";
    }

    template<typename parameter_type, typename ed_options>
    void fermionic_sp_Greens_function<parameter_type, ed_options>::compute_Greens_functions_ca_translation(function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w     > >& G_r_w,
                                                                                                           function<std::complex<double>, dmn_4<nu_dmn, nu_dmn, r_dmn, w_REAL> >& G_r_w_real,
                                                                                                           function<             double , dmn_4<nu_dmn, nu_dmn, r_dmn, t     > >& G_r_t)
    {
      cout << "\n\n\t" << __FUNCTION__ << "\n\n";

      std::vector< Hilbert_space_type >& Hilbert_spaces = fermionic_Fock_dmn_type::get_elements();

//       matrix_type annihilation_bsr_i;
//       matrix_type creation_bsr_j;

      scalar_type beta    = parameters.get_beta();
      scalar_type off_set = parameters.get_real_frequencies_off_set();

      scalar_type  ONE(1);
      complex_type I(0,1);

//       bs_dmn_type  bs_dmn;
//       bsr_dmn_type bsr_dmn;

      double zero=0, nonzero=0;

      for(int b_i=0; b_i<b_dmn::dmn_size(); b_i++){
        for(int s_i=0; s_i<s_dmn::dmn_size(); s_i++){

          int r_i = r_dmn::parameter_type::origin_index();

          for(int b_j=0; b_j<b_dmn::dmn_size(); b_j++){
            for(int s_j=0; s_j<s_dmn::dmn_size(); s_j++){

#ifdef USE_OPENMP_DIRECTIVES
 	      //omp_set_num_threads(4);
#pragma omp parallel for
#endif
              for(int r_j=0; r_j<r_dmn::dmn_size(); r_j++){

		bs_dmn_type  bs_dmn;
		bsr_dmn_type bsr_dmn;

		matrix_type tmp("tmp", 128);

		matrix_type annihilation_bsr_i;
		matrix_type creation_bsr_j;

                int delta_r = r_j;

                int nu_i = bs_dmn(b_i, s_i);
                int nu_j = bs_dmn(b_j, s_j);

                int bsr_i = bsr_dmn(b_i, s_i, r_i);
                int bsr_j = bsr_dmn(b_j, s_j, r_j);

		{
		  stringstream ss;
		  ss << "bsr_i : " << bsr_i
                     << "\t bsr_j : " << bsr_j
                     << "\t" << print_time()
                     << "\n\n";
		  cout << ss.str();
		}

                for(int HS_0 = 0; HS_0 < Hilbert_spaces.size(); ++HS_0)
                  {
                    for(int HS_1 = 0; HS_1 < Hilbert_spaces.size(); ++HS_1)
                      {
                        bool done = false;

                        if(annihilation_set_all(HS_1, HS_0, bsr_i) != -1 &&
                           creation_set_all    (HS_0, HS_1, bsr_j) != -1)
                          {
                            for(int n0 = 0; n0 < Hilbert_spaces[HS_0].size(); ++n0)
                              {
                                scalar_type E_n0 = eigen_energies(HS_0)[n0];
                                scalar_type w_e  = std::exp(-beta*E_n0);

                                if(w_e > CUT_OFF)
                                  {
                                    for(int n1 = 0; n1 < Hilbert_spaces[HS_1].size(); ++n1)
                                      {
                                        if(not done)
                                          {
                                            overlap.compute_annihilation_matrix_fast(HS_1, HS_0, bsr_i, annihilation_bsr_i, tmp);
                                            overlap.compute_creation_matrix_fast    (HS_0, HS_1, bsr_j, creation_bsr_j    , tmp);

                                            done = true;
                                          }

                                        scalar_type E_n1 = eigen_energies(HS_1)[n1];

                                        complex_type factor = w_e * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);

                                        if(abs(factor) > CUT_OFF)
                                          {
                                            nonzero += 1;

                                            scalar_type  factor_re  = real(factor);

                                            for(int t_i = t::dmn_size()/2; t_i < t::dmn_size(); ++t_i)
                                              {
                                                scalar_type tau   = t::get_elements()[t_i];
                                                scalar_type G_tau = 1./(std::exp((beta-tau)*(E_n1 - E_n0)) + std::exp(-tau*(E_n1 - E_n0)));

                                                //                                               G_r_t(nu_i, nu_j, delta_r, t_i) += w_e * G_tau * real(creation_bsr_j(n0,n1))
                                                //                                                 * real(annihilation_bsr_i(n1,n0));
                                                G_r_t(nu_i, nu_j, delta_r, t_i) += factor_re * G_tau;
                                              }

                                            for(int w_i = 0; w_i < w::dmn_size(); ++w_i)
                                              {
                                                scalar_type w_im = w::get_elements()[w_i];

                                                complex_type iw   = I*w_im;
                                                complex_type G_w  = ONE/(iw - E_n0 + E_n1);

                                                //                                               G_r_w(nu_i, nu_j, delta_r, w_i) += w_e * G_w * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                                G_r_w(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                              }

                                            for(int w_i = 0; w_i < w_REAL::dmn_size(); ++w_i)
                                              {
                                                scalar_type w_re = w_REAL::get_elements()[w_i];

                                                complex_type iw  = w_re + I*off_set;
                                                complex_type G_w = ONE/(iw - E_n0 + E_n1);

                                                //                                               G_r_w_real(nu_i, nu_j, delta_r, w_i) += w_e * G_w * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                                G_r_w_real(nu_i, nu_j, delta_r, w_i) += factor * G_w;// * creation_bsr_j(n0,n1) * annihilation_bsr_i(n1,n0);
                                              }
                                          }
                                        else
                                          {
                                            zero += 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
            }
          }
        }
      }

      cout << "\n\t nonzero/total : " << nonzero/(zero+nonzero) << "\n";
    }

  }

}

#endif
