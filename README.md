## OxPig

An open source CLI tool for systems administrators.
Generates high entropy, yet easy to type, "[xkcd-style](https://xkcd.com/936/)" passwords.

### Features

* Written in modern C++
* Uses [CLI11](https://github.com/CLIUtils/CLI11), an open source C++11 argument parser
* Options include length (wip), range, count, source, randomness (wip), verbosity (wip)

### Usage

~~~
% oxpig -h

  OxPig: Oliver's Xkcd Password Idea Generator
  Source code: <https://github.com/oliverocean/oxpig>
  Released under the GNU GPL, 2020
  
Usage: oxpig [OPTIONS]

Options:
  -h,--help                 Print this help message and exit
  -m,--min UINT=4           Minimum word length
  -M,--max UINT=8           Maximum word length
  -w,--wc UINT=4            Total number of words
  -d,--dict TEXT:FILE       Dictionary source file
~~~

### Examples

~~~
% oxpig
Press <ENTER> key to continue...
correcthorsebatterystaple
%
~~~

~~~
% oxpig -m 5 -M 8 --wc 5 --src ./mydict.txt
Press <ENTER> key to continue...
coffeebatterystaplehorsecorrect
%
~~~

### Notes
Development is currently in progress. Basic functions are working but this tool should still be considered beta. Comments in the code indicate areas that are being actively worked on (wip) and/or additional functionality expected in version 0.1.0.
