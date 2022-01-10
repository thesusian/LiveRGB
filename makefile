CC = g++
CFLAGS = -std=c++17 
LDFLAGS = -lX11 

App: $(OBJECTS)
	$(CC) $(CFLAGS) main.cpp -o LiveRGB $(LDFLAGS)

run: App
	./LiveRGB

clean:
	rm -f LiveRGB
