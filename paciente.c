#include <stdio.h>
#include "paciente.h"

void imprimir_paciente(const Paciente* p) {
    if (p != NULL) {
        printf("%-5d %-15s %-30s %-10d %-15s\n",
               p->id,
               p->cpf,
               p->nome,
               p->idade,
               p->data_cadastro);
    }
}