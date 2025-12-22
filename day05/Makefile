CPP = clang++
CPPFLAGS = -std=c++23 -ggdb -Wall -Wextra -O0

EXENAME = main
EXEDIR = bin
EXE = $(EXEDIR)/$(EXENAME)

$(EXE): obj/main.o obj/machine.o
	@mkdir -p $(EXEDIR)
	$(CPP) $(CPPFLAGS) $^ -o $@

obj/main.o: src/main.cpp
	@mkdir -p obj
	$(CPP) $(CPPFLAGS) -c $< -o $@

obj/machine.o: src/machine.cpp
	@mkdir -p obj
	$(CPP) $(CPPFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

