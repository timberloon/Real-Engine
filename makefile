make:
	g++ main.cpp -o main -Isrc/include -Lsrc/lib -lglfw3 -lglew32 -lopengl32 -lgdi32 -luser32 -lkernel32
