#ifndef MATERIAL_H
#define MATERIAL_H

#define MAT_COOKIE 32456123

class material_t
{
  public:
  // constructors (overloaded)
  material_t() : \
	cookie(MAT_COOKIE), \
	ambient(0.0,0.0,0.0), \
	diffuse(0.0,0.0,0.0), \
	specular(0.0,0.0,0.0), \
	alpha(0.0), \
	ior(0.0) \
	{ };

  // copy constructor
  material_t(const material_t& rhs) : \
	cookie(rhs.cookie), \
	name(rhs.name), \
	ambient(rhs.ambient), \
	diffuse(rhs.diffuse), \
	specular(rhs.specular) \
	{ };

  // destructors (default ok, no 'new' in constructor)
  ~material_t()
	{ };

  // operators (incl. assignment operator)
  const material_t& operator=(const material_t& rhs)
	{
	  if(this != &rhs) {
	    cookie = rhs.cookie;
	    name = rhs.name;
	    ambient = rhs.ambient;
	    diffuse = rhs.diffuse;
	    specular = rhs.specular;
	  }
          return *this;
	}

  // friends
  friend std::ostream& operator<<(std::ostream& s, const material_t& rhs);
  friend std::ostream& operator<<(std::ostream& s, material_t *rhs)
		{ return(s << (*rhs)); }

  friend std::istream& operator>>(std::istream& s, material_t& rhs);
  friend std::istream& operator>>(std::istream& s, material_t *rhs)
		{ return(s >> (*rhs)); }

  // methods
  int		getcookie()	{ return cookie; }
  std::string	getname()	{ return name; }
  rgb_t<double>	getamb()	{ return ambient; }
  rgb_t<double>	getdiff()	{ return diffuse; }
  rgb_t<double>	getspec()	{ return specular; }
  float		getAlpha()	{ return alpha;	}
  float		getIor()	{ return ior; }


  private:
  int		cookie;		// magic number
  std::string	name;		// material name
  rgb_t<double>	ambient;	// ambient color
  rgb_t<double>	diffuse;	// diffuse color
  rgb_t<double>	specular;	// specular color
  float		alpha;		// alpha value
  float		ior;		// ior value
};

#endif
