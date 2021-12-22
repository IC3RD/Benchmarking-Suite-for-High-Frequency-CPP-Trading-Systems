#!/usr/bin/env python3

import os
import numpy as np
import matplotlib.pyplot as plt
import json
import argparse
from datetime import datetime
from fpdf import FPDF

OUTPUT_DIR = 'outputs'  # global variable that specifies the name of the outputs/inputs folder
FLAG_LAST = False
ROOT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


# function for plotting the two graphs
def plotting(old_data, new_data, functions_names, is_cpu: bool):
    n_groups = len(functions_names)

    fig, ax = plt.subplots()
    ax.set_yscale('log')  # use logarithmic scale to have the results more presentable (change if you wish)

    index = np.arange(n_groups)
    bar_width = 0.35
    opacity = 1

    # plot the first graph
    plt.bar(index, old_data, bar_width,
            alpha=opacity,
            color='r',
            label='Previous')

    # plot the second graph
    plt.bar(index + bar_width, new_data, bar_width,
            alpha=opacity,
            color='g',
            label='Current')

    # add the correct labels and title
    plt.xlabel('Function name')
    plt.ylabel('Time (ns)')
    if is_cpu:
        plt.title('CPU time per function')
    else:
        plt.title('Time per function')
    plt.xticks(index + 0.5 * bar_width, functions_names, rotation=20, fontsize=4)
    plt.legend()
    plt.tight_layout()
    # save them according to their title (will get deleted anyway)
    if is_cpu:
        plt.savefig("CPU_time_graph", dpi=250)
    else:
        plt.savefig("time_graph", dpi=250)


# function to recompile the project to benchmark the functions
def run_functions():
    os.chdir(ROOT_DIR)
    os.system('cmake -S . -DBENCHMARK_HOTPATH:BOOL=False -DENABLE_CPP_BENCHMARKS:BOOL=True -B build')
    os.system('cmake --build build')
    os.system('cmake --install build')


# function to recompile the project to benchmark the hotpath
def run_hot_path():
    os.chdir(ROOT_DIR)
    os.system('cmake -S . -DBENCHMARK_HOTPATH:BOOL=True -DENABLE_CPP_BENCHMARKS:BOOL=False -B build')
    os.system('cmake --build build')
    os.system('cmake --install build')
    print(os.getcwd())
    os.chdir(f'{ROOT_DIR}/bin')
    os.system(f"./benchmarker --benchmark_out={ROOT_DIR}/benchmarking/{OUTPUT_DIR}/temp_hotpath")


# runs the benchmark and saved the output in /outputs
# the name of the file will be "benchmark_at" + current time
def run_benchmark(output_path):
    global OUTPUT_DIR
    OUTPUT_DIR = output_path
    run_functions()
    # get the time to create the name for the benchmark
    # (this takes more than 1sec to run so there should not be any conflicting namings)
    time = str(datetime.now())
    times = time.split(".")
    time = times[0].replace(" ", "_")

    # everything needs to be made correctly for this to work - make sure you follow the README.md
    file_name = f"benchmark_at[{time}]"
    os.chdir(f"{ROOT_DIR}/bin")  # this is where the executable of benchmarking is
    os.system(f"./benchmarker --benchmark_out={ROOT_DIR}/benchmarking/{OUTPUT_DIR}/temp")
    run_hot_path()
    os.chdir(f"{ROOT_DIR}/benchmarking/{OUTPUT_DIR}")
    f_temp = open('temp')
    dict_temp = dict(json.load(f_temp))
    f_temp_hotpath = open('temp_hotpath')
    dict_temp_hotpath = json.load(f_temp_hotpath)
    dict_temp['benchmarks'] += dict_temp_hotpath['benchmarks']
    with open(file_name, 'w') as f:
        json.dump(dict_temp, f)
    os.remove('temp')
    os.remove('temp_hotpath')
    return file_name


# make sure that the directory for outputs/inputs is there, if not create it
def init_dir():
    if not os.path.isdir(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)


# main comparison function: compares the two given files (passed as arguments or from running the benchmarker)
def compare(old_file, new_file, input_path, output_path):
    os.chdir(f'{ROOT_DIR}/benchmarking')
    file_name = f"comparison_{old_file}_{new_file}"  # the name of the new file created (for the report)
    os.system(
        f"python3 lib/benchmark/tools/compare.py benchmarks {input_path}/{old_file} {input_path}/{new_file}")

    # open the json files to read from (make sure you only provide the name and not the path)
    f_old = open(input_path + "/" + old_file)
    f_new = open(input_path + "/" + new_file)

    # make dictionaries from the json files
    dict_old = json.load(f_old)
    dict_new = json.load(f_new)

    # throw away all meaningless stuff from the dictionary
    dict_old = dict_old['benchmarks']
    dict_new = dict_new['benchmarks']

    # Initialise the lists with the title of each column to plot the table later
    names_list = []
    old_times = []
    new_times = []
    old_cpu_times = []
    new_cpu_times = []
    time_differences = []
    cpu_time_differences = []

    # loop through the dictionaries
    for v_old, v_new in zip(dict_old, dict_new):
        old_time = v_old['real_time']  # these are floats already
        new_time = v_new['real_time']
        old_cpu_time = v_old['cpu_time']  # these are floats already too
        new_cpu_time = v_new['cpu_time']

        names_list.append(v_old['name'])  # this is the only string (important for splitting the tables)
        # append each value to the correct list
        old_times.append(old_time)
        new_times.append(new_time)
        old_cpu_times.append(old_cpu_time)
        new_cpu_times.append(new_cpu_time)
        time_differences.append(new_time - old_time)
        cpu_time_differences.append(new_cpu_time - old_cpu_time)

    plotting(old_times, new_times, names_list, False)  # plot the total time graph
    plotting(old_cpu_times, new_cpu_times, names_list, True)  # plot the cpu time graph
    split = split_data(zip(names_list, old_times, new_times, old_cpu_times, new_cpu_times, time_differences,
                           cpu_time_differences))
    produce_pdf(old_file, new_file, file_name, split)  # produce the pdf with the data above


# will get the zipped data and will split it into classes
def split_data(zipped_data):
    order_book = []
    strategy = []
    order_executor = []
    order_data_store = []
    hot_path = []
    for row in zipped_data:
        for col in row:
            if type(col) is str:  # we know that we have the function name now
                ''' this is why the naming convention must be followed '''
                # switch ont he beginning of the string
                if str(col).startswith('OrderBookFixture/OrderBook'):
                    order_book.append(row)
                    break
                elif str(col).startswith('OrderBookFixture/TradingStrategy'):
                    strategy.append(row)
                    break
                elif str(col).startswith('ExchangeOrderExecutor'):
                    order_executor.append(row)
                    break
                elif str(col).startswith('OrderDataStoreFixture/OrderDataStore'):
                    order_data_store.append(row)
                    break
                elif str(col).startswith('OrderBookFixture/benchmark_hotpath'):
                    hot_path.append(row)
                    break
                else:
                    print("something went wrong: " + col)
                    break

    return [order_book, strategy, order_executor, order_data_store, hot_path]


# function that adds the initial text to the pdf
def add_init_text(pdf, file1, file2, line_height):
    pdf.set_font_size(10)
    text = f'The results of the comparison between {file1} and {file2}.\n' \
           f'All the timings are measured in nanoseconds.\n' \
           f'The graphs have the y-axis set to logarithmic scale ' \
           f'to account for big difference in times amongst the benchmarked functions'
    pdf.multi_cell(pdf.w - 2 * pdf.l_margin, line_height, text)


# function that adds the short description before each class table
def add_text(class_name, pdf, line_height):
    pdf.set_font_size(10)
    if class_name == 'benchmark':
        text = 'This is the benchmarked '
        class_name = 'Hot Path'
        pdf.cell(pdf.get_string_width(text), line_height * 3, text)
        pdf.set_font('Times', 'B', 10)  # change the text to bold
        pdf.cell(pdf.get_string_width(class_name), line_height * 3, class_name)  # add the class name in bold
        pdf.set_font('Times', '', 10)  # change back to normal text
    else:
        text = 'These are the results of the functions in the '  # split the text to make the class name bold
        text2 = ' class'
        pdf.cell(pdf.get_string_width(text), line_height * 3, text)  # add the first part of the text
        pdf.set_font('Times', 'B', 10)  # change the text to bold
        pdf.cell(pdf.get_string_width(class_name), line_height * 3, class_name)  # add the class name in bold
        pdf.set_font('Times', '', 10)  # change back to normal text
        pdf.cell(pdf.get_string_width(text2), line_height * 3, text2)  # add the last bit of text
    pdf.ln(line_height)


# function that adds the title row in a table
def add_title(pdf, col_width, line_height):
    pdf.set_font_size(7)
    pdf.cell(2 * col_width + 1, line_height, 'Function Name', border=1)
    pdf.cell(col_width + 1, line_height, 'Previous Time', border=1)
    pdf.cell(col_width + 1, line_height, 'New Time', border=1)
    pdf.cell(col_width + 1, line_height, 'Previous CPU Time', border=1)
    pdf.cell(col_width + 1, line_height, 'New CPU Time', border=1)
    pdf.cell(col_width + 1, line_height, 'Time Difference', border=1)
    pdf.cell(col_width + 1, line_height, 'CPU Time Difference', border=1)
    pdf.ln(line_height)


# function for adding the graphs to the pdf document
def add_plots(pdf):
    pdf.add_page()  # add a new page
    pdf.set_font_size(14)
    # add a small description
    pdf.cell(pdf.w - 2 * pdf.l_margin, pdf.font_size * 2.5, 'This graph shows the difference in total '
                                                            'time between runs:')
    pdf.ln(pdf.font_size * 2.5)
    # add the first graph to the pdf
    pdf.image('time_graph.png', h=pdf.h / 3)

    pdf.ln(pdf.font_size * 4)
    pdf.set_font_size(14)
    pdf.cell(pdf.w - 2 * pdf.l_margin, pdf.font_size * 2.5, 'This graph shows the difference in CPU '
                                                            'time between runs:')
    pdf.ln(pdf.font_size * 2.5)
    # add the second graph to the pdf
    pdf.image('CPU_time_graph.png', h=pdf.h / 3)
    # delete the graph files
    os.remove('time_graph.png')
    os.remove('CPU_time_graph.png')


# function that produces the pdf, saves it and opens it
def produce_pdf(old_file1, old_file2, new_file_name, zipped_data):
    pdf = FPDF()  # make the pdf object
    pdf.add_page()  # start a page
    pdf.set_font("Times", size=6)
    line_height = pdf.font_size * 2.5
    # set the col_width to 1/8th (2 for func name and 1 for each measurement (7 total))
    col_width = (pdf.w - 2 * pdf.l_margin - 8) / 8

    add_init_text(pdf, old_file1, old_file2, line_height)  # add the initial text of the report (edit this to add more)

    for table in zipped_data:
        fixture = str(table[0][0]).split('/')
        if len(fixture) == 1:  # no fixture case
            split = fixture[0].split('_')  # naming convention is FIXTURE?/CLASS-NAME_FUNCTION-NAME (sort of)
            class_name = split[0]
        else:  # we have fixture
            split = fixture[1].split('_')
            class_name = split[0]

        add_text(class_name, pdf, line_height)  # add the description of the table (which class it corresponds to)
        pdf.ln(line_height)
        add_title(pdf, col_width, line_height)  # add the titles of the table columns (Function Name, Time Prev., etc)
        pdf.set_font_size(6)
        for row in table:
            for i, value in enumerate(row):
                if type(value) is str:
                    pdf.set_font_size(4)  # to account for large function names
                    # if the value has type string then we know it is the function name and allocate more width for it
                    pdf.cell(2 * col_width + 1, line_height, value, border=1)
                    pdf.set_font_size(6)
                else:
                    fill = False  # boolean flag to set cell filling on and off
                    if i >= 5:
                        fill = True  # make fill true only if we are at the comparison column
                        if value < 0:
                            # if the value is negative (meaning better performance) make it green
                            pdf.set_fill_color(0, 255, 0)
                        elif value > 0:
                            # if the value is positive (meaning worse performance) make it red
                            pdf.set_fill_color(255, 0, 0)
                        else:
                            fill = False  # don't fill when value == 0
                    string = "{:.2f}".format(value)  # format the values to be in 2 decimal points
                    pdf.cell(col_width + 1, line_height, string, border=1, fill=fill)  # make the cell of the table
            pdf.ln(line_height)
        pdf.ln(line_height * 1.5)
    add_plots(pdf)  # add the two graphs to the pdf
    pdf.output(f'{OUTPUT_DIR}/{new_file_name}.pdf')  # save the pdf
    # open the pdf automatically after generation (only works on linux - uses default application to open pdf)
    os.system(f'mimeopen {OUTPUT_DIR}/{new_file_name}.pdf')


def find_latest_run():
    files = os.listdir(f'{ROOT_DIR}/benchmarking/{OUTPUT_DIR}/')
    newest = None
    for file in files:
        if file.startswith('benchmark_at'):
            prefix, timestamp = file[:-1].split('[')  # get the timestamp to compare
            if newest is None:
                newest = timestamp
            elif newest < timestamp:
                newest = timestamp
    print(newest)
    return f'benchmark_at[{newest}]'


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Script to benchmark and produce reports.')
    parser.add_argument('input_file_1', nargs='?', action='store', help='input file name')
    parser.add_argument('input_file_2', nargs='?', action='store', help='input file name')
    parser.add_argument('--output_path', '--out', action='store', default="outputs",
                        help='path to output report (default: outputs)')
    parser.add_argument('--input_path', '--in', action='store', default="outputs",
                        help='path to input benchmarks (default: outputs)')
    parser.add_argument('--last', '-l', action='store_true', default='False',
                        help='flag to set the option to use the last run for comparison')
    args = parser.parse_args()
    init_dir()
    FLAG_LAST = args.last
    if args.input_file_1 is None:  # No arguments case: run the benchmarker
        if FLAG_LAST:
            compare(find_latest_run(), run_benchmark(args.output_path), args.output_path, args.input_path)
        else:
            run_benchmark(args.output_path)
    elif args.input_file_2 is None:  # One argument: run benchmarker and compare with given file
        compare(args.input_file_1, run_benchmark(args.output_path), args.output_path, args.input_path)
    else:  # Two arguments: compare the two given files
        compare(args.input_file_1, args.input_file_2, args.output_path, args.input_path)
