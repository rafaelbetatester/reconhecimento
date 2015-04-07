EXEC = reconhecimento.out
SRCS = reconhecimentoCaracter.cpp traducaoImagem.cpp estruturas.h constantes.h treinamento.cpp
LIBS = -lallegro -lallegro_primitives -lallegro_dialog

${EXEC}: ${SRCS}
	g++ -o ${EXEC} $^ ${LIBS}
