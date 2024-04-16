#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Earthquake {
    std::string state;
    double magnitude;
    std::string data_type;
    double longitude;
    double latitude;
};

bool isState(const std::string& name) {
    // List of valid state names for the United States
    static const std::unordered_set<std::string> validStates = {
        "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware",
        "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky",
        "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi",
        "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico",
        "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania",
        "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont",
        "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"
    };

    return validStates.find(name) != validStates.end();
}

int main() {
    std::ifstream file("earthquake_data.csv");
    std::vector<Earthquake> earthquakes;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Earthquake eq;

        // Read state (first column)
        if (std::getline(ss, eq.state, ',')) {
            eq.state.erase(0, eq.state.find_first_not_of(" \t\n\r\f\v"));
            eq.state.erase(eq.state.find_last_not_of(" \t\n\r\f\v") + 1);
        }

        // Read magnitude (second column)
        if (std::getline(ss, field, ',')) {
            eq.magnitude = std::stod(field);
        }

        // Read data type (third column)
        if (std::getline(ss, eq.data_type, ',')) {
            eq.data_type.erase(0, eq.data_type.find_first_not_of(" \t\n\r\f\v"));
            eq.data_type.erase(eq.data_type.find_last_not_of(" \t\n\r\f\v") + 1);
        }

        // Read longitude (fourth column)
        if (std::getline(ss, field, ',')) {
            eq.longitude = std::stod(field);
        }

        // Read latitude (fifth column)
        if (std::getline(ss, field, ',')) {
            eq.latitude = std::stod(field);
        }

        // Check if earthquake data meets all criteria
        if (isState(eq.state) && eq.magnitude >= 3.0 && eq.data_type == "earthquake") {
            earthquakes.push_back(eq);
        }
    }

    // Output filtered earthquake data to JSON file
    std::ofstream jsonFile("earthquake_data.json");
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening JSON file for writing!" << std::endl;
        return 1;
    }

    jsonFile << "[\n";
    for (size_t i = 0; i < earthquakes.size(); ++i) {
        const Earthquake& eq = earthquakes[i];
        jsonFile << "    {\n";
        jsonFile << "        \"state\": \"" << eq.state << "\",\n";
        jsonFile << "        \"magnitude\": " << eq.magnitude << ",\n";
        jsonFile << "        \"longitude\": " << eq.longitude << ",\n";
        jsonFile << "        \"latitude\": " << eq.latitude << "\n";
        jsonFile << "    }";
        if (i < earthquakes.size() - 1) {
            jsonFile << ",";
        }
        jsonFile << "\n";
    }
    jsonFile << "]\n";

    jsonFile.close();
    std::cout << "Successfully wrote filtered earthquake data to earthquake_data.json" << std::endl;

    return 0;
}