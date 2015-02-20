# define the C compiler to use:
CC = gcc

# define any compile-time flags:
CFLAGS = -c -Wall

# define any directories containing header files other than /usr/include:
INCLUDES = -I$(shell pwd)/inc -I$(shell pwd)/data

# define library paths in addition to /usr/lib:
LFLAGS =

# define any libraries to link into executable:
LIBS = -lm -lsndfile

# define paths for .c files:
vpath %.c $(shell pwd)/src

# define the C source files:
SOURCES = main.c gnuplot_i.c phy_layer.c resources.c \
	  statics.c plots.c lte_adc.c interleaver.c \
	  lte_turbo_encoder.c generators.c modulation.c

# define the C object files:
OBJECTS = $(patsubst %.c,obj/%.o,$(SOURCES))

# define the executable file:
EXECUTABLE = lte_simulator

LTE: $(SOURCES) $(EXECUTABLE)

# build executable:
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDES) $(LIBS) $(LFLAGS)

# if any OBJECTS must be built then obj must be built first:
$(OBJECTS): | obj

# replacement rule for building .o's from .c's:
obj/%.o : %.c
	$(CC) -o $@ $< $(CFLAGS) $(INCLUDES)

# run command:
run:
	./$(EXECUTABLE)

# clean command: remove object files:
clean:
	$(RM) $(shell pwd)/obj/*.o 
	$(RM) $(shell pwd)/src/*~ 
	$(RM) *~ $(EXECUTABLE)

