#include "DataFrame.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

// TODO: check documentation

PYBIND11_MODULE(data_frame, m) {
    py::class_<DataFrame>(m, "DataFrame")
        .def(py::init<>(), 
            R"(Constructor for the DataFrame class

            Parameters:
                None
            )")
        .def("read_csv", &DataFrame::read_csv, py::arg("filename"), py::arg("separator") = ',', py::arg("has_header") = true, 
            R"(Read from CSV file, specifing the separator (if necessary) and a bool to specify if
            contains the header or not (if not it will provide a default header: Col1, Col2, ...)
            
            Parameters:
                filename (string): Path of the CSV file to read
                separator (char): Separator of the CSV file (default: ',')
                has_header (bool): Specify if the CSV file has a header (default: True)
            
            Returns:
                None
            
            )")
        .def("read_json", &DataFrame::read_json, py::arg("filename"), 
            R"(Read from JSON file, passing the filename (with the extension)
            
            Parameters:
                filename (string): Path of the JSON file to read

            Returns:
                None
            
            )")
        .def("get_data", &DataFrame::get_data, 
            R"(Return data of the dataset (without the header)
            
            Parameters:
                None
            
            Returns:
                list of list of values: Data of the Dataframe
            
            )")
        .def("shape", &DataFrame::shape, 
            R"(Return the pair: number of rows, number of columns
            
            Parameters:
                None

            Returns:
                tuple: Dimensions of the Dataframe (number of rows, number of columns)
            
            )")
        .def("get_column", &DataFrame::get_column, py::arg("column"), 
            R"(Return the data from a particular column, passing the index (number)
            
            Parameters:
                column (int): Index of the column to get
            
            )")
        .def("get_header", &DataFrame::get_header, 
            R"(Return the header of the dataframe
            
            Parameters:
                None
            
            )")
        .def("add_column", &DataFrame::add_column, py::arg("column_name"), py::arg("new_col"), 
            R"(Insert a column in the dataset, passing the name and the data
            
            Parameters:
                column_name (string): Name of the column to add
                new_col (list): Column to add
            
            )")
        .def("set_header", &DataFrame::set_header, py::arg("new_header"),
            R"(Set a custom header by passing as a vector of strings
            
            Parameters:
                new_header (list of strings): Header to set
            
            )")
        .def("drop_row", &DataFrame::drop_row, py::arg("row"), 
            R"(Drop a row by index (numeric)
            
            Parameters:
                row (int): Index of the row to drop
            
            )")
        .def("drop_col", &DataFrame::drop_col, py::arg("name"), 
            R"(Drop a column by name (string)
            
            Parameters:
                name (string): Name of the column to drop
            
            )")
        .def("find_idx", &DataFrame::find_idx, py::arg("name"), 
            R"(Extract the column index for a given attribute name
            if not present throw an error
            
            Parameters:
                name (string): Name of the column to find
            
            )")
        .def("is_numeric", &DataFrame::is_numeric, py::arg("name"), 
            R"(Check if the data in the column (by name) are numeric
            
            Parameters:
                name (string): Name of the column to check
            
            )")
        .def("table_nan", &DataFrame::table_nan, 
            R"(Print the number of nans for each attribute
            
            Parameters:
                None
            
            )")
        .def("drop_row_nan", &DataFrame::drop_row_nan, 
            R"(Drop rows with NaN values from the Dataframe
            
            Parameters:
                None
            
            )")
        .def("get_double_column", &DataFrame::get_double_column, py::arg("name"), 
            R"(Get a vector of double from a numeric column (passed by name)
            its needed for every gsl method
            
            Parameters:
                name (string): Name of the column to get
            
            )")
        .def("get_string_column", &DataFrame::get_string_column, py::arg("name"), 
            R"(Get a vector of strings from a non numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to get
            
            )")
        .def("formatting_width", &DataFrame::formatting_width, 
            R"(Usefull method to display the output in a formatted style
            
            Parameters:
                None
            
            )")
        .def("mean", &DataFrame::mean, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the mean
            
            )")
        .def("median", &DataFrame::median, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the median
            
            )")
        .def("min", &DataFrame::min, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the minimum
            
            )")
        .def("max", &DataFrame::max, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the maximum
            
            )")
        .def("quantile", &DataFrame::quantile, py::arg("name"), py::arg("q"), 
            R"(Return the quantile of a column for a give value of probability
            
            Parameters:
                name (string): Name of the column to compute the quantile
                q (float): Value of probability
            
            )")
        .def("var", &DataFrame::var, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the variance
            
            )")
        .def("sd", &DataFrame::sd, py::arg("name"), 
            R"(Statistics functions on numerical column (passed by name)
            
            Parameters:
                name (string): Name of the column to compute the standard deviation
            
            )")
        .def("covariance", &DataFrame::covariance, py::arg("name1"), py::arg("name2"), 
            R"(Compute the covariance of the values in two columns of the Dataframe
            
            Parameters:
                name1 (string): Name of the first column to compute the covariance
                name2 (string): Name of the second column to compute the covariance
            
            )")
        .def("correlation", &DataFrame::correlation, py::arg("name1"), py::arg("name2"), 
            R"(Compute the correlation of the values in two columns of the Dataframe
            
            Parameters:
                name1 (string): Name of the first column to compute the correlation
                name2 (string): Name of the second column to compute the correlation
            
            )")
        .def("correlation_matrix", &DataFrame::correlation_matrix, py::arg("names"), 
            R"(Print the correlation matrix for some attributes (passed as a vector of strings)
            
            Parameters:
                names (list of strings): Names of the columns to compute the correlation matrix
            
            )")
        .def("table", &DataFrame::table, py::arg("name"), 
            R"(Frequency table for the categorical data
            
            Parameters:
                name (string): Name of the column to print the table
            
            )")
        .def("head", &DataFrame::head, 
            R"(Print the first 5 rows of the dataframe
            
            Parameters:
                None
            
            )")
        .def("histogram", &DataFrame::histogram, py::arg("name"), py::arg("num_bins") = 10, 
            R"(Print the histogram for a numerical column, for a given number of bins (default 10)
            
            Parameters:
                name (string): Name of the column to print the histogram
                num_bins (int): Number of bins for the histogram (default 10)
            
            )")
        .def("summary", &DataFrame::summary, 
            R"(Print: min, 1st qu., median, mean, 3rd qu., max for all the numerical attributes
            
            Parameters:
                None
            
            )")
        .def("begin", &DataFrame::begin, 
            R"(Return the begin iterator
            
            Parameters:
                None
            
            )")
        .def("end", &DataFrame::end, 
            R"(Return the end iterator
            
            Parameters:
                None
            
            )");
            
    py::class_<DataFrame::row_iterator>(m, "row_iterator")
        .def("operator++", static_cast<DataFrame::row_iterator& (DataFrame::row_iterator::*)()>(&DataFrame::row_iterator::operator++), 
            R"(Pre-increment the iterator)")
        .def("operator++", static_cast<DataFrame::row_iterator (DataFrame::row_iterator::*)(int)>(&DataFrame::row_iterator::operator++), 
            R"(Post-increment the iterator)")
        .def("operator*", &DataFrame::row_iterator::operator*, 
            R"(Dereference operator, return the current row
            
            Parameters:
                None
            
            )")
        .def("operator!=", &DataFrame::row_iterator::operator!=, 
            R"(Check if the iterator is different from another
            
            Parameters:
                None
            
            )");
}
