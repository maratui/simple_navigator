CC      = g++
CFLAGS  = -std=c++17 -Wall -Wextra -Werror -Wuninitialized
CLIBS   = -lgtest -lgtest_main
FILES   = *.h *.cc adaptors/* ant_colony/* controller/* facade/* tests/*.h tests/*.cc

all: main_program
	./bin/simple_navigator

clean:
	rm -rf build
	rm -rf report
	rm -rf bin

main_program: clean graph.a graph_algorithms.a stack.a queue.a
	mkdir -p bin
	cd build && $(CC) $(CFLAGS) ../facade/* ../controller/* \
	../main_program.cc ../main.cc -o simple_navigator \
	graph.a graph_algorithms.a stack.a queue.a $(CLIBS) \
	&& mv simple_navigator ../bin/ && cd .. && rm -rf build

test: clean graph.a graph_algorithms.a stack.a queue.a
	cd build && $(CC) $(CFLAGS) ../tests/*.cc -o tests \
	graph.a graph_algorithms.a stack.a queue.a $(CLIBS) && \
	./tests && cd .. && rm -rf build

graph.a: graph.o
	cd build && ar -rcs graph.a graph.o && cd ..

graph.o:
	mkdir -p build
	cd build && $(CC) $(CFLAGS) -c ../graph.cc && cd ..

graph_algorithms.a: graph_algorithms.o ant_colony.o
	cd build && ar -rcs graph_algorithms.a graph_algorithms.o ant_colony.o \
	&& cd ..

graph_algorithms.o:
	mkdir -p build
	cd build && $(CC) $(CFLAGS) -c ../graph_algorithms.cc && cd ..

ant_colony.o:
	mkdir -p build
	cd build && $(CC) $(CFLAGS) -c ../ant_colony/ant_colony.cc && cd ..

stack.a: stack.o
	cd build && ar -rcs stack.a stack.o && cd ..

stack.o:
	mkdir -p build
	cd build && $(CC) $(CFLAGS) -c ../adaptors/stack.cc && cd ..

queue.a: queue.o
	cd build && ar -rcs queue.a queue.o && cd ..

queue.o:
	mkdir -p build
	cd build && $(CC) $(CFLAGS) -c ../adaptors/queue.cc && cd ..

gcov-report: clean stack.a queue.a
	cd build && $(CC) $(CFLAGS) --coverage \
	../graph.cc ../graph_algorithms.cc ../ant_colony/*.cc ../tests/*.cc \
	-o tests stack.a queue.a $(CLIBS) && \
	lcov -c -i -d . -o base.info && \
	./tests && \
	lcov -c -d . -o test.info && \
	lcov -a base.info -a test.info -o total.info && \
	lcov -r total.info "/usr/*" "*/A2_SimpleNavigator_v1.0-1/src/tests/*" \
	"*/A2_SimpleNavigator_v1.0-1/src/adaptors/*" -o filtered.info \
	&& genhtml --ignore-errors source filtered.info -o ../report && \
	cd .. && rm -rf build
ifeq ($(shell uname -s), Darwin)
	open report/index.html
else
	xdg-open ./report/index.html
endif

googlestyle:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(FILES)
	rm -f ./.clang-format

clang-format:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(FILES)
	rm -f ./.clang-format

valgrind: clean graph.a graph_algorithms.a stack.a queue.a
	cd build && $(CC) $(CFLAGS) -g \
	../tests/*.cc -o tests graph.a graph_algorithms.a stack.a queue.a \
	$(CLIBS) && \
	valgrind --tool=memcheck --leak-check=yes -s -q ./tests && \
	cd .. && rm -rf build

leaks: clean graph.a graph_algorithms.a stack.a queue.a
	cd build && $(CC) $(CFLAGS) \
	../tests/*.cc -o tests graph.a graph_algorithms.a stack.a queue.a \
	$(CLIBS) && \
	CK_FORK=no leaks -atExit -- ./tests && \
	cd .. && rm -rf build
