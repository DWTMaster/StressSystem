<h1 align="center"> Stress system for Olympiad programming (for CLion users)</h1>

The system implemented in this project allows you to quickly generate random tests and compare two solutions on them. It's able to catch errors such as: Wrong answer, Runtime error and Time limit exceeded


<h1 align="center"> Guide how to connect and use </h1>
<h1 allign="left"> Connection </h1>
1) Copy the folder "StressTesting" to your project\
2) Add to your CMakeLists the lines from this CMake come after the comment\

<h1 allign="left"> Ussage </h1>
1) In the file "StressTesting/launcher.cpp" set the "sol_exe" constant to the name of exe solution you want to test\
2) Write a right solution in the file "StressTesting/solution.cpp"\
3) In right and testing solution in main() add lines "#ifdef STRESS...#endif" as shown in the project\
4) Write a test generation in file "StressTesting/generator.cpp" (like shown in the project)\
5) Write a logic of comparison right and testing solutions in function check() in "StressTesting/checker.cpp"\
6) Run Launcher\
