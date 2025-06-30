#include <stdio.h>
#include "bd_paciente.h"
#include "interface.h"

int main() {
    const char* NOME_ARQUIVO = "bd_paciente.csv";

    // 1. Cria o banco de dados em memória
    BDPaciente* banco = bd_create();

    // 2. Carrega os dados do arquivo para a memória e trata o resultado
    if (bd_load_csv(banco, NOME_ARQUIVO) == 0) {
        printf(CLR_YELLOW "AVISO: Arquivo '%s' nao encontrado. Um novo sera criado ao salvar.\n" CLR_RESET, NOME_ARQUIVO);
        pausarExecucao(); // Agora o main pode chamar a função de pausar
    }
    
    // 3. Inicia a interface com o usuário, que gerencia o programa
    iniciarLoopPrincipal(banco);
    
    // 4. Salva os dados de volta no arquivo ao sair
    bd_save_csv(banco, NOME_ARQUIVO);
    printf(CLR_GREEN "Dados salvos em '%s'. Programa encerrado.\n" CLR_RESET, NOME_ARQUIVO);

    // 5. Libera toda a memória alocada dinamicamente
    bd_free(banco);

    return 0;
}
