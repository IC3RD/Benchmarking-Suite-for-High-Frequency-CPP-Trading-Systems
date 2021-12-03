# Benchmarking the codebase with report generation
[Back to homepage](../README.md)

## Set-Up and Prerequisites 
*Note: This script is meant for Linux machines - it will not work for any other OS*
1. Set the venv folder in the root directory of the project as your python interpreter 
2. Build the project as specified in the root directory [README.md](../README.md) file 
3. Load (run) the `CMakeLists.txt` file in the root directory to get the benchmarker executable
4. Move to `CPP-design-pattern-for-low-latency/benchmarking` directory before running the script
5. Output files from the script will be written to `/outputs/benchmarking` folder

## Running the script 
1. Run `./benchmarking_script.py [args] [options]` with args and options as below

- *Note: The script is configured to be run with three different configurations (based on the number of arguments provided):*
#### Number of arguments:
###### No arguments:
- This will run the benchmarking with results printed in the **terminal**

###### One argument:
- Giving the script a **file name** as an argument will cause it to run the benchmarker and then compare the results with the
results in the given file. 
- The script produces a report which will be saved in the `/outputs` folder as a pdf.
- **Make sure the file given as an argument is in the `/outputs` folder**

###### Two arguments:
- Giving the script **two file names** as arguments will cause it to compare the results of the given files.
- The script produces a report which will be saved in the `/outputs` folder as a pdf.
- **Make sure the given files are in the `/outputs` folder**

#### Notes:
* Please make sure you run it at least once without arguments (to produce at least one file)
* The script is configured to work with files it has previously produced (to get the correct format), so do not try to 
run it with your own files.
* The naming conventions used are:
    * `benchmark_at[DATE_TIME]` for files produced by the benchmarker (json files)
    * `comparison_[FILE_1]_[FILE_2].pdf` for each report produced
      * here `FILE_1` and `FILE_2` are named as `benchamark_at[DATE_TIME]` as mentioned above

#### Options:
* `-h` or `--help`: get help
* `-output-path OUTPUT_PATH` or `--out OUTPUT_PATH`: specify the path for the outputted files (default `/outputs`)
* `-input-path INPUT_PATH` or `--in INPUT_PATH`: specify the path for the input files (default `/outputs`)

[Back to home page](../README.md)

