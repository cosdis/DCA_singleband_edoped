//-*-C++-*-

/* 
 * 	 This is a C++ file generated by write_union_domains.py 
 *
 * 	 author: Peter Staar  
 */ 


#ifndef UNION_11_H_
#define UNION_11_H_

#include "domain.h"   
#include "type_list.h"   
#include "type_list_definitions.h"   

using namespace TL; 


template< typename domain_0_t,
		  typename domain_1_t,
		  typename domain_2_t,
		  typename domain_3_t,
		  typename domain_4_t,
		  typename domain_5_t,
		  typename domain_6_t,
		  typename domain_7_t,
		  typename domain_8_t,
		  typename domain_9_t,
		  typename domain_10_t>
class union_11 : public domain 
{

public:
 
 	typedef typename domain_0_t::this_type domain_typelist_0;
	typedef typename domain_1_t::this_type domain_typelist_1;
	typedef typename domain_2_t::this_type domain_typelist_2;
	typedef typename domain_3_t::this_type domain_typelist_3;
	typedef typename domain_4_t::this_type domain_typelist_4;
	typedef typename domain_5_t::this_type domain_typelist_5;
	typedef typename domain_6_t::this_type domain_typelist_6;
	typedef typename domain_7_t::this_type domain_typelist_7;
	typedef typename domain_8_t::this_type domain_typelist_8;
	typedef typename domain_9_t::this_type domain_typelist_9;
	typedef typename domain_10_t::this_type domain_typelist_10;
	
	typedef typename Append<domain_typelist_0, typename Append<domain_typelist_1, typename Append<domain_typelist_2, typename Append<domain_typelist_3, typename Append<domain_typelist_4, typename Append<domain_typelist_5, typename Append<domain_typelist_6, typename Append<domain_typelist_7, typename Append<domain_typelist_8, typename Append<domain_typelist_9, domain_typelist_10>::Result >::Result >::Result >::Result >::Result >::Result >::Result >::Result >::Result >::Result  this_type;
 
 	union_11();
 
 	void reset(); 
 
 	int operator()(int l);

protected:

	domain_0_t domain_0;
	domain_1_t domain_1;
	domain_2_t domain_2;
	domain_3_t domain_3;
	domain_4_t domain_4;
	domain_5_t domain_5;
	domain_6_t domain_6;
	domain_7_t domain_7;
	domain_8_t domain_8;
	domain_9_t domain_9;
	domain_10_t domain_10;

};



template< typename domain_0_t,
		  typename domain_1_t,
		  typename domain_2_t,
		  typename domain_3_t,
		  typename domain_4_t,
		  typename domain_5_t,
		  typename domain_6_t,
		  typename domain_7_t,
		  typename domain_8_t,
		  typename domain_9_t,
		  typename domain_10_t>
union_11<domain_0_t, domain_1_t, domain_2_t, domain_3_t, domain_4_t, domain_5_t, domain_6_t, domain_7_t, domain_8_t, domain_9_t, domain_10_t>::union_11():
	domain(),
	domain_0(),
	domain_1(),
	domain_2(),
	domain_3(),
	domain_4(),
	domain_5(),
	domain_6(),
	domain_7(),
	domain_8(),
	domain_9(),
	domain_10()
{

	size = domain_0.get_size() + domain_1.get_size() + domain_2.get_size() + domain_3.get_size() + domain_4.get_size() + domain_5.get_size() + domain_6.get_size() + domain_7.get_size() + domain_8.get_size() + domain_9.get_size() + domain_10.get_size();
	
	branch_domain_sizes.push_back(size);
	leaf_domain_sizes.push_back(size);
}

template< typename domain_0_t,
		  typename domain_1_t,
		  typename domain_2_t,
		  typename domain_3_t,
		  typename domain_4_t,
		  typename domain_5_t,
		  typename domain_6_t,
		  typename domain_7_t,
		  typename domain_8_t,
		  typename domain_9_t,
		  typename domain_10_t>
void union_11<domain_0_t, domain_1_t, domain_2_t, domain_3_t, domain_4_t, domain_5_t, domain_6_t, domain_7_t, domain_8_t, domain_9_t, domain_10_t>::reset()
{
domain::reset();

domain_0.reset();
domain_1.reset();
domain_2.reset();
domain_3.reset();
domain_4.reset();
domain_5.reset();
domain_6.reset();
domain_7.reset();
domain_8.reset();
domain_9.reset();
domain_10.reset();


	size = domain_0.get_size() + domain_1.get_size() + domain_2.get_size() + domain_3.get_size() + domain_4.get_size() + domain_5.get_size() + domain_6.get_size() + domain_7.get_size() + domain_8.get_size() + domain_9.get_size() + domain_10.get_size();
	
branch_domain_sizes.resize(0);
branch_domain_sizes.push_back(size);

leaf_domain_sizes.resize(0);
leaf_domain_sizes.push_back(size);
}

template< typename domain_0_t,
		  typename domain_1_t,
		  typename domain_2_t,
		  typename domain_3_t,
		  typename domain_4_t,
		  typename domain_5_t,
		  typename domain_6_t,
		  typename domain_7_t,
		  typename domain_8_t,
		  typename domain_9_t,
		  typename domain_10_t>
int union_11<domain_0_t, domain_1_t, domain_2_t, domain_3_t, domain_4_t, domain_5_t, domain_6_t, domain_7_t, domain_8_t, domain_9_t, domain_10_t>::operator()(int l)
{
	 assert(l>=0 && l<size);
	 return l;
}

#endif
