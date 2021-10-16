# Estructuras de datos (21/22)

Repositorio con ejercicios y entregas de la asignatura **Estructuras de datos** del
curso 2021/2022.

## Organización 

- `tads`: este directorio contiene las implementaciones de los *TAD*s que hemos
  dado en la asignatura.
- `tests`: este directorio contiene algunos códigos útiles para comprobar que
  las implementaciones funcionan correctamente.
- El fichero `Makefile` contiene las reglas de compilación del código fuente y
  linkeado de los binarios.

## Compilación

La manera mas cómoda de compilar los códigos de este repositorio es usando
[*GNU Make*](https://www.gnu.org/software/make/), cuyas opciones están en el
fichero `Makefile`. Además será necesario tener instalado el compilador
[*GCC*](https://www.gnu.org/software/gcc/).

Antes de empezar a compilar es necesario crear las carpetas `bin` y `obj`, por
ejemplo mediante el comando `make dirs`.

Para compilar un test, por ejemplo el fichero `test/test_pila.cpp`, podemos
ejecutar el comando:
```
make test_pila
```
Esto creará el binario `bin/test_pila` que podemos ejecutar directamente desde
la línea de comandos:
```
./bin/test_pila
```
