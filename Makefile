CC = g++
OUT = bin
TADS = tads
TESTS = tests

_TESTS = test_pila test_pila_int test_pila_int_static test_cola
tests: $(patsubst %,$(OUT)/%,$(_TESTS))

$(OUT)/test_%: $(TESTS)/test_%.cpp $(TADS)/%.hpp  $(TADS)/basicos.hpp
	$(CC) -o $@ $<

# Make directories
mkdirs:
	mkdir -p $(OUT) $(OBJS)

# Clean bins and objs
.PHONY: clean
clean:
	rm -r $(ODIR)/*.o $(OUT)/*
