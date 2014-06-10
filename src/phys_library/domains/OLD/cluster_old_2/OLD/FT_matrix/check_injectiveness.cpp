
template<class cluster_type>
bool check_injectiveness()
{
  cout << endl << "<FULL, FULL> * (<FULL, FULL>)^(-1)" << endl;
  cout << "size : " << cluster_type::get_cluster_size() << endl;
  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, FULL, FULL>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, FULL, FULL>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_cluster_size()*l]*matrix_inv[l + cluster_type::get_cluster_size()*j];

	//i==j? c -= 1.: c;

	if(abs(c) < 1e-10)
	  cout << "-----------------------";
	else
	  cout << c;
	cout << "\t";
      }
      cout << endl;
    }

  }

  cout << endl << "<IRREDUCIBLE, IRREDUCIBLE> * (<IRREDUCIBLE, IRREDUCIBLE>)^(-1)" << endl;
  cout << "size : " << cluster_type::get_irreducible_cluster_size() << endl;
  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, IRREDUCIBLE, IRREDUCIBLE>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, IRREDUCIBLE, IRREDUCIBLE>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_irreducible_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_irreducible_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_irreducible_cluster_size(); l++)
	c += matrix[i + cluster_type::get_irreducible_cluster_size()*l]*matrix_inv[l + cluster_type::get_irreducible_cluster_size()*j];

	//c = matrix[i + cluster_type::get_irreducible_cluster_size()*j];
	if(abs(c) < 1e-10)
	  cout << "-----------------------";
	else
	  cout << c;
	cout << "\t";

      }
      cout << endl;
    }
    
  }
  
  /*
  cout << endl << "<FULL, IRREDUCIBLE> * (<IRREDUCIBLE, FULL>)^(-1)" << endl;
  cout << "size : " << cluster_type::get_cluster_size() << endl;
  {
    std::complex<double>* matrix    = cluster_FT_matrix<cluster_type, FULL, IRREDUCIBLE>::get_matrix();
    std::complex<double>* matrix_inv = cluster_FT_matrix<cluster_type, IRREDUCIBLE, FULL>::get_matrix_inverse();

    for(int i=0; i<cluster_type::get_cluster_size(); i++){
      for(int j=0; j<cluster_type::get_cluster_size(); j++){
      
	std::complex<double> c(0.,0.);
	for(int l=0; l<cluster_type::get_irreducible_cluster_size(); l++)
	  c += matrix[i + cluster_type::get_cluster_size()*l]*matrix_inv[l + cluster_type::get_irreducible_cluster_size()*j];

	//c = matrix[i + cluster_type::get_irreducible_cluster_size()*j];
	if(abs(c) < 1e-10)
	  cout << "-----------------------";
	else
	  cout << c;
	cout << "\t";
	//i==j? c -= 1. : c;

	//if(abs(c) > 1e-10)
	//cout << "ERROR in <FULL, IRREDUCIBLE> * (<IRREDUCIBLE, FULL>)^(-1)";

      }
      cout << endl;
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
  */
  return true;
}








template<class parameters>
void do_cluster_tests()
{
  // const static int DIMENSION=2;
  //typedef D4                                      point_group_type;
  /*typedef cluster<Parameters >   cluster_type;
  
  int A[2] = {2,-2}; 
  int B[2] = {2,2}; 

  cluster_type::initializer::initialize(Parameters::A, Parameters::B);
  reduce< cluster_type >::execute();
  cluster_type::print();

  check_injectiveness<cluster_type>();


  typedef r_cluster<FULL,cluster_type>       r_cluster_type;
  typedef k_cluster<FULL,cluster_type>       k_cluster_type;
  typedef time_domain<FULL, Parameters>      time_domain_type;
  typedef frequency_domain<FULL, Parameters> frequency_domain_type;

  typedef dmn_0<r_cluster_type>         r;
  typedef dmn_0<k_cluster_type>         k;
  //typedef dmn_0<time_domain_type >      t;
  //typedef dmn_0<frequency_domain_type > w;

  //typedef dmn_2<r,t> r_t;
  //typedef dmn_2<r,w> r_w;
  //typedef dmn_3<r,r,t> r_r_t;
  //typedef dmn_3<k,k,t> k_k_t;

  //function<double              , r_r_t> f;
  //function<std::complex<double>, k_k_t> F;
  //function<std::complex<double>, r_r_t> f2;

  //f.print_fingerprint();
  //F.print_fingerprint();

  */
  
}


