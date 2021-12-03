int_trap() {
    echo "Ctrl-C pressed"
}


trap int_trap INT

echo "Running perf, please press CTRL-C to finish the benchmark."

perf record -e cpu-clock --call-graph fp -F 10000 --delay 10000 ./bin/main > /dev/null 2>&1
perf report -g fractal --stdio --hide-unresolved --dsos=main > $1
echo "DONE"
echo "Output written to " $1
