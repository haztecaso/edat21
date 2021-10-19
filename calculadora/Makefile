CC = g++
OUT = ../bin
TADS = ../tads

$(OUT)/calculadora: calculadora.cpp $(TADS)/pila.hpp
	$(CC) $< -o $@ -I $(TADS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o $(OUT)/*
