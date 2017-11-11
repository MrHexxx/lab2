//Mateusz Okulus listopad 2017
//Projekt PRI laboratoria nr 1
#include <stdio.h> //konsola

typedef struct
{
  double x, y, z;
  char name[21];
} Point;

int compare(Point a, Point b); //porównanie dwóch punktów rosnąco
int readNewLine(); //czy wczytano pustą linię? (tylko znak nowej linii)
void swap(Point array[], int i, int j); //zamiana 2 punktów w tablicy
int isZero(Point a); //czy punkt jest punktem (0,0,0)
int shouldSwap(Point a, Point b, int ascending); //czy powinno zamienić miejscami punkty a i b

int main()
{
    Point points[80];//maksimum
    int numOfPoints = 0; //ile punktów wczytano
    const int bsize = 1024; //rozmiar bufora
    char buffer[bsize];
    printf("Prosze podac punkty w formacie X Y Z nazwa\n")
    //przerywamy, gdy podano pustą linię ALE wymagamy co najmniej 1 punktu(pusta linia nie przerwie gdy mamy 0 punktów)
    //przerwiemy, gdy mamy 80 punktów(już więcej nie powinniśmy wczytać)
    while( (!readNewLine() || numOfPoints == 0) && numOfPoints < 80 )
    {
      Point temp; //do wczytywania
      fgets(buffer, bsize, stdin);
      if(4 == sscanf(buffer, "%lf %lf %lf %20s", &temp.x, &temp.y, &temp.z, temp.name))
      {
        points[numOfPoints] = temp;
        numOfPoints++;
      }
      else
      {
        printf("Wpisano złe dane. Prosze kontynuowac.\n");
      }
    }
    //wczytano wszystkie punkty
    printf("Sortowac rosnaco czy malejaco? [r/m]\n");
    char c = 0;
    fgets(buffer, bsize, stdin);
    sscanf(buffer, "%c", &c);
    while(c != 'r' && c != 'm')
    {
        printf("Wybierz r by sortowac rosnaco, m by sortowac malejaco\n");
        fgets(buffer, bsize, stdin);
        sscanf(buffer, "%c", &c);
    }
    int ascending = 1;
    if(c == 'm')
      ascending = -1;

    for(int j = 0; j < numOfPoints - 1; j++)
    {
      for(int i = 0; i < numOfPoints - 1 - j; i++)
      {
        Point a = points[i];
        Point b = points[i+1];
        if(shouldSwap(a, b, ascending))
        {
          swap(points, i, i+1);
        }
      }
    }

    for(int i = 0; i < numOfPoints; i++)
    {
      Point p = points[i];
      printf("%s %lf %lf %lf\n", p.name, p.x, p.y, p.z);
    }
}

int compare(Point a, Point b)
{
    return (a.x * a.x + a.y * a.y + a.z * a.z) - (b.x * b.x + b.y * b.y + b.z * b.z);
}

int readNewLine()
{
  char c = getchar();
  if(c == '\n')
    return 1;
  ungetc(c, stdin);
  return 0;
}

void swap(Point array[], int i, int j)
{
  Point temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

int isZero(Point a)
{
  return a.x == 0 && a.y == 0 && a.z == 0;
}

int shouldSwap(Point a, Point b, int ascending)
{
  return !isZero(b) && (isZero(a) || ascending * compare(a, b) > 0);
}
