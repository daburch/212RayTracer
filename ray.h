#ifndef RAY_H
#define RAY_H

#define MAX_DIST 100

class ray_t
{
  public:
  // constructors (overloaded)
  ray_t() : \
	dis(0.0), \
	pos(0.0,0.0,0.0), \
	dir(0.0,0.0,0.0) \
	{ };

  ray_t(const vec_t& o, const vec_t& d, double r=0.0) : \
	dis(r), \
	pos(o), \
	dir(d) \
	{ };

  // copy constructor
  ray_t(const ray_t& rhs) : \
	dis(rhs.dis), \
	pos(rhs.pos), \
	dir(rhs.dir) \
	{ };

  // operators (incl. assignment operator)
  const ray_t& operator=(const ray_t& rhs)
	{
	  if(this != &rhs) {
	    dis = rhs.dis;
	    pos = rhs.pos;
	    dir = rhs.dir;
	  }
          return *this;
	}

  // methods
  void trace(model_t&, rgb_t<double>&, int);

  // destructors (default ok, no 'new' in constructor)
  ~ray_t()
	{ };

  private:
  double   dis;	// distance
  vec_t    pos;	// position
  vec_t    dir;	// direction
};

#endif
