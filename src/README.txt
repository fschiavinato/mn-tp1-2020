Para correr los scripts, desde una consola ejecutar:

$ python metnum.py opcion

donde opcion puede ser:

compile: Compila todos los *.cpp que hayan en el directorio.
link: Genera el ejecutable en base a los *.o generados previamente.
build: compile + link
clean: borra los *.o y el ejecutable.
test: hace el build, busca lo archivos *.in en la carpeta tests/, ejecuta el programa y guarda el
resultado para cada corrida en el correspondiente .out. Despues, chequea que el resultado sea el "mismo" que el
.expected, tambien del directorio test. En este caso, la comparacion es por tolerancia coordenada a coordeanda del vector
solucion.

Para compilar, ejecutar el script metnum.py con alguna de sus opciones
Para ejecutar el programa con algún achivo de entrada, hacer:
	./tp ruta_archivo_entrada nombre_archivo_salida método
	donde método puede ser 0,1,2,3,4
	-0 Colley con eliminación gaussiana
	-1 wp
	-2 sistema Glicko
	-3 Colley con Cholesky
	-4 Cholesky para matrices dispersas
Para comparar el ránking obtenido por un determinado jugador entre distintos métodos:
	ejecutar compare.py y pasarle los parámetros de los archivos de salida con los rankings calculados
	y el número del jugador o equipo que se quiere analizar
