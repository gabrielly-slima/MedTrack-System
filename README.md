# MedTrack - Sistema de Gestão de Medicamentos

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Focus](https://img.shields.io/badge/Focus-Health__Tech_%26_Data-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

## 🏥 Gestão de Dosagem e Medicação (ODS 3: Saúde e Bem-estar)
Muitas pessoas precisam fazer uso contínuo de medicamentos, seja para tratar doenças crônicas, controlar condições de saúde ou atender a outras necessidades específicas. A gestão correta da medicação é essencial para garantir a eficácia dos tratamentos e evitar erros que possam comprometer a saúde. Em um asilo, assegurar que os moradores tomem seus medicamentos nos horários corretos e manter o controle adequado do estoque são fatores fundamentais para a qualidade do cuidado prestado.

## 📌 Sobre o Projeto
O **MedTrack** é um programa desenvolvido em **Linguagem C**, com o  objetivo de simular um sistema para o controle e gerenciamento de medicações utilizadas pelos residentes de um asilo, com foco na organização das dosagens e no agendamento dos horários de administração. 

Embora desenvolvido como base acadêmica na disciplina de Algoritmos 1 do primeiro semestre de Engenharia de Computação, o projeto foi arquitetado para simular regras de negócio reais de **Health Tech**, focando na integridade dos dados, controle de estoque e na rastreabilidade da administração de medicamentos.

## Estrutura do Repositório 
📁 MedTrack/
│
├── 📄 README.md        # Documentação do projeto (Você está aqui)
├── 📄 .gitignore       # Arquivo de exclusão de binários (.exe/.out)
│
└── 📁 src/             # Código Fonte
    └── 📄 main.c       # Lógica principal do sistema

## ⚙️ Funcionalidades do Sistema

### 1. Gestão de Cadastros e Data Quality
O sistema possui regras de validação na entrada para garantir a qualidade dos dados:
* **Validação de Residentes:** O sistema recusa nomes simples ou curtos (regra: > 8 caracteres, composto e sem números) e valida telefones de contato (formato 11/12 dígitos iniciando com '0').
* **Validação Temporal:** Possui um algoritmo de validação de datas baseado no calendário gregoriano (considerando anos bissextos e dias variáveis por mês).
* **Cadastro de Medicamentos:** Registro detalhado contendo nome, dosagem, frequência e vínculo com o residente.

### 2. Prescrição e Controle
* **Emissão de Prescrição:** Gera um identificador único vinculando um **Residente** a um **Medicamento**.
* **Controle de Status:** Gerencia automaticamente o estado do tratamento (Flag: *Tomando* / *Interrompido*).
* **Busca Otimizada:** Permite localizar prescrições tanto pelo **Nome do Paciente** quanto pelo **ID da Prescrição** para agilidade no dia a dia.

### 3. Registro de Administração (Rastreabilidade)
* **Log de Aplicação:** Registra cada dose administrada com carimbo de tempo (Data/Hora) e identifica o **Enfermeiro responsável** pelo procedimento.
* **Baixa Automática:** A cada registro, o sistema decrementa automaticamente a quantidade do estoque físico vinculado àquela prescrição.

### 4. Monitoramento e Alertas (Lógica de Negócio)
* **Alerta de Estoque Crítico:** Identifica os medicamentos que atingiram **10% ou menos** da capacidade da cartela, sinalizando a necessidade de reposição enquanto o paciente ainda está em tratamento.
* **Auditoria de Interrupção:** Relatório tabular que cruza dados para listar residentes que interromperam a medicação (Status: *Não*) mas ainda possuem estoque, filtrando casos onde a última administração ocorreu há mais de **7 dias**.
* **Detecção de Falhas:** Algoritmo que analisa o intervalo entre doses para sinalizar interrupções não planejadas ou esquecimentos.