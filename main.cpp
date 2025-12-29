#include <iostream>    // For input and output operations
#include <string>      // To use string data type
#include <fstream>     // For reading from and writing to files
#include <sstream>     // For parsing lines using stringstream
using namespace std;

const int MAX_PATIENTS = 30;  // Maximum number of patients that can be stored in arrays

// Function to calculate BMI category based on weight (kg) and height (m)
string calculateBMI(float weight, float height) {
    float bmi = weight / (height * height);  // BMI formula
    if (bmi < 18.5) return "Underweight";    // Underweight
    else if (bmi < 25) return "Normal";      // Normal weight
    else if (bmi < 30) return "Overweight";  // Overweight
    else return "Obese";                     // Obese
}

// Function to categorize blood pressure based on systolic and diastolic values
string calculateBPCategory(int systolic, int diastolic) {
    if (systolic < 120 && diastolic < 80) return "Normal";      // Normal
    else if (systolic <= 139 || diastolic <= 89) return "Elevated"; // Prehypertension / Elevated
    else return "High";                                         // Hypertension (High)
}

// Function to determine triage level based on temperature, heart rate, and systolic BP
string calculateTriage(float temperature, int heartRate, int systolicBP) {
    if (temperature > 39 || heartRate > 120 || systolicBP > 180) return "Red";    // Emergency (highest priority)
    else if (temperature >= 38 || heartRate >= 100 || systolicBP >= 140) return "Yellow"; // Urgent
    else return "Green";                                                          // Stable / Non-urgent
}

// Function to read patient data from a CSV file and store it in the provided arrays
int readPatientsFromCSV(const string& filename, int ids[], string names[], int ages[], string genders[],
                        float weights[], float heights[], float temperatures[], int systolicBPs[], int diastolicBPs[], int heartRates[]) {
    ifstream file(filename);      // Open file for reading
    string line;                  // To store each line from the file
    int patientCount = 0;         // Counter for number of patients read

    while (getline(file, line) && patientCount < MAX_PATIENTS) {  // Read lines until EOF or max reached
        stringstream ss(line);    // Convert line to stream for easy comma-separated parsing
        string temp;              // Temporary variable to read each field

        getline(ss, temp, ','); ids[patientCount] = stoi(temp);              // ID
        getline(ss, names[patientCount], ',');                               // Name
        getline(ss, temp, ','); ages[patientCount] = stoi(temp);             // Age
        getline(ss, genders[patientCount], ',');                             // Gender
        getline(ss, temp, ','); weights[patientCount] = stof(temp);          // Weight
        getline(ss, temp, ','); heights[patientCount] = stof(temp);          // Height
        getline(ss, temp, ','); temperatures[patientCount] = stof(temp);     // Temperature
        getline(ss, temp, ','); systolicBPs[patientCount] = stoi(temp);      // Systolic BP
        getline(ss, temp, ','); diastolicBPs[patientCount] = stoi(temp);     // Diastolic BP
        getline(ss, temp, ','); heartRates[patientCount] = stoi(temp);       // Heart Rate

        patientCount++;  // Increment counter
    }
    file.close();        // Close the file
    return patientCount; // Return the actual number of patients read
}

// Function to append a new patient record to the CSV file (append mode)
void appendPatientToCSV(const string& filename, int id, const string& name, int age, const string& gender,
                        float weight, float height, float temperature, int systolicBP, int diastolicBP, int heartRate) {
    ofstream file(filename, ios::app);  // Open file in append mode
    file << id << "," << name << "," << age << "," << gender << ","
         << weight << "," << height << "," << temperature << ","
         << systolicBP << "," << diastolicBP << "," << heartRate << "\n";  // Write data with commas and newline
    file.close();  // Close the file
}

// Function to sort patients in ascending order by BMI using Bubble Sort algorithm
void sortPatientsByBMI(int patientCount, float weights[], float heights[], string names[], int ids[]) {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            float bmi1 = weights[j] / (heights[j] * heights[j]);      // BMI of current patient
            float bmi2 = weights[j+1] / (heights[j+1] * heights[j+1]); // BMI of next patient
            if (bmi1 > bmi2) {  // If current BMI is greater, swap to sort ascending
                swap(weights[j], weights[j+1]);
                swap(heights[j], heights[j+1]);
                swap(names[j], names[j+1]);
                swap(ids[j], ids[j+1]);
            }
        }
    }
}

int main() {
    // Arrays to store patient data (maximum 30 patients)
    int ids[MAX_PATIENTS];
    string names[MAX_PATIENTS];
    int ages[MAX_PATIENTS];
    string genders[MAX_PATIENTS];
    float weights[MAX_PATIENTS];
    float heights[MAX_PATIENTS];
    float temperatures[MAX_PATIENTS];
    int systolicBPs[MAX_PATIENTS];
    int diastolicBPs[MAX_PATIENTS];
    int heartRates[MAX_PATIENTS];

    // Load initial patient data from patients.csv
    int patientCount = readPatientsFromCSV("patients.csv",
                                           ids, names, ages, genders,
                                           weights, heights, temperatures,
                                           systolicBPs, diastolicBPs, heartRates);

    int choice;  // User's menu selection
    do {
        // Display main menu
        cout << "\nEnter your choice: " << endl;
        cout << "1. Add New Patient" << endl;
        cout << "2. Display All Patients" << endl;
        cout << "3. Search Patient by ID" << endl;
        cout << "4. Generate Daily Summary" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {  // Add a new patient
                cout << "Enter patient ID: ";
                cin >> ids[patientCount];
                cout << "Enter name: ";
                cin >> names[patientCount];
                cout << "Enter age: ";
                cin >> ages[patientCount];
                while (ages[patientCount] < 0) {  // Validate age is non-negative
                    cout << "Age cannot be negative. Enter age again: ";
                    cin >> ages[patientCount];
                }
                cout << "Enter gender: ";
                cin >> genders[patientCount];
                cout << "Enter weight: ";
                cin >> weights[patientCount];
                while (weights[patientCount] <= 0) {  // Validate weight is positive
                    cout << "Weight must be positive. Enter weight again: ";
                    cin >> weights[patientCount];
                }
                cout << "Enter height: ";
                cin >> heights[patientCount];
                while (heights[patientCount] <= 0) {  // Validate height is positive
                    cout << "Height must be positive. Enter height again: ";
                    cin >> heights[patientCount];
                }
                cout << "Enter body temperature: ";
                cin >> temperatures[patientCount];
                while (temperatures[patientCount] < 30 || temperatures[patientCount] > 45) {  // Realistic temperature range
                    cout << "Enter a realistic temperature. Try again: ";
                    cin >> temperatures[patientCount];
                }
                cout << "Enter systolic: ";
                cin >> systolicBPs[patientCount];
                cout << "Enter Diastolic: ";
                cin >> diastolicBPs[patientCount];
                cout << "Enter heart rate: ";
                cin >> heartRates[patientCount];
                while (heartRates[patientCount] < 30 || heartRates[patientCount] > 200) {  // Realistic heart rate range
                    cout << "Enter a realistic heart rate. Try again: ";
                    cin >> heartRates[patientCount];
                }

                // Append new patient to file and update counter
                appendPatientToCSV("patients.csv",
                                   ids[patientCount], names[patientCount], ages[patientCount],
                                   genders[patientCount], weights[patientCount], heights[patientCount],
                                   temperatures[patientCount], systolicBPs[patientCount], diastolicBPs[patientCount], heartRates[patientCount]);
                patientCount++;
                cout << "Patient added successfully!" << endl;
                break;
            }
            case 2: {  // Display all patients sorted by BMI (ascending)
                sortPatientsByBMI(patientCount, weights, heights, names, ids);
                cout << "===== All Patients =====" << endl;
                for (int i = 0; i < patientCount; i++) {
                    cout << "ID: " << ids[i] << endl;
                    cout << "Name: " << names[i] << endl;
                    cout << "Age: " << ages[i] << endl;
                    cout << "Gender: " << genders[i] << endl;
                    cout << "BMI: " << weights[i] / (heights[i] * heights[i]) << endl;
                    cout << endl;
                }
                break;
            }
            case 3: {  // Search patient by ID
                int searchID;
                cout << "Enter patient ID to search: ";
                cin >> searchID;
                bool found = false;
                for (int i = 0; i < patientCount; i++) {
                    if (ids[i] == searchID) {
                        cout << "Patient Found:" << endl;
                        cout << "Name: " << names[i] << endl;
                        cout << "Age: " << ages[i] << endl;
                        cout << "Gender: " << genders[i] << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 4: {  // Generate daily statistical summary
                int highBPCount = 0;      // Count of patients with high blood pressure
                int redTriageCount = 0;   // Count of red triage cases
                int overweightCount = 0;  // Count of overweight patients
                float totalBMI = 0;       // Sum of all BMI values

                for (int i = 0; i < patientCount; i++) {
                    string bmiCategory = calculateBMI(weights[i], heights[i]);
                    string bpCategory = calculateBPCategory(systolicBPs[i], diastolicBPs[i]);
                    string triage = calculateTriage(temperatures[i], heartRates[i], systolicBPs[i]);

                    totalBMI += weights[i] / (heights[i] * heights[i]);

                    if (bpCategory == "High") highBPCount++;
                    if (triage == "Red") redTriageCount++;
                    if (bmiCategory == "Overweight") overweightCount++;
                }

                cout << "===== Daily Summary =====" << endl;
                cout << "Total patients: " << patientCount << endl;
                cout << "Average BMI: " << totalBMI / patientCount << endl;
                cout << "Patients with high BP: " << highBPCount << endl;
                cout << "Red triage cases: " << redTriageCount << endl;
                cout << "Overweight patients: " << overweightCount << endl;
                break;
            }
            case 5:  // Exit the program
                cout << "Exiting program..." << endl;
                break;
            default:  // Invalid menu choice
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);  // Continue loop until user chooses to exit

    return 0;  // Successful program termination
}
