# Define o compilador C a ser usado
CC = gcc
# Define as flags de compilação: -Wall e -Wextra para todos os avisos, -std=c11 para o padrão C11, -g para símbolos de debug
CFLAGS = -Wall -Wextra -std=c11 -g

# Define o nome do executável final
TARGET = healthsys

# Lista todos os arquivos-fonte .c que compõem o projeto
SRCS = main.c bd_paciente.c paciente.c interface.c
# Gera automaticamente a lista de arquivos objeto (.o) a partir dos fontes (.c)
OBJS = $(SRCS:.c=.o)

# Regra padrão: é a primeira regra, executada quando 'make' é chamado sem argumentos.
# Depende do executável final.
all: $(TARGET)

# Regra para linkar os arquivos objeto e criar o executável final.
# $@ é uma variável automática para o nome do alvo (healthsys).
# $^ é uma variável automática para o nome de todas as dependências (os arquivos .o).
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "\n--- Compilação concluída com sucesso! ---"
	@echo "Execute o programa com: ./$(TARGET) ou 'make run'"

# Regra genérica para compilar arquivos .c em .o.
# Esta regra é usada para criar cada um dos arquivos objeto listados em $(OBJS).
# $< é uma variável automática para a primeira dependência (o arquivo .c correspondente).
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Definição de Dependências Explícitas ---
# Ajuda o 'make' a saber quando um arquivo .o precisa ser recompilado
# porque um de seus arquivos de cabeçalho (.h) foi modificado.

main.o: main.c interface.h bd_paciente.h

interface.o: interface.c interface.h bd_paciente.h

bd_paciente.o: bd_paciente.c bd_paciente.h paciente.h

paciente.o: paciente.c paciente.h


# Regra para limpar os arquivos gerados pela compilação (objetos e executável).
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Arquivos de build removidos."

# Regra para compilar e executar o programa.
run: all
	./$(TARGET)

# Declara alvos que não são nomes de arquivos, para evitar conflitos.
.PHONY: all clean run