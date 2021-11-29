#!/usr/bin/env python3

import os
import numpy as np
import matplotlib.pyplot as plt
import json


def plotting(old_data, new_data, functions_names):
    n_groups = len(names_list)

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


counter = 1  # defo not working
os.chdir("../cmake-build-debug/benchmarking")
# os.system(f"./benchmarking --benchmark_out=../../benchmarking/outputs/newFile{counter} --benchmark_out_format=json")
counter += 1
os.chdir("../../benchmarking")
os.system("./lib/benchmark/tools/compare.py benchmarks outputs/newFile outputs/newFile1 | sed 's/\x1b\[[0-9;]*m//g' > "
          "outputs/output")
os.system("./lib/benchmark/tools/compare.py benchmarks outputs/newFile outputs/newFile1")

f_old = open("outputs/newFile")
f_new = open("outputs/newFile1")

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
