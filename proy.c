#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Función auxiliar para calcular la media, factor de aceleración y eficiencia para cada muestra de ejecuciones en paralelo
void procesarLinea(char *linea, FILE *resultado, float tSerie)
{
  int p;
  float suma = 0.0;
  char *split = strtok(linea, " \t\n"); //Divide la línea por espacios

  if (split != NULL)
  {
	p = atoi(split); //Guarda el número de procesadores
	int cont = 0;
	while ((split = strtok(NULL, " \t\n")) != NULL)
	{
	  suma += atof(split); //Suma todas las muestras de tiempo
       	  cont++; //Cuenta el número de ejecuciones
	}

	//Calcula y escribe la media, factor de aceleración y eficiencia
	float media = suma / cont;
	float fa = tSerie/media;
	float ef = fa/p;
	fprintf(resultado, "%d %f %f %f\n", p, media, fa, ef);
  }
}


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
	printf("Uso %s <archivo>\n", argv[0]);
	return 1;
  }

  //Abre el archivo en modo lectura
  FILE *archivo;
  char *nombreArchivo = argv[1];
  archivo = fopen(nombreArchivo, "r");

  //Verifica si el archivo existe
  if (archivo == NULL)
  {
	printf("El archivo %s no existe.\n", nombreArchivo);
	return 1;
  }

  //Crea un archivo para los resultados
  FILE *output;
  char *nombreOutput = "resultados.txt";
  output = fopen(nombreOutput, "w");
  fprintf(output, "#procs runtime speedup efficiency\n");
  fprintf(output, "#===== ======= ======= ==========\n");


  char linea[256];
  fgets(linea, sizeof(linea), archivo); //Ignora la primera línea del archivo

  //Trata la línea con los tiempos en serie
  fgets(linea, sizeof(linea), archivo);

  char *split = strtok(linea, " \t\n");
  int cont = 0;
  float tSerie = 0.0;
  if (split != NULL)
  {
	while ((split = strtok(NULL, " \t\n")) != NULL)
	{
          tSerie += atof(split); //Suma todas las muestras de tiempo
          cont++; //Cuenta el número de ejecuciones
	}
	tSerie = tSerie/cont;
	fprintf(output, "1 %f %f %f\n", tSerie, 1.0, 1.0);//Escribe la linea en el fichero de resultados
  }
  //Trata las demás líneas
  while (fgets(linea, sizeof(linea), archivo) != NULL)
  {
	  procesarLinea(linea, output, tSerie);
  }


  //Cierra ambos archivos
  fclose(archivo);
  fclose(output);

  //Ejecuta el comando Gnuplot y genera los gráficos
  system("gnuplot graficos.gp");

  return 0;
}
