# 🏥 MedTrack - Sistema de Gestão de Medicamentos

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Focus](https://img.shields.io/badge/Focus-Health__Tech_%26_Data-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

## Gestão de Dodagem e Medicação (ODS 3: Saúde e Bem-estar)
Muitas pessoas precisam fazer uso contínuo de medicamentos, seja para tratar doenças crônicas, controlar condições de saúde ou atender a outras necessidades específicas. A gestão correta da medicação é essencial para garantir a eficácia dos tratamentos e evitar erros que possam comprometer a saúde. Em um asilo, assegurar que os moradores tomem seus medicamentos nos horários corretos e manter o controle adequado do estoque são fatores fundamentais para a qualidade do cuidado prestado.

## 📌 Sobre o Projeto
O **MedTrack** é um programa desenvolvido em **Linguagem C**, com o  objetivo de simular um sistema para o controle e gerenciamento de medicações utilizadas pelos residentes de um asilo, com foco na organização das dosagens e no agendamento dos horários de administração. 

Embora desenvolvido como base acadêmica na disciplina de Algoritmos 1 do primeiro semestre de Engenharia de Computação, o projeto foi arquitetado para simular regras de negócio reais de **Health Tech**, focando na integridade dos dados, controle de estoque e na rastreabilidade da administração de medicamentos.

## 📊 Arquitetura do Sistema

### 1. Modelagem das Entidades (Dados)
A estrutura abaixo demonstra como os dados foram organizados via `structs`:

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
    Prescricao "1" --> "N" RegistroAdministracao : Gera Historico

graph TD
    A["Início / Menu Principal"] -->|Input| B{"Opções"}
    B -->|Cadastro| C["Dados Mestres: Residentes/Medicamentos"]
    B -->|Processo| D["Prescrição Médica"]
    C -.->|Vincula| D
    B -->|Operação| E["Registro de Administração"]
    E -->|Validação| E1{"Identificar Enfermeiro"}
    E1 -->|Sucesso| E2["Baixa no Estoque & Log"]
    E2 --> E3["Alerta: Estoque Baixo?"]
    B -->|Analytics| F["Auditoria de Compliance"]
    F -->|Cálculo| F1["Verificar Interrupção do Tratamento"]