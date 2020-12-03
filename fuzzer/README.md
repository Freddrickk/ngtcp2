# Fuzzer for the handshake server

## Build

To build the fuzzer, use clang (tested with clang 9) as a C compiler when
building the project:

```bash
mkdir <cmake_output_dir>
cd <cmake_output_dir>
CC=clang cmake ..
cmake --build . --target ServerHandshakeFuzzer
```

## Run

To run the fuzzer, go in the output directory and run `ServerHandshakeFuzzer`
in the `fuzzer/` directory:

```bash
./fuzzer/ServerHandshakeFuzzer
```

## Run the crashing output

To run the fuzzer with the input resulting in a crash, use the file in the
directory
`<project_dir>/fuzzer/input/crash-7d4017f07931d479974dac32a22a9da736ebd857` as
such:

```bash
<cmake_output_dir>/fuzzer/ServerHandshakeFuzzer
<project_dir>/fuzzer/input/crash-7d4017f07931d479974dac32a22a9da736ebd857
```
