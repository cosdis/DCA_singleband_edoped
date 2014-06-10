//-*-C++-*-

#ifndef DFT_MODEL_H
#define DFT_MODEL_H

/*!
 *  \author peter staar
 */
template<int DIM, typename point_group_type>
class dft_model 
{
public:

  const static int DIMENSION = DIM;

  const static cluster_shape_type DCA_cluster_shape = BETT_CLUSTER;
  const static cluster_shape_type LDA_cluster_shape = PARALLELEPIPED;

  typedef no_symmetry<DIMENSION> LDA_point_group;
  typedef point_group_type       DCA_point_group;


  static int    BANDS;
//   static string filename;
//   static double Fermi_energy;
//   static double density;

  template<class parameters_type>
  static void initialize(parameters_type& parameters);

  static void write_domains(std::string filename);
  
  static void read_flavors_and_a_vectors();
  
  static void read_basis();
  
//   template<class concurrency_type>
//   static void read(concurrency_type& concurrency);

//   static std::vector<int>& DCA_grid_size();
//   static std::vector<int>& LDA_grid_size();

  static std::vector<int>& get_H_k_grid_size();

  static double* get_r_DCA_basis();
  static double* get_k_DCA_basis();

  static double* get_r_LDA_basis();
  static double* get_k_LDA_basis();

  static std::vector<int>&                  get_flavors();
  static std::vector<std::vector<double> >& get_a_vectors();

  static int* Hamiltonian_symmetries();

  static std::vector<std::pair<std::pair<int,int>, std::pair<int,int> > > get_orbital_permutations();

  template<class domain, class parameters_type>
  static void                 initialize_H_LDA(function<std::complex<double> , domain >& H_LDA,
					       parameters_type&                          parameters);

  template<class domain, class parameters_type>
  static void                 initialize_H_interaction(function<double , domain >& H_interactions,
						       parameters_type&            parameters);

  template<class domain>
  static void                 initialize_H_symmetries(function<int , domain >& H_symmetries);

  static void                 symmetrize_Hamiltonian(std::complex<double>* H_matrix);

  template<class concurrency_type>
  int get_buffer_size(concurrency_type& concurrency);

  template<class concurrency_type>
  void pack(concurrency_type& concurrency, int* buffer, int buffer_size, int& position);
  
  template<class concurrency_type>
  void unpack(concurrency_type& concurrency, int* buffer, int buffer_size, int& position);
};

template<int DIMENSION, typename point_group_type>
int dft_model<DIMENSION, point_group_type>::BANDS = -1;

template<int DIMENSION, typename point_group_type>
template<class parameters_type>
void dft_model<DIMENSION, point_group_type>::initialize(parameters_type& parameters)
{
  typedef typename parameters_type::Concurrency_Type concurrency_type;
  concurrency_type& concurrency = parameters.get_concurrency();

  if(concurrency.id()==concurrency.first()){
    cout << "\n\n starts reading : " << parameters.get_H_LDA_file() << "\n\n";

    write_domains(parameters.get_H_LDA_file());

    read_flavors_and_a_vectors();

    read_basis();
  }

  concurrency.broadcast(BANDS, concurrency.first());

  if(concurrency.id() != concurrency.first()){
    get_flavors()  .resize(BANDS, 0);
    get_a_vectors().resize(BANDS, std::vector<double>(DIMENSION, 0.));
  }

  dft_model<DIMENSION, point_group_type> model_obj;
  concurrency.broadcastObj(model_obj);

//   {
//     cout << concurrency.id() << "\t" << BANDS << endl;
//     VECTOR_OPERATIONS::PRINT(get_flavors());
//     cout << endl;
//     for(int i=0; i<BANDS; ++i){
//       VECTOR_OPERATIONS::PRINT(get_a_vectors()[i]);
//       cout << endl;
//     }
//     cout << endl;
//   }
}

template<int DIMENSION, typename point_group_type>
void dft_model<DIMENSION, point_group_type>::write_domains(std::string filename)
{
  std::fstream input_file (filename.c_str(), ios::in);  
  std::fstream output_file("domains.json", ios::out);  

  const static int buffer_size = 2024;
  char* buffer = new char[buffer_size];

  string new_line("\n");

  while (! input_file.eof() )
  {
    input_file.getline(buffer,buffer_size);

    string str(buffer);
    
    output_file.write(str     .c_str(), str     .size());
    output_file.write(new_line.c_str(), new_line.size());

    if(str.rfind(string("functions"),str.size()) != string::npos)
      break;
  }
  
  std::string str(" \"none\"\n}");
  output_file.write(str.c_str(), str.size());

  input_file .close();
  output_file.close();
}

template<int DIMENSION, typename point_group_type>
void dft_model<DIMENSION, point_group_type>::read_flavors_and_a_vectors()
{
  dca::JsonReader reader("domains.json");
  typedef typename dca::JsonReader::JsonAccessor JsonAccessor;
  cout << "\n\n";

  int                 flavor;
  std::vector<double> a_vec;

  BANDS = 0;
  while(true){

    try
      {
	std::stringstream ss;
	ss << "orbital " << BANDS;
	
	const JsonAccessor control(reader["electron_band_domain"][ss.str()]);
      
	flavor <= control["flavor"];
	a_vec  <= control["a_vec"];
	
	get_flavors()  .push_back(flavor);
	get_a_vectors().push_back(a_vec);
	
	BANDS += 1;
      }
    catch(const std::exception& r_e){
      break;
    }
  }
}

template<int DIMENSION, typename point_group_type>
std::vector<int>& dft_model<DIMENSION, point_group_type>::get_flavors()
{
  static std::vector<int> flavors(0);
  return flavors;
}

template<int DIMENSION, typename point_group_type>
std::vector<std::vector<double> >& dft_model<DIMENSION, point_group_type>::get_a_vectors()
{
  static std::vector<std::vector<double> > a_vecs(0);
  return a_vecs;
}

template<int DIMENSION, typename point_group_type>
void dft_model<DIMENSION, point_group_type>::read_basis()
{
  dca::JsonReader reader("domains.json");
  cout << "\n\n";

  std::vector<double> r_vec;
  for(int i=0; i<DIMENSION; ++i){

    std::stringstream ss;
    ss << "R_" << i;

    r_vec <= reader["cluster"]["BASIS"]["R"][ss.str()];

    for(int j=0; j<DIMENSION; ++j){
      get_r_DCA_basis()[j+i*DIMENSION] = r_vec[j];
      get_r_LDA_basis()[j+i*DIMENSION] = r_vec[j];
    } 
  }

  std::vector<double> k_vec;
  for(int i=0; i<DIMENSION; ++i){

    std::stringstream ss;
    ss << "K_" << i;

    k_vec <= reader["cluster"]["BASIS"]["K"][ss.str()];

    for(int j=0; j<DIMENSION; ++j){
      get_k_DCA_basis()[j+i*DIMENSION] = k_vec[j];
      get_k_LDA_basis()[j+i*DIMENSION] = k_vec[j];
    } 
  }
}

template<int DIMENSION, typename point_group_type>
double* dft_model<DIMENSION, point_group_type>::get_r_DCA_basis()
{
  static double* basis = new double[DIMENSION*DIMENSION];
  return basis;
}

template<int DIMENSION, typename point_group_type>
double* dft_model<DIMENSION, point_group_type>::get_k_DCA_basis()
{
  static double* basis = new double[DIMENSION*DIMENSION];
  return basis;
}

template<int DIMENSION, typename point_group_type>
double* dft_model<DIMENSION, point_group_type>::get_r_LDA_basis()
{
  static double* basis = new double[DIMENSION*DIMENSION];
  return basis;
}

template<int DIMENSION, typename point_group_type>
double* dft_model<DIMENSION, point_group_type>::get_k_LDA_basis()
{
  static double* basis = new double[DIMENSION*DIMENSION];
  return basis;
}




template<int DIMENSION, typename point_group_type>
template<class domain>
void dft_model<DIMENSION, point_group_type>::initialize_H_symmetries(function<int, domain >& H_symmetries)
{
//   std::fstream input_file(&(parameters.get_H_LDA_file())[0], ios::in);

//   H_symmetries.from_JSON(input_file, concurrency);

//   input_file.close();
}

template<int DIMENSION, typename point_group_type>
template<class domain, class parameters_type>
void dft_model<DIMENSION, point_group_type>::initialize_H_interaction(function<double, domain >& H_interaction,
								      parameters_type&           parameters)
{
  std::fstream input_file(&(parameters.get_H_LDA_file())[0], ios::in);  
  H_interaction.from_JSON(input_file);
  input_file.close();

  cout << "\n\n\t H_int : \n";
  for(int i=0; i<2*BANDS; ++i){
    cout << "\t\t";
    for(int j=0; j<2*BANDS; ++j)
      cout << H_interaction(i,j,0) << "\t";
    cout << endl;
  }
  cout << endl;
}

template<int DIMENSION, typename point_group_type>
template<class domain, class parameters_type>
void dft_model<DIMENSION, point_group_type>::initialize_H_LDA(function<std::complex<double>, domain >& H_LDA,
							      parameters_type&                          parameters)
{
  std::fstream input_file(&(parameters.get_H_LDA_file())[0], ios::in);  
  H_LDA.from_JSON(input_file);
  input_file.close();
}





template<int DIMENSION, typename point_group_type>
void dft_model<DIMENSION, point_group_type>::symmetrize_Hamiltonian(std::complex<double>* H_matrix)
{
  // spin -symmetrization

  for(int i=0; i<BANDS; i++){
    for(int j=0; j<BANDS; j++){
      std::complex<double> tmp = (H_matrix[i+j*2*BANDS] + H_matrix[(i+BANDS)+(j+BANDS)*2*BANDS])/2.;
      H_matrix[i+j*2*BANDS]                 = tmp;
      H_matrix[(i+BANDS)+(j+BANDS)*2*BANDS] = tmp; 
    }
  }
}





template<int DIMENSION, typename point_group_type>
template<class concurrency_type>
int dft_model<DIMENSION, point_group_type>::get_buffer_size(concurrency_type& concurrency)
{
  int result = 0;

  result += concurrency.getBufferSize(get_flavors()); 
  
  {
    result += concurrency.getBufferSize(std::vector<double>(BANDS*DIMENSION)); 
  }

  {
    result += concurrency.getBufferSize(std::vector<double>(DIMENSION*DIMENSION)); 
    result += concurrency.getBufferSize(std::vector<double>(DIMENSION*DIMENSION)); 
    
    result += concurrency.getBufferSize(std::vector<double>(DIMENSION*DIMENSION)); 
    result += concurrency.getBufferSize(std::vector<double>(DIMENSION*DIMENSION)); 
  }

  return result;
}

template<int DIMENSION, typename point_group_type>
template<class concurrency_type>
void dft_model<DIMENSION, point_group_type>::pack(concurrency_type& concurrency, int* buffer, int buffer_size, int& position)
{
  concurrency.pack(buffer, buffer_size, position, get_flavors());
  
  {
    std::vector<double> tmp(BANDS*DIMENSION);
    for(int i=0; i<BANDS; ++i)
      for(int j=0; j<DIMENSION; ++j)
	tmp[j+i*DIMENSION] = get_a_vectors()[i][j];

    concurrency.pack(buffer, buffer_size, position, tmp);
  }  

  {
    std::vector<double> tmp(DIMENSION*DIMENSION);
    
    memcpy(&tmp[0], get_r_DCA_basis(), sizeof(double)*DIMENSION*DIMENSION);
    concurrency.pack(buffer, buffer_size, position, tmp);
    
    memcpy(&tmp[0], get_k_DCA_basis(), sizeof(double)*DIMENSION*DIMENSION);
    concurrency.pack(buffer, buffer_size, position, tmp);
    
    memcpy(&tmp[0], get_r_LDA_basis(), sizeof(double)*DIMENSION*DIMENSION);
    concurrency.pack(buffer, buffer_size, position, tmp);
    
    memcpy(&tmp[0], get_k_LDA_basis(), sizeof(double)*DIMENSION*DIMENSION);
    concurrency.pack(buffer, buffer_size, position, tmp);
  }
}

template<int DIMENSION, typename point_group_type>
template<class concurrency_type>
void dft_model<DIMENSION, point_group_type>::unpack(concurrency_type& concurrency, int* buffer, int buffer_size, int& position)
{
  concurrency.unpack(buffer, buffer_size, position, get_flavors());

  {
    std::vector<double> tmp(BANDS*DIMENSION);

    concurrency.unpack(buffer, buffer_size, position, tmp);

    for(int i=0; i<BANDS; ++i)
      for(int j=0; j<DIMENSION; ++j)
	get_a_vectors()[i][j] = tmp[j+i*DIMENSION];
  }  

  {
    std::vector<double> tmp(DIMENSION*DIMENSION);
    
    concurrency.unpack(buffer, buffer_size, position, tmp);
    memcpy(get_r_DCA_basis(), &tmp[0], sizeof(double)*DIMENSION*DIMENSION);
    
    concurrency.unpack(buffer, buffer_size, position, tmp);
    memcpy(get_k_DCA_basis(), &tmp[0], sizeof(double)*DIMENSION*DIMENSION);
    
    concurrency.unpack(buffer, buffer_size, position, tmp);
    memcpy(get_r_LDA_basis(), &tmp[0], sizeof(double)*DIMENSION*DIMENSION);
    
    concurrency.unpack(buffer, buffer_size, position, tmp);
    memcpy(get_k_LDA_basis(), &tmp[0], sizeof(double)*DIMENSION*DIMENSION);
  }
}

#endif
