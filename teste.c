#include <stdio.h>
#include <math.h>
#include "xwc.h"

int main(int ac, char **av)
{
  int ii, c;
  double a;
  char cc[256];
  WINDOW *w;

  puts("Iniciando o sistema gráfico e abrindo uma janela");
  w = InitGraph(400,400, "Janelao");
  
  for (ii = 0; ii < 400; ii++)
	WPlot(w,ii,200, ii%3);
  WLine(w,1,1,300,300,2);

  puts("Aperte <enter>");
  getchar();
  for (a = 0.; a < 1.75; a+=.1)
    WLine(w,0,0,100, 100*tan(a), 23);

  WCor(w,c=WNamedColor("gold"));
  printf("::%d::\n",c);
  WPrint(w,10,10,"So isso");

  c = WNamedColor("Red");
  puts("Agora,  escreva vários nomes de cores,  ou uma cor no  formato\n"
	   "'#RRGGBB',  onde RR,  GG e BB correspondem às intensidades, em\n"
	   "hexadecimal,  das componentes vermelha,  verde e azul, respec.\n"
	   "Os nomes válidos de cores estão em /usr/X11R6/lib/X11/rgb.txt.\n"
	   "Termine a lista de cores com um 'q'.");

  for(;;) {
    scanf("%s", cc);
    if ((cc[0]=='q') && (cc[1]=='\x0')) break;
    c=WNamedColor(cc);
    WFillRect(w,20,20, 80, 230, c);
  }
  CloseGraph();
  return 0;
}


