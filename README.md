# pytoolbox

This project is the third homework assignment for the *Advanced Programming* course at the University of Trieste. It extends the functionality of the previous C++ library, *sci-toolbox*, by transforming it into `pytoolbox`—an enhanced scientific toolbox that integrates seamlessly with Python and introduces additional features.

The toolbox includes two main components:

- **Statistics Module**  
- **Interpolation Module**  

The original C++ libraries are made accessible in Python as `dataframe_bindings` and `interpolation_bindings` after building the bindings using CMake. These bindings can be directly used in Python, as demonstrated in the provided Jupyter notebooks. Alternatively, the entire Python package, `pytoolbox`, can be installed as a unified package. It includes two submodules, `dataframe` and `interpolation`, which incorporate the respective C++ bindings along with new Python methods that extend and enhance the functionality of the original classes.

To ensure robustness, the project includes comprehensive tests for all functionalities, alongside two dedicated Jupyter notebooks that showcase and validate the toolbox's features.


## Table of contents

- [pytoolbox](#pytoolbox)
  - [Table of contents](#table-of-contents)
  - [Project structure](#project-structure)
  - [Build \& Install](#build--install)
    - [Installing third part libraries](#installing-third-part-libraries)
    - [Building the bindings via CMake](#building-the-bindings-via-cmake)
    - [Installing `pytoolbox` via pip](#installing-pytoolbox-via-pip)
  - [Module A: Statistics](#module-a-statistics)
    - [C++ Class](#c-class)
    - [Python Class](#python-class)
    - [Python Class](#python-class-1)
  - [Module B: Interpolation](#module-b-interpolation)
  - [Authors and contributions](#authors-and-contributions)

## Project structure

```
📂 project/
│
├── 📂 apps/
│   ├── 📓 interpolation.ipynb
│   └── 📓 statistics.ipynb
│
├── 📂 bindings/
│   ├── 📄 DataFrameBindings.cpp
│   └── 📄 InterpolationBindings.cpp
│
├── 📂 datasets/
│   ├── 📊 iris.csv
│   └── 📊 iris.json
│
├── 📂 include/
│   ├── 📄 CardinalCubicSpline.hpp
│   ├── 📄 GslPolynomialInterpolator.hpp
│   ├── 📄 Interpolator.hpp
│   ├── 📄 LinearInterpolator.hpp
│   ├── 📄 NewtonInterpolator.hpp
│   └── 📄 DataFrame.hpp
│
├── 📂 pytoolbox/
│   ├── 🐍 __init__.py
│   ├── 🐍 dataframe.py
│   └── 🐍 interpolation.py
│
├── 📂 src/
│   ├── 📄 CardinalCubicSpline.cpp
│   ├── 📄 GslPolynomialInterpolator.cpp
│   ├── 📄 Interpolator.cpp
│   ├── 📄 LinearInterpolator.cpp
│   ├── 📄 NewtonInterpolator.cpp
│   └── 📄 DataFrame.cpp
│
├── 🛑 .gitignore
├── 🛠️ CMakeLists.txt
├── 📦 requirements.txt
├── 🐍 setup.py
└── 📜 README.md

```
## Build & Install

### Installing third part libraries

The two modules uses functions from *GSL-GNU Scientific Library* and *BOOST library*, so its necessary to install both libraries before building the toolbox.

You can install the third part library from the terminal writing

```bash
sudo apt-get install libboost-all-dev
```
for BOOST and

```bash
sudo apt-get install libgsl-dev
```
for GSL.

### Building the bindings via CMake

To build both the modules (default behavior), run the following commands from the project's root directory:

```bash
cmake -S . -B build
cmake --build build
```

To build only one of the two modules, specify the desired options with `ON` or `OFF`. For example, to build `dataframe_bindings` and exclude the `interpolation_bindings`, use:

```bash
cmake -S . -B build -DBUILD_DATAFRAME_BINDINGS=ON -DBUILD_INTERPOLATION_BINDINGS=OFF
cmake --build build
```

Once the two modules are built, they are placed in the `build/` directory. To use them in a Python script, from the root of the project, you can import them by appending the `build/` directory to your `sys.path` as follows:

```python
import sys
sys.path.append('./build')  # Ensure the build directory is in the Python path

import dataframe_bindings
import interpolation_bindings
``` 

### Installing `pytoolbox` via pip

To install the entire `pytoolbox` package, navigate to the project's root directory and execute the following commands:

```bash
python setup.py build
pip install .
```

After installation, you can seamlessly import and use the submodules. For example:

```python
from pytoolbox.dataframe import DataFrame
from pytoolbox.interpolation import Interpolator
```

For detailed examples and usage demonstrations, refer to the accompanying Jupyter notebooks.


## Module A: Statistics

### C++ Class

The `DataFrame` class serves as the core of the statistics module, offering a comprehensive framework for data storage, manipulation, and analysis. It includes functionalities for reading from file (CSV, JSON), handling tabular data and performing basic statistical operations.

The class stores its data in a **column-oriented** structure, which means the data is maintained as a **vector of column vectors**. This design choice has several implications for performance and flexibility, particularly for operations involving entire columns or statistical calculations.

Each element in the DataFrame can either be a `double` or a `std::string`, this is achieved using the C++ `std::variant` type. Each column is represented as a vector of `std::optional<DataType>`. The use of `std::optional` allows individual elements to be `null` or missing ( i.e. `std::nullopt`).

The class provides methods for reading data from both CSV and JSON files. For details on these methods, as well as the available statistical functions, refer to the corresponding `.hpp` and `.cpp` files.

Finally, the class also provides an iterator that allows for easy row-by-row traversal of the DataFrame, for example a range-based loop looks like:

```cpp
for (const auto& row : df) {
    // Each `row` is a vector of std::optional<DataType> representing a dataframe's row.
}
```

### Python Class

### Python Class

The `DataFrame` class from the `dataframe_bindings` module, originally implemented in C++ and exposed to Python using Pybind11, has been dynamically extended to provide a more Pythonic and feature-rich interface. Additional methods, such as `to_pandas`, `plot_histogram`, `plot_correlation_matrix`, `scatter_plot`, and `advanced_stat`, leverage powerful Python libraries like `pandas`, `seaborn`, and `numpy` to enhance functionality. Special methods like `__str__`, `__len__`, and `__getitem__` have been overridden to enable intuitive interactions, such as viewing the DataFrame as a string, accessing columns using square brackets, or obtaining its length with `len()`. 

Additionally, an iterator method (`__iter__`) has been implemented (based on the C++ iterator), allowing for Pythonic iteration over the rows of the `DataFrame`. By using a simple `for` loop, each row can be accessed sequentially using for example:

```python
df = DataFrame()

for row in df:
    print(row)  # Process each row
```


## Module B: Interpolation

## Authors and contributions

**Elena Ruiz de la Cuesta**: 
elenaruizdelacuestacastano@gmail.com

Interpolation module and documentation

**Giovanni Lucarelli**: 
giovanni.lucarelli@studenti.units.it

Statistics module and documentation.
