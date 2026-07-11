CC = g++
CFLAGS = -Wall -O2 -mwindows
LIBS = -lShlwapi -lAdvapi32

all: anti_share_bypass.exe

%.obj: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

anti_share_bypass.exe: anti_share_bypass.obj
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	del *.obj *.exe

.PHONY: all clean
