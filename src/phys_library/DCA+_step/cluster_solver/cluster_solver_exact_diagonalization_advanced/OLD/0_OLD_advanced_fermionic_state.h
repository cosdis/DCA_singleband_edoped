//-*-C++-*-

#ifndef ADVANCED_FERMIONIC_STATE_H
#define ADVANCED_FERMIONIC_STATE_H

namespace DCA
{
  namespace ADVANCED_EXACT_DIAGONALIZATION
  {
    /*
      template<typename parameter_type, typename ed_options>       // N: size of bitset sequence
      struct phi_struct
      {
      typedef typename ed_options::scalar_type  scalar_type;
      typedef typename ed_options::complex_type complex_type;

      typedef typename ed_options::phi_type phi_type;

      phi_type     phi;
      complex_type alpha;
      };

      template<typename parameter_type, typename ed_options>
      bool operator< (const phi_struct<parameter_type, ed_options>& phi_obj1,
      const phi_struct<parameter_type, ed_options>& phi_obj2)
      {
      return phi_obj1.phi.to_ulong() < phi_obj2.phi.to_ulong();
      }

      template<typename parameter_type, typename ed_options>
      bool operator== (const phi_struct<parameter_type, ed_options>& phi_obj1,
      const phi_struct<parameter_type, ed_options>& phi_obj2)
      {
      return (phi_obj1.phi == phi_obj2.phi and phi_obj1.alpha == phi_obj2.alpha);
      }
    */

    /*
    template<typename parameter_type, typename ed_options>       // N: size of bitset sequence
    class psi_state
    {
    public:

      typedef typename ed_options::scalar_type  scalar_type;
      typedef typename ed_options::complex_type complex_type;

      typedef typename ed_options::b_dmn b_dmn;
      typedef typename ed_options::s_dmn s_dmn;
      typedef typename ed_options::r_dmn r_dmn;
      typedef typename ed_options::k_dmn k_dmn;

      typedef typename ed_options::phi_type phi_type;

    public:

      // Construct state from integer
      psi_state(const int& s);

      psi_state(const phi_state<parameter_type, ed_options>& phi_obj_);

      // Contruct eigenstate of symmetry operation O with eigenvalue 'eigenvalue'
      template<class symmetry_operation>
      psi_state(const complex_type eigenvalue, const int order, symmetry_operation& Op,
                const psi_state<parameter_type, ed_options>& phi0, int k);

      void print() const;

      int  occupation_number() const;

      int  magnetization() const;
      // Return number of different states in linear combination (phis)
      int  size() const { return phi_obj.size(); }
      // Remove lth state of linear combination (phi_l)
      void erase(const unsigned int l) { phi_obj.erase(phi_obj.begin()+l); }

      void simplify();
      void normalize();

      // void set_eigenvalues(const std::vector< complex_type >& evals) { eigenvalues = evals; }
      // void add_eigenvalue(const complex_type& eval)                  { eigenvalues.push_back(eval); }

      void sort();

      std::vector< phi_state<parameter_type, ed_options> >& get_phi_obj()       { return phi_obj; }
      std::vector< phi_state<parameter_type, ed_options> >  get_phi_obj() const { return phi_obj; }

      phi_state<parameter_type, ed_options>& get_phi_obj(int i)       { assert(i >= 0 && i < size()); return phi_obj[i]; }
      phi_state<parameter_type, ed_options>  get_phi_obj(int i) const { assert(i >= 0 && i < size()); return phi_obj[i]; }

      phi_type& get_phi(int i)       { assert(i >= 0 && i < size()); return phi_obj[i].phi; }
      phi_type  get_phi(int i) const { assert(i >= 0 && i < size()); return phi_obj[i].phi; }

      complex_type& get_alpha(int i)       { assert(i >= 0 && i < size()); return phi_obj[i].alpha; }
      complex_type  get_alpha(int i) const { assert(i >= 0 && i < size()); return phi_obj[i].alpha; }

      std::vector< complex_type >& get_eigenvalues()       { return eigenvalues; }
      std::vector< complex_type >  get_eigenvalues() const { return eigenvalues; }

      bool is_marked() { return marker; }
      void mark()      { marker = true; }


    private:

      // std::vector< phi_type > phis;
      // std::vector< complex_type >   coefficients;

      std::vector< phi_state<parameter_type, ed_options> > phi_obj;

      std::vector< complex_type > eigenvalues;

      bool marker;

    };

    template<typename parameter_type, typename ed_options>
    psi_state<parameter_type, ed_options>::psi_state(const int& s):
      marker(false)
    {
      phi_state<parameter_type, ed_options> tmp;
      tmp.phi   = phi_type(s);
      tmp.alpha = complex_type(1.);
      phi_obj.push_back(tmp);
    }

    template<typename parameter_type, typename ed_options>
    psi_state<parameter_type, ed_options>::psi_state(const phi_state<parameter_type, ed_options>& phi_obj_):
      phi_obj(1, phi_obj_)
    {}

    template<typename parameter_type, typename ed_options>
    template<class symmetry_operation>
    psi_state<parameter_type, ed_options>::psi_state(const complex_type eigenvalue,
                                                     const int order,
                                                     symmetry_operation& Op,
                                                     const psi_state<parameter_type, ed_options>& phi0, int k):
      eigenvalues(phi0.get_eigenvalues()),
      marker(false)
    {
      eigenvalues.push_back(eigenvalue);

      for (int l = 0; l < phi0.size(); ++l){

        psi_state<parameter_type, ed_options> phi_tmp(phi0.get_phi_obj(l));

        //        complex_type coeff = 1./sqrt(order);
        phi_tmp.get_alpha(0) /= sqrt(order);

        for (int i = 0; i < order; ++i){

          phi_obj.push_back(phi_tmp.get_phi_obj(0));

          Op.execute(phi_tmp);
          phi_tmp.get_alpha(0) /= eigenvalue;
        }
      }

      simplify();

      normalize();

      sort();

    }

    template<typename parameter_type, typename ed_options>
    void psi_state<parameter_type, ed_options>::print() const
    {
      int num_states = b_dmn::dmn_size() * s_dmn::dmn_size() * r_dmn::dmn_size();

      for (int i = 0; i < size(); ++i) {
        for (int j = 0; j < num_states; ++j) {
          std::cout << phi_obj[i].phi[j];
        }
        std::cout << " * " << phi_obj[i].alpha << "\n";
      }
    }

    template<typename parameter_type, typename ed_options>
    int psi_state<parameter_type, ed_options>::occupation_number() const
    {
      return phi_obj[0].phi.count();
    }

    template<typename parameter_type, typename ed_options>
    int psi_state<parameter_type, ed_options>::magnetization() const
    {
      phi_type mask_up(0);

      for (int r = r_dmn::dmn_size()-1; r >= 0; --r){
        for (int s = s_dmn::dmn_size()-1; s >= 0; --s){
          for (int b = b_dmn::dmn_size()-1;b >= 0; --b){
            mask_up <<= 1;
            if (s == 0) mask_up |= 1;
          }
        }
      }

      phi_type mask_down(~mask_up);

      int number_spins_up   = (phi_obj[0].phi & mask_up).count();
      int number_spins_down = (phi_obj[0].phi & mask_down).count();

      int mag = number_spins_up - number_spins_down;

      int tmp_mag = 0;
      int index = 0;
      for(int r=0; r<r_dmn::dmn_size(); ++r){
        for(int i=0; i<s_dmn::dmn_size(); ++i){
          for(int j=0; j<b_dmn::dmn_size(); ++j){
            if(i == 0 and phi_obj[0].phi[index] == 1)
              tmp_mag += 1;
            if(i == 1 and phi_obj[0].phi[index] == 1)
              tmp_mag -= 1;

            index += 1;
          }
        }
      }

      assert(tmp_mag == mag);

      return mag;
    }

    template<typename parameter_type, typename ed_options>
    void psi_state<parameter_type, ed_options>::simplify()
    {
      std::vector< phi_state<parameter_type, ed_options> > simplified_phi_obj;

      std::vector< phi_state<parameter_type, ed_options> > new_phi_obj;

      for (int i = 0; i < size(); ++i){

        int index = 0;
        while(index < simplified_phi_obj.size() && get_phi(i) != simplified_phi_obj[index].phi)
          ++index;

        if(index == simplified_phi_obj.size())
          {
            simplified_phi_obj.push_back(get_phi_obj(i));
          }
        else
          {
            simplified_phi_obj[index].alpha += get_alpha(i);
          }
      }

      for (int i = 0; i < simplified_phi_obj.size(); ++i){
        if(abs(simplified_phi_obj[i].alpha) > 1.e-10){
          new_phi_obj.push_back(simplified_phi_obj[i]);
        }
      }

      phi_obj.swap(new_phi_obj);

    }

    template<typename parameter_type, typename ed_options>
    void psi_state<parameter_type, ed_options>::normalize()
    {
      complex_type tmp = scalar_product(*this, *this);

      assert( abs(tmp.imag()) < 1.e-14 && tmp.real() >= 0 );

      scalar_type norm = sqrt(tmp.real());

      for (int i = 0; i < size(); ++i){
        get_alpha(i) /= norm;
      }
    }

    template<typename parameter_type, typename ed_options>
    void psi_state<parameter_type, ed_options>::sort()
    {
      // std::vector< phi_type >       sorted_phis;
      // std::vector< complex_type >   sorted_coefficients;

      // for(int i = 0; i < size(); ++i){

      //   int index = 0;
      //   while (index < sorted_phis.size() && phis[i].to_ulong() >= sorted_phis[index].to_ulong()){
      //     ++index;
      //   }
      //   sorted_phis.insert(sorted_phis.begin()+index, phis[i]);
      //   sorted_coefficients.insert(sorted_coefficients.begin()+index, coefficients[i]);
      // }

      // phis.swap(sorted_phis);
      // coefficients.swap(sorted_coefficients);

      std::sort(phi_obj.begin(), phi_obj.end());
    }
*/

  }
}

#endif
