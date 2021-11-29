#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

int menu();
void pause();
void linha();
void abrir_pessoa();
void abrir_tempo();
float tirandoImc(float peso, float altura);

void cadastrar();
int procurar(int num_cpf);
void mostra();
void listar();

typedef struct {
    char nome[30];
    float altura;
    float peso;
    int cpf;
    //char sexo[10];
    float imc;
    char status[30];

    int dia;
    int mes;
    int ano;
}Pessoa;

typedef struct tempo {
    int tm_sec; //representa os segundos de 0 a 59
    int tm_min; //representa os minutos de 0 a 59
    int tm_hour; //representa as horas de 0 a 24
    int tm_mday; //dia do mês de 1 a 31
    int tm_mon; //representa os meses do ano de 0 a 11
    int tm_year; //representa o ano a partir de 1900
    int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
    int tm_yday; // dia do ano de 1 a 365
    int tm_isdst; //indica horário de verão se for diferente de zero
}Temp;

    Pessoa pessoais;
    Temp *data;

    FILE *ptr_pessoa;

int main(){
    int qq;
    int escolha;

    time_t segundos;
    time(&segundos);

    data = localtime(&segundos);


    abrir_pessoa();
    abrir_pessoa();
    abrir_tempo();

    escolha = menu();

    do {
         switch(escolha){

            case 1:
                 cadastrar();
            break;

            case 2:
                mostra();
            break;

            case 3:
                listar();
            break;

            case 4:
                printf("Tem certeza que desejar apaga todos os dados ? (1-sim/ 0-não");
                scanf("%d", &qq);
                __fpurge(stdin);

                if(qq == 1){
                    limpar();
                }else {
                    printf("\n\n Operação cancelada.");
                    pause();
                }

            break;

            case 0:
                exit(1);
            break;

            default:
                printf("Opção invalida, tente novamente!");
                pause();
            break;
        }

        escolha = menu();

    }while(escolha !=0);

    fclose(ptr_pessoa);

 return 0;
}

float tirandoImc(float peso, float altura){

    float imc;
    imc = (peso/(altura * altura));

    return imc;
}

void cadastrar(){

    int resp, dia = 0, mes = 0, ano = 0;
    int verificar_resp;

    //  char sexo[10];


    do {

        printf("\n\n\nDigite o nome da pessoa: ");
        scanf("%s", pessoais.nome);
        __fpurge(stdin);

        printf("\n\n");
        printf("Digite o CPF: ");
        scanf("%d", &pessoais.cpf);
        __fpurge(stdin);

        printf("Digite a altura de %s: ", pessoais.nome);
        scanf("%f", &pessoais.altura);
        __fpurge(stdin);

        printf("\n\n");

        printf("Digite o peso de %s ", pessoais.nome);
        scanf("%f", &pessoais.peso);
        __fpurge(stdin);

        printf("\n\n");

        pessoais.dia = data->tm_mday;
        pessoais.mes = data->tm_mon;
        pessoais.ano = data->tm_year+1900;
/*
        printf("Digite o sexo: (M-masculino/F-feminino)\n");
        scanf("%s", &sexo);
        __fpurge(stdin);

        strcpy(pessoais.sexo, sexo);
*/

        pessoais.imc = tirandoImc(pessoais.peso, pessoais.altura);


    if(pessoais.imc < 18.5){
        char mensagens[] = "abaixo do peso.";
        strcpy(pessoais.status, mensagens);
    }else if(pessoais.imc >= 18.5 && pessoais.imc < 24.9){
       char mensagens[] = "Peso normal";
        strcpy(pessoais.status, mensagens);
    }else if(pessoais.imc >= 24.9 && pessoais.imc < 29.9){
        char mensagens[] = "Sobrepeso";
        strcpy(pessoais.status, mensagens);
    }else if(pessoais.imc >= 29.9 && pessoais.imc < 34.9){
        char mensagens[] = "Obesidade grau 1";
        strcpy(pessoais.status, mensagens);
    }else if(pessoais.imc >= 34.9 && pessoais.imc < 39.9){
        char mensagens[] = "Obesidade grau 2";
        strcpy(pessoais.status, mensagens);
    }else if (pessoais.imc >= 39.9){
        char mensagens[] = "Obesidade grau 3";
        strcpy(pessoais.status, mensagens);
    }

        fseek(ptr_pessoa, 0, SEEK_END);

        fwrite(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);

    }while(resp == 0);

    pause();
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

 void mostra(){

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
        fread(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);

        printf("------------\ Pessoa encontrada /------------\n\n\n");
        printf("Nome: %s.\n", pessoais.nome);
        printf("Altura: %.2f.\n", pessoais.altura);
        printf("Peso: %.2f.\n", pessoais.peso);
        printf("Cpf: %d.\n", pessoais.cpf);
        //printf("Sexo: %c.\n", pessoais.sexo);
        printf("\n");
        printf("Imc: %.2f.", pessoais.imc);
        printf("Status: %s.", pessoais.status);
        printf(" Data: %.2d/%.2d/%d ", pessoais.dia, pessoais.mes, pessoais.ano);
    }
    pause();
 }

void listar(){

    system("clear");

    rewind(ptr_pessoa);
    fread(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);

    printf("----------------\\ Lista De Pessoas /----------------\n\n");

    while(feof(ptr_pessoa) == 0){
        linha();
        printf("\n\n");
        printf("Nome: %s.\n", pessoais.nome);
        printf("Altura: %.2f.\n", pessoais.altura);
        printf("Peso: %.2f.\n", pessoais.peso);
        printf("Cpf: %d.\n", pessoais.cpf);
        //printf("Sexo: %c.\n", pessoais.sexo);
        printf("\n");
        printf("Imc: %.2f.", pessoais.imc);
        printf("Status: %s.", pessoais.status);
        printf(" Data: %.2d/%.2d/%d ", pessoais.dia, pessoais.mes, pessoais.ano);

        printf("\n\n");
        linha();
        printf("\n\n");

        fread(&pessoais, sizeof(Pessoa), 1, ptr_pessoa);
    }

    pause();
}

int menu(){
    system("clear");

    int num;
    printf("---------------\\ Menu do IMC /---------------\n\n\n");
    printf("1) Cadastrar pessoa.\n");
    printf("2) Consulta por cpf. \n");
    printf("3) Listar todas as pessoas cadastradas.\n");
    printf("4) Excluir todos os dados.\n");
    printf("0) Sair do programa.\n\n\n");

    printf("Digite a opção que você desejar: ");
    scanf("%d", &num);
    __fpurge(stdin);

    return num;
}

void abrir_pessoa() {
     ptr_pessoa = fopen("pessoais.dat", "r+b");

    if( ptr_pessoa == NULL){
        ptr_pessoa = fopen("pessoais.dat", "w+b");
    }
}

void abrir_tempo() {

    ptr_tempo = fopen("tempo.dat", "r+b");

    if(ptr_tempo == NULL){
        ptr_tempo = fopen("tempo.dat", "w+b");
    }

}

void linha() {
    for(int i = 0; i < 20; i++){
        printf("-");
    }
    printf("\n\n\n");
}

void limpar(){

    ptr_pessoa = fopen("pessoais.dat", "w+b");


}

void pause() {
    printf("\n\n\nDigite qualquer tecla para continuar...");
    getchar();
}
