Strassen
========

Implementation of the Strassen algorithm in C

Testing :
=========
_./gen\_tests_ reads 3 integers : _start_, _step_ and _end_
It generates pairs of random square matrices of sizes _start_, _start + step_, _start + 2*step_, ..., _end_.

They are stored in the _tests_ folder.

Then, running _./benchmark.sh_ checks that the algorithm returns correct answers and measures the execution time.
The output is a tab separated value stream.


