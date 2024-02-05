set terminal pngcairo enhanced font 'Verdana,12'


#Gráfico de Te medio:
set output 'Tejecucion.png'
set title 'Tiempo de Ejecución'
set xlabel 'Procesadores'
set ylabel 'Tiempo de Ejecución (ms)'
plot 'resultados.txt' using 1:2 with linespoints title 'T.Ejecución'

#Gráfico de factor de aceleración y eficiencia:
set output 'FAyEf.png'
set title 'Factor de Aceleración y Eficiencia'
set xlabel 'Procesadores'
set ylabel 'Factor de Aceleración'
set y2label 'Eficiencia'
set y2tics
set y2range [0:1]

plot 'resultados.txt' using 1:3 with linespoints title 'Speedup' axis x1y1, 'resultados.txt' using 1:4 with linespoints title 'Eficiencia' axis x1y2
