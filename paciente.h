#ifndef PACIENTE_H
#define PACIENTE_H

// Define a estrutura para armazenar os dados de um único paciente.
typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

/**
 * @brief Imprime os dados de um único paciente de forma formatada.
 * @param p Ponteiro para o paciente a ser impresso.
 */
void imprimir_paciente(const Paciente* p);

#endif // PACIENTE_H