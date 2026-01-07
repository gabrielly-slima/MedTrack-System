# 🏥 MedTrack - Sistema de Gestão Medicamentosa

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Focus](https://img.shields.io/badge/Focus-Health__Tech_%26_Data-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

## 📌 Sobre o Projeto
O **MedTrack** é um sistema desenvolvido em **Linguagem C** focado na gestão segura de medicamentos e adesão ao tratamento em ambientes residenciais de saúde.

Embora desenvolvido como base acadêmica na disciplina de Algoritmos e Estrutura de Dados 1, o projeto foi arquitetado para simular regras de negócio reais de **Health Tech**, focando na integridade dos dados, controle de estoque e na rastreabilidade da administração medicamentosa.

## 🎯 Conexão com Análise de Dados & Health Tech
Como estudante de Engenharia de Computação em transição para a área de Dados, projetei este sistema pensando não apenas na entrada e saída (I/O), mas na **qualidade e utilidade do dado gerado**.

Destaques da lógica implementada com foco em dados:

* **Modelagem de Dados (Structs):** Implementação de estruturas relacionais em memória, vinculando entidades (Residentes $\leftrightarrow$ Prescrições $\leftrightarrow$ Histórico), simulando a lógica de chaves estrangeiras (Foreign Keys) de um Banco de Dados Relacional.
* **Auditoria de Adesão (Data Quality):** Desenvolvimento de um algoritmo de auditoria (`verificarRegistroAdministracao`) que calcula automaticamente o intervalo entre as datas de administração, identificando possíveis abandonos de tratamento (Compliance).
* **Lógica Preditiva de Estoque:** Monitoramento ativo que gera alertas automáticos quando o estoque atinge níveis críticos (10%), prevenindo a quebra na continuidade do tratamento.

## 📊 Arquitetura do Sistema

### 1. Modelagem das Entidades (Dados)
A estrutura abaixo demonstra como os dados foram organizados via `structs` para garantir a consistência das informações:

```mermaid
classDiagram
    direction LR
    class Residente {
        string nome
        string contatoResponsavel
        date dataNascimento
    }

    class Medicamento {
        string nome
        int dosagem
        int periodo
        int estoque
    }

    class Prescricao {
        int id
        char tomando
        int qtdEstoque
    }

    class RegistroAdministracao {
        int idEnfermeiro
        date dataHora
    }

    Residente "1" --> "N" Prescricao : Recebe
    Medicamento "1" --> "N" Prescricao : Compõe
    Prescricao "1" --> "N" RegistroAdministracao : Gera Histórico

    graph TD
    A[Início / Menu Principal] -->|Input| B{Opções}
    B -->|Cadastro| C[Dados Mestres: Residentes/Medicamentos]
    B -->|Processo| D[Prescrição Médica]
    C -.->|Vincula| D
    B -->|Operação| E[Registro de Administração]
    E -->|Validação| E1{Identificar Enfermeiro}
    E1 -->|Sucesso| E2[Baixa no Estoque & Log]
    E2 --> E3[Alerta: Estoque Baixo?]
    B -->|Analytics| F[Auditoria de Compliance]
    F -->|Cálculo| F1[Verificar Interrupção do Tratamento]