# Find the cat

Find the cat is a school project made for TELECOM Nancy. The purpose of this project is to familiarise students with system calls in the C language.
The aim of the project is to create a CLI tool to search files inside a linux OS.

## Installation

To install the CLI tool you just need to clone the repo and use the given makefile.

```bash
git clone https://github.com/thibault-cne/find-the-cat
cd find-the-cat
make
```

## Documentation

Here is a list of the currently available options and parameter for the CLI

| Options name | Description | Parameters |
|----------|:-------------:|------:|
| -name | Search files by name inside the subdirectories. | A string with the file extension. |
| -size | Search files by size inside the subdirectories. | For the size measurement units please refer to the next tables. You can add a `+` or a `-` in front of the size to specify if it should search for files with greater or lower size. |
| -date | Search files by last modification date inside the subdirectories. | For the date measurement units please refer to the next tables. You can add a `+` to search for oldest files. By default, it searches newest files. |

Files size
| Symbol | Size |
|--------|:-----:|
| c | bytes (by default) |
| k | kibibytes (KiB, 1024 bytes) |
| M | mebibytes (MiB, 1024 * 1024 = 1048576 bytes) |
| G | gibibytes (GiB, 1024 \* 1024 \* 1024 = 1073741824 bytes) |

Files date
| Symbol | Duration |
|--------|:-----:|
| m | minutes |
| h | hours |
| j | days |

In addition to those parameters, you should give a valid path to analyse has the first parameter.
For exemple :

```bash
./build/findTheCat ./baz -date 3h
```

This line search for files last modified earlier than 3 hours inside the `./baz` folder.
