rm -rf core
ulimit -c unlimited

#./mytest
valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./mytest
#valgrind --tool=memcheck --leak-check=full ./mytest

