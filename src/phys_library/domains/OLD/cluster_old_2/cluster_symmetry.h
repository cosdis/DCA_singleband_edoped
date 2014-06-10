//-*-C++-*-

#ifndef CLUSTER_SYMMETRY_H
#define CLUSTER_SYMMETRY_H

/*!
 *  \author Peter Staar
 */
template<typename cluster_type>
class cluster_symmetry
{};

/*!
 *  \author Peter Staar
 */
template<typename base_cluster>
class cluster_symmetry<r_cluster<FULL,  base_cluster> >
{
public:

  typedef r_cluster<FULL,  base_cluster> cluster_type;

  typedef dmn_0<electron_band_domain> b_dmn_t;
  typedef dmn_0<cluster_type>         c_dmn_t;

//   typedef typename cluster_type::base_cluster      base_cluster;

//   typedef typename cluster_type  ::parameter_type  parameter_type;
//   typedef typename parameter_type::point_group     point_group_type;

  typedef dmn_0<point_group_symmetry_domain<UNIT_CELL , base_cluster> > sym_unit_cell_dmn_t;
  typedef dmn_0<point_group_symmetry_domain<SUPER_CELL, base_cluster> > sym_super_cell_dmn_t;

  typedef dmn_2< dmn_2<c_dmn_t,b_dmn_t>, sym_super_cell_dmn_t> symmetry_matrix_dmn_t;

public:

  static function<std::pair<int,int>, symmetry_matrix_dmn_t>& get_symmetry_matrix(){
    static function<std::pair<int,int>, symmetry_matrix_dmn_t> symmetry_matrix("r_symmetry_matrix_super_cell");
    return symmetry_matrix;
  }

};

/*!
 *  \author Peter Staar
 */
template<typename base_cluster>
class cluster_symmetry<k_cluster<FULL,  base_cluster> >
{
public:

  typedef k_cluster<FULL,  base_cluster> cluster_type;

  typedef dmn_0<electron_band_domain> b_dmn_t;
  typedef dmn_0<cluster_type>         c_dmn_t;

//   typedef typename cluster_type::base_cluster      base_cluster;

//   typedef typename cluster_type  ::parameter_type  parameter_type;
//   typedef typename parameter_type::point_group     point_group_type;

  typedef dmn_0<point_group_symmetry_domain<UNIT_CELL , base_cluster> > sym_unit_cell_dmn_t;
  typedef dmn_0<point_group_symmetry_domain<SUPER_CELL, base_cluster> > sym_super_cell_dmn_t;

  typedef dmn_2< dmn_2<c_dmn_t,b_dmn_t>, sym_super_cell_dmn_t> symmetry_matrix_dmn_t;

public:

  static function<std::pair<int,int>, symmetry_matrix_dmn_t>& get_symmetry_matrix(){
    static function<std::pair<int,int>, symmetry_matrix_dmn_t> symmetry_matrix("k_symmetry_matrix_super_cell");
    return symmetry_matrix;
  }

};


#endif
