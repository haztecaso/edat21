CC = g++
OUT = bin
ODIR = obj
TADS = tads
TESTS = tests

all: tests

#TODO: arreglar tests targets para que no se regeneren innecesariamente
tests: test_pila test_pila_int test_pila_int_static test_cola

test_pila: $(TESTS)/test_pila.cpp $(TADS)/pila.hpp
	$(CC) -o $(OUT)/$@ $<

test_pila_int: $(TESTS)/test_pila_int.cpp $(ODIR)/pila_int.o
	$(CC) -o $(OUT)/$@ $< $(ODIR)/pila_int.o

test_pila_int_static: $(TESTS)/test_pila_int_static.cpp $(ODIR)/pila_int_static.o
	$(CC) -o $(OUT)/$@ $< $(ODIR)/pila_int_static.o

test_cola: $(TESTS)/test_cola.cpp $(TADS)/cola.hpp
	$(CC) -o $(OUT)/$@ $<

# Object files
$(ODIR)/%.o: $(TADS)/%.cpp $(TADS)/%.hpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

# Make directories
dirs:
	mkdir -p $(OUT) $(OBJS)

# Clean bins and objs
.PHONY: clean clean_bin clean_obj

clean: clean_obj clean_bin

clean_bin:
	rm $(OUT)/*
clean_obj:
	rm $(ODIR)/*.o
