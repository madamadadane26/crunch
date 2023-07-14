# crunch

This program randomly combines words contained in its input stream and sends them to
the output stream. At program execution, the application shall read in the entire set of words to
use during the combination process. After reaching the EOF symbol, the program shall then
begin randomly selecting words and combining them into a concatenated output word. By
default, the program produces only one combined output word for each execution, but users
may change this behavior by providing an optional command line argument (through *argv)
