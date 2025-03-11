typedef struct cliente {
    int codigo;
    char nome[100];
    char empresa[100];
    char depto[100];
    char tel[14];
    char cel[14];
    char email[100];
}CLIENTE;

typedef struct elemento* Lista;

Lista *criaLista();
void abortaPrograma();

void apagaLista(Lista *li);

int tamanhoLista(Lista *li);
int listaVazia(Lista *li);

CLIENTE coletaCliente();
int insereOrdenado(Lista *li, CLIENTE cl);
int removeOrdenado(Lista *li, int cod);

int consultaCod(Lista *li, int cod, CLIENTE *cl);
int consultaNome(Lista *li , char* nomecon);
void exibirCliente(CLIENTE cl);
void exibeTudo(Lista *li);

int editarCliente(CLIENTE* cl);
void alteraCliente(Lista* li);

void salvaClientes(Lista *li, FILE *f);
void carregaClientes(Lista *li, FILE *f);

void listaIndividual(Lista *li);
void inserirCliente(Lista *li);
void buscaNome(Lista *li);
void removeCliente(Lista *li);
void encerraPrograma(Lista *li);
char menu();
