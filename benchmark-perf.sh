int_trap() {
    echo "Ctrl-C pressed"
}


trap int_trap INT

echo "Running perf, please press CTRL-C to finish the benchmark."

perf record -e cpu-clock --user-callchains -g -F 10000 --delay 10000 ./bin/main > /dev/null 2>&1

perf report --stdio --no-children -n -g folded,0,caller,count --dsos main -s dso --ignore-callees Listener::collectOrderData --hide-unresolved | awk '/^ / { comm = $3 } /^[0-9]/ {cnt=$1; $1=""; print comm ";" $0, cnt}' | ./lib/FlameGraph/flamegraph.pl perf_folded.out > $1

echo "DONE"
echo "FlameGraph written to" $1
