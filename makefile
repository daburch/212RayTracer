CC	= g++

INCLUDE	= -I.

#CFLAGS	= -g -m32 -DDEBUG
CFLAGS	= -g -m32 -fopenmp

LDFLAGS = \
  -L. \
  -L/usr/lib

LDLIBS	= \
  -lc -lm

.cpp.o:
	$(CC) -c $(INCLUDE) $(CFLAGS) $<

SRCS = \
vector.cpp \
list.cpp \
pixel.cpp \
material.cpp \
object.cpp \
plane.cpp \
sphere.cpp \
model.cpp \
camera.cpp \
light.cpp \
ray.cpp \
timer.cpp \
main.cpp

OBJS = $(SRCS:.cpp=.o)

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *.o core
	rm -f *.a
	rm -f main
	rm -f *.ps *.pdf

depend: $(SRCS)
	makedepend -- $(CLFAGS) -- $(SRCS)
#	gccmakedep -- $(CFLAGS) -- $(SRCS)

ENSCRIPTFLAGS = \
  --fancy-header=mya2ps \
  --columns=1 \
  --pretty-print=makefile \
  --ul-font=Times-Roman100 \
  --underlay="asg01" \
  --portrait

PS2PDFFLAGS = \
  -dCompatibilityLevel=1.3 \
  -dMaxSubsetPct=100 \
  -dSubsetFonts=true \
  -dEmbedAllFonts=true \
  -dAutoFilterColorImages=false \
  -dAutoFilterGrayImages=false \
  -dColorImageFilter=/FlateEncode \
  -dGrayImageFilter=/FlateEncode \
  -dMonoImageFilter=/FlateEncode

ps:
	enscript $(ENSCRIPTFLAGS) Makefile -p makefile.ps
	enscript $(ENSCRIPTFLAGS) *.h -p interface.ps
	enscript $(ENSCRIPTFLAGS) *.c* -p implementation.ps

pdf:
	ps2pdf $(PS2PDFFLAGS) makefile.ps
	ps2pdf $(PS2PDFFLAGS) interface.ps
	ps2pdf $(PS2PDFFLAGS) implementation.ps

# DO NOT DELETE

vector.o: vector.h
list.o: vector.h pixel.h light.h material.h object.h list.h
pixel.o: pixel.h
material.o: pixel.h material.h
object.o: vector.h pixel.h material.h object.h
plane.o: vector.h pixel.h material.h object.h plane.h
sphere.o: vector.h pixel.h material.h object.h sphere.h
model.o: vector.h pixel.h material.h object.h list.h plane.h sphere.h light.h
model.o: camera.h model.h
camera.o: vector.h pixel.h camera.h
light.o: vector.h pixel.h light.h
ray.o: vector.h pixel.h camera.h light.h material.h object.h list.h plane.h
ray.o: model.h ray.h
timer.o: /usr/include/sys/time.h /usr/include/sys/feature_tests.h
timer.o: /usr/include/sys/ccompile.h /usr/include/sys/isa_defs.h
timer.o: /usr/include/sys/types.h /usr/include/sys/machtypes.h
timer.o: /usr/include/ia32/sys/machtypes.h /usr/include/sys/int_types.h
timer.o: /usr/include/sys/select.h /usr/include/sys/time_impl.h
timer.o: /usr/include/sys/time.h timer.h
main.o: /usr/include/omp.h vector.h pixel.h camera.h light.h material.h
main.o: object.h list.h plane.h model.h ray.h timer.h
