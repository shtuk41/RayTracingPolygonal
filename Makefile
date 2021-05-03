WD="./source/"
CFLAGS = -g -Wall -std=c++11 
INCLUDES = -I/usr/local -I/usr/include/SOIL -I../common -I./include `pkg-config --cflags glfw3` `pkg-config --cflags opencv`
LIBS = -lm -L/usr/local/lib -lGL -lGLU -lGLEW -lSOIL `pkg-config --static --libs glfw3` `pkg-config --libs opencv`
CC = g++ 

all: main

main:	shader camera field sphere raytracerviewer
	$(CC) $(CFLAGS) $(INCLUDES) $(WD)main.cpp shader.o camera.o field.o sphere.o raytracerviewer.o -o main $(LIBS)
	
shader:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(WD)shader.cpp -o shader.o $(LIBS)
	
camera:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(WD)Camera.cpp -o camera.o $(LIBS)
	
field:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(WD)Field.cpp -o field.o $(LIBS)
	
sphere:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(WD)sphere.cpp -o sphere.o $(LIBS)	
	
raytracerviewer:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(WD)RayTracerViewer.cpp -o raytracerviewer.o $(LIBS)

clean:
	rm main