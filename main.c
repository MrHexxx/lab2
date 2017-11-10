#include <stdio.h>
#include <string.h> //memset

const int bsize = 1024;
typedef struct
{
  double x, y, z;
  char name[21];
} Point;

Point readPoint(const char* line);
int compare(Point a, Point b);
int readNewLine();
void swap(Point array[], int i, int j);
int isZero(Point a);

int main()
{
    Point points[80];
    int numOfPoints = 0;
    char buffer[bsize];
    while(!readNewLine() || numOfPoints == 0)
    {
      Point temp;
      fgets(buffer, bsize, stdin);
      if(4 == sscanf(buffer, "%lf %lf %lf %20s", &temp.x, &temp.y, &temp.z, temp.name))
      {
        points[numOfPoints] = temp;
        numOfPoints++;
      }
      else
      {
        printf("Wpisano złe dane. Prosze kontynuowac.\n");
        //memset(&buffer, 0, sizeof(char) * bsize);
      }
    }
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
        if(!isZero(b) && (isZero(a) || ascending * compare(a, b) > 0))
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

Point readPoint(const char* line)
{
    Point p;
    sscanf(line, "%lf %lf %lf %20s", &p.x, &p.y, &p.z, p.name);
    return p;
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
