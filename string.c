#include <stdio.h>
#include "stringc.h"

int main(void)
{
	string texto;//declarando a string com o próprio tipo de dado string;

	texto = get_string("");//Opção de inserir mensagem;

	free_strings();//Necessário para liberar a memória alocada no uso da(s) string(s),
	               //sempre colocar no fim do código.
	return 0;
}
