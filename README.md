# MedTrack - Sistema de Gestão de Medicamentos

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Focus](https://img.shields.io/badge/Focus-Health__Tech_%26_Data-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

## 🏥 Gestão de Dosagem e Medicação (ODS 3: Saúde e Bem-estar)
Muitas pessoas precisam fazer uso contínuo de medicamentos, seja para tratar doenças crônicas, controlar condições de saúde ou atender a outras necessidades específicas. A gestão correta da medicação é essencial para garantir a eficácia dos tratamentos e evitar erros que possam comprometer a saúde. Em um asilo, assegurar que os moradores tomem seus medicamentos nos horários corretos e manter o controle adequado do estoque são fatores fundamentais para a qualidade do cuidado prestado.

## 📌 Sobre o Projeto
O **MedTrack** é um programa desenvolvido em **Linguagem C**, com o  objetivo de simular um sistema para o controle e gerenciamento de medicações utilizadas pelos residentes de um asilo, com foco na organização das dosagens e no agendamento dos horários de administração. 

Embora desenvolvido como base acadêmica na disciplina de Algoritmos 1 do primeiro semestre de Engenharia de Computação, o projeto foi arquitetado para simular regras de negócio reais de **Health Tech**, focando na integridade dos dados, controle de estoque e na rastreabilidade da administração de medicamentos.

## 📂 Estrutura do Repositório

```bash
📁 MedTrack/
│
├── 📄 README.md        # Documentação técnica e funcional do projeto
├── 📄 .gitignore       # Configuração para ignorar arquivos compilados (.exe/.out)
│
└── 📁 src/             # Source Code (Código Fonte)
    └── 📄 main.c       # Arquivo principal contendo as Structs e Regras de Negócio
```

## ⚙️ Funcionalidades do sistema

### 1. Validação de Dados

* **Validação de Nomes:** Função `validarNomes()` - Assegura que o input seja um nome composto, sem números e com tamanho mínimo (>8 caracteres).
* **Validação de Contato:** Função `validarTelefones()` - Verifica formatação padrão (11/12 dígitos) e dígito inicial '0'.
* **Validação Temporal:** Função `validarDatas()` - Algoritmo baseado no calendário gregoriano para validar dias, meses e anos bissextos.

### 2. Gestão de Cadastros
* **Cadastro de Residentes:** Função `cadastrarResidentes()` - Coleta e valida dados pessoais.
* **Cadastro de Medicamentos:** Função `cadastrarMedicamento()` - Registra dosagem, período e quantidade inicial.
* **Busca Otimizada:** Funções `buscarResidentes()` e `buscarMedicamentos()` utilizam busca linear para encontrar os dados.

### 3. Prescrição e Tratamento
* **Gerar Prescrição:** Função `cadastrarPrescricaoMedica()` - Gera um identificador único vinculando um **Residente** a um **Medicamento** e inicializa o status como "Tomando".
* **Consulta de Receitas:** Função `buscarPrescricoes()` - Permite localizar tratamentos ativos pelo nome do paciente ou ID único.

### 4. Rastreabilidade
* **Registro de Dose:** Função `RegistrarAdministracaoMedicamento()` - Registra cada dose administrada com carimbo de tempo (Data/Hora) e identifica o **Enfermeiro responsável** pelo procedimento.
* **Baixa Automática:** A cada registro, o sistema decrementa automaticamente a quantidade do estoque físico vinculado a determinada prescrição.

### 5. Monitoramento e alertas
* **Alerta de Estoque Crítico:** Função `identificarEstoqueBaixo()` - Identifica os medicamentos que atingiram **10% ou menos** da capacidade da cartela, sinalizando necessidade de reposição enquanto o paciente ainda está em tratamento.
* **Auditoria de Conformidade:** Função `verificarRegistroAdministracao()` - Cruza a data atual com a última administração (`obterUltimoRegistro`) para identificar interrupções de tratamento superiores a 7 dias ou falhas de registro.