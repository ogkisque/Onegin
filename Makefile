CC = g++
CFLAGS = -c -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align\
-Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations\
-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra\
-Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy\
-Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op\
-Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith\
-Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel\
-Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

HEADERS = input_output_copy.h my_sort.h
OBJ = main.o input_output_copy.o my_sort.o

all: onegin.exe

onegin.exe: $(OBJ) $(HEADERS)
	$(CC) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $<

.PHONY: clean all

clean:
	rm -rf *.o onegin.exe
