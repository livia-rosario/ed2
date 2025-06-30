#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

struct bd_paciente {
    PacienteNode* first;
    int proximo_id;
};

struct paciente_node {
    Paciente info;
    PacienteNode* next;
};

BDPaciente* bd_create() {
    BDPaciente* bd = (BDPaciente*)malloc(sizeof(BDPaciente));
    if (bd == NULL) return NULL;
    bd->first = NULL;
    bd->proximo_id = 1;
    return bd;
}

void bd_free(BDPaciente* bd) {
    if (bd == NULL) return;
    PacienteNode* p = bd->first;
    while (p != NULL) {
        PacienteNode* t = p->next;
        free(p);
        p = t;
    }
    free(bd);
}

void bd_append(BDPaciente* bd, Paciente paciente) {
    PacienteNode* node = (PacienteNode*)malloc(sizeof(PacienteNode));
    if (node == NULL) return;
    node->info = paciente;
    node->next = NULL;

    if (paciente.id >= bd->proximo_id) {
        bd->proximo_id = paciente.id + 1;
    }

    if (bd->first == NULL) {
        bd->first = node;
    } else {
        PacienteNode* p = bd->first;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = node;
    }
}

int bd_remove(BDPaciente* bd, int id) {
    PacienteNode* p = bd->first;
    PacienteNode* prev = NULL;

    while (p != NULL && p->info.id != id) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) return 0;

    if (prev == NULL) {
        bd->first = p->next;
    } else {
        prev->next = p->next;
    }
    free(p);
    return 1;
}

int bd_load_csv(BDPaciente* bd, const char* filepath) {
    FILE* file = fopen(filepath, "r");
    // Se o arquivo não existe, apenas retorna 0 para que o chamador decida o que fazer.
    if (file == NULL) {
        return 0; // Retorna 0 para "Arquivo não encontrado"
    }

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Paciente p;
        sscanf(line, "%d,%[^,],%[^,],%d,%s", &p.id, p.cpf, p.nome, &p.idade, p.data_cadastro);
        bd_append(bd, p);
    }
    
    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo de leitura");
    }

    return 1; // Retorna 1 para "Sucesso"
}

void bd_save_csv(BDPaciente* bd, const char* filepath) {
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        perror("ERRO CRITICO AO SALVAR ARQUIVO");
        return;
    }

    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n");
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) {
        fprintf(file, "%d,%s,%s,%d,%s\n",
                p->info.id, p->info.cpf, p->info.nome,
                p->info.idade, p->info.data_cadastro);
    }

    if (fclose(file) != 0) {
        perror("Erro ao fechar o arquivo de escrita");
    }
}

PacienteNode* bd_get_first(BDPaciente* bd) {
    return bd->first;
}

Paciente bd_get_paciente_info(PacienteNode* node) {
    return node->info;
}

PacienteNode* bd_get_next_node(PacienteNode* node) {
    return node->next;
}

PacienteNode* bd_find_by_id(BDPaciente* bd, int id) {
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) {
        if (p->info.id == id) {
            return p;
        }
    }
    return NULL;
}

int bd_get_proximo_id(BDPaciente* bd) {
    return bd->proximo_id;
}

void bd_update_node_info(PacienteNode* node, Paciente new_info) {
    if (node != NULL) {
        node->info = new_info;
    }
}

PacienteNode* bd_find_by_cpf(BDPaciente* bd, const char* cpf) {
    for (PacienteNode* p = bd->first; p != NULL; p = p->next) {
        if (strcmp(p->info.cpf, cpf) == 0) {
            return p;
        }
    }
    return NULL;
}
