//-*-C++-*-

#ifndef TB_HUBBARD_MODEL_PARAMETERS_H
#define TB_HUBBARD_MODEL_PARAMETERS_H

/*!
 *  \author: Peter Staar
 */
template<typename lattice_type, typename interaction_type>
class model_parameters<tight_binding_model<lattice_type, interaction_type> >
{

public:

  model_parameters();
  ~model_parameters();

/******************************************
 ***        CONCURRENCY                 ***
 ******************************************/

  template<class concurrency_type>
  int  get_buffer_size( concurrency_type& concurrency);

  template<class concurrency_type>
  void pack( concurrency_type& concurrency, int* buffer, int buffer_size, int& position);

  template<class concurrency_type>
  void unpack( concurrency_type& concurrency, int* buffer, int buffer_size, int& position);

/******************************************
 ***        READ/WRITE                  ***
 ******************************************/

  template<class read_write_type>
  void read_write(read_write_type& read_write_obj);

/******************************************
 ***        DATA                        ***
 ******************************************/

  double  get_U();
  double  get_U_prime();

  double  get_t();
  double  get_t_prime();
  
private:
 
  double t;
  double t_prime;
 
  double U;
  double U_prime;
};

template<typename lattice_type, typename interaction_type>
model_parameters<tight_binding_model<lattice_type, interaction_type> >::model_parameters():
  t(1),
  t_prime(0),

  U(4),
  U_prime(0)
{}

template<typename lattice_type, typename interaction_type>
model_parameters<tight_binding_model<lattice_type, interaction_type> >::~model_parameters()
{}

/******************************************
 ***        CONCURRENCY                 ***
 ******************************************/

template<typename lattice_type, typename interaction_type>
template<class concurrency_type>
int model_parameters<tight_binding_model<lattice_type, interaction_type> >::get_buffer_size( concurrency_type& concurrency)
{
  int buffer_size = 0;

  buffer_size += concurrency.get_buffer_size(t);
  buffer_size += concurrency.get_buffer_size(t_prime);

  buffer_size += concurrency.get_buffer_size(U);
  buffer_size += concurrency.get_buffer_size(U_prime);

  return buffer_size;
}

template<typename lattice_type, typename interaction_type>
template<class concurrency_type>
void model_parameters<tight_binding_model<lattice_type, interaction_type> >::pack( concurrency_type& concurrency, int* buffer, int buffer_size, int& position)
{
  concurrency.pack(buffer, buffer_size, position, t);
  concurrency.pack(buffer, buffer_size, position, t_prime);

  concurrency.pack(buffer, buffer_size, position, U);
  concurrency.pack(buffer, buffer_size, position, U_prime);
}

template<typename lattice_type, typename interaction_type>
template<class concurrency_type>
void model_parameters<tight_binding_model<lattice_type, interaction_type> >::unpack( concurrency_type& concurrency, int* buffer, int buffer_size, int& position)
{
  concurrency.unpack(buffer, buffer_size, position, t);
  concurrency.unpack(buffer, buffer_size, position, t_prime);

  concurrency.unpack(buffer, buffer_size, position, U);
  concurrency.unpack(buffer, buffer_size, position, U_prime);
}

/******************************************
 ***        READ/WRITE                  ***
 ******************************************/

template<typename lattice_type, typename interaction_type>
template<class read_write_type>
void  model_parameters<tight_binding_model<lattice_type, interaction_type> >::read_write(read_write_type& read_write_obj)
{
  try
    {
      read_write_obj.open_group("2D-Hubbard-model");

      try { read_write_obj.execute("t"      , t);       } catch(const std::exception& r_e) {}
      try { read_write_obj.execute("t-prime", t_prime); } catch(const std::exception& r_e) {}	
      try { read_write_obj.execute("U"      , U);       } catch(const std::exception& r_e) {}
      try { read_write_obj.execute("U_prime", U_prime); } catch(const std::exception& r_e) {}

      read_write_obj.close_group();
    }
  catch(const std::exception& r_e) 
    { 
      cout << "\n\t 2D-Hubbard-model parameters defined !!\n\n";
      throw std::logic_error(__PRETTY_FUNCTION__);
    }
}

/******************************************
 ***        DATA                        ***
 ******************************************/

template<typename lattice_type, typename interaction_type>
double model_parameters<tight_binding_model<lattice_type, interaction_type> >::get_t()
{
  return t;
}

template<typename lattice_type, typename interaction_type>
double model_parameters<tight_binding_model<lattice_type, interaction_type> >::get_t_prime()
{
  return t_prime;
}

template<typename lattice_type, typename interaction_type>
double model_parameters<tight_binding_model<lattice_type, interaction_type> >::get_U()
{
  return U;
}
 
template<typename lattice_type, typename interaction_type>
double model_parameters<tight_binding_model<lattice_type, interaction_type> >::get_U_prime()
{
  return U_prime;
}

#endif
