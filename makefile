# compiler
CXX = g++

# objective programs
OBJS = main.o  segment.o entrance.o vehicle.o toll.o Highway.o

# executable program
EXEC = attiki_odos

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 1 5 5 20 70

$(EXEC): $(OBJS)
	$(CXX)  $(OBJS) -o $(EXEC) 

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC) -E $(ARGS)
gdb: $(EXEC)
	./$(EXEC) $(ARGS)