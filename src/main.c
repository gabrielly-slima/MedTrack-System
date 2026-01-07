/*
Nome........: Gabrielly Santos Lima e Lavínia Nicola Pereira
Turma.......: EC41A-C11
Data........: 02/12/2025
Projeto.....: Trabalho Final - MedTrack
*/

#include <stdio.h>
#include <string.h>

// structs
typedef struct Data{
    int dia;
    int mes;
    int ano;
} TpData;

typedef struct Residente{
    char nomeDoResidente[50];
    char contatoDoResponsavel[15];
    TpData dataNascimento;
} TpResidente;

typedef struct Medicamento{
    char nomeDoMedicamento[50];
    int dosagem;
    int periodo;
    int quantidade;
} TpMedicamento;

typedef struct Prescricao{
    int identificador;
    TpResidente residente;
    TpMedicamento medicamento;
    int quantidadeEstoque;
    char tomando;
} TpPrescricao;

typedef struct RegistroDeAdministracao{
    int identificador;
    int idDaPrescricao;
    TpData dataDaAdministracao;
    int horaDaAdministracao;
    int idEnfermeiro;
} TpRegistroDeAdministracao;

typedef struct Registros{
    int idDaPrescricao;
    TpData dataDaAdministracao;
} TpRegistro;

// variáveis globais
TpMedicamento listaMedicamentos[10];
TpPrescricao listaPrescricao[50];
TpRegistro listaRegistros[500];
TpResidente listaResidentes[20];
int totalResidentes = 2, totalMedicamentos = 2, totalPrescricao = 2, autoPrescricao = 3, totalRegistros = 2;


// protótipos das funções
int buscarMedicamento(char nome[50]);
int buscarMedicamentos(void);
int buscarPrescricao(char nome[50]);
int buscarPrescricaoId(int auxIdPrescricao);
int buscarPrescricoes(void);
int buscarResidente(char nome[50]);
int compararDatas(TpData data1, TpData data2);
int identificarEnfermeiro(void);
int identificarEstoqueBaixo(TpPrescricao auxPrescricao);
int Menu(void);
int obterUltimoRegistro(int idPrescricao);
int transformarDataEmDias(TpData data);
int validarDatas(TpData data);
int validarNomeMedicamento(char nome[50]);
int validarNomes(char nome[50]);
int validarPeriodoMedicamento(TpMedicamento novoMedicamento);
int validarQuantMedicamento(TpMedicamento novoMedicamento);
int validarTelefones(char telefone[15]);
int verificarAnoBissexto(int ano);
TpMedicamento cadastrarMedicamento(void);
TpPrescricao cadastrarPrescricaoMedica(void);
TpRegistroDeAdministracao RegistrarAdministracaoMedicamento(void);
TpResidente cadastrarResidentes(void);
void alterarStatusTomando(void);
void buscarResidentes(void);
void imprimirDadosPrescricao(TpPrescricao presc);
void imprimirDadosResidentes(TpResidente r);
void preencher(void);
void verificarRegistroAdministracao(int posPrescricao);

// funções
int buscarMedicamento(char nome[50]){
    int i = 0;
    for(i = 0; i < totalMedicamentos; i++){
        if(strcmp(nome, listaMedicamentos[i].nomeDoMedicamento) == 0){
            return i;
        }  
    }    
    return -1;
}

int buscarMedicamentos(void){
    char nomePesquisado[50];
    int pesquisa = -1;
    
    do{
        printf("\nDigite o nome do medicamento:\n");
        fgets(nomePesquisado, 50, stdin); 
        nomePesquisado[strcspn(nomePesquisado, "\n")] = '\0';
        
        if(validarNomeMedicamento(nomePesquisado) == 0){
            printf("Nome invalido!\n");
        } else{
            pesquisa = buscarMedicamento(nomePesquisado);
            if(pesquisa == -1){
                printf("Esse nome nao existe na lista de cadastrados!\n");
            } else {
               return pesquisa;
            }
        }
    } while(pesquisa == -1);
}

int buscarPrescricao(char nome[50]){
    int i = 0;
    for(i = 0; i < totalPrescricao; i++){
        if(strcmp(nome, listaPrescricao[i].residente.nomeDoResidente) == 0){
            return i;
        }  
    }    
    return -1;
}

int buscarPrescricaoId(int auxIdPrescricao){
    int i = 0;
    for(i = 0; i < totalPrescricao; i++){
        if(auxIdPrescricao == listaPrescricao[i].identificador){
            return i;
        }  
    }    
    return -1;
}

int buscarPrescricoes(void){
    char nomePesquisado[50];
    int resposta = 0,
        auxIdPrescricao = 0,
        posicao = -1;
    
    do{
        printf("Digite para buscar a prescricao:\n");
        printf("1 - Pelo paciente\n");
        printf("2 - Pelo ID da prescricao\n");
        
        scanf("%d", &resposta);
        getchar();
        
        if(resposta == 1){

            do{
                printf("\nDigite o nome do residente:\n");
                fgets(nomePesquisado, 50, stdin); 
                nomePesquisado[strcspn(nomePesquisado, "\n")] = '\0';

                if(validarNomes(nomePesquisado) == 1){

                    posicao = buscarPrescricao(nomePesquisado);

                    if(posicao == -1){
                        printf("Esse residente nao se encontra na lista! Digite novamente.\n");
                    }

                } else {
                    printf("Nome invalido! Digite novamente.\n");
                }

            } while(validarNomes(nomePesquisado) != 1 || posicao == -1);

        } else {
            if(resposta == 2){
                
                do{
                    printf("\nDigite o ID da prescricao:\n");
                    scanf("%d", &auxIdPrescricao);
                    getchar();
            
                    posicao = buscarPrescricaoId(auxIdPrescricao);

                    if(posicao == -1){
                        printf("Nenhuma prescricao encontrada com este ID!\n");
                    } 
                    
                } while(posicao == -1);
            }
        }
        
    } while(resposta != 1 && resposta != 2);

    return posicao;

}

int buscarResidente(char nome[50]){
    int i = 0;
    for(i = 0; i < totalResidentes; i++){
        if(strcmp(nome, listaResidentes[i].nomeDoResidente) == 0){
            return i;
        }  
    }    
    return -1;
}

int compararDatas(TpData data1, TpData data2){
    int diferenca = 0;
    
    diferenca = transformarDataEmDias(data1) - transformarDataEmDias(data2);
    return diferenca;
}

int identificarEnfermeiro(void){
    int auxIdEnfermeiro = 0;
    
    do{
        printf("Ola enfermeiro(a)! Digite seu ID para Registrar uma Administracao\n");
        scanf("%d", &auxIdEnfermeiro);
        
        if(auxIdEnfermeiro < 1001 || auxIdEnfermeiro > 1005){
            printf("ID invalido! Digite novamente:\n");
        }
    } while(auxIdEnfermeiro < 1001 || auxIdEnfermeiro > 1005);

    switch(auxIdEnfermeiro){
        case 1001: 
            printf("\nOla Bento Curativo!\n"); 
            break;
        case 1002: 
            printf("\nOla Valdemar Remedio!\n"); 
            break;
        case 1003: 
            printf("\nOla Tadeu Seringa!\n"); 
            break;
        case 1004: 
            printf("\nOla Lucio Sergio Gaze!\n"); 
            break;
        case 1005: 
            printf("\nOla Helena Salva Vidas!\n"); 
            break;
        
    }
    return auxIdEnfermeiro;
}

int identificarEstoqueBaixo(TpPrescricao auxPrescricao){
    int limite = 0;
    
    limite = auxPrescricao.medicamento.quantidade * 0.10;
    
    if(limite < 1){
        limite = 1;
    }
    
    if(auxPrescricao.tomando != 'S'){
        return 0;
    }
    
    if(auxPrescricao.quantidadeEstoque <= limite){
        return 1;
    }
    
    return 0;
}

int Menu(void){
    int resp = 0;
    printf("\n==================================\n");
    printf("           MedTrack        \n");
    printf("==================================\n");
    printf("1 - Cadastrar residentes\n");
    printf("2 - Cadastrar medicamentos\n");
    printf("3 - Cadastrar prescricao\n");
    printf("4 - Buscar residentes\n");
    printf("5 - Registrar administracao\n");
    printf("6 - Auditoria de medicamentos\n");
    printf("7 - Alterar status tomando\n");
    printf("8 - Sair\n");
    printf("==================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &resp);
    printf("\n");
    return resp;
}

int obterUltimoRegistro(int idPrescricao) {
    int pos = -1;
    
    for (int i = 0; i < totalRegistros; i++) {
        if (listaRegistros[i].idDaPrescricao == idPrescricao) {

            if (pos == -1) {
                pos = i;
            } else {
                if (compararDatas(listaRegistros[i].dataDaAdministracao,
                                   listaRegistros[pos].dataDaAdministracao) > 0) {
                pos = i;
            }
        }
    }
    }
    return pos;
}

int transformarDataEmDias(TpData data){
    int i = 0, totalDias = 0;
    
    for(i = 1; i < data.mes; i++){
        if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
            totalDias += 31;
        } else{
            if(i == 2){
                totalDias += 28;
                if(verificarAnoBissexto(data.ano)){
                    totalDias += 1;
                }
            } else{
                totalDias += 30;
            }
        }
    }
    return totalDias;
}

int validarDatas(TpData data){
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if(data.ano < 1000 || data.ano > 9999){
        return 0;
    }
    
    if(data.mes < 1 || data.mes > 12){
        return 0;
    }
    
    if(data.dia < 1){
        return 0;
    }
    
    if(data.mes == 2) {
        if(verificarAnoBissexto(data.ano)) {
            if(data.dia > 29) {
                return 0;
            }
        } else{
            if(data.dia > 28) {
                return 0;
            }
        }
    } else{
        if(data.dia > diasPorMes[data.mes]) {
            return 0;
        }
    }
    
    return 1;
}

int validarNomeMedicamento(char nome[50]){
    int i = 0;
    
    if(nome[0] == ' '){
        return 0;
    } else{ 
        for(i = 0; nome[i] != ' ' && nome[i] != '\0'; i++){
            if(nome[i] >= '0' && nome[i] <= '9'){
                return 0;
            } 
        }
    }   
    return 1;
}

int validarNomes(char nome[50]){
    int i = 0,
        temEspaco = 0,
        semNumero = 0;
    
    if(nome[0] == ' '){
        return 0;
    }
    
    if(strlen(nome) < 8){
        return 0;
    }
        
    for(i = 0; nome[i]  != '\0'; i++){
        if(nome[i] >= '0' && nome[i] <= '9'){
            return 0;
        }
        
        if(nome[i] == ' '){
            temEspaco = 1;
        }
    }
    
    if(temEspaco == 1){
        return 1;
    }
    return 0;
}

int validarPeriodoMedicamento(TpMedicamento novoMedicamento){    
    if(novoMedicamento.periodo <= 0){
        return 0;
    }
    return 1;
}

int validarQuantMedicamento(TpMedicamento novoMedicamento){    
    if(novoMedicamento.quantidade <= 0){
        return 0;
    }
    return 1;
}

int validarTelefones(char telefone[15]){
    int i = 0,
        valido = 0;
    
    if(telefone[0] != '0'){
        return 0;
    } else{
        valido++;
    }
    
    if(strlen(telefone) > 13 || strlen(telefone) < 11){
        return 0;
    } else{
        valido++;
    }
    
    for(i = 0; telefone[i]  != '\0'; i++){
        if(telefone[i] < '0' || telefone[i] > '9'){
            return 0;
        }
    }
    
    if(valido == 2){
        return 1;
    }
}

int verificarAnoBissexto(int ano){
    if((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
        return 1; 
    } else{
        return 0;  
    }
}

TpMedicamento cadastrarMedicamento(void){
    TpMedicamento novoMedicamento;
    int aux;
    char auxNomeResidente[50];
    
    printf("\n==================================\n");
    printf("     CADASTRO DE MEDICAMENTOS        \n");
    printf("==================================\n");
    getchar();
    
    do{
        printf("\nDigite o nome do medicamento:\n");
        fgets(novoMedicamento.nomeDoMedicamento, 50, stdin); 
        novoMedicamento.nomeDoMedicamento[strcspn(novoMedicamento.nomeDoMedicamento, "\n")] = '\0';
        
        if(validarNomeMedicamento(novoMedicamento.nomeDoMedicamento) != 1){
            printf("Nome invalido! Digite novamente.\n");
        }
        
    } while(validarNomeMedicamento(novoMedicamento.nomeDoMedicamento) != 1);    
        
    printf("\nDigite a dosagem do medicamento:\n");
    scanf("%d", &novoMedicamento.dosagem);
    
    do{    
        printf("\nDigite o período do medicamento:\n");
        scanf("%d", &novoMedicamento.periodo);
        
        if(validarPeriodoMedicamento(novoMedicamento) != 1){
            printf("Periodo invalido! Digite novamente.\n");
        }
        
    } while(validarPeriodoMedicamento(novoMedicamento) != 1);   
        
    do{
        printf("\nDigite a quantidade em estoque do medicamento:\n");
        scanf("%d", &novoMedicamento.quantidade);
        
        if(validarQuantMedicamento(novoMedicamento) != 1){
            printf("Quantidade invalida! Digite novamente.\n");
        }
        
    } while(validarQuantMedicamento(novoMedicamento) != 1);   
    
    printf("\nMedicamento cadastrado com sucesso!\n");
    
    return novoMedicamento;
}

TpPrescricao cadastrarPrescricaoMedica(void){
    TpPrescricao novaPrescricao;
    char auxNomeResidente[50],
         auxNomeMedicamento[50];
    int posResidente = 0,
        posMedicamento = 0;
    
    printf("\n==================================\n");
    printf("      CADASTRO DE PRESCRICAO        \n");
    printf("==================================\n");

    do{
        getchar();
        printf("Digite o nome do residente:\n");
        fgets(auxNomeResidente, 50, stdin); 
        auxNomeResidente[strcspn(auxNomeResidente, "\n")] = '\0';
        
        if(validarNomes(auxNomeResidente) == 0){
            printf("Nome invalido!\n");
        } else {
            posResidente = buscarResidente(auxNomeResidente);
            if(posResidente == -1){
                printf("Esse nome nao existe na lista de cadastrados!\n");
        } 
        }
    } while(posResidente == -1 || validarNomes(auxNomeResidente) == 0);
    
    novaPrescricao.residente = listaResidentes[posResidente];
    
    posMedicamento = buscarMedicamentos();
    
    novaPrescricao.medicamento = listaMedicamentos[posMedicamento];
    
    novaPrescricao.quantidadeEstoque = listaMedicamentos[posMedicamento].quantidade;
    
    novaPrescricao.tomando = 'S';
    
    novaPrescricao.identificador = autoPrescricao;
    autoPrescricao++;
    totalPrescricao++;
    
    printf("\nPrescricao cadastrada com sucesso!\n");
    
    return novaPrescricao;
}

TpRegistroDeAdministracao RegistrarAdministracaoMedicamento(void){
    TpRegistroDeAdministracao novoRegistro;
    int validacaoData = 0,
        posPrescricao = -1;
    
    printf("\n==================================\n");
    printf("      REGISTRO DE ADMINISTRACAO        \n");
    printf("==================================\n");
    getchar();
    
    novoRegistro.idEnfermeiro = identificarEnfermeiro();
    
    posPrescricao = buscarPrescricoes();
    
    novoRegistro.idDaPrescricao = listaPrescricao[posPrescricao].identificador;
    
    do{
        printf("\nData que este medicamento esta sendo administrado:\n");
        scanf("%d/%d/%d", &novoRegistro.dataDaAdministracao.dia, &novoRegistro.dataDaAdministracao.mes, &novoRegistro.dataDaAdministracao.ano);
        
        if(validarDatas(novoRegistro.dataDaAdministracao) != 1){
            printf("Data invalida! Digite novamente (dd/mm/aaaa):\n");
        }
    } while(validarDatas(novoRegistro.dataDaAdministracao) != 1);
    
    printf("\nHorario que este medicamento esta sendo administrado:\n");
    scanf("%d", &novoRegistro.horaDaAdministracao);
    
    listaPrescricao[posPrescricao].quantidadeEstoque -= listaPrescricao[posPrescricao].medicamento.dosagem;
    
    if(identificarEstoqueBaixo(listaPrescricao[posPrescricao]) == 1){
        printf("\nATENCAO: Estoque baixo da medicacao!\n");
    }
    
    printf("Registro realizado com sucesso!\n");
    totalRegistros++;
    
    return novoRegistro;
}

TpResidente cadastrarResidentes(void){
    TpResidente novoResidente;
    char auxNomeResidente[50];
    
    printf("\n==================================\n");
    printf("      CADASTRO DE RESIDENTES        \n");
    printf("==================================\n");
    getchar();

    do{
        printf("\nDigite o nome do residente:\n");
        fgets(auxNomeResidente, 50, stdin); 
        auxNomeResidente[strcspn(auxNomeResidente, "\n")] = '\0';
        
        if(validarNomes(auxNomeResidente) != 1){
            printf("Nome invalido! Digite novamente.\n");
        }
        
    } while(validarNomes(auxNomeResidente) != 1);
    strcpy(novoResidente.nomeDoResidente, auxNomeResidente);
    
    do{
        printf("\nDigite o contato do responsavel pelo residente:\n");
        fgets(novoResidente.contatoDoResponsavel, 15, stdin);
        novoResidente.contatoDoResponsavel[strcspn(novoResidente.contatoDoResponsavel, "\n")] = '\0';
        
        if(validarTelefones(novoResidente.contatoDoResponsavel) != 1){
            printf("Telefone invalido! Digite novamente.\n");
        }
        
    } while(validarTelefones(novoResidente.contatoDoResponsavel) != 1);
   
    do{
        printf("\nDigite a data de nascimento:\n");
        scanf("%d/%d/%d", &novoResidente.dataNascimento.dia, &novoResidente.dataNascimento.mes, &novoResidente.dataNascimento.ano);
        
        if(validarDatas(novoResidente.dataNascimento) != 1){
            printf("Data invalida! Digite novamente (dd/mm/aaaa):\n");
        }

    } while(validarDatas(novoResidente.dataNascimento) != 1);

    printf("\nResidente cadastrado com sucesso!\n");
    return novoResidente;
}

void alterarStatusTomando(void){
    int auxIdPrescricao = 0, 
        indice = 0;
    char novoStatus;

    do {
        printf("\nDigite o ID da prescricao que deseja alterar: ");
        scanf("%d", &auxIdPrescricao);
        getchar(); 

        indice = buscarPrescricaoId(auxIdPrescricao); 

        if(indice == -1){
            printf("Prescricao inexistente. Digite novamente.\n");
        }
        
    } while(indice == -1);


    do{
        printf("\nDigite o novo status (S = tomando / N = interrompido): ");
        scanf(" %c", &novoStatus);

        if(novoStatus == 'S' || novoStatus == 'N'){
            listaPrescricao[indice].tomando = novoStatus;
            printf("Status atualizado com sucesso!\n");
        } else {
            printf("Status invalido.\n");
        }
        
    } while(novoStatus != 'S' && novoStatus != 'N');

}

void buscarResidentes(void){
    char nomePesquisado[50];
    int pesquisa = -1;
    
    getchar();
    
    do{
        printf("Digite o nome do residente que deseja buscar:\n");
        fgets(nomePesquisado, 50, stdin); 
        nomePesquisado[strcspn(nomePesquisado, "\n")] = '\0';
        
        if(validarNomes(nomePesquisado) == 0){
            printf("\nNome invalido!\n");
        } else {
            pesquisa = buscarResidente(nomePesquisado);
            if(pesquisa == -1){
                printf("\nEsse nome nao existe na lista de cadastrados!\n");
            } else {
                imprimirDadosResidentes(listaResidentes[pesquisa]);
            }
        }
    } while(pesquisa == -1);
}

void imprimirDadosPrescricao(TpPrescricao aux){
    printf("\n==================================\n");
    printf("       LISTA DE PRESCRICOES        \n");
    printf("==================================\n\n");

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("|     ID | Residente                                | Medicamento                  | Quantidade |   Tomando   |\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("| %6d | %-40s | %-28s |    %03d     |      %c      |\n",
           aux.identificador, aux.residente.nomeDoResidente, aux.medicamento.nomeDoMedicamento, aux.quantidadeEstoque, aux.tomando);
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void imprimirDadosResidentes(TpResidente r){
    printf("\n==================================\n");
    printf("       LISTA DE RESIDENTES        \n");
    printf("==================================\n");
    printf("\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| Nome                                           | Telefone                     | Data       |\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| %-46s | %-28s | %02d/%02d/%04d |\n", r.nomeDoResidente, r.contatoDoResponsavel, r.dataNascimento.dia, r.dataNascimento.mes, r.dataNascimento.ano);
    printf("----------------------------------------------------------------------------------------------\n");
}

void preencher(void){
    
    TpData datas[] = {{10, 5, 1980}, {22, 8, 2006}, {10, 11, 2025}, {18, 11, 2025}};
    
    strcpy(listaResidentes[0].nomeDoResidente, "Maria Silva Pereira");
    strcpy(listaResidentes[0].contatoDoResponsavel, "013988491606");
    listaResidentes[0].dataNascimento = datas[0];
    
    strcpy(listaResidentes[1].nomeDoResidente, "Joao da Silva Ferreira");
    strcpy(listaResidentes[1].contatoDoResponsavel, "013597845143");
    listaResidentes[1].dataNascimento = datas[1];
    
    strcpy(listaMedicamentos[0].nomeDoMedicamento, "Dipirona");
    listaMedicamentos[0].dosagem = 1;
    listaMedicamentos[0].periodo = 8;
    listaMedicamentos[0].quantidade = 3;

    strcpy(listaMedicamentos[1].nomeDoMedicamento, "Paracetamol");
    listaMedicamentos[1].dosagem = 1;
    listaMedicamentos[1].periodo = 6;
    listaMedicamentos[1].quantidade = 50;
    
    listaPrescricao[0].identificador = 1;
    listaPrescricao[0].residente = listaResidentes[0];
    listaPrescricao[0].medicamento = listaMedicamentos[0];
    listaPrescricao[0].quantidadeEstoque = listaMedicamentos[0].quantidade;
    listaPrescricao[0].tomando = 'S';
    
    listaPrescricao[1].identificador = 2;
    listaPrescricao[1].residente = listaResidentes[1];
    listaPrescricao[1].medicamento = listaMedicamentos[1];
    listaPrescricao[1].quantidadeEstoque = listaMedicamentos[1].quantidade;
    listaPrescricao[1].tomando = 'N';
    
    listaRegistros[0].idDaPrescricao = 1;
    listaRegistros[0].dataDaAdministracao = datas[2];
    
    listaRegistros[1].idDaPrescricao = 2;
    listaRegistros[1].dataDaAdministracao = datas[3];
}

void verificarRegistroAdministracao(int posPrescricao){
    TpPrescricao presc = listaPrescricao[posPrescricao];
    int i, diasSemAdministrar, interrompeu = 0;
    TpData dataUltima, dataAtual;

    do{
        printf("\nDigite a data atual: ");
        scanf(" %d/%d/%d", &dataAtual.dia, &dataAtual.mes, &dataAtual.ano);

        if(validarDatas(dataAtual) != 1){
            printf("Data invalida! Digite novamente.\n");
        }
    } while(validarDatas(dataAtual) != 1);

    i = obterUltimoRegistro(presc.identificador);
    if(i == -1){
        printf("Nenhum registro para esta prescricao!\n");
        return;
    }

    dataUltima = listaRegistros[i].dataDaAdministracao;
    diasSemAdministrar = compararDatas(dataAtual, dataUltima);

    if(diasSemAdministrar > 7 || presc.tomando == 'N'){
        interrompeu = 1;
    }

    if(interrompeu){
        printf("\nO residente interrompeu o uso da medicacao\n");
        imprimirDadosPrescricao(presc);
    } else {
        printf("\nResidente nao interrompeu o uso da medicacao\n");
    }
}


//main
int main(){   
    int resp = 0, aux = 0, pos = 0;

    preencher();
    
    while(resp != 8){
        resp = Menu();

        if(resp == 1){
            listaResidentes[totalResidentes] = cadastrarResidentes();
            totalResidentes++;
        }
    
        if(resp == 2){
            listaMedicamentos[totalMedicamentos] = cadastrarMedicamento();
            totalMedicamentos++;
        }
        
        if(resp == 3){
            if(totalResidentes == 0){
                getchar();
                printf("Nao ha residentes cadastrados ainda!\n");
            } else {
                listaPrescricao[totalPrescricao] = cadastrarPrescricaoMedica();
                totalPrescricao++;
            }
        }
    
        if(resp == 4){
            if(totalResidentes == 0){
                getchar();
                printf("Nao ha residentes cadastrados ainda!\n");
            } else {
                buscarResidentes();
            }
        }
        
        if(resp == 5){
            if(totalPrescricao == 0){
                getchar();
                printf("Para registrar uma administracao e necessario que tenha prescricoes cadastradas\n");
            } else {
                RegistrarAdministracaoMedicamento();
            }
        }
        
        if(resp == 6){
            aux = buscarPrescricoes();
            verificarRegistroAdministracao(aux);
        }
        
        if(resp == 7){
            alterarStatusTomando();
        }
    }
    
    return 0;
}