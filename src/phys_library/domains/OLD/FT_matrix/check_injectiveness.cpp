


template<class cluster_type>
bool check_injectiveness()
{
  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, FULL, FULL>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, FULL, FULL>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_cluster_size()*l]*matrix_inv[l + cluster_type::get_cluster_size()*j];

	i==j? c -= 1.: c;

	if(abs(c) > 1e-10)
	  cout << "ERROR in <FULL, FULL> * (<FULL, FULL>)^(-1)";

      }
    }

  }


  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, IRREDUCIBLE, IRREDUCIBLE>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, IRREDUCIBLE, IRREDUCIBLE>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_irreducible_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_irreducible_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_irreducible_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_irreducible_cluster_size()*l]*matrix_inv[l + cluster_type::get_irreducible_cluster_size()*j];

	i==j? c -= 1.: c;

	if(abs(c) > 1e-10)
	  cout << "ERROR in <IRREDUCIBLE, IRREDUCIBLE> * (<IRREDUCIBLE, IRREDUCIBLE>)^(-1)";

      }
    }
    
  }

  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, FULL, IRREDUCIBLE>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, IRREDUCIBLE, FULL>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_irreducible_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_cluster_size()*l]*matrix_inv[l + cluster_type::get_irreducible_cluster_size()*j];

	i==j? c -= 1. : c;

	if(abs(c) > 1e-10)
	  cout << "ERROR in <FULL, IRREDUCIBLE> * (<IRREDUCIBLE, FULL>)^(-1)";

      }
    }
    
  }


  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, IRREDUCIBLE, FULL>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, FULL, IRREDUCIBLE>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_irreducible_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_irreducible_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_irreducible_cluster_size()*l]*matrix_inv[l + cluster_type::get_cluster_size()*j];

	i==j? c -= 1. : c;

	if(abs(c) > 1e-10)
	  cout << "ERROR in <IRREDUCIBLE, FULL> * (<FULL, IRREDUCIBLE>)^(-1)";

      }
    }
  }
    return true;
}
