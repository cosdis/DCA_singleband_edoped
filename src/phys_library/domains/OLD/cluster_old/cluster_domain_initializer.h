//-*-C++-*-

#ifndef INITIALIZE_CLUSTER_DOMAIN_H
#define INITIALIZE_CLUSTER_DOMAIN_H

template<typename cluster_type>
class cluster_domain_initializer
{};

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
class cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >
{
public:

  typedef std::vector<scalar_type> element_type;
  
  typedef cluster_domain<scalar_type, NAME, REAL_SPACE    , SHAPE> r_dmn;
  typedef cluster_domain<scalar_type, NAME, MOMENTUM_SPACE, SHAPE> k_dmn;


public:

  static void execute(scalar_type*     r_basis,
		      std::vector<int> R_basis);
  
  static void execute(scalar_type*                   r_basis,
		      std::vector<std::vector<int> > R_basis);

private:

  static void initialize_basis(scalar_type*          r_basis,
			       std::vector<int> R_basis);

  static void initialize_basis(scalar_type*                   r_basis,
			       std::vector<std::vector<int> > R_basis);

  static void initialize_elements();

  static void initialize_elements_1D(scalar_type shift);
  static void initialize_elements_2D(scalar_type shift);
  static void initialize_elements_3D(scalar_type shift);

  static void initialize_add(scalar_type*                             basis,
			     std::vector<std::vector<scalar_type> >&  elements,
			     LIN_ALG::matrix<int, LIN_ALG::CPU>& A);

  static void initialize_subtract(scalar_type*                             basis,
				  std::vector<std::vector<scalar_type> >&  elements,
				  LIN_ALG::matrix<int, LIN_ALG::CPU>& A);
};

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::execute(scalar_type*     r_basis,
													std::vector<int> R_basis)
{
  //assert(SHAPE==PARALLELLEPIPEDUM);

  initialize_basis(r_basis, R_basis);
  
  initialize_elements();
  
  r_dmn::is_initialized() = true;
  k_dmn::is_initialized() = true;

  initialize_add(r_dmn::get_super_basis(), r_dmn::get_elements(), r_dmn::get_add_matrix());
  initialize_add(k_dmn::get_super_basis(), k_dmn::get_elements(), k_dmn::get_add_matrix());

  initialize_subtract(r_dmn::get_super_basis(), r_dmn::get_elements(), r_dmn::get_subtract_matrix());
  initialize_subtract(k_dmn::get_super_basis(), k_dmn::get_elements(), k_dmn::get_subtract_matrix());
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_basis(scalar_type*     r_basis,
														 std::vector<int> R_basis)
{
  {
    r_dmn::DIMENSION = R_basis.size();
  
    r_dmn::get_dimensions()  = new int[r_dmn::DIMENSION];
    r_dmn::get_basis()       = new scalar_type[r_dmn::DIMENSION*r_dmn::DIMENSION];
    r_dmn::get_super_basis() = new scalar_type[r_dmn::DIMENSION*r_dmn::DIMENSION];

    k_dmn::DIMENSION = R_basis.size();

    k_dmn::get_dimensions()  = new int[k_dmn::DIMENSION];
    k_dmn::get_basis()       = new scalar_type[k_dmn::DIMENSION*k_dmn::DIMENSION];
    k_dmn::get_super_basis() = new scalar_type[k_dmn::DIMENSION*k_dmn::DIMENSION];
  }

  {
    for(int d0=0; d0<r_dmn::DIMENSION; d0++)
      for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	r_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] = r_basis[d0+d1*r_dmn::DIMENSION];
	
    {
      LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", r_dmn::DIMENSION);
      
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  A(d0,d1) = r_dmn::get_basis()[d0+d1*r_dmn::DIMENSION];
    
      LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);
    
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION] = A(d0,d1)*(2*M_PI);
    }
  }

  {
    for(int d0=0; d0<r_dmn::DIMENSION; d0++)
      for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	r_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION] = R_basis[d1]*r_basis[d0+d1*r_dmn::DIMENSION];

    {
      LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", r_dmn::DIMENSION);
    
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  A(d0,d1) = r_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION];
      
      LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);
      
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] = A(d0,d1);

      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] *= (2*M_PI);
    }
  }
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::execute(scalar_type*                   r_basis,
													std::vector<std::vector<int> > R_basis)
{
  assert(SHAPE==BRILLOUIN_ZONE);

  initialize_basis(r_basis, R_basis);
  
  initialize_elements();
  
  r_dmn::is_initialized() = true;
  k_dmn::is_initialized() = true;

  initialize_add(r_dmn::get_super_basis(), r_dmn::get_elements(), r_dmn::get_add_matrix());
  initialize_add(k_dmn::get_super_basis(), k_dmn::get_elements(), k_dmn::get_add_matrix());

  initialize_subtract(r_dmn::get_super_basis(), r_dmn::get_elements(), r_dmn::get_subtract_matrix());
  initialize_subtract(k_dmn::get_super_basis(), k_dmn::get_elements(), k_dmn::get_subtract_matrix());
}
 
template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_basis(scalar_type*                   r_basis,
														 std::vector<std::vector<int> > R_basis)
{
  //cout << __FUNCTION__ << endl;

  {
    r_dmn::DIMENSION = R_basis.size();
  
    r_dmn::get_dimensions()  = new int[r_dmn::DIMENSION];
    r_dmn::get_basis()       = new scalar_type[r_dmn::DIMENSION*r_dmn::DIMENSION];
    r_dmn::get_super_basis() = new scalar_type[r_dmn::DIMENSION*r_dmn::DIMENSION];

    k_dmn::DIMENSION = R_basis.size();

    k_dmn::get_dimensions()  = new int[k_dmn::DIMENSION];
    k_dmn::get_basis()       = new scalar_type[k_dmn::DIMENSION*k_dmn::DIMENSION];
    k_dmn::get_super_basis() = new scalar_type[k_dmn::DIMENSION*k_dmn::DIMENSION];
  }

  {
    for(int d0=0; d0<r_dmn::DIMENSION; d0++)
      for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	r_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] = r_basis[d0+d1*r_dmn::DIMENSION];
	
    {
      LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", r_dmn::DIMENSION);
      
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  A(d0,d1) = r_dmn::get_basis()[d0+d1*r_dmn::DIMENSION];
    
      LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);
    
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION] = A(d0,d1)*(2*M_PI);
    }
  }

  {
    for(int d0=0; d0<r_dmn::DIMENSION; d0++){
      for(int d1=0; d1<r_dmn::DIMENSION; d1++){
      
	r_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION] = 0;
	
	for(int d2=0; d2<r_dmn::DIMENSION; d2++)
	  r_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION] += r_dmn::get_basis()[d0+d2*r_dmn::DIMENSION]*R_basis[d1][d2];
      }
    }
  
    {
      LIN_ALG::matrix<scalar_type, LIN_ALG::CPU> A("A", r_dmn::DIMENSION);
    
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  A(d0,d1) = r_dmn::get_super_basis()[d0+d1*r_dmn::DIMENSION];
      
      LIN_ALG::GEINV<LIN_ALG::CPU>::execute(A);
      
      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] = A(d0,d1);

      for(int d0=0; d0<r_dmn::DIMENSION; d0++)
	for(int d1=0; d1<r_dmn::DIMENSION; d1++)
	  k_dmn::get_basis()[d0+d1*r_dmn::DIMENSION] *= (2*M_PI);
    }
  }
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_elements()
{
  const static scalar_type shift = 0.0;

  //cout << __FUNCTION__ << endl;

  switch(r_dmn::DIMENSION)
    {
    case 1:
      initialize_elements_1D(shift);
      break;

    case 2:
      initialize_elements_2D(shift);
      break;

    case 3:
      initialize_elements_3D(shift);
      break;
	
    default:
      throw std::logic_error(__FUNCTION__);
    }
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_elements_1D(scalar_type shift)
{
  {
    scalar_type t[1];
    scalar_type c[1];
      
    k_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
	  
      t[0] = d0*k_dmn::get_basis()[0];

      c[0] = t[0]/k_dmn::get_super_basis()[0];
	  
      if(c[0]>-1.e-6 and c[0]<1-1.e-6)
	{
	  element_type tmp(1, 0);
	      
	  tmp[0] = t[0];

	  k_dmn::get_elements().push_back(tmp);
	}	
    }
      
    k_dmn::get_size() = k_dmn::get_elements().size();

    sort(k_dmn::get_elements().begin(), k_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }

  {
    scalar_type t[1];
    scalar_type c[1];
      
    r_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
	
      t[0] = d0*r_dmn::get_basis()[0];
	
      c[0] = t[0]/r_dmn::get_super_basis()[0];
	
      if(c[0]>shift-1.e-6 and c[0]<shift+1.-1.e-6)
	{
	  element_type tmp(1, 0);
	    
	  tmp[0] = t[0];
	    
	  r_dmn::get_elements().push_back(tmp);
	}
    }

    r_dmn::get_size() = r_dmn::get_elements().size();

    sort(r_dmn::get_elements().begin(), r_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }   
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_elements_2D(scalar_type shift)
{
  VECTOR_OPERATIONS::coordinate_transformation<scalar_type> coordinate_trafo(2);
    
  {
    coordinate_trafo.set_basis(k_dmn::get_super_basis());
      
    scalar_type t[2];
    scalar_type c[2];
      
    k_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
      for(int d1=-100; d1<100; d1++){
	  
	t[0] = d0*k_dmn::get_basis()[0]+d1*k_dmn::get_basis()[2];
	t[1] = d0*k_dmn::get_basis()[1]+d1*k_dmn::get_basis()[3];
	  
	coordinate_trafo.execute(t, c);

	if(c[0]>shift-1.e-6 and c[0]<shift+1.-1.e-6 and
	   c[1]>shift-1.e-6 and c[1]<shift+1.-1.e-6)
	  {
	    element_type tmp(2, 0);
	      
	    tmp[0] = t[0];
	    tmp[1] = t[1];
	      
	    k_dmn::get_elements().push_back(tmp);
	  }
      }
    }
      
    k_dmn::get_size() = k_dmn::get_elements().size();

    sort(k_dmn::get_elements().begin(), k_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }
    
  {
    coordinate_trafo.set_basis(r_dmn::get_super_basis());
      
    scalar_type t[2];
    scalar_type c[2];
      
    r_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
      for(int d1=-100; d1<100; d1++){
	  
	t[0] = d0*r_dmn::get_basis()[0]+d1*r_dmn::get_basis()[2];
	t[1] = d0*r_dmn::get_basis()[1]+d1*r_dmn::get_basis()[3];
	  
	coordinate_trafo.execute(t, c);
	  
	if(c[0]>shift-1.e-6 and c[0]<shift+1.-1.e-6 and
	   c[1]>shift-1.e-6 and c[1]<shift+1.-1.e-6)
	  {
	    element_type tmp(2, 0);
	      
	    tmp[0] = t[0];
	    tmp[1] = t[1];
	      
	    r_dmn::get_elements().push_back(tmp);
	  }
      }
    }
	
    r_dmn::get_size() = r_dmn::get_elements().size();

    sort(r_dmn::get_elements().begin(), r_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_elements_3D(scalar_type shift)
{
  VECTOR_OPERATIONS::coordinate_transformation<scalar_type> coordinate_trafo(3);

  {
    coordinate_trafo.set_basis(k_dmn::get_super_basis());

    scalar_type t[3];
    scalar_type c[3];
      
    k_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
      for(int d1=-100; d1<100; d1++){
	for(int d2=-100; d2<100; d2++){
	  
	  t[0] = d0*k_dmn::get_basis()[0]+d1*k_dmn::get_basis()[3]+d2*k_dmn::get_basis()[6];
	  t[1] = d0*k_dmn::get_basis()[1]+d1*k_dmn::get_basis()[4]+d2*k_dmn::get_basis()[7];
	  t[1] = d0*k_dmn::get_basis()[2]+d1*k_dmn::get_basis()[5]+d2*k_dmn::get_basis()[8];
	  
	  coordinate_trafo.execute(t, c);
	  
	  if(c[0]>shift-1.e-6 and c[0]<shift+1.-1.e-6 and
	     c[1]>shift-1.e-6 and c[1]<shift+1.-1.e-6 and
	     c[2]>shift-1.e-6 and c[2]<shift+1.-1.e-6)
	    {
	      element_type tmp(3, 0);
	      
	      tmp[0] = t[0];
	      tmp[1] = t[1];
	      tmp[2] = t[2];
	      
	      k_dmn::get_elements().push_back(tmp);
	    }
	}
      }
    }
      
    k_dmn::get_size() = k_dmn::get_elements().size();

    sort(k_dmn::get_elements().begin(), k_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }

  {
    coordinate_trafo.set_basis(r_dmn::get_super_basis());

    scalar_type t[3];
    scalar_type c[3];
      
    r_dmn::get_elements().resize(0);
    for(int d0=-100; d0<100; d0++){
      for(int d1=-100; d1<100; d1++){
	for(int d2=-100; d2<100; d2++){
	  
	  t[0] = d0*r_dmn::get_basis()[0]+d1*r_dmn::get_basis()[3]+d2*r_dmn::get_basis()[6];
	  t[1] = d0*r_dmn::get_basis()[1]+d1*r_dmn::get_basis()[4]+d2*r_dmn::get_basis()[7];
	  t[1] = d0*r_dmn::get_basis()[2]+d1*r_dmn::get_basis()[5]+d2*r_dmn::get_basis()[8];
	  
	  coordinate_trafo.execute(t, c);
	  
	  if(c[0]>shift-1.e-6 and c[0]<shift+1.-1.e-6 and
	     c[1]>shift-1.e-6 and c[1]<shift+1.-1.e-6 and
	     c[2]>shift-1.e-6 and c[2]<shift+1.-1.e-6)
	    {
	      element_type tmp(3, 0);
	      
	      tmp[0] = t[0];
	      tmp[1] = t[1];
	      tmp[2] = t[2];
	      
	      r_dmn::get_elements().push_back(tmp);
	    }
	}
      }
    }
      
    r_dmn::get_size() = r_dmn::get_elements().size();

    sort(r_dmn::get_elements().begin(), r_dmn::get_elements().end(), VECTOR_OPERATIONS::IS_LARGER_VECTOR);
  }
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_add(scalar_type*                            basis,
													       std::vector<std::vector<scalar_type> >& elements,
													       LIN_ALG::matrix<int, LIN_ALG::CPU>&     A)
{
  //cout << __FUNCTION__ << endl;

  int DIMENSION = r_dmn::DIMENSION;

  std::vector<std::vector<scalar_type> > basis_vecs(0);

  for(int i=0; i<DIMENSION; i++){

    std::vector<scalar_type> b_vec;
    for(int j=0; j<DIMENSION; j++)
      b_vec.push_back(basis[j+i*DIMENSION]);

    basis_vecs.push_back(b_vec);
  }

  for(int i=0; i<elements.size(); i++){
    for(int j=0; j<elements.size(); j++){
	    
      A(i,j) = -1;
      
      std::vector<scalar_type>& x_i = elements[i];
      std::vector<scalar_type>& x_j = elements[j];
      
      std::vector<scalar_type> x_i_plus_x_j = x_i;
      for(int d=0; d<x_i_plus_x_j.size(); d++)
	x_i_plus_x_j[d] += x_j[d];
      
      x_i_plus_x_j = cluster_operations::translate_inside_cluster(x_i_plus_x_j, basis_vecs);

      A(i,j) = cluster_operations::index(x_i_plus_x_j, elements);

      if(A(i,j)==-1)
	throw std::logic_error(__FUNCTION__);
    }
  }

  //A.print();
}

template<typename scalar_type, CLUSTER_NAMES NAME, CLUSTER_SHAPE SHAPE>
void cluster_domain_initializer<dmn_0<cluster_domain<scalar_type, NAME, REAL_SPACE, SHAPE> > >::initialize_subtract(scalar_type*                            basis,
														    std::vector<std::vector<scalar_type> >& elements,
														    LIN_ALG::matrix<int, LIN_ALG::CPU>&     A)
{
  //cout << __FUNCTION__ << endl;

  int DIMENSION = r_dmn::DIMENSION;

  std::vector<std::vector<scalar_type> > basis_vecs(0);

  for(int i=0; i<DIMENSION; i++){

    std::vector<scalar_type> b_vec;
    for(int j=0; j<DIMENSION; j++)
      b_vec.push_back(basis[j+i*DIMENSION]);

    basis_vecs.push_back(b_vec);
  }

  for(int i=0; i<elements.size(); i++){
    for(int j=0; j<elements.size(); j++){
	    
      A(i,j) = -1;
      
      std::vector<scalar_type>& x_i = elements[i];
      std::vector<scalar_type>& x_j = elements[j];
      
      std::vector<scalar_type> x_j_min_x_i = x_j;
      for(int d=0; d<DIMENSION; d++)
	x_j_min_x_i[d] -= x_i[d];
      
      x_j_min_x_i = cluster_operations::translate_inside_cluster(x_j_min_x_i, basis_vecs);

      A(i,j) = cluster_operations::index(x_j_min_x_i, elements);

      if(A(i,j)==-1)
	throw std::logic_error(__FUNCTION__);
    }
  }
}

#endif
