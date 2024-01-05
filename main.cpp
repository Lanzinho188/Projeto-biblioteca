#include <stdio.h>
#include "head.h"

// Execute essa parte 

int main()
{
  system(limp);
  srand(time(NULL));
  
  int opc = -1;
  init_structs(&listBook, &listStud); // Inicializa o campo das estruturas

  do
  {
    print_menu();
    if(scanf("%d", &opc))
    {
      switch (opc)
      {
        case 1:
          system(limp);
          fill_book(); 
          break;
    
        case 2:
          system(limp);
          fill_student();
          break;

        case 3:
          system(limp);
          print_book(&listBook);
          break;

        case 4:
          system(limp);
          print_student();
          break;
      
        case 5:
          system(limp);
          printf("Total: %d livros cadastrados.\n", print_total_book(&listBook));
          break;

        case 6:
          system(limp);
          print_loan();
          break;

        case 7:
          system(limp);
          lend_book(&listBook, &listStud); 
          break;
        
        case 8:
          system(limp);
          receive_book(&listBook);
          break;

        case 0:
          system(limp);
          printf("saindo ...\n");
          break;

        default:
          system(limp);
          printf("Opção inválida!\n");
          break;
      }
    }
    else { 
      system(limp);
      printf("Por favor, utilize números!\n");
      clear_buffer(); // Limpa o buffer de entrada
    }
  } while (opc != 0);
  
  return 0;
}