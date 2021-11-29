#!/usr/bin/env python3

import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import json
from datetime import datetime


def plotting(old_data, new_data, functions_names):
    n_groups = len(functions_names)

    fig, ax = plt.subplots()
    ax.set_yscale('log')

    index = np.arange(n_groups)
    bar_width = 0.35
    opacity = 1

    rects1 = plt.bar(index, old_data, bar_width,
                     alpha=opacity,
                     color='r',
                     label='Previous')

    rects2 = plt.bar(index + bar_width, new_data, bar_width,
                     alpha=opacity,
                     color='g',
                     label='Current')

    plt.xlabel('Function name')
    plt.ylabel('Time (ns)')
    plt.title('Time per function')
    plt.xticks(index + bar_width, functions_names)
    plt.legend()

    plt.tight_layout()
    plt.show()


# runs the benchmark and saved the output in /outputs
# the name of the file will be "benchmark_at" + current time
def run_benchmark():
    time = str(datetime.now())
    times = time.split(".")
    time = times[0].replace(" ", "_")

    os.chdir("../cmake-build-debug/benchmarking")  # this is where the executable of benchmarking is
    os.system(f"./benchmarking --benchmark_out=../../benchmarking/outputs/benchmark_at[{time}]")
    os.chdir("../../benchmarking")
    return f"benchmark_at[{time}]"


def compare(old_file, new_file):
    os.system(f"./lib/benchmark/tools/compare.py benchmarks outputs/{old_file} outputs/{new_file} | sed 's/\x1b\[["
              f"0-9;]*m//g' > outputs/comparison_{old_file}_{new_file}")
    os.system("./lib/benchmark/tools/compare.py benchmarks outputs/newFile outputs/newFile1")

    f_old = open("outputs/" + old_file)
    f_new = open("outputs/" + new_file)

    dict_old = json.load(f_old)
    dict_new = json.load(f_new)

    dict_old = dict_old['benchmarks']
    dict_new = dict_new['benchmarks']

    names_list = []
    old_values = []
    new_values = []

    for v_old, v_new in zip(dict_old, dict_new):
        names_list.append(v_old["name"])
        old_values.append(v_old['real_time'])
        new_values.append(v_new['real_time'])

    plotting(old_values, new_values, names_list)


if __name__ == "__main__":
    length = len(sys.argv)
    if length < 1:
        print("please provide a file name")
        sys.exit(1)
    elif length == 1:
        run_benchmark()
    elif length == 2:
        compare(sys.argv[1], run_benchmark())
    elif length == 3:
        compare(sys.argv[1], sys.argv[2])
    else:
        print("too many arguments provided")
        sys.exit(1)
