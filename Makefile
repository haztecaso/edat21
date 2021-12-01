CC = g++
CCFLAGS = -O1 -Wall -Wextra -Wshadow -Wdouble-promotion -Werror
OUT = bin

TESTS = test_pila test_pila_static test_cola test_cola_static test_lista test_abb
PROGRAMAS = calculadora parentesis_equilibrados pilas_de_pilas abb_diagrama quicksort_secuencia

build: tests programas

programas: mkdirs $(patsubst %,$(OUT)/%,$(PROGRAMAS))
$(OUT)/%: programas/%.cpp tads/*.hpp
	$(CC) $(CCFLAGS) $< -I tads -o $@

tests: mkdirs $(patsubst %,$(OUT)/%,$(TESTS))
$(OUT)/test_%: tests/test_%.cpp tests/test_utils.hpp tads/%.hpp tads/basicos.hpp
	$(CC) $(CCFLAGS) $< -I tads -o $@
$(OUT)/test_%_static: tests/test_%.cpp tests/test_utils.hpp tads/%_static.hpp tads/basicos.hpp
	$(CC) $(CCFLAGS) -D STATIC $< -I tads -o $@

.PHONY: test test_%
test: $(TESTS)
test_%: $(OUT)/test_%
	./$<

.PHONY: mkdirs
mkdirs:
	@mkdir -p $(OUT)

.PHONY: clean
clean:
	@rm -r $(OUT)
