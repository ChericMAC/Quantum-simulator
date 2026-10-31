# Quantum simulator
A lightweight quantum circuit simulator implemented in C++ and CUDA for GPU-accelerated state vector manipulation and performance benchmarking.

## Overview
This project was initially built as a way to research and understand how logical quantum gates operate in a quantum computer and how they affect the probabilities of individual measurement outcomes.

Today, it is a functional tool that allows users to build quantum circuits via a CLI, execute them, and inspect the results—either as the complete state vector, a measurement shot chart, or a CLI listing of the shots.

The project was originally written entirely in C++ (as shown in the secondary branch). Later on, I decided to redesign and port core parts of the codebase to CUDA to use GPU acceleration, significantly reducing execution time and improving overall performance.

## Key Features
- **Comprehensive Gate Support:** Implementation of a wide variety of quantum gates, ranging from single-target, controlled, and multi-target/control operations to arbitrary rotation gates.
- **Thread Optimization:** Use of bitwise logical operations on state vector indices, completely avoiding heavy matrix multiplication operating costs.
- **Circuit Optimization:** Real-time simplification for simple single-target gates.
- **Lightweight Architecture:** Built from scratch without heavy or complex external frameworks.

## Architecture & technical design
This simulator is built around a clear separation between the host (CPU) and the device (GPU):
- **State Vector Management:** The state vector is allocated in two separate `cuDoubleComplex` vectors in GPU memory. The primary vector holds the main state, while the auxiliary vector acts as a temporary buffer during gate operations where thread indices swap or combine with partner indices. This dual-buffer approach prevents race conditions and ensures memory safety during parallel execution. Once operations finish, the auxiliary data is synchronized back to the main vector.
- **Bitwise Gate Operations:** To avoid explicitly constructing dense $2^n \times 2^n$ unitary matrices (which would destroy performance), the kernels use bitwise operations on thread indices combined with direct gate matrix math, achieving nearly $O(n)$ complexity per operation.
- **Gate Simplification & Optimization:** 
  - *Single-target gates:* Operations like Pauli-X or Hadamard are tracked and simplified upon insertion using a boolean map, allowing consecutive self-inverse gates to cancel each other out.
  - *Rotation gates:* Gates like $R_y$ manage accumulated angles dynamically, combining consecutive controlled rotations by simply summing their $\theta$ parameters.
- **Workflow:** 
  1. The user specifies the number of qubits via the CLI, initializing two state vectors of size $2^n$ in the GPU.
  2. Circuit commands are entered interactively and optimized on the fly.
  3. When non-simplifiable gates are reached or execution is triggered, the corresponding CUDA kernels are dispatched to the GPU.
  4. Once all quantum gates have finished executing, a copy of the final state vector is transferred from the GPU back to the CPU memory to safely handle the measurement and result processing.
  5. Finally, measurement shots are simulated via a probability vector and a pseudo-random number generator, printing results to the CLI and optionally invoking an external Python script to render a `matplotlib` chart.

## Performance & benchmarking
Using a Quantum Fourier Transform (QFT) circuit—which generates an equal superposition of all possible states—the performance of both the C++ CPU and CUDA GPU circuit simulators was tested against an industrial standard like Qiskit Aer (averaging 10 runs per data point). The results of execution time prior to measurement (shots) are shown in the table below:

| Number of Qubits | CUDA (ms) | CPU (ms) | Qiskit + Transpiler (ms) | Qiskit - Transpiler (ms) |
| :--------------: | :-------: | :------: | :----------------------: | :----------------------: |
|      **4**       |  3.3766   |  1.8497  |         67.4325          |          0,6265          |
|      **10**      |  9.0990   |  5.5532  |          70.766          |          2.1372          |
|      **16**      |  15.6187  | 128.138  |          80.84           |          4.8339          |
|      **20**      |  19.2858  | 1,875.10 |          85.319          |          7.6777          |
|      **25**      |  27.4391  | 49,363.4 |         98.8593          |         11.4013          |
### Key Considerations:
- **Exponential Scaling of CPU:** As seen in the table above, the execution time of the CPU increases exponentially. This is due to the exponential memory scaling at a rate of $2^n$ required to represent the state vectors.
- **GPU-Acceleration:** Thanks to the parallelism of GPU threads, a vast number of operations can be executed simultaneously, yielding far greater efficiency at scale. However, due to the initial overhead of allocating memory in the GPU's VRAM, CPU execution times can outperform the GPU at a very low number of qubits.
- **Qiskit Transpiler Consideration:** Beyond the circuit simplification processes implemented in this repository, Qiskit's transpiler performs complex optimizations, decomposes gates into native hardware instructions, and executes processes necessary to target real quantum hardware. Because it does not perform the exact same pipeline functions, a direct raw comparison has technical nuances; maintaining both data sets ensures transparent and honest benchmarking.
## Getting started
### Prerequisites
To be able to compile and run the program locally, you will need:
- An **NVIDIA GPU** with CUDA support (required only for the GPU version).
- **NVIDIA CUDA Toolkit** (required only for the GPU version).
- A **C++20** compatible compiler.
- **Python 3** with `matplotlib` installed (optional, required only to generate the shot results charts).

### Compilation
Make sure all prerequisites are met, then follow these steps:
1. Clone or download the files of the repository into a new empty folder.
2. Create an extra `results` folder inside the project directory.
3. Open an **x64 Native Tools Command Prompt** and navigate to the project folder.
4. Compile using the `nvcc` CUDA compiler:
```bash
nvcc -std=c++20 src/main.cu src/gates.cu src/gate_cache_manager.cu src/statevector.cu src/run.cu -Iinclude -o main.exe
```
5.  Execute the program:
```bash
main.exe
```

If you want to compile and test the CPU-only implementation:
1. Download the code from the `cpu-version` branch.
2. Create a new `results` folder inside the project directory.
3. Open a **Developer Command Prompt** and navigate to the project folder.
4. Compile the C++ files using MSVC (`cl`):
```bash
  cl /EHsc /std:c++20 /I include src/*.cpp /Fe:main.exe
```
5. Execute the program:
```bash
main.exe
```
