CC = g++
OUT = bin
TADS = tads
TESTS = tests

all: tests sc

sc: $(OUT)/sc
$(OUT)/sc: sc/sc.cpp
	$(MAKE) -C sc

_TESTS = test_pila test_pila_int test_pila_int_static test_cola
tests: $(patsubst %,$(OUT)/%,$(_TESTS))
$(OUT)/test_%: $(TESTS)/test_%.cpp $(TADS)/%.hpp  $(TADS)/basicos.hpp
	$(CC) $< -o $@ -I$(TADS)

mkdirs:
	mkdir -p $(OUT)

.PHONY: clean
clean:
	rm -r $(OUT)/*
