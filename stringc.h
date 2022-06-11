#include <stdio.h>
#include <stdlib.h>
#ifndef STRINGC_H
#define STRINGC_H

/*Este é um projeto inspirado na biblioteca cs50 do curso de Introdução a Ciência
da Computação de Harvard. Contrui a biblioteca com o intuito de desenvolver minhas habilidades na linguagem C.
É livre a utilização deste material para fins didáticos e de estudo.
@Bruno Davis - 11/06/2022*/

typedef char *string;//Redefinindo o tipo de dado char* para string;

static size_t allocations = 0;//Controlará o índice que será armazenado a string no array de strings;

static string *strings = NULL;//Array de strings que será liberado no final do programa com a função free_strings();

string get_string(string mensagem)//Função que receberá e retornará a string, independentemente do tamanho;
{
	printf("%s",mensagem);
	string text = (string) malloc(2 * sizeof(char));
	string text_copy = NULL;
	int len = 0;
	int i;

	do
	{
		scanf("%c",&text[len]);//Lendo o caractere;

		len++;

        free(text_copy);
		text_copy = (string) malloc((len + 1) * sizeof(char));//Alocando memória suficiente para receber todos os caracteres
		                                                      //lidos até o momento e fazer um "backup" dos mesmos;
		if(text_copy == NULL)
		{
		   free(text);
		   return NULL;
		}

		for(i = 0; i < len; i++)
		{
			text_copy[i] = text[i];
		}//Fazendo "backup";

        free(text);
		text = (string) malloc((len + 1) * sizeof(char));//Após já ter um "backup" da string no ponteiro text_copy,
		                                                 //podemos então aumentar o tamanho da memória alocada no ponteiro text;
		if(text == NULL)
		{
		   free(text_copy);
		   return NULL;
		}

		for(i = 0; i < len; i++)
		{
			text[i] = text_copy[i];
		}//Pegando novamente os caracteres, mas agora mais espaço no ponteiro, para receber o próximo caractere;
	}
	while(text[len - 1] != 10 && text[len - 1] != '\r' && text[len - 1] != EOF);//Quando for pressionado o enter, finalizar o loop de leitura;
	text[len - 1] = '\0';//Inserindo o caractere de fim de string na nossa string;
	free(text_copy);//Liberando a string cópia;

	string *tmp = realloc(strings, sizeof (string) * (allocations + 1));//Realocando com uma variável temporária o tamanho do nosso array de strings;
    if (tmp == NULL)
    {
        free(text);
        return NULL;
    }
    strings = tmp;

    strings[allocations] = text;//Alocando o endereço da nossa string no nosso array de strings;
    allocations++;

	return text;//Retornando nossa string feita em todo esse processo;
}

void free_strings(void)//Função que liberará toda memória alocada por malloc;
{
	size_t i;
	if (strings != NULL)
    {
        for (i = 0; i < allocations; i++)
        {
            free(strings[i]);
        }
        free(strings);
    }
}

#endif
