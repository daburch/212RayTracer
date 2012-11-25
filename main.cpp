#include <omp.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>

#include "vector.h"
#include "pixel.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "object.h"
#include "list.h"
#include "plane.h"
#include "model.h"
#include "ray.h"
#include "timer.h"

// prototypes
int  main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	model_t		model;		// model (the world)
	std::ifstream	model_ifs;	// input file stream
	atd::timer_t	timer;

  if(argc != 2) {
    std::cerr << "Usage " << argv[0] << " <model_file>" << std::endl;
    return 1;
  }

  // open file, read in model
  model_ifs.open(argv[1],std::ifstream::in);
  model_ifs >> model;
  model_ifs.close();

  // debugging
  std::cerr << model;

	int		tid,ncores=1;
	int		w=model.getpixel_w(), h=model.getpixel_h();
	int		chunk;
	double		wx,wy,wz=0.0;
	double		ww=model.getworld_w(), wh=model.getworld_h();
	vec_t		pos=model.getviewpoint();
	vec_t		pix,dir;
	ray_t		*ray=NULL;
	rgb_t<double>	color;
	rgb_t<uchar>	*imgloc,*img=NULL;

  img = new rgb_t<uchar>[w*h];
  memset(img,0,3*w*h);

  // figure out how many threads we have available, then calculate chunk,
  // splitting up the work as evenly as possible
  #pragma omp parallel private(tid)
  {
    if((tid = omp_get_thread_num())==0)
      ncores = omp_get_num_threads();
  }
  chunk = h/ncores;

  timer.start();

// two statements...
//#pragma omp parallel \
//          shared(model,w,h,ww,wh,wz,pos,img) \
//          private(tid,wx,wy,pix,dir,ray,color,imgloc)
//#pragma omp for schedule(static,chunk)

// ...or all-in-one
  #pragma omp parallel for \
            shared(model,w,h,ww,wh,wz,pos,img) \
            private(tid,wx,wy,pix,dir,ray,color,imgloc) \
            schedule(static,chunk)
  for(int y=h-1;y>=0;y--) {
    for(int x=0;x<w;x++) {
      wx = (double)x/(double)(w-1) * ww;
      wy = (double)y/(double)(h-1) * wh;

      // set pixel position vector (in world coordinates)
      pix = vec_t(wx,wy,wz);

      // compute the vector difference  v3 = v2 - v1
      dir = pix - pos;

      // our ray is now {pos, dir} (in world coordinates), normalize dir
      dir = dir.norm();

      // zero out color
      color.zero();

      // spawn new ray
      ray = new ray_t(pos,dir);

      // trace ray
      ray->trace(model, color, 0);

      // nuke this ray, we don't need it anymore, prevent memory leak
      delete ray;

      // where are we in the image (using old i*c + j)
      imgloc = img + y*w + x;

      // scale pixel by maxval, store at dereferenced image location
      for(int i=0;i<3;i++) (*imgloc)[i] = static_cast<uchar>(255.0 * color[i]);
    }
  }
  timer.end();

  std::cerr << "cores: " << ncores << ", ";
  std::cerr << "time: " << timer.elapsed_ms() << " ms" << std::endl;

  // output image
  std::cout << "P6 " << w << " " << h << " " << 255 << std::endl;
  for(int y=h-1;y>=0;y--) {
    for(int x=0;x<w;x++) {
      imgloc = img + y*w + x;
      std::cout.write((char *)imgloc,3);
    }
  }

  return 0;
}
