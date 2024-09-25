# CSV Field Extractor

## Overview

This program filters and displays data from a CSV file based on user-defined conditions. It processes the data in a way that the order of conditions specified by the user is strictly followed. After filtering, the program outputs a specific field as requested by the user.

## Features

- **Flexible Condition Filtering**: You can filter data based on any combination of Roll No, First Name, Middle Name, Last Name, Gender, Year, and Degree.
- **Condition Order Preservation**: Conditions are evaluated in the order specified by the user.
- **CSV Input**: The program processes data from a CSV file where fields are structured as `RollNo, FirstName MiddleName LastName, Gender, Year, Degree`.
- **Field Display**: Once the conditions are matched, the program outputs the field specified by the user (e.g., First Name, Roll No, etc.).

## How It Works

1. **Condition Specification**: The user specifies filtering conditions (e.g., Degree, Gender, Year) via command-line arguments.
2. **Field Output**: After specifying the conditions, the user provides the field they want to display, such as the First Name of students matching the conditions.
3. **CSV Structure**: The program assumes the CSV file follows the format:

   ```csv
   RollNo, FirstName MiddleName LastName, Gender, Year, Degree
   ```

## Prerequisites

- Ensure you have a C compiler (e.g., gcc) installed.
- A CSV file containing data in the format mentioned above.

## Program Syntax

```bash
$ gcc parseField.c -o parseField
$ ./parseField <csv-file> <field1> <value1> <field2> <value2> ... -print <fieldx>
```

### Example

To display the **First Names** of students with:

- **Degree**: MSc
- **Gender**: Female (F)
- **Year**: 2024

Use the command:

```bash
$ ./parseField student.csv -d MSc -g F -y 2024 -print -fn
```

This command will search for students in the `student.csv` file where:

- The Degree is `MSc`
- The Gender is `F`
- The Year is `2024`

And will display their First Names.

## Field and Condition Keywords

You have to use the following keywords to specify fields and conditions in the command-line arguments:

| Keyword | Field         |
|---------|---------------|
| `-r`    | Roll No       |
| `-fn`   | First Name    |
| `-mn`   | Middle Name   |
| `-ln`   | Last Name     |
| `-g`    | Gender        |
| `-y`    | Year          |
| `-d`    | Degree        |
| `-print`| Print Field   |

### Important Notes:
- **Conditions**: You can specify any combination of fields as conditions.
- **Print Field**: Only one field can be specified for output using the `-print` option, and must be mentioned in the last.
- **Order of Conditions**: The program evaluates the conditions in the order they are provided.
  
## Error Handling

The program performs the following validations:

1. **CSV File Extension**: The input file must have a `.csv` extension.
2. **Number of Arguments**: The command should have a valid number of arguments. Invalid argument counts will result in an error message.
3. **Field Validation**: The program checks whether the specified field keywords are valid. If not, it returns an error.

## Compilation and Execution

1. **Compilation**: 

   ```bash
   $ gcc parseField.c -o parseField
   ```

2. **Execution**:

   Example of running the program to filter students with `MSc` degree, `F` gender, and `2024` year, displaying their first names:

   ```bash
   $ ./parseField student.csv -d MSc -g F -y 2024 -print -fn
   ```
