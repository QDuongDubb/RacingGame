CXX = g++
# Update these paths as necessary to match your installation
SDL_LIB = -LC:/SDL2-2.30.5/i686-w64-mingw32/lib -lSDL2main -lSDL2
SDL_INCLUDE = -IC:/SDL2-2.30.5/i686-w64-mingw32/include
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
EXE = SDL_Lesson0.exe

all: $(EXE)

debug: $(CXXFLAGS) += -DDEBUG -g
debug: executable

$(EXE): main.o
	$(CXX) $< $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	del *.o && del $(EXE)