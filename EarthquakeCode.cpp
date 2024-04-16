#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

struct Earthquake 
{
    string state;
    double magnitude;
};

bool isState(const string& name) 
{
    // List of valid state names for the United States
    static const unordered_set<string> validStates = 
    {
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

int main() 
{
    ifstream file("earthquake_data.csv");
    unordered_map<string, int> state_counts;

    if (!file.is_open()) 
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string field;
        Earthquake eq;

        // Reading state from the first column
        if (getline(ss, eq.state, ',')) 
        {
            // Removing leading and trailing whitespace from state name
            eq.state.erase(0, eq.state.find_first_not_of(" \t\n\r\f\v"));
            eq.state.erase(eq.state.find_last_not_of(" \t\n\r\f\v") + 1);
        }

        // Reading magnitude from the second column
        if (getline(ss, field, ',')) 
        {
            eq.magnitude = stod(field);
        }

        // Filter earthquakes for United States and magnitude >= 2.5
        if (isState(eq.state) && eq.magnitude >= 2.5) 
        {
            state_counts[eq.state]++;
        }
    }

    // Sorting the states by frequency in descending order
    vector<pair<string, int>> sorted_states(state_counts.begin(), state_counts.end());
    sort(sorted_states.begin(), sorted_states.end(), [](const auto& a, const auto& b) 
    {
        return a.second > b.second;
    });

    // Outputting the states in order by frequency
    cout << "States ordered by frequency of earthquakes:\n";
    for (const auto& state : sorted_states) 
    {
        cout << state.first << " - " << state.second << " earthquakes\n";
    }

    return 0;
}