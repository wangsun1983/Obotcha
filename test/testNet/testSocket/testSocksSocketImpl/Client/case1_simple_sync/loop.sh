rm -rf core
ulimit -c unlimited
for ((i=1; i<=10000; i++))
do
    {
        python test_udp_recv.py
    } &
    sleep 1
    ./mytest
    wait
    sleep 3
done
