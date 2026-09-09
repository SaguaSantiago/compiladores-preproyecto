# Preproyecto - Compiladores
## Integrantes

- Brizuela Paloma
- Lillo Lucas
- Sagua Santiago

## Requisitos

Para compilar el proyecto se necesitan:

- GCC
- GNU Make
- Flex
- Bison

## Compilacion

Desde la carpeta raiz del repositorio, ejecutar:

```bash
make
```

Esto genera el ejecutable `compilador` y, si es necesario, regenera los archivos de Flex y Bison.

## Ejecucion

El programa recibe el codigo desde `input.txt`. Para compilar y ejecutarlo:

```bash
make run
```

Tambien se puede ejecutar directamente:

```bash
./compilador < input.txt
```

La salida generada se guarda en `output.txt`.

## Archivos principales

- `lex.l`: reglas del analizador lexico.
- `bisson.y`: reglas del analizador sintactico y acciones semanticas.
- `ASTdef.h` y `ASTdef.c`: definicion y construccion del AST.
- `TSdef.h` y `TSdef.c`: tabla de simbolos.
- `interprete.c` y `interprete.h`: ejecucion del AST.
- `generadorAssembly.c` y `generadorAssembly.h`: generacion de salida.
- `main.c`: punto de entrada del programa.
- `input.txt`: archivo de entrada de ejemplo.