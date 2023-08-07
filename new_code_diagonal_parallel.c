#include <stdio.h>
#include <math.h>
#include <omp.h> // Include the OpenMP header file
#include <stdlib.h>

int main() {
  FILE *file = fopen("output_1m.csv", "w");
  if (file == NULL)
  {
    printf("Error opening file!\n");
    return 1;
  }

  long i, j;
  long condi;
  long numi;
  long demi;
  long write_result;
  long rt;
  long rt2;
  long quad = 1000000;

  omp_set_num_threads(6);

  #pragma omp parallel for private(i, j, condi, numi, demi, rt, rt2,write_result) schedule(dynamic)// OpenMP parallel for loop
  for (i = 0; i <= quad; ++i)
  {
    for (j = 0; j <= i; ++j)
    {
      condi = (2*i*j+i+j-pow(i,2)-pow(j,2));
      if (condi > 0)
      {
        numi = -2*i*j;
        demi = pow(i-j,2) - (i+j);
        if (demi != 0)
        {
            rt = fmod(numi, demi);
            if (rt == 0)
            {
                rt2 = numi / demi;

                #pragma omp critical // Only one thread can execute the next command at a time
                fprintf(file, "%ld,%ld,%ld\n", i, j, rt2);
            }
        }
      }
    }
  }

  fclose(file);
  return 0;
}
