#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

constexpr int TIME_LIMIT = 500; // milliseconds
constexpr std::string solution_exe = "Main.exe";


namespace fs = std::filesystem;

void clear_folders() {
    const std::string path = fs::current_path().parent_path().string() + "\\StressTesting\\Tests";
    for (const auto &entry: fs::directory_iterator(path)) {
        remove_all(entry);
    }
}

std::string launch_program(const std::string &exe_path, const std::vector<std::string> &args) {
    std::string commandLine = "\"" + exe_path + "\"";
    for (const auto &arg: args) {
        commandLine += " " + arg;
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    if (!CreateProcess(
        exe_path.c_str(),
        const_cast<char *>(commandLine.c_str()),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    )) {
        std::cerr << "CreateProcess failed with the exit code: " << GetLastError() << std::endl;
        std::cerr << "Unsuccessful file is: " << exe_path << std::endl;
        exit(-1);
    }

    DWORD waitResult = WaitForSingleObject(pi.hProcess, TIME_LIMIT);
    if (waitResult == WAIT_TIMEOUT) {
        TerminateProcess(pi.hProcess, 0);
        return "TL";
    }

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    if (exitCode) {
        return "RE";
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return "OK";
}

std::string create_test(const int &test) {
    const std::string test_folder = fs::current_path().parent_path().string() + R"(\StressTesting\Tests\Test_)" +
                                    std::to_string(test);
    fs::create_directory(test_folder);
    fs::create_directory(test_folder + "\\Output");

    const std::string input_path = test_folder + "\\Input.txt";
    const std::string tsol_output_path = test_folder + "\\Output\\TestingSolution.txt";
    const std::string rsol_output_path = test_folder + "\\Output\\RightSolution.txt";
    const std::string report_path = test_folder + "\\Report.txt";
    {
        // Generator launch
        std::ofstream input(input_path);
        const std::string generator_exe_path = fs::current_path().string() + "\\Generator.exe";
        const std::string verdict = launch_program(generator_exe_path, {input_path});
        if (verdict != "OK") {
            std::cerr << "Generator launch failed!";
            exit(-1);
        }
    } {
        // Testing solution launch
        std::ofstream tsol_output(tsol_output_path);
        const std::string tsol_exe_path = fs::current_path().string() + "\\" + solution_exe;
        const std::string verdict = launch_program(tsol_exe_path, {input_path, tsol_output_path});
        if (verdict != "OK") { return verdict; }
    } {
        // Right solution launch
        std::ofstream rsol_output(rsol_output_path);
        const std::string rsol_exe_path = fs::current_path().string() + "\\Solution.exe";
        const std::string verdict = launch_program(rsol_exe_path, {input_path, rsol_output_path});
        if (verdict != "OK") {
            std::cerr << "Right Solution launch failed with the exit code: " << verdict << std::endl;
            exit(-1);
        }
    } {
        // Checker launch
        std::ofstream report(report_path);
        const std::string checker_exe_path = fs::current_path().string() + "\\Checker.exe";
        const std::string verdict = launch_program(checker_exe_path, {
                                                       input_path,
                                                       report_path,
                                                       tsol_output_path,
                                                       rsol_output_path
                                                   });
        if (verdict == "RE") {
            return "WA";
        }
        if (verdict != "OK") {
            std::cerr << "Report launch failed!";
            exit(-1);
        }
        return "OK";
    }
}

void print_from_file(const std::string &filepath) {
    std::string line;
    std::ifstream file(filepath);
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void print_test_info(const int &test) {
    const std::string test_folder = fs::current_path().parent_path().string() + R"(\StressTesting\Tests\Test_)" + std::to_string(test);
    std::cout << "---------------Input---------------\n";
    print_from_file(test_folder + "\\Input.txt");
    std::cout << "------Testing solution output------\n";
    print_from_file(test_folder + "\\Output\\TestingSolution.txt");
    std::cout << "-------Right solution output-------\n";
    print_from_file(test_folder + "\\Output\\RightSolution.txt");
    std::cout << "--------------Report--------------\n";
    print_from_file(test_folder + "\\Report.txt");
}

int main() {
    clear_folders();
    int TEST_COUNT;
    std::cout << "Enter the number of tests:\t";
    std::cin >> TEST_COUNT;
    for (int test = 1; test <= TEST_COUNT; ++test) {
        const std::string verdict = create_test(test);
        if (verdict == "OK") { continue; }
        std::cerr << "Failed💀 on the test " << test << std::endl;
        std::cerr << "Checker's verdict: " << verdict << std::endl;
        std::cerr << "Get all test info? [YES/NO]:\t";

        std::string answer;
        std::cin >> answer;
        for (char &c: answer) {
            c = static_cast<char>(std::tolower(c));
        }
        if (answer == "y" || answer == "ye" || answer == "yes") {
            print_test_info(test);
        }
        return 1;
    }
    std::cout << "All tests passed!😊😊😊" << std::endl;
    return 0;
}
