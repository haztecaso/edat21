CC = g++
OUT = bin
TADS = tads
TESTS = tests

build: tests calculadora

calculadora: $(OUT)/calculadora
$(OUT)/calculadora: calculadora/calculadora.cpp
	$(MAKE) -C calculadora

_TESTS = test_pila test_pila_static test_pila_int test_pila_int_static\
		 test_cola test_cola_static
tests: $(patsubst %,$(OUT)/%,$(_TESTS))
$(OUT)/test_%: $(TESTS)/test_%.cpp $(TADS)/%.hpp  $(TADS)/basicos.hpp
	$(CC) $< -o $@ -I$(TADS)

.PHONY: test test_%
test: $(_TESTS)
test_%: $(OUT)/test_%
	./$<

.PHONY: mkdirs
mkdirs:
	mkdir -p $(OUT)

.PHONY: clean
clean:
	rm -r $(OUT)/*
