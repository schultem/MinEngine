CC = g++
CC_FLAGS = -Ipatch -Iengine -std=c++11 
CC_LINKS = -lgdi32 -static-libgcc -static-libstdc++ -Wl,--subsystem,windows
EXEC = seeder

export PATH:=C:\MinGW\bin;C:\Program Files (x86)\GnuWin32\bin;$(Path)

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

all: $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CC_LINKS)
	@echo ==============
	@echo Build Complete
	@$(EXEC).exe

clean:
	del /f *.o
	del /f game\*.o
	del /f engine\*.o
	del /f *.exe
