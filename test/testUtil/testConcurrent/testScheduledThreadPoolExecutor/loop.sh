rm -rf core
ulimit -c unlimited
for ((i=1; i<=10000; i++))
do
    ./mytest
    #valgrind --tool=memcheck --leak-check=full ./mytest
done
