CC = g++
OUT = ../bin
TADS = ../tads

$(OUT)/sc: sc.cpp $(TADS)/pila.hpp
	$(CC) $< -o $@ -I $(TADS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o $(OUT)/*
