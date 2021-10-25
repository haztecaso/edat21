CC = g++
CCFLAGS = -O1
OUT = bin
TADS = tads
TESTS = tests

build: tests calculadora

calculadora: $(OUT)/calculadora
$(OUT)/calculadora: calculadora/calculadora.cpp
	$(MAKE) -C calculadora

_TESTS = test_pila test_pila_static test_cola test_cola_static
tests: $(patsubst %,$(OUT)/%,$(_TESTS))

$(OUT)/test_%: $(TESTS)/test_%.cpp $(TESTS)/test_utils.hpp $(TADS)/%.hpp $(TADS)/basicos.hpp
	$(CC) $(CCFLAGS) $< -o $@ -I$(TADS)

$(OUT)/test_%_static: $(TESTS)/test_%.cpp $(TESTS)/test_utils.hpp $(TADS)/%_static.hpp $(TADS)/basicos.hpp
	$(CC) $(CCFLAGS) -D STATIC $< -o $@ -I$(TADS)

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
