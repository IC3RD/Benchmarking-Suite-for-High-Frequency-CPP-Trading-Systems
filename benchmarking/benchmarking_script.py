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

    plt.bar(index, old_data, bar_width,
            alpha=opacity,
            color='r',
            label='Previous')

    plt.bar(index + bar_width, new_data, bar_width,
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

    file_name = f"benchmark_at[{time}]"
    os.chdir("../cmake-build-debug/benchmarking")  # this is where the executable of benchmarking is
    os.system(f"./benchmarking --benchmark_out=../../benchmarking/outputs/{file_name}")
    os.chdir("../../benchmarking")
    return file_name


def compare(old_file, new_file):
    file_name = f"comparison_{old_file}_{new_file}"  # the name of the new file created (for the report)
    os.system(
        f"python3 lib/benchmark/tools/compare.py benchmarks outputs/{old_file} outputs/{new_file} | sed 's/\x1b\[["
        f"0-9;]*m//g' > outputs/{file_name}")

    # open the json files to read from (make sure you only provide the name and not the path)
    f_old = open("outputs/" + old_file)
    f_new = open("outputs/" + new_file)

    # make dictionaries from the json files
    dict_old = json.load(f_old)
    dict_new = json.load(f_new)

    # throw away all meaningless stuff from the dictionary
    dict_old = dict_old['benchmarks']
    dict_new = dict_new['benchmarks']

    names_list = []
    old_times = []
    new_times = []
    old_cpu_times = []
    new_cpu_times = []
    time_differences = []
    cpu_time_differences = []

    for v_old, v_new in zip(dict_old, dict_new):
        old_time = v_old['real_time']  # these are floats already
        new_time = v_new['real_time']
        old_cpu_time = v_old['cpu_time']  # these are floats already
        new_cpu_time = v_new['cpu_time']

        names_list.append(v_old['name'])
        old_times.append(old_time)
        new_times.append(new_time)
        old_cpu_times.append(old_cpu_time)
        new_cpu_times.append(new_cpu_time)
        time_differences.append(new_time - old_time)
        cpu_time_differences.append(new_cpu_time - old_cpu_time)

    plotting(old_times, new_times, names_list)


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
