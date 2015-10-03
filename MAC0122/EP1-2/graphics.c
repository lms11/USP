/* ************************************************************* */
/* *   Caio Henrique Cohn          9426575
  Vinicius Henrique Crispim Rosa   9395067                         
/* *   Exercício-Programa 1                                    * */
/* *   Professor: Fernando Mário Oliveira Filho                * */
/* *   Turma: 30                                               * */
/* ************************************************************* */
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>

  typedef struct circle Circle;
  typedef struct line Line;

  struct drawing_struct{
    Line *l;
    Circle *c;
    Drawing next;
  };

  struct circle{
    double r, x, y, thickness;
    int filled;
  };
  struct line{
    double x1, y1, x2, y2, thickness;
  };

  Drawing create_drawing()
  {
    Drawing D=malloc(sizeof(Drawing));
    D->l=NULL;
    D->c=NULL;
    D->next=NULL;
    return D;
  }

  void destroy_drawing(Drawing D)
  {
    Drawing cur=D;
    Drawing next;
    while(cur){
      if (cur->l != NULL)
      {
        free(cur->l);
      }
      if (cur->c != NULL)
      {
        free(cur->c);
      }
      next=cur->next;
      free(cur);
      cur=next;
    }
    free(D);
  }

/* */

  int add_line_segment(Drawing D, double x1, double y1, double x2, double y2, double thickness)
  {
    Drawing ci = create_drawing();
    Line *li = malloc(sizeof(Line));
    ci->next=D->next;
    D->next=ci;
    ci->l=li;
    ci->l->x1=x1;
    ci->l->y1=y1;
    ci->l->x2=x2;
    ci->l->y2=y2;
    ci->l->thickness=thickness;
    return 1;
  }

  int add_circle(Drawing D, double x, double y, double r,  double thickness, int filled)
  {
    Drawing ci = create_drawing();
    ci->next=D->next;
    D->next=ci;
    Circle *cir = malloc(sizeof(Circle));
    ci->c=cir;
    ci->c->x=x;
    ci->c->y=y;
    ci->c->r=r;
    ci->c->thickness=thickness;
    ci->c->filled=filled;
    return 1;
  }

  int get_image_dimensions2(Drawing D, int pix_per_unit, double *xg, double *yg, double *xp, double *yp)
  {
    *xg=0;
    *yg=0;
    *xp=0;
    *yp=0;

    Drawing CI=D->next;
    if (CI == NULL)
      return 0;
    
    else {
      for (; CI ; CI = CI->next){
        if (CI->l != NULL){
          if (CI->l->x1 > CI->l->x2){
            if ((CI->l->x1  + CI->l->thickness) > *xg) *xg = CI->l->x1 + CI->l->thickness;
            if ((CI->l->x2  - CI->l->thickness) < *xp) *xp = CI->l->x2 - CI->l->thickness;
          
          } else if (CI->l->x1 < CI->l->x2){
            if ((CI->l->x2 + CI->l->thickness) > *xg) *xg = CI->l->x2 + CI->l->thickness;
            if ((CI->l->x1 - CI->l->thickness) < *xp) *xp = CI->l->x1 - CI->l->thickness;
          
          }
          
          if (CI->l->y1 > CI->l->y2){
            if ((CI->l->y1 + CI->l->thickness) > *yg) *yg = CI->l->y1 + CI->l->thickness;
            if ((CI->l->y2 - CI->l->thickness) < *yp) *yp = CI->l->y2 - CI->l->thickness;
          
          } else if (CI->l->y1 < CI->l->y2){
            if ((CI->l->y2 + CI->l->thickness) > *yg) *yg = CI->l->y2 + CI->l->thickness;
            if ((CI->l->y1 - CI->l->thickness) < *yp) *yp = CI->l->y1 - CI->l->thickness;
          
          }
        }

        if (CI->c != NULL)
        {
          if ((CI->c->x + CI->c->r + CI->c->thickness) > *xg) *xg = CI->c->x + CI->c->r + CI->c->thickness;
          if ((CI->c->y + CI->c->r + CI->c->thickness) > *yg) *yg = CI->c->y + CI->c->r + CI->c->thickness;
          if ((CI->c->x - CI->c->r - CI->c->thickness) < *xp) *xp = CI->c->x - CI->c->r - CI->c->thickness;
          if ((CI->c->y - CI->c->r - CI->c->thickness) < *yp) *yp = CI->c->y - CI->c->r - CI->c->thickness;
        }
      }
    }

    return 1;
  }

double distanciaPontoAPonto(double x1, double y1, double x2, double y2) {
  return sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}

double min(double a, double b) {
  if (a < b) return a;
  else return b;
}

double max(double a, double b) {
  if (a > b) return a;
  else return b;
}


double distanciaPontoASegmento(double x, double y, double x1, double y1, double x2, double y2) 
{
  // Se a reta for vertical, não podemos dividir por 0. Então fazemos duas abordagens distintas
  if (x1 == x2) {
    if (y1 > y2) {
      if (y <= y1 && y >= y2) return abs(x - x2);
      else return min(distanciaPontoAPonto(x, y, x1, y1), distanciaPontoAPonto(x, y, x2, y2));

    } else {
      if (y >= y1 && y <= y2) return abs(x - x2);
      else return min(distanciaPontoAPonto(x, y, x1, y1), distanciaPontoAPonto(x, y, x2, y2));
      
    }

  } else {
    // equação da reta q contem o segment: y = alpha * x + b
    double alpha = (y1 - y2) / (x1 - x2);
    double b = y1 - alpha * x1;

    // equação da reta perpenciular: y' = -x/alpha + b'
    double alpha2 = -1.0/alpha;
    double b2 = y + x/alpha;

    // interseção de y=y'
    // alpha * x + b = alpha2 * x + b2
    // x (alpha - alpha2) = b2 - b
    // x = (b2 - b) / (alpha - alpha2)
    double x_interc = (b2 - b) / (alpha - alpha2);
    double distancia = 0;

    // verificar se x está no segmento
    if (x_interc >= min(x1, x2) && x_interc <= max(x1, x2)) {
      // está na reta
      distancia = distanciaPontoAPonto(x, y, x_interc, alpha * x_interc + b);

    } else {
      distancia = min(distanciaPontoAPonto(x, y, x1, y1), distanciaPontoAPonto(x, y, x2, y2));

    }

    return distancia;
  }
}

int save_pgm(Drawing D, int pix_per_unit, int sample_type, int sample_size, FILE *outfile)
{
  printf("PQPPPP\n");
  double xg=0, yg=0, xp=0, yp=0, distancia;
  int largura, altura;
  int i = get_image_dimensions2(D, pix_per_unit, &xg, &yg, &xp, &yp);
  if(i == 0)
  {
    return EMPTY_IMAGE_ERROR;
  }
  altura = ceil(yg - yp) * pix_per_unit;
  largura = ceil(xg - xp) * pix_per_unit;
  fprintf(outfile, "P2\n");
  fprintf(outfile, "%d %d\n", largura, altura );
  fprintf(outfile, "255\n");
  int **m = malloc(altura*sizeof(int*));
  if(!m)
  {
    printf("ERRO DE ALOCACAO DE MEMORIA.\n");
    return MEMORY_ERROR;
  }
  for(int i=0; i<altura; i++)
  {
    m[i]=malloc(largura*sizeof(int));
    if(!m[i])
    {
      printf("ERRO DE ALOCACAO DE MEMORIA. \n");
      return MEMORY_ERROR;
    }
  }
  double y_pix, x_pix;
  int n;
  for(i=0; i<altura; i++)
  {
    for(int j=0; j<largura; j++)
    {
      m[i][j]=255;
    }
  }
  // Normaliza e translada tudo
  for(Drawing cur=D->next; cur; cur=cur->next) 
  {
    if (cur->l) 
    {
      cur->l->x1 -= xp;
      cur->l->x2 -= xp;
      cur->l->y1 -= yp;
      cur->l->y2 -= yp;
      cur->l->x1 *= pix_per_unit;
      cur->l->x2 *= pix_per_unit;
      cur->l->y1 *= pix_per_unit;
      cur->l->y2 *= pix_per_unit;
      cur->l->thickness *= pix_per_unit;
    } 
    else 
    {
      cur->c->x -= xp;
      cur->c->y -= yp;
      cur->c->x *= pix_per_unit;
      cur->c->y *= pix_per_unit;
      cur->c->r *= pix_per_unit;
      cur->c->thickness *= pix_per_unit;
     }
   }
  for(Drawing cur=D->next; cur; cur=cur->next) 
  {
    for(i = 0; i<largura; i++)
    {
      for(int j = 0; j < altura; j++)
      {
        n=0;
        if(sample_type == GRID_SAMPLE)
        {
          for(int k = 0; k <sample_size; k++)
          {
            for(int l = 0; l<sample_size; l++)
            {
              y_pix = j + 1.0 * k / (sample_size + 1.0);
              x_pix = i + 1.0 * l / (sample_size + 1.0);
              if (cur->l) 
              {
                distancia = distanciaPontoASegmento(x_pix, y_pix, cur->l->x1, cur->l->y1, cur->l->x2, cur->l->y2);
                if (distancia <= cur->l->thickness)
                 n++;  
              } 
              else 
              {
                distancia = distanciaPontoAPonto(x_pix, y_pix, cur->c->x*pix_per_unit, cur->c->y*pix_per_unit);
                if (cur->c->filled) 
                {
                  if (distancia <= pix_per_unit * (cur->c->r + cur->c->thickness)) 
                  {
                    n++;
                  }
                 } 
                 else 
                 {
                  if (distancia <= pix_per_unit * (cur->c->r + cur->c->thickness) &&
                    distancia >= pix_per_unit * (cur->c->r - cur->c->thickness)) 
                  {
                    n++;
                  }
                }
              }
            }
          }
          m[j][i] = floor(min(1.0 * m[j][i], 255.0 * (1.0 - (1.0 * n) / (sample_size * sample_size))));
        }
        else{
          for(int k = 0; k < sample_size; k++)
          {
            y_pix = j + (double)rand() / (double)((unsigned)RAND_MAX + 1);
            x_pix = i + (double)rand() / (double)((unsigned)RAND_MAX + 1);
            if (cur->l)
            {
              distancia = distanciaPontoASegmento(x_pix, y_pix, cur->l->x1, cur->l->y1, cur->l->x2, cur->l->y2);
              if (distancia <= cur->l->thickness)
                n++;
            } else 
            {
              distancia = distanciaPontoAPonto(x_pix, y_pix, cur->c->x*pix_per_unit, cur->c->y*pix_per_unit);
                if (cur->c->filled) 
              {
                if (distancia <= pix_per_unit * (cur->c->r + cur->c->thickness)) 
                {
                  n++;
                }
               } 
               else 
               {
                if (distancia <= pix_per_unit * (cur->c->r + cur->c->thickness) &&
                  distancia >= pix_per_unit * (cur->c->r - cur->c->thickness)) 
                {
                  n++;
                }
              }
            }
          }
          m[j][i] = floor(min(1.0 * m[j][i], 255.0 * (1.0 - (1.0 * n) / sample_size)));
        }
      }
    }
  }
  for(i = 0; i < largura; i++)
  {
    for (int k = 0; k < altura; k++)
    {
      fprintf(outfile, "%d\n",m[k][i]);
    }
    fprintf(outfile, "\n");
  }
  printf("ACABOU PORRA\n");
  return 1;
}