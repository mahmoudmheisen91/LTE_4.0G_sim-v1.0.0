CC=gcc
LIBS=-lm -lsndfile
OBJ = main.c gnuplot_i.c phy_layer.c resources.c

lte_simulator: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

