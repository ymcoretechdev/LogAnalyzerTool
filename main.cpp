#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: analyze <log_folder_path>\n";
        return 1;
    }

    std::string folderPath = argv[1];
    std::map<std::string, int> errorCount;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_regular_file()) continue;

        std::ifstream file(entry.path());
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("ERROR") != std::string::npos) {
                errorCount["ERROR"]++;
            }
            if (line.find("Exception") != std::string::npos) {
                errorCount["Exception"]++;
            }
        }
    }

    // Sort results
    std::vector<std::pair<std::string, int>> sortedErrors(errorCount.begin(), errorCount.end());
    std::sort(sortedErrors.begin(), sortedErrors.end(),
        [](auto& a, auto& b) { return a.second > b.second; });

    // Output to console
    std::cout << "\nError Frequency Ranking:\n";
    for (auto& e : sortedErrors) {
        std::cout << e.first << ": " << e.second << "\n";
    }

    // Save to CSV
    std::ofstream out("result.csv");
    out << "ErrorType,Count\n";
    for (auto& e : sortedErrors) {
        out << e.first << "," << e.second << "\n";
    }
    out.close();

    std::cout << "\nResult saved to result.csv\n";
    return 0;
}
