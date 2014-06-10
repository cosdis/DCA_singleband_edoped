//-*-C++-*-

#ifndef ADVANCED_FERMIONIC_HILBERT_SPACE_PHI_REPRESENTATION_H
#define ADVANCED_FERMIONIC_HILBERT_SPACE_PHI_REPRESENTATION_H

namespace DCA
{
  namespace ADVANCED_EXACT_DIAGONALIZATION
  {
    template<typename parameter_type, typename ed_options>       // N: size of bitset sequence
    class Hilbert_space_phi_representation
    {
      typedef typename ed_options::scalar_type  scalar_type;
      typedef typename ed_options::complex_type complex_type;
 
      typedef typename ed_options::phi_type phi_type;
 
    public:

      Hilbert_space_phi_representation();
      ~Hilbert_space_phi_representation();

      template<typename Hilbert_space_type>
      void initialize(Hilbert_space_type& HS);

      int size() { return rep.size(); }

      phi_type&                  get_phi(int i)     { assert(i>=0 && i<size()); return rep[i].phi; }
      std::vector<int>&          get_indices(int i) { assert(i>=0 && i<size()); return rep[i].index; }
      std::vector<complex_type>& get_alphas(int i)  { assert(i>=0 && i<size()); return rep[i].alpha; }

      int find(const phi_type& phi_);

    private:

      void sort();

      void merge();

      void sort_phis();

    private:

      std::vector< phi_state<parameter_type, ed_options, PHI_MULTIPLET> > rep;
    };

    template<typename parameter_type, typename ed_options>
    Hilbert_space_phi_representation<parameter_type, ed_options>::Hilbert_space_phi_representation()
    {}

    template<typename parameter_type, typename ed_options>
    Hilbert_space_phi_representation<parameter_type, ed_options>::~Hilbert_space_phi_representation()
    {}

    template<typename parameter_type, typename ed_options>
    template<typename Hilbert_space_type>
    void Hilbert_space_phi_representation<parameter_type, ed_options>::initialize(Hilbert_space_type& HS)//Hilbert_space<parameter_type, ed_options>& HS)
    {
      for(int i = 0; i < HS.size(); ++i)
	{	
	  psi_state<parameter_type, ed_options>& Psi = HS.get_element(i);

	  for (int j = 0; j < Psi.size(); ++j)
	    {	  
	      phi_state<parameter_type, ed_options, PHI_MULTIPLET> tmp;

	      tmp.phi   = Psi.get_phi(j);
	      tmp.index = std::vector<int>(1,i);
	      tmp.alpha = std::vector<complex_type>(1,Psi.get_alpha(j));

	      rep.push_back(tmp);
	    }
	}

      sort();
      
      merge();
      
      sort_phis();
    }

    template<typename parameter_type, typename ed_options>
    void Hilbert_space_phi_representation<parameter_type, ed_options>::sort()
    {
      std::sort(rep.begin(), rep.end());
    }

    template<typename parameter_type, typename ed_options>
    void Hilbert_space_phi_representation<parameter_type, ed_options>::merge()
    {
      std::vector< phi_state<parameter_type, ed_options, PHI_MULTIPLET> > merged_rep;

      merged_rep.push_back(rep[0]);

      for(int i = 1; i < size(); ++i){
	
	if(rep[i].phi == merged_rep.back().phi)
	  {
	    merged_rep.back().index.insert(merged_rep.back().index.end(), rep[i].index.begin(), rep[i].index.end());
	    merged_rep.back().alpha.insert(merged_rep.back().alpha.end(), rep[i].alpha.begin(), rep[i].alpha.end());
	  }
	else
	  {
	    merged_rep.push_back(rep[i]);
	  }
      }

      rep.swap(merged_rep);
    }

    template<typename parameter_type, typename ed_options>
    void Hilbert_space_phi_representation<parameter_type, ed_options>::sort_phis()
    {
      for(int i = 0; i < size(); ++i)
	rep[i].sort();
    }

    template<typename parameter_type, typename ed_options>
    int Hilbert_space_phi_representation<parameter_type, ed_options>::find(const phi_type& phi_)
    {
      phi_state<parameter_type, ed_options, PHI_MULTIPLET> tmp;
      tmp.phi = phi_;

      typename std::vector< phi_state<parameter_type, ed_options, PHI_MULTIPLET> >::iterator it = std::lower_bound(rep.begin(), rep.end(), tmp);

      if(it != rep.end() && !(tmp < *it))
	return it - rep.begin();
      else
	return rep.size();
    }

  }

}

#endif
