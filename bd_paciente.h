#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

// Incluir 'paciente.h' PRIMEIRO para que o compilador saiba o que é 'Paciente'.
#include "paciente.h" 

// Define as estruturas BDPaciente e PacienteNode no estilo do professor
typedef struct bd_paciente BDPaciente;   // Representa o banco de dados (a lista)
typedef struct paciente_node PacienteNode; // Representa um nó da lista

// --- Operações sobre o Banco de Dados (Interface do TAD) ---

BDPaciente* bd_create();
void bd_free(BDPaciente* bd);
void bd_append(BDPaciente* bd, Paciente paciente);
int bd_remove(BDPaciente* bd, int id);
void bd_load_csv(BDPaciente* bd, const char* filepath);
void bd_save_csv(BDPaciente* bd, const char* filepath);
PacienteNode* bd_get_first(BDPaciente* bd);
Paciente bd_get_paciente_info(PacienteNode* node);
PacienteNode* bd_get_next_node(PacienteNode* node);
PacienteNode* bd_find_by_id(BDPaciente* bd, int id);
PacienteNode* bd_find_by_cpf(BDPaciente* bd, const char* cpf); // <-- FUNÇÃO ADICIONADA
int bd_get_proximo_id(BDPaciente* bd);
void bd_update_node_info(PacienteNode* node, Paciente new_info);

#endif // BD_PACIENTE_H