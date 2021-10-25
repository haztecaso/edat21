CC = g++
OUT = ../bin
TADS = ../tads

all: $(OUT)/parentesis_equilibrados $(OUT)/pilas_de_pilas

$(OUT)/parentesis_equilibrados: parentesis_equilibrados.cpp $(TADS)/pila.hpp
	$(CC) $< -o $@ -I $(TADS)

$(OUT)/pilas_de_pilas: pilas_de_pilas.cpp $(TADS)/pila.hpp
	$(CC) $< -o $@ -I $(TADS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o $(OUT)/*
