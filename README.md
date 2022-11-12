# Find the cat

Find the cat is a school project made for TELECOM Nancy. The purpose of this project is to familiarise students with system calls in the C language.
The aim of the project is to create a CLI tool to search files inside a linux OS.

IF YOU ARE A TNCY STUDENT PLEASE DO NOT COPY PASTE THE PROGRAM TRY TO MAKE IT ON YOUR OWN.

## Installation

To install the CLI tool you just need to clone the repo and use the given makefile.

```bash
git clone https://github.com/thibault-cne/find-the-cat
cd find-the-cat
make
```

If you want to install it on windows (yes it works on too). You can dowload [msys2](https://www.msys2.org) to use linux like commands such as make and gcc. On `msys2` you will need a couple of things :
- gcc
- regex.h

You can dowload all those things with the following commands :

``` bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S $MINGW_PACKAGE_PREFIX-libsystre
```

## Documentation

Here is a list of the currently available options and parameter for the CLI. Please note that for now, all commands are run as AND commands (the CLI handle multiple options as AND options).

| Options name | Description | Parameters |
| :--- | :---: | ---: |
| -name | Search files by name inside the subdirectories. | A string with the file extension or a regex. |
| -size | Search files by size inside the subdirectories. | An integer with a `+`, `-` or nothing in front and a file size symbol (check bellow). |
| -date | Search files by last modification date inside the subdirectories. | An integer with a `+` or nothing in front and a file date symbol (check bellow). |
| -mime | Search files by mime type. | You can use any mime types to search for. Mime types are calculated regarding file extension not encryption. |
| -ctc | Search files by regex inside it. | A string or a regex |
| -dir | Search files by dir name. If no parameters are passed, just display the subdirectories. | A string or a regex. |
| -color | Active color mode | None |
| -test | Test parssing of the arguments | None |
| -perm | Search files or directory by permissions. | An octal value of the permissions. |
| -threads | Activate thread mode. | The number of thread you want. Must be greater than one. |
| -ou | Exec options with `or` instead of `and`. | None |
| -link | Activate the follow of symbolic links directories. | None |

Files size
| Symbol | Size |
| :---: | :---: |
| c | bytes (by default) |
| k | kibibytes (KiB, 1024 bytes) |
| M | mebibytes (MiB, 1024 * 1024 = 1048576 bytes) |
| G | gibibytes (GiB, 1024 \* 1024 \* 1024 = 1073741824 bytes) |

Files date
| Symbol | Duration |
| :---: | :---: |
| m | minutes |
| h | hours |
| j | days |

In addition to those parameters, you should give a valid path to analyse as the first parameter.
For exemple :

```bash
./ftc ./baz -date 3h
```

This line search for files last modified earlier than 3 hours inside the `./baz` folder.
