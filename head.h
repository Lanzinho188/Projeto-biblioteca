#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define limp "clear"  // Alterar para "cls" caso seja executado no Windows

// Estrutura para informações de data
typedef struct 
{
  int day;  // Dia
  int month;  // Mês
  int year; // Ano
}date;

// Estrutura para dados do livro
typedef struct nodeB
{
  char name[60];             // Nome do livro
  char area[20];             // Área do conhecimento do livro 
  char isbn[20];            // ISBN do livro
  char author[60];          // Autor do livro
  char language[20];        // Idioma do livro
  int amount;               //Quantidade disponível na biblioteca
  date loanDate;            // Data para empréstimo do livro  
  date dueDate;             // Data para devolução do livro

  struct nodeB *previous;
  struct nodeB *next;
}book;

// Estrutua para monitorar os livros cadastrados
typedef struct 
{
  book *first; 
  book *last;  
}bookControl;

// Estrutura para dados do estudante
typedef struct nodeS
{
  char name[60];          // Nome do aluno
  char cpf[20];           // CPF do aluno
  date nasc;              // Data de nascimento do aluno
  long int ra;            // Registro de aluno
  int bookLimit;          // Limite de livro do estudante
  bookControl studList;   // Lista de livros emprestados

  struct nodeS *previous;
  struct nodeS *next;
}student;

// Estrutura para monitorar os estudantes cadastrados
typedef struct
{
  int totalStud; // Total de estudantes cadastrados
  student *first;
  student *last;
}studentControl;

bookControl listBook;         // Lista de livros
studentControl listStud;      // Lista de estudantes

// Função inicializa as estruturas
void init_structs(bookControl *bc, studentControl *sc)
{
  bc->first = NULL;
  bc->last = NULL;

  sc->first = NULL;
  sc->last = NULL;
  sc->totalStud = 0;
}

// Função encontrar livro pelo ISBN
book *find_book(char *isbnAux, bookControl *bc)
{
  book *auxBook = bc->first;      // Primeiro da lista

  while (auxBook != NULL)
  {
    if (strcasecmp(auxBook->isbn, isbnAux)==0) {      // Encontrou
      return auxBook; 
    }
    auxBook = auxBook->next;
  } 
  return NULL;  // Não encontrou 
}

// Função encontrar estudante pelo RA(Registro de Aluno)
student *find_stud_ra(long int *auxRa, studentControl *sc)
{
  student *auxStud = sc->first;   // Primeiro da lista
  
  while(auxStud != NULL)
  {
    if (auxStud->ra == *auxRa) {    // Encontrou
      return auxStud;
    }
    auxStud = auxStud->next;
  }
  return NULL;    // Não encontrou
}

// Função encontrar estudante pelo CPF
bool find_stud_cpf(char *auxCpf)
{
  student *auxStud = listStud.first;    // Primeiro da lista de estudantes

  while (auxStud != NULL)
  {
    if (strcasecmp(auxStud->cpf, auxCpf)==0) {    // Encontrou
      return true;
    }
    auxStud = auxStud->next;
  }
  return false;   // Não encontrou
}

// Função validar ISBN
bool validate_isbn(char *isbn)
{
  char auxIsbn[20];
  int j = 0, length;

  // Colocar apenas os caracteres alfanum na string auxiliar
  for(int i=0; isbn[i] != '\0'; i++)
  {
    if (isdigit(isbn[i])) {   // verifica se é dígito
      auxIsbn[j++] = isbn[i];
    }
  }

  auxIsbn[j] = '\0';          // Final de auxIsbn
  length = strlen(auxIsbn);   // Comprimento de auxIsbn

  if(length == 13) { return true; } 
  else { return false; }
}

// Função validar CPF
bool validate_cpf(char *auxCpf)
{
  size_t length = strlen(auxCpf);   // Comprimento do CPF
  if(length < 11) { return false; }     // CPF inválido

  int j = 0;
  int d1 = 0, d2 = 0;
  int vet_aux[20], dig_verif[2];

  // Eliminar os carateres especiais
  for (int i = 0; auxCpf[i] != '\0'; i++) 
  {
    if (isdigit(auxCpf[i])) // Verifica se é dígito
    { 
      char digit = auxCpf[i];  // Recebe o carácter
      vet_aux[j++] = digit - '0'; // Converte o carácter para inteiro
    }
  }

  j = 10;
  for (int i = 0; i < 9; i++) {    // Encontrar o primeiro digíto verificador
    d1 += vet_aux[i] * j; 
    j--;
  }

  d1 = d1 % 11;
  dig_verif[0] = (d1 < 2) ? 0 : 11 - d1;

  j = 11;
  for (int i = 0; i < 10; i++) {    // Encontrar o segunddo dígito verificador
    d2 += vet_aux[i] * j;
    j--;
  }

  d2 = d2 % 11;
  dig_verif[1] = (d2 < 2) ? 0 : 11 - d2; 

  if ((vet_aux[9] == dig_verif[0]) && (vet_aux[10] == dig_verif[1])) {    // Válido
    return true; 
  }
  else { return false; }  // Inválido
}

// Função verificar quantidade de livros
bool verify_number(int *num)
{
  if(*num > 0) { return true; }    // Quantidade válida
  else { return false; } 
}

// Função Limpar bufferr
void clear_buffer() { while (getchar() != '\n'); }

// Função inserir estudante
void insert_student(student *New, studentControl *auxList)
{
  New->next = NULL;
  New->previous = NULL;
  
  if (auxList->first == NULL)   // Inserir na lista vazia
  {
    auxList->first = New;
    auxList->last = New;
  }   
  else    // Inserir na lista não vazia
  {
    New->previous = auxList->last;
    auxList->last->next = New;
    auxList->last = New;
  }
  auxList->totalStud ++;
}

// Função inserir livro
void insert_book(book *New, bookControl *auxList)
{
  New->next = NULL;
  New->previous = NULL;

  if (auxList->first == NULL)   // Inserir na lista vazia
  {
    auxList->first = New;
    auxList->last = New;
  } 
  else  // Inserir na lista não vazia
  {
    New->previous = auxList->last;
    auxList->last->next = New;
    auxList->last = New;
  }
}

// Função preencher dados do livro
void fill_book()
{
  int val = 0;

  book *newBook = (book*)malloc(sizeof(book));
  book *auxBook = NULL;   // Ponteiro auxiliar para um livro já inserido

  if (newBook == NULL)    // Sem memória disponível
  {
    printf("Erro: Não foi possível alocar memória!\n");
    printf("Programa encerrado.\n");
    exit(1);
  }

  printf("Você está na área para cadastro de livros:\n\n");
  printf("Informe o ISBN: ");
  scanf("%s", newBook->isbn);

  while(!validate_isbn(newBook->isbn))    // Exige um isbn com 13 dígitos
  {
    printf("\nPor favor, informe um ISBN com 13 dígitos!\nInforme o ISBN: ");
    scanf("%s", newBook->isbn);
  }

  auxBook = find_book(newBook->isbn, &listBook);  // Procura o livro
  if(auxBook != NULL)   // Livro já cadastrado
  {
    printf("O livro com ISBN (%s) já estar cadastrado!\n", auxBook->isbn);
    printf("Informe a quantidade a ser incrementada: ");

    if (!scanf("%d", &val)) {   // Caso seja letra, limpa o buffer
      clear_buffer();
    }

    while (!verify_number(&val)) // Receber um valor maior que 0
    {
      printf("\nPor favor, informe uma quantidade válida: ");
      if (!scanf("%d", &val)) {   // Caso seja letra limpa o buffer
        clear_buffer();
      }
    }
    auxBook->amount += val;   // Incrementa a quantidade
    free(newBook);  // Libera a memória de newBook

    system(limp);
    printf("Quantidade atualizada!\n");
    return;
  }

  printf("\nInforme o título: ");
  scanf(" %[^\n]", newBook->name);

  printf("Informe a área do conhecimento: ");
  scanf(" %[^\n]", newBook->area);

  printf("Informe o idioma: ");
  scanf(" %[^\n]", newBook->language);

  printf("Informe o nome do autor: ");
  scanf(" %[^\n]", newBook->author);

  printf("Informe a quantidade disponível: ");
  if(!scanf("%d", &val)) {clear_buffer();}  // Caso seja letra limpa o buffer

  while (!verify_number(&val)) // Receber um valor maior que 0
  {
    printf("Por favor, informe uma quantidade válida: ");
    if (!scanf("%d", &val)) {   // Caso seja letra, limpa o buffer
      clear_buffer();
    }
  }
  newBook->amount = val;

  insert_book(newBook, &listBook); // Insere o livro na lista

  system(limp);
  printf("Livro cadastrado com sucesso!\n");
}

// Função preencher dados do estudante
void fill_student()
{
  student *newStud = (student*)malloc(sizeof(student));
  date *auxNasc = &newStud->nasc;

  if (newStud == NULL)  // Sem memória disponível
  {
    printf("Erro: Não foi possível alocar memória!\n");
    printf("Programa encerrado.\n");
    exit(1);
  }

  printf("Você está na área para cadastro de alunos:\n\n");
  printf("CPF [xxx.xxx.xxx-xx]: ");
  scanf("%s", newStud->cpf);

  while(!validate_cpf(newStud->cpf))    // Inserir cpf válido
  {
    printf("\nO CPF que você informou não é valido!\n");
    printf("Tente novamente.\nCPF [xxx.xxx.xxx-xx]: "); 
    scanf("%s", newStud->cpf);
  }

  if(find_stud_cpf(newStud->cpf))  // Estudante já cadastrado
  {
    free(newStud);  // Libera a memória de newStud
    system(limp);
    printf("O estudante já está cadastrado!\n");
    return;
  }

  printf("Informe o nome: ");
  scanf(" %[^\n]", newStud->name);

  printf("Informe a data de nascimento (dd/mm/aaa): ");
  scanf("%d/%d/%d", &auxNasc->day, &auxNasc->month, &auxNasc->year);

  newStud->bookLimit = 0;
  newStud->ra = (rand() % 90000000) + 10000000; // Registro de Aluno(RA) de 8 dígitos

  insert_student(newStud, &listStud);  // Insere o estudante na lista

  system(limp);
  printf("Estudante cadastrado com sucesso!\n");
}

// Função imprimir informações do livro
void info_book(book *aux)
{
  printf("\n\t\t---------------------------------------- ");
  printf("\n\t\t| Título: %s", aux->name);
  printf("\n\t\t| Área do conhecimento: %s", aux->area);
  printf("\n\t\t| ISBN: %s", aux->isbn);
  printf("\n\t\t| Idioma: %s", aux->language);
  printf("\n\t\t| Autor: %s", aux->author);
  printf("\n\t\t| Quantidade: %d", aux->amount);
  printf("\n\t\t|--------------------------------------- ");
}

// Função imprimir informações do estudante
void info_student(student *auxStud)
{
  date aux = auxStud->nasc;
  printf("\n\t\t|-----------------------------------------");
  printf("\n\t\t| Nome: %s", auxStud->name);
  printf("\n\t\t| CPF: %s", auxStud->cpf);
  printf("\n\t\t| Data de nascismento: %02d/%02d/%d", aux.day, aux.month, aux.year);
  printf("\n\t\t| Livros emprestados: %d", auxStud->bookLimit);
  printf("\n\t\t| RA: %ld", auxStud->ra);
  printf("\n\t\t|-----------------------------------------\n");
}

// Função imprimir estudantes cadastrados
void print_student()
{
  if (listStud.totalStud == 0)  {  // Lista vazia
    printf("Não há estudantes cadastrado.\n");
    return;
  }

  student *auxStud = listStud.first;    // Primeiro da lista
  while(auxStud != NULL) 
  {
    info_student(auxStud);
    auxStud = auxStud->next;
  }
}

// Função imprimir total de livros cadastrados
int print_total_book(bookControl *bc)
{
  int soma = 0;
  book *auxBook = bc->first;  // Primeiro da lista

  while(auxBook != NULL)
  {
    soma += auxBook->amount;
    auxBook = auxBook->next;
  }
  return soma;
}

// Função imprimir livros cadastrados
void print_book(bookControl *bc)
{
  if (print_total_book(bc) == 0) {    // Lista vazia
    printf("Não há livros disponíveis no momento.\n");
    return;
  }

  book *aux = bc->first;  // Primeiro da lista
  while (aux != NULL) 
  {
    info_book(aux);
    aux = aux->next;
  }
}

// Função remover livro
void remove_book(book *aux_book, bookControl *bc)
{
  if(bc->first == aux_book && aux_book->next == NULL) // Lista com um elemento
  {
    bc->first = NULL;
    bc->last = NULL;
    return;
  }

  if(bc->first == aux_book) // Lista com mais de um elemento. Remover no início 
  {
    bc->first = aux_book->next;
    bc->first->previous = NULL;
  }
  else 
  {
    book *pos = aux_book->next;
    book *pre = aux_book->previous;

    if (pos == NULL) {  // Remover elemento no final da lista
      bc->last = aux_book->previous;
      bc->last->next = NULL;
    }
    else {  // Remover elemento no meio da lista
      pre->next = pos;
      pos->previous = pre;
    }
  }
}

// Função verificar a escolha do usuário
char opc_user()
{
  char opc = ' '; // Inicializa com nulo

  while((opc != 'S' && opc != 's') && (opc !='N' && opc != 'n'))  // Opção
  {
    printf("\nTem livro com outro ISBN?\n[S/s] = Sim [N/n] = Não: ");
    scanf(" %c", &opc);
  }

  if ((opc == 'S') || (opc == 's')) {   // Sim
    return 'S'; 
  }
  else { return 'N'; }
}

// Função calcular data do empréstimo
void loan_date(book *auxBook)
{
  time_t temp;
  struct tm *infoTemp;

  time(&temp);                    // Obtem o tempo atual em segundos
  infoTemp = localtime(&temp);    // Converte o tempo em segundos para dados legíveis

  // Data de empréstimo
  auxBook->loanDate.day = infoTemp->tm_mday;          // Dia ataul
  auxBook->loanDate.month = infoTemp->tm_mon + 1;     // Mês atual (0/11) + 1
  auxBook->loanDate.year = infoTemp->tm_year + 1900;  // Ano atual desde de 1900 
  
  temp += (7 * 24 * 60 * 60);   // Aumenta temp em 7 dias (7*86400)segundos
  infoTemp = localtime(&temp);  // Converte novamente

  /*
    OBS: Como o programa não vai ficar rodando em um servidor, para testar o cálculo de possíveis multas, altere os campos de Data de devolução abaixo
  */

  // Data de devolução Após 7 dias
  auxBook->dueDate.day = 05;       // Dia de devolução
  auxBook->dueDate.month = 12;    // Mês de devolução 
  auxBook->dueDate.year = 2023; // Ano de devolução
}

// Função imprimir informações de livros emprestados
void print_loan()
{
  long int auxRa;
  student *auxStud = NULL;
  book *auxBook = NULL;
  date auxld;
  date auxdd;

  printf("Informe o RA do aluno: ");
  scanf("%ld", &auxRa);

  auxStud = find_stud_ra(&auxRa, &listStud);  // Busca o cadastro no sistema 

    system(limp);
  if (auxStud == NULL) {  // Não encontrou
    printf("O estudante não está cadastrado no sistema.\n");
  }
  else  // Encontrou
  {
    auxBook = auxStud->studList.first; 
    if(auxBook != NULL)   // Verificase tem livros emprestados
    {
      auxld = auxBook->loanDate;  // Data de saída do livro
      auxdd = auxBook->dueDate;   // Data de devolução do livro

      printf("Dados:\n");
      while (auxBook != NULL)
      {
        info_book(auxBook); // Informações do livro
        printf("\n\t\t|Data de saída: %02d/%02d/%d", auxld.day, auxld.month, auxld.year);
        printf("\n\t\t|Data de devolução: %02d/%02d/%d\n", auxdd.day, auxdd.month, auxdd.year);
        printf("\t\t|----------------------------------------");
        auxBook = auxBook->next;
      }
    }
    else {  // Estudante sem livros
      printf("Não há emprestimos para (%s).\n", auxStud->name);
    }
  }
}

// Função emprestar livro
void lend_book(bookControl *bc, studentControl *sc)
{
  if (print_total_book(bc) == 0) {    // Lista sem livros
    printf("Biblioteca Vazia.\n"); 
    return; 
  }

  long int auxRa;         // RA a ser buscado 
  int qtyLoan = 0;        // Quantidade de livros a ser emprestada
  int maxBook;            // Quantidade max de livros para o estudante 
  char auxIsbn[20];       // ISBN do livro a ser procurado
  bool teste = false;     // Condição de parada 

  student *auxStud = NULL; 
  book *auxBook = NULL;     
  book *auxBookStud = NULL;

  printf("Informe o RA do aluno: ");
  scanf("%ld", &auxRa);

  auxStud = find_stud_ra(&auxRa, sc);  // Busca o cadastro no sistema

  if (auxStud == NULL) {    // Não encontrou o cadastro
    system(limp);
    printf("O aluno não está cadastrado.\n");
  }
  else  
  {
    while(!teste)   // Enquanto emprestar livros de áreas diferentes
    {
      if (auxStud->bookLimit == 3)    // Estudante não pode pegar livros
      {
        printf("Estudante: (%s) com RA:(%ld),\n", auxStud->name, auxStud->ra);
        printf("já atingiu o limite máximo de livros.\n");
        return;
      }
      else  // Estudante com menos de 3 livros
      {
        printf("Informe o ISBN do livro: "); 
        scanf("%s", auxIsbn);

        auxBook = find_book(auxIsbn, &listBook); // Busca o cadastro do livro no sistema
        auxBookStud = find_book(auxIsbn, &auxStud->studList); // Busca o livro da lista de empréstimos do estudante  

        if(auxBook != NULL)  // Econtrou o livro na lista da biblioteca
        {
          maxBook = 3-auxStud->bookLimit;  // Quant. máxima de livros para o estudante

          while (!teste)  // Verifica a quantidade de livros do empréstimo
          {
            printf("Quantidade de livros a ser emprestada: ");
            scanf("%d", &qtyLoan);

            // Verifica se o aluno pode levar a quantidade desejada 
            if (qtyLoan > maxBook || qtyLoan <= 0) {
              printf("Estudante (%s) pode levar no máximo %d livro(s)!\n", auxStud->name, maxBook);
            }
            else { teste = true; }  // Caso a quantidade seja válida
          }
          if (auxBookStud != NULL) {            // Livro já emprestado 
            auxBookStud->amount += qtyLoan;     // Incrementa o(s) livro(s) do estudante  
          }
          else  // Emprestar a primeira vez
          {  
            book *bookCopy = (book*)malloc(sizeof(book));
            *bookCopy = *auxBook;  // Recebe uma cópia dos dados do livro

            bookCopy->amount = qtyLoan;  // Atribui a quantidade a ser emprestada na cópia
            insert_book(bookCopy, &auxStud->studList);  // Insere a cópia na lista de livros do estudante
            loan_date(bookCopy);  // Atribui a data de empréstimo e devolução
          }
          auxBook->amount -= qtyLoan; // Decrementa a quantidade do livro emprestado
          auxStud->bookLimit += qtyLoan;  // Incrementa o limite de livros do aluno

          // Verifica se tem livro(s) de outra área 
          if (opc_user() == 'S') {  // Continua o loop
            teste = false; 
          } 
        }
        else  // Não encontrou o livro no sistema
        { 
          printf("O livro não está cadastrado no sistema.\n");
          return;
        }
      }
      system(limp);
    }
  }
}

// Função verificar mês para a multa
int verify_month(int auxMonth, int auxYear)
{
  int daysInMonth;  // Quantidade de dias no mês

  // Meses com 30 dias
  if (auxMonth == 4 || auxMonth == 6 || auxMonth == 9 || auxMonth == 11) {
    // Abril, Junho, Setembro, Novembro
    daysInMonth = 30;
  }
  else if (auxMonth == 2)  // Verifica se o ano é bissexto para fevereiro
  {
    // Ano bissexto
    if ((auxYear % 4 == 0 && auxYear % 100 != 0) || (auxYear % 400 == 0)) {
      daysInMonth = 29;
    } 
    else {  // Mês fevereiro normal
      daysInMonth = 28; 
    }
  } 
  else {  // Meses com 31 dias: Janeiro, Março, Maio, Julho, Agosto, Outubro, Dezembro
    daysInMonth = 31; 
  }

  return daysInMonth;
}

// Função verificar multa do estudante
void check_fine(book *auxBook, int qBook)
{
  time_t temp;
  date dateDevo = auxBook->dueDate;  // Cópia da data de retorno do livro do estudante 
  int last_day;                     // Ultimo dia do mês  
  int auxDay, auxMonth, auxYear;    // dia, mês e ano auxiliar para hoje
  float fine = 0.0;                 // Multa
  struct tm *today;

  time(&temp);
  today = localtime(&temp);
  last_day = verify_month(dateDevo.month, dateDevo.year);  // Recebe o ultimo dia do mês

  auxDay = today->tm_mday;        // Dia atual
  auxMonth = today->tm_mon+1;     // Mês atual
  auxYear = today->tm_year +1900; // Ano atual

  // Devolução em dias. Sem multa
  if((auxDay <= dateDevo.day) && (auxMonth == dateDevo.month) && (auxYear <= dateDevo.year))
  {
    printf("Não há multas pendentes.\n");
  }
  else  // Calcula a multa pendente
  {
    if(dateDevo.month < auxMonth)  // Mês de hoje à frente do mês de devolução
    {
      for(int i = dateDevo.day; i <= last_day; i++)  // Percorre até chegar no dia e mês atual
      {
        if ((i == auxDay) && (dateDevo.month == auxMonth)) { // Econtrou o dia e mês atual 
          // Encerra o loop
          break;
        }

        if (i == last_day)  // Chegou no ultimo dia do mês de devolução
        {  
          i = 1;  // Reinicia o contador
          dateDevo.month++;  // Recebe o próximo mês
          last_day = verify_month(dateDevo.month, auxYear); // Último dia do próximo mês
        } 
        fine += qBook;  // Incrementa a multa de acordo com a quantidade de livros
      }
    }
    else // Outro ano. Mês atual menor que o mês de devolução
    {
      for(int j = dateDevo.day; j <= last_day; j++)  // Percorre até chegar no dia e mês atual
      {
        if ((j == auxDay) && (dateDevo.month == auxMonth)) { // Encontrou o dia e mês atual
          // Encerra o loop
          break;
        }

        if (j == last_day)  // contador igual ao último dia do mês de devolução
        {
          j = 1;  // Reinicia o contador
          dateDevo.month %= 11; // Recebe o mês o próximo ano 
          last_day = verify_month(dateDevo.month, dateDevo.year);  // Ultimo dia do próximo mês
        }
        fine += qBook;  // Incrementa a multa de acordo com a quantidade de livros
      }
    }
    printf("Multa pendente: R$ %.2f\n", fine);
  }
}

// Função receber livro emprestado
void receive_book(bookControl *bc)
{
  if(listStud.totalStud == 0) {
    printf("Não estudantes cadastrados.\n");
    return;
  }

  char auxIsbn[20];
  bool test = false;
  long int auxRa;
  int auxQty, maxDevo;

  book *auxStudBook = NULL;
  book *auxListBook = NULL;
  student *auxStud = NULL;

  printf("Informe o RA do aluno: ");
  scanf("%ld", &auxRa);

  auxStud = find_stud_ra(&auxRa, &listStud);  // Procura o cadastro no sistema

  if(auxStud != NULL)   // Encontrou
  {
    while(!test)
    {
      printf("Informe o ISBN do livro: ");
      scanf("%s", auxIsbn);

      auxStudBook = find_book(auxIsbn, &auxStud->studList); // Procura o livro na lista de empréstimos do estudante

      if(auxStudBook != NULL) // Econtrou
      {
        auxListBook = find_book(auxIsbn, bc);   // Procura o livro na lista da biblioteca

        maxDevo = auxStudBook->amount; // Quantidade máxima de devolução
        while(!test)  // Exige uma quantidade válida
        { 
          printf("O estudante pode devolver %d livro(s)\n", auxStudBook->amount);
          printf("Informe a quantidade a ser devolvida: ");
          scanf("%d", &auxQty);
          if((auxQty <= maxDevo) && (auxQty > 0)) { 
            test = true;
          }
        }
        check_fine(auxStudBook, auxQty);  // Verifica se tem multa

        if (auxQty == auxStudBook->amount) {    // Recebendo todos os livros emprestados
          remove_book(auxStudBook ,&auxStud->studList);
          free(auxStudBook);
        }
        else {
          auxStudBook->amount -= auxQty;
        }

        auxListBook->amount += auxQty;  // Aumenta a quantidade na biblioteca
        auxStud->bookLimit -= auxQty;   // Diminui a quantidade de livros do estudante 
      }
      else {
        printf("O livro não foi encontrado\n");
      }

      // Verifica se tem livro de outra área
      if(opc_user() == 'S') { test = false; }
      system(limp);
    }
  }
  else {
    printf("O estudante não está cadastrado no sistema!\n");
  }
}

//Função imprimir menu de opções
void print_menu()
{
  printf("\n\n\t\t\t\t\t   ========  \n");
  printf("\t\t\t\t\t   | MENU |\n");
  printf("\t\t\t|=============================================|\n");
  printf("\t\t\t| 1- Cadastrar livro                          |\n");
  printf("\t\t\t| 2- Cadastrar aluno                          |\n");
  printf("\t\t\t|=============================================|\n");
  printf("\t\t\t| 3- Consultar livros cadastrados             |\n");
  printf("\t\t\t| 4- Consultar alunos cadastrados             |\n");
  printf("\t\t\t|=============================================|\n");
  printf("\t\t\t| 5- Consultar quantidade total de livros     |\n");
  printf("\t\t\t| 6- Consultar livros pegues pelo estudante   |\n");
  printf("\t\t\t|=============================================|\n");
  printf("\t\t\t| 7- Fazer o empréstimo de livro(s)           |\n");
  printf("\t\t\t| 8- Receber livro emprestado                 |\n");
  printf("\t\t\t|=============================================|\n");
  printf("\t\t\t| 0- Encerrar e sair do programa              |\n");
  printf("\t\t\t|=============================================|\n\n");
  printf("-> ");
}