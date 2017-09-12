#tested on: Ubuntu 16.04, mac os 10.12 (sierra)

src = $(shell find src/ -name "*.cpp")
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

#if empty disables CUDA
CUDAPATH	= /usr/local/cuda


LPATHS          = -L/usr/local/lib -L/usr/lib
LIBRARIES       = -llog4cpp -lm -lpthread $(shell pkg-config --libs fftw3) $(shell pkg-config --libs fftw3f) $(shell pkg-config --libs Magick++) -fopenmp
INCLUDES        = -I/usr/local/include -I/usr/include $(shell pkg-config --cflags-only-I ImageMagick)

ifeq ($(CUDAPATH), )
CUDAFLAG        =
else
CUDAFLAG	= -DCHI2CUDA
LPATHS         += -L$(CUDAPATH)/lib64
LIBRARIES      += -lChi2HD_Cuda -lcufft -lcudart
INCLUDES       += -I$(CUDAPATH)/include
endif

CFLAGS		= $(CUDAFLAG) -O3 -march=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -fmessage-length=0 -MMD -MP $(shell pkg-config --cflags-only-other ImageMagick)

all: Ptrack2

Ptrack2: $(obj)
	@echo 'Starting PTRACK2 compilation'
	$(CXX) $(LPATHS) -o $@ $^ $(LIBRARIES)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CFLAGS) -c -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

clean:
	rm -f $(obj) $(dep) Ptrack2

cleandep:
	rm -f $(dep)

