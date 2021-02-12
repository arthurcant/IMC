#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE ptr_pessoa;
FILE ptr_tempo;

int menu();
void pause();
void abrir_pessoa();
void abrir_tempo();

void cadastrar();
int procurar(int num_cpf);
void mostra(int num_cpf);

typedef struct {
    char nome[30];
    float altura;
    float peso;
    int cpf;
    char sexo;
}Pessoa;

typedef struct {
    int dia;
    int mes;
    int ano;
}Tempo;

    Pessoa pessoais;
    Tempo temp;

int main(){

    int escolha;

    abrir_pessoa();
    abrir_tempo();


    escolha = menu();

    switch(escolha){



    case 1:
         cadastrar();
    break;

    case 2:

    break;

    case 3:

    break;

    case 0:

    break;

    default:
        printf("")
    break;



    }

 return 0;
}

void cadastrar(){

    int resp;



    do {


        printf("Digite o nome da pessoa: ");
        scanf("%s", pessoais->nome);
        __fpurge(stdin);

        printf("\n\n");

        printf("Digite a altura de %s: ", pessoais.nome);
        scanf("%f", &pessoais.altura);
        __fpurge(stdin);

        printf("\n\n");

        printf("Digite o peso de %s", pessoais.nome)
        scanf("%f", &pessoais.peso);
        __fpurge(stdin);

        printf("\n\n");
        printf("Digite o CPF: ");
        scanf("%d", &pessoais.cpf)
        __fpurge(stdin);

        char sex;
        printf("Digite o sexo: (M-masculino/F-feminino)\n");
        scanf("%c", sex);
        __fpurge(stdin);

        if(islower(sex) == 0){
            sex = toupper(sex);
            pessoais.sexo = sex;
        }else {
            pessoais.sexo = sex;
        }

        fseek(ptr_pessoa, sizeof(Pessoa), SEEK_END);
        fwrite(&pessoais, sizeof(Pessoa),1, ptr_pessoa);

        do{
            system("clear");
            int verificar_resp = 0;
            printf("Desejar registrar outra pessoa: (1-Sim/0-Não)\n");
            scanf("%d", &resp);
            __fpurge(stdin);

            if(resp == 0 || resp == 1){
                verificar_resp = 1;

            }else {

                verificar_resp = 0;
                printf("\n\n\nVocê digitou uma opção invalida.\nTente novamente!");
                pause();

            }

        }while(verificar_resp == 0);

    }while(resp != 1);

}

 int procurar(int num_cpf) {

     int p = 0;

    rewind(ptr_pessoa);
    fread(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);

    while(feof(ptr_pessoa) == 0){
        if(pessoais.cpf == num_cpf){
            return p;

        }else {

            fread(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);

            p++;
        }

    }

    return -1;
 }

 void mostra(int num_cpf){

    int buscar;
    printf("Digite o cpf a ser buscado: ");
    scanf("%d", &buscar);
    __fpurge(stdin);

    int posicao = procurar(buscar);

    if(posicao == -1){
        printf("Pessoa não encontrada.");
        pause();

    } else {
        system("clear");

        rewind(ptr_pessoa);
        fseek(ptr_pessoa, posicao * sizeof(Pessoa), SEEK_SET);
        fread(&pessoais, sizeof(Pessoa),1, ptr_pessoa);

        printf("------------\ Pessoa encontrada /------------\n\n\n");
        printf("Nome: %s\n", pessoais->nome);
        printf("Altura: %f\n", pessoais->altura);
        printf("Peso: %f\n", pessoais->peso);
        printf("Cpf: %d\n", pessoais->cpf);
        printf("Sexo: %c\n", pessoais->sexo);

    }



 }


int menu(){

    int num;
    printf("---------------\ Menu do MMC /---------------\n\n\n");
    printf("1) Cadastrar pessoa.\n");
    printf("2) Consulta por cpf. \n");
    printf("3) Listar todas as pessoas cadastradas.\n");
    printf("0) Sair do programa.\n\n\n");

    printf("Digite a opção que você desejar: ");
    scanf("%d", &num);
    __fpurge(stdin);

    return num;
}

void abrir_pessoa() {

    if( ptr_pessoa != NULL){
        ptr_pessoa = fopen("pessoais.dat", "w+b");
    }else {
        ptr_pessoa = fopen("pessoais.dat", "r+b");
    }

}

void abrir_tempo() {

    if(ptr_tempo != NULL){
        ptr_tempo = fopen("tempo.dat", "w+b");
    } else {
        ptr_tempo = fopen("tempo.dat", "r+b");
    }


}

void pause() {
    printf("\n\n\nDigite qualquer tecla para continuar...");
    getchar();
}
