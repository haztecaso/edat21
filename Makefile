CC = g++
CCFLAGS = -O1
OUT = bin
TADS = tads
TESTS = tests

build: tests programas

_PROGRAMAS = parentesis_equilibrados pilas_de_pilas calculadora
programas: mkdirs $(patsubst %,$(OUT)/%,$(_PROGRAMAS))
$(OUT)/%: programas/%.cpp $(TADS)/*.hpp
	$(CC) $(CCFLAGS) $< -o $@ -I $(TADS)

_TESTS = test_pila test_pila_static test_cola test_cola_static
tests: mkdirs $(patsubst %,$(OUT)/%,$(_TESTS))
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
	@mkdir -p $(OUT)

.PHONY: clean
clean:
	@rm -r $(OUT)
