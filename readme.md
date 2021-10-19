# Estructuras de datos 2021

![make](https://github.com/haztecaso/edat21/actions/workflows/make.yml/badge.svg)

Repositorio con ejercicios y entregas de la asignatura **Estructuras de datos** del
curso 2021/2022.

## Organización 

- `tads`: este directorio contiene las implementaciones de los *TAD*s que hemos
  dado en la asignatura. Cada implementación se encuentra en un fichero con
  extensión `.hpp`.
- `tests`: este directorio contiene algunos códigos útiles para comprobar que
  las implementaciones funcionan correctamente.
- El fichero `Makefile` contiene las reglas de compilación del código fuente y
  linkeado de los binarios.

## Compilación

La manera mas cómoda de compilar los códigos de este repositorio es usando
[*GNU Make*](https://www.gnu.org/software/make/), cuyas opciones están en el
fichero `Makefile`. Además será necesario tener instalado el compilador
[*GCC*](https://www.gnu.org/software/gcc/).

Antes de empezar a compilar es necesario crear la carpeta `bin` y , por
ejemplo mediante el comando `make dirs` o `mkdir -p bin`.

Para compilar los tests podemos ejecutar el comando `make tests`. Esto creará el
binario `bin/test_pila` que podemos ejecutar directamente desde la línea de
comandos: `./bin/test_pila`.

### Manualmente

```
g++ -o bin/test_pila tests/test_pila.cpp -Itads
```
