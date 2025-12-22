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

obj/test.o: src/test.cpp
	@mkdir -p obj
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(EXEDIR)/test: obj/machine.o obj/test.o
	@mkdir -p $(EXEDIR)
	$(CPP) $(CPPFLAGS) $^ -o $@

test: $(EXEDIR)/test
	$(EXEDIR)/test

run: $(EXE)
	./$(EXE)

