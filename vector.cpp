#include <iostream>
#include <cmath>

#include "vector.h"

// compute the dot product of two vectors
double vec_t::dot(const vec_t& rhs) const
{
	double	s=0.0;

  for(int i=0;i<3;i++) s += vec[i] * rhs[i];

  return(s);
}

// compute the length of the vector v1
double vec_t::len() const
{
  return(sqrt(dot(*this)));
}

// compute the dot product of two vectors
vec_t vec_t::norm() const
{
	vec_t	result(*this);
	double	length = len();

  for(int i=0;i<3;i++) result[i] /= length;

  return(result);
}

// compute the reflection vector: v = u - 2 (u dot n) n
vec_t vec_t::reflect(const vec_t& n) const
{
	vec_t	u(*this);
	vec_t	result;

  // u - 2 (u dot n) n
  result = u - 2.0 * u.dot(n) * n;

  return result;
}

// refract a giver vector about n
vec_t vec_t::refract(const vec_t& n, double n_t) const {

  vec_t u(*this);
  vec_t result;
  double n_i = 1.000293;		// refraction index of air
  double ndotu = u.dot(n);		// direction dotted with normal
  double nior = n_i / n_t;		// n_i divided by the refraction index of the object
  double d = 1.0 - (nior * nior * (1.0 - ndotu * ndotu));
  
  // TIR
  if(d < 0)
	result = u.reflect(n);
  else
	result = (nior * (u - (ndotu * n))) - (sqrt(d) * n);
	
  return result;
}
