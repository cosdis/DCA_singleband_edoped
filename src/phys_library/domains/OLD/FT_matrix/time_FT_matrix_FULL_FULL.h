//-*-C++-*-

/*
 *      Author: peterstaar
 */

#ifndef TIME_FT_MATRIX_FULL_FULL_H_
#define TIME_FT_MATRIX_FULL_FULL_H_

#include "time_domain.h"
#include "frequency_domain.h"
#include <complex>
#include <math.h>

using namespace std;

template<class parameters>
class time_FT_matrix<parameters, FULL, FULL>
{
public:
  
  static std::complex<double>* get_matrix();
  static std::complex<double>* get_matrix_inverse();

private:

  static std::complex<double>* initialize();
  static std::complex<double>* initialize_inverse();

};

template<class parameters>
std::complex<double>* time_FT_matrix<parameters, FULL, FULL>::get_matrix()
{
  static std::complex<double>* matrix = initialize();
  return matrix;
}

template<class parameters>
std::complex<double>* time_FT_matrix<parameters, FULL, FULL>::get_matrix_inverse()
{
  static std::complex<double>* matrix = initialize_inverse();
  return matrix;
}

template<class parameters>
std::complex<double>* time_FT_matrix<parameters, FULL, FULL>::initialize()
{
  // t --> w
  int time_size = time_domain<FULL, parameters>::get_size();
  int freq_size = frequency_domain<FULL, parameters>::get_size();

  static std::complex<double>* matrix_ptr = new std::complex<double>[time_size*freq_size];

  for(int i=0; i<freq_size; i++){
    for(int j=0; j<time_size; j++){

      double w = frequency_domain<FULL, parameters>::get_elements()[i];
      double t = time_domain<FULL, parameters>::get_elements()[j];

      std::complex<double> c(cos(w*t),sin(w*t));
      matrix_ptr[i + freq_size*j] = c;
    }
  }

  return matrix_ptr;
}

template<class parameters>
std::complex<double>* time_FT_matrix<parameters, FULL, FULL>::initialize_inverse()
{
  // w --> t

  int time_size = time_domain<FULL, parameters>::get_size();
  int freq_size = frequency_domain<FULL, parameters>::get_size();

  static std::complex<double>* matrix_ptr = new std::complex<double>[time_size*freq_size];

  for(int i=0; i<time_size; i++){
    for(int j=0; j<freq_size; j++){

      double t = time_domain<FULL, parameters>::get_elements()[i];
      double w = frequency_domain<FULL, parameters>::get_elements()[j];

      std::complex<double> c(cos(w*t),-sin(w*t));
      matrix_ptr[i + time_size*j] = c/parameters::beta;
    }
  }

  return matrix_ptr;
}

#endif
