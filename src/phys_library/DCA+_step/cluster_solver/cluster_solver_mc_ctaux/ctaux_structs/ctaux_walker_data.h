//-*-C++-*-

#ifndef DCA_QMCI_CT_AUX_WALKER_MATRICES_H
#define DCA_QMCI_CT_AUX_WALKER_MATRICES_H

namespace DCA
{
  namespace QMCI
  {
    /*!
     *  \class   ct_aux_matrices
     *  \ingroup STRUCTURES
     *
     *  \author Peter Staar
     *  \version 1.0
     *  \brief
     *
     *   \f{eqnarray}{
     *   \f}
     */
    template<LIN_ALG::device_type device_t, typename parameters_type>
    class MC_walker_data<CT_AUX_SOLVER, device_t, parameters_type>
    {
      const static int MAX_VERTEX_SINGLETS=4;

    public:

      MC_walker_data(parameters_type& parameters,
                     int              id);

      ~MC_walker_data();

    public:

      int thread_id;

      LIN_ALG::matrix<double, device_t> N_up;
      LIN_ALG::matrix<double, device_t> N_dn;

      LIN_ALG::matrix<double, device_t> G0_up;
      LIN_ALG::matrix<double, device_t> G0_dn;

      LIN_ALG::matrix<double, device_t> Gamma_up;
      LIN_ALG::matrix<double, device_t> Gamma_dn;

      LIN_ALG::matrix<double, device_t> stored_Gamma_up;
      LIN_ALG::matrix<double, device_t> stored_Gamma_dn;

      LIN_ALG::matrix<double, device_t> G_up;
      LIN_ALG::matrix<double, device_t> G_dn;
    };

    template<LIN_ALG::device_type device_t, typename parameters_type>
    MC_walker_data<CT_AUX_SOLVER, device_t, parameters_type>::MC_walker_data(parameters_type& parameters,
                                                                             int              id):
      thread_id(id),

      N_up("N_up", 0, parameters.get_initial_matrix_size()),
      N_dn("N_dn", 0, parameters.get_initial_matrix_size()),

      G0_up("G0_up", 0, parameters.get_initial_matrix_size()),
      G0_dn("G0_dn", 0, parameters.get_initial_matrix_size()),

      Gamma_up("Gamma_up", 0, MAX_VERTEX_SINGLETS*parameters.get_K_PHANI()),
      Gamma_dn("Gamma_dn", 0, MAX_VERTEX_SINGLETS*parameters.get_K_PHANI()),

      stored_Gamma_up("stored_Gamma_up", 0, MAX_VERTEX_SINGLETS*parameters.get_K_PHANI()),
      stored_Gamma_dn("stored_Gamma_dn", 0, MAX_VERTEX_SINGLETS*parameters.get_K_PHANI()),

      G_up("G_up", std::pair<int,int>(0,0), std::pair<int,int>(parameters.get_initial_matrix_size(), MAX_VERTEX_SINGLETS*parameters.get_K_PHANI())),
      G_dn("G_dn", std::pair<int,int>(0,0), std::pair<int,int>(parameters.get_initial_matrix_size(), MAX_VERTEX_SINGLETS*parameters.get_K_PHANI()))
    {
      N_up.set_thread_and_stream_id(thread_id, 0);
      N_dn.set_thread_and_stream_id(thread_id, 0);

      G0_up.set_thread_and_stream_id(thread_id, 0);
      G0_dn.set_thread_and_stream_id(thread_id, 0);

      Gamma_up.set_thread_and_stream_id(thread_id, 0);
      Gamma_dn.set_thread_and_stream_id(thread_id, 0);

      stored_Gamma_up.set_thread_and_stream_id(thread_id, 0);
      stored_Gamma_dn.set_thread_and_stream_id(thread_id, 0);

      G_up.set_thread_and_stream_id(thread_id, 0);
      G_dn.set_thread_and_stream_id(thread_id, 0);
    }

    template<LIN_ALG::device_type device_t, typename parameters_type>
    MC_walker_data<CT_AUX_SOLVER, device_t, parameters_type>::~MC_walker_data()
    {}

  }

}

#endif
