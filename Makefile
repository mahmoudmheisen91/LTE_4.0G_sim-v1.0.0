# define the C compiler to use:
CC = gcc

# define any compile-time flags:
CFLAGS = -c -Wall

# define any directories containing header files other than /usr/include:
INCLUDES = -I$(shell pwd)/incs

# define library paths in addition to /usr/lib:
LFLAGS =

# define any libraries to link into executable:
LIBS = -lm -lsndfile

# define the C source files:
SOURCES = main.c gnuplot_i.c phy_layer.c resources.c

# define the C header files:
HEADERS = gnuplot_i.h phy_layer.h resources.h LTE_err.h

# define the C object files:
OBJECTS = $(SOURCES:.c=.o)

# define the executable file:
EXECUTABLE = lte_simulator

LTE: $(SOURCES) $(EXECUTABLE)

# build executable:
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS) $(INCLUDES) $(LFLAGS)

# replacement rule for building .o's from .c's:
.c.o:
	$(CC) -o $@ $< $(CFLAGS) $(INCLUDES)

# clean command: remove object files:
clean:
	$(RM) *.o *~ $(EXECUTABLE)

