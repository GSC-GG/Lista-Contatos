#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLigada.h"


struct elemento {
    CLIENTE dados;
    struct elemento *prox;
};

typedef struct elemento ELEM;

Lista *criaLista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}

void abortaPrograma() {
    printf("Erro! Lista nao foi alocada");
    system("pause");
    exit(1);
}

void apagaLista(Lista *li) {
    if (li != NULL) {
        ELEM *no;
        while((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanhoLista(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    int acum = 0;
    ELEM *no = *li;
    while (no != NULL) {
        acum++;
        no = no->prox;
    }
    return acum;
}

int listaVazia(Lista *li) {
    if(li == NULL) {
        abortaPrograma();
    }
    if(*li == NULL) {
        return 1;
    }
    return 0;
}

CLIENTE coletaCliente(){
    CLIENTE dummy;
    printf("\nInsira os dados:\n");
    printf("\nCodigo: ");
    scanf("%d", &dummy.codigo);

    printf("Nome: ");
    fflush(stdin);
    gets(dummy.nome);

    printf("Empresa: ");
    fflush(stdin);
    gets(dummy.empresa);

    printf("Departamento: ");
    fflush(stdin);
    gets(dummy.depto);

    printf("Telefone: ");
    fflush(stdin);
    gets(dummy.tel);

    printf("Celular: ");
    fflush(stdin);
    gets(dummy.cel);

    printf("E-mail: ");
    fflush(stdin);
    gets(dummy.email);

    return dummy;
}

int insereOrdenado(Lista *li, CLIENTE cl) {
    if(li == NULL) {
        abortaPrograma();
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no == NULL) {
        return 0;
    }
    no->dados = cl;
    if(listaVazia(li)) {
        no->prox = (*li);
        *li = no;
        return cl.codigo;
    } else {
        ELEM *ant, *atual = *li;
        while(atual != NULL && atual->dados.codigo < cl.codigo) {
            ant = atual;
            atual = atual->prox;
        }

        if((atual != NULL && atual->dados.codigo == cl.codigo)){
            printf("\nJa existe cliente com o codigo %d cadastrado\n", cl.codigo);
            return 0;
        }
        else{
            if(atual == *li) {
                no->prox = (*li);
                *li = no;
            } else {
                no->prox = ant->prox;
                ant->prox = no;
            }
            return cl.codigo;
        }
    }
}

int removeOrdenado(Lista *li, int cod) {
    int codigo;
    if (li == NULL) {
        abortaPrograma();
    }
    ELEM *ant, *no = *li;
    while(no != NULL && no->dados.codigo != cod) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    }
    if (no == *li) {
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }
    codigo = no->dados.codigo;
    free(no);
    return codigo;
}

int consultaCod(Lista *li, int cod, CLIENTE *cl) {
    if (li == NULL) {
        abortaPrograma();
    }

    ELEM *no = *li;

    while(no != NULL && no->dados.codigo != cod) {
        no = no->prox;
    }
    if(no == NULL) {
        return 0;
    } else {
        *cl = no->dados;
        return 1;
    }
}

void exibirCliente(CLIENTE cl){
    puts("\n------------------------------------");
    printf("Codigo: %d", cl.codigo);
    printf("\nNome: %s", cl.nome);
    printf("\nEmpresa: %s", cl.empresa);
    printf("\nDepartamento: %s", cl.depto);
    printf("\nTelefone: %s", cl.tel);
    printf("\nCelular: %s", cl.cel);
    printf("\nE-mail: %s\n", cl.email);
    puts("------------------------------------");
}

void exibeTudo(Lista *li){
    if (li != NULL) {
        ELEM *no = *li;
        CLIENTE cl;
        puts("\n##Lista de Clientes##");
        while(no != NULL) {
            cl = no->dados;
            exibirCliente(cl);
            no = no->prox;
        }
    }
}

int editarCliente(CLIENTE* cl){
    if(cl == NULL){
        return 0;
    }
    char r;

    printf("\nInsira os novos dados:\n");

    printf("Editar nome? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("Nome: ");
        fflush(stdin);
        gets(cl->nome);
    }

    printf("Editar empresa? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("Empresa: ");
        fflush(stdin);
        gets(cl->empresa);
    }

    printf("Editar departamento? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("Departamento: ");
        fflush(stdin);
        gets(cl->depto);
    }

    printf("Editar telefone? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("Telefone: ");
        fflush(stdin);
        gets(cl->tel);
    }

    printf("Editar celular? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("Celular: ");
        fflush(stdin);
        gets(cl->cel);
    }

    printf("Editar e-mail? (s/n): ");
    scanf(" %c", &r);
    if(r == 's'){
        printf("E-mail: ");
        fflush(stdin);
        gets(cl->email);
    }
    return 1;
}

void alteraCliente(Lista* li){
    int cod, x = 1, y = 1;
    char resp;
    CLIENTE cl, backup;

    printf("\nDigite o codigo do cliente a ser alterado:\n");
    scanf(" %d", &cod);

    consultaCod(li, cod, &cl);

    exibirCliente(cl);

    printf("\nDeseja alterar o cliente exibido? (s/n)\n");
    scanf(" %c", &resp);

    if(resp == 's'){
        backup = cl;
        x = editarCliente(&cl);
        if(x){
            x = removeOrdenado(li, cod);
            if(x){
                x = insereOrdenado(li, cl);
                if(x){
                    printf("\nCliente editado com sucesso!\n");
                }else{
                    y = insereOrdenado(li, backup);
                }
            }
        }
        if(!x){
            printf("\nERRO! Nao foi possivel editar o cliente.\n");
            if(!y){
                printf("\nERRO FATAL, o cliente com o codigo %d foi corrompido!\n", cod);
            }
        }
    }else{
        printf("\nCliente %d nao editado.\n", cod);
    }
}

void salvaClientes(Lista *li, FILE *f){
    if (li != NULL) {
        ELEM *no = *li;
        CLIENTE cl;
        while(no != NULL) {
            cl = no->dados;
            fwrite(&cl, sizeof(CLIENTE), 1, f);
            no = no->prox;
        }
    }
}

void carregaClientes(Lista *li, FILE *f){
    CLIENTE dummy;
    while(!feof(f)){
        fread(&dummy, sizeof(CLIENTE), 1, f);
        insereOrdenado(li, dummy);
    }
}

//li   a lista e nomecon   o nome a ser consultado
int consultaNome(Lista *li , char* nomecon){
    int cont = 0;
    ELEM* no = *li;
    strlwr(nomecon);
    CLIENTE cl;
    //nomemin   o nome com todas as letras em minusculo
    char nomemin[100];
    while(no!=NULL){
        cl = no->dados;
        strcpy(nomemin, cl.nome);
        strlwr(nomemin);

        //a funcao strstr retorna nulo se uma string nao estiver contida na outra
        if(strstr(nomemin, nomecon) != NULL){
            exibirCliente(cl);
            cont++;
        }
        no = no->prox;
    }
    return cont;

}

char menu(){
    char op;
    
	printf("\n");
    puts("///      ///////   ////    ///     ////////");
    puts("//  //   //        // //   ////     //");
    puts("//   //   //        //  //  ////     //////");
    puts("////////   //        //   // // //    //");
    puts("//     //   //        //    //// //   //");
    puts("//      //   ///////   //    ///  //   ///////");
    printf("\nTodos os Direitos Reservados\n\n");

    puts("----------------MENU----------------");
    printf("(1) Inserir cliente\n");
    printf("(2) Listar todos os clientes\n");
    printf("(3) Buscar cliente por codigo\n");
    printf("(4) Buscar cliente[s] por nome\n");
    printf("(5) Editar cliente\n");
    printf("(6) Remover cliente da lista\n");
    printf("(7) Salvar e encerrar o programa\n");
    puts("------------------------------------\n");

    scanf(" %c", &op);
    return op;
}

void inserirCliente(Lista *li){
    int x;
    CLIENTE cl;
    cl = coletaCliente();
    x = insereOrdenado(li, cl);

    if(x){
        printf("\nCliente com o codigo %d inserido com sucesso.\n", x);
    }
    else{
        printf("\nErro! Cliente nao pode ser inserido.\n");
    }

}

void listaIndividual(Lista *li){
    int x, cod;
    CLIENTE cl;

    printf("\nDigite o codigo do cliente a ser consultado: ");
    fflush(stdin);
    scanf(" %d", &cod);

    x = consultaCod(li, cod, &cl);
    if(x){
        printf("\nConsulta no codigo %d feita com sucesso.\n\nAqui esta o cliente:\n", cod);
        exibirCliente(cl);
    }else{
        printf("\nErro! Consulta no codigo %d deu errado.\n", cod);
    }
}

void buscaNome(Lista *li){
    int x;
    char nomecon[100];

    printf("\nDigite o nome a ser consultado: ");
    fflush(stdin);
    scanf("%s", nomecon);

    x = consultaNome(li, nomecon);
    if(x != 0){
        printf("\n%d cliente[s] encontrado[s] com o nome %s, ele[s] pode[m] ser visto[s] acima\n", x, nomecon);
    }else{
        printf("\nNao foram encontrados clientes com o nome %s.\n", nomecon);
    }
}

void removeCliente(Lista *li){
    int x, cod;

    printf("\nDigite o codigo do cliente a ser consultado: ");
    fflush(stdin);
    scanf(" %d", &cod);

    x = removeOrdenado(li, cod);


    if(x){
        printf("\nCliente com o codigo %d removido com sucesso.\n", x);
    }
    else{
        printf("\nErro! Remocao nao pode ser concluida com sucesso.\n");
    }
}

void encerraPrograma(Lista *li){
    FILE* f;
    f = fopen("contatos.txt", "wb");
    if(f == NULL){
        printf("\nErro na abertura\n");
        system("pause");
        exit(1);
    }
    printf("\nSalvando sua lista...\n");
    salvaClientes(li, f);
    fclose(f);
    printf("\nSaindo...\n");
}


