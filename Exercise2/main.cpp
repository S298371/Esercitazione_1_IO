#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

double map_values(double x, double old_min, double old_max, double new_min, double new_max) {
    return ((x - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
}

vector<double> calculate_mapped_avg(const vector<double>& values) {
    vector<double> mapped_avg_list;
    double running_sum = 0;

    for (int i = 0; i < values.size(); ++i) {
        double mapped_value = map_values(values[i], 1, 5, -1, 2);
        running_sum += mapped_value;
        mapped_avg_list.push_back(running_sum / (i + 1));
    }
    return mapped_avg_list;
}

int main() {
    ifstream file("data.csv");
    if (!file.is_open()) {
        cerr << "Impossibile aprire il file." << endl;
        return 1;
    }
    vector<double> values;
    string line, value;
    while (getline(file, line)) {
        stringstream ss(line);
        while (getline(ss, value, ',')) {
            values.push_back(stod(value));
        }
    }
    file.close();

    vector<double> mapped_avg = calculate_mapped_avg(values);
    ofstream outfile("result.csv");
    if (!outfile.is_open()) {
        cerr << "Impossibile creare il file result.csv." << endl;
        return 1;
    }

    for (int i = 0; i < mapped_avg.size(); ++i) {
        outfile << mapped_avg[i] << endl;
    }
    outfile.close();
    return 0;
}
