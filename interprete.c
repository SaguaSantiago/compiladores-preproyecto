#include <stdio.h>
#include "interprete.h"

typedef struct resultado {
	int retorno;
	int valor;
} Resultado;

Resultado evaluar(Nodo* nodo)
{
    Resultado resultado = {0, 0};

    if (nodo == NULL) {
        return resultado;
    }
    switch (nodo->tipo) {
        case NODO_NUMERO:
        case NODO_IDENTIFICADOR:
		case NODO_BOOLEAN:
            resultado.valor = nodo->simbolo->valor;
            break;

        case NODO_SUMA: {
            Resultado izquierda = evaluar(nodo->izq);
            Resultado derecha = evaluar(nodo->der);

            resultado.valor = izquierda.valor + derecha.valor;
            break;
        }

        case NODO_MULTIPLICACION: {
            Resultado izquierda = evaluar(nodo->izq);
            Resultado derecha = evaluar(nodo->der);

            resultado.valor = izquierda.valor * derecha.valor;
            break;
        }

        default:
            break;
    }

    return resultado;
}

Resultado ejecutar(Nodo* nodo)
{
    Resultado resultado = {0, 0};

    if (nodo == NULL) {
        return resultado;
    }

    switch (nodo->tipo) {
        case NODO_PROGRAMA:
            ejecutar(nodo->izq);
            resultado = ejecutar(nodo->der);
            break;

        case NODO_DECLS:

            ejecutar(nodo->izq);
            ejecutar(nodo->der);
            break;

        case NODO_DECL:

            break;

        case NODO_SENTENCIAS:

            resultado = ejecutar(nodo->izq);

            if (!resultado.retorno) {
                resultado = ejecutar(nodo->der);
            }
            break;

        case NODO_ASIGNACION: {
            Resultado valor = evaluar(nodo->der);

            nodo->izq->simbolo->valor = valor.valor;
            break;
        }

        case NODO_RETORNO:
            resultado.retorno = 1;
            
            if (nodo->izq != NULL) {
                resultado.valor = evaluar(nodo->izq).valor;
            }
            break;
            
            default:
            break;
        }

    return resultado;
}

void interprete(Nodo* raiz){
	Resultado res = ejecutar(raiz);
	if(res.retorno){
		if(raiz->simbolo->tipo == TIPO_INT) printf("--EJECUCION EXITOSA-- RESULTADO: %d", res.valor);
		else if(raiz->simbolo->tipo == TIPO_BOOLEAN) printf("--EJECUCION EXITOSA-- RESULTADO: %s", res.valor == 1 ? "true" : "false");
		else printf("--EJECUCION EXITOSA--");
	}
}