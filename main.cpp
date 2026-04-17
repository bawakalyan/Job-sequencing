#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

struct Job {
    string id;
    int deadline;
    int profit;
};

// Sort jobs by profit in descending order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to display line
void printLine() {
    cout << "------------------------------------------------------------\n";
}

// Function to perform Job Sequencing
void jobSequencing(vector<Job>& jobs, int n) {
    // Step 1: Sort jobs by profit
    sort(jobs.begin(), jobs.end(), compare);

    cout << "\n\n===== Jobs After Sorting by Profit (Descending) =====\n";
    printLine();
    cout << left << setw(10) << "Job ID" << setw(15) << "Deadline" << setw(10) << "Profit" << endl;
    printLine();
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << jobs[i].id << setw(15) << jobs[i].deadline << setw(10) << jobs[i].profit << endl;
    }
    printLine();

    // Step 2: Find maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // Step 3: Create slots
    vector<string> slot(maxDeadline, "Empty");
    vector<bool> filled(maxDeadline, false);

    int totalProfit = 0;
    int jobsDone = 0;

    // To store skipped jobs
    vector<string> skippedJobs;

    cout << "\n===== Step-by-Step Job Scheduling =====\n";

    // Step 4: Assign jobs
    for (int i = 0; i < n; i++) {
        bool placed = false;

        cout << "\nTrying to schedule Job " << jobs[i].id
             << " (Deadline: " << jobs[i].deadline
             << ", Profit: " << jobs[i].profit << ")\n";

        for (int j = min(maxDeadline, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!filled[j]) {
                filled[j] = true;
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                jobsDone++;
                placed = true;

                cout << "-> Job " << jobs[i].id << " placed in Slot " << j + 1 << endl;
                break;
            }
        }

        if (!placed) {
            skippedJobs.push_back(jobs[i].id);
            cout << "-> Job " << jobs[i].id << " could NOT be scheduled (Skipped)\n";
        }
    }

    // Step 5: Final slot display
    cout << "\n\n===== Final Slot Allocation =====\n";
    printLine();
    cout << left << setw(10) << "Slot No." << setw(15) << "Assigned Job" << endl;
    printLine();
    for (int i = 0; i < maxDeadline; i++) {
        cout << left << setw(10) << i + 1 << setw(15) << slot[i] << endl;
    }
    printLine();

    // Step 6: Display scheduled jobs in order
    cout << "\n===== Scheduled Jobs in Execution Order =====\n";
    for (int i = 0; i < maxDeadline; i++) {
        if (filled[i]) {
            cout << slot[i] << " ";
        }
    }

    // Step 7: Display skipped jobs
    cout << "\n\n===== Skipped Jobs =====\n";
    if (skippedJobs.empty()) {
        cout << "None\n";
    } else {
        for (size_t i = 0; i < skippedJobs.size(); i++) {
            cout << skippedJobs[i] << " ";
        }
        cout << endl;
    }

    // Step 8: Final result summary
    cout << "\n===== Final Result Summary =====\n";
    printLine();
    cout << "Total Jobs Entered      : " << n << endl;
    cout << "Number of Jobs Done     : " << jobsDone << endl;
    cout << "Number of Jobs Skipped  : " << skippedJobs.size() << endl;
    cout << "Maximum Profit Earned   : " << totalProfit << endl;
    printLine();
}

int main() {
    int n;

    cout << "============================================================\n";
    cout << "        JOB SEQUENCING WITH DEADLINES (GREEDY METHOD)\n";
    cout << "============================================================\n";

    // Input validation for number of jobs
    do {
        cout << "Enter number of jobs (must be greater than 0): ";
        cin >> n;

        if (n <= 0) {
            cout << "Invalid input! Number of jobs must be greater than 0.\n";
        }
    } while (n <= 0);

    vector<Job> jobs(n);

    // Input jobs
    cout << "\nEnter details for each job:\n";
    cout << "(Job ID, Deadline, Profit)\n";

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Job " << i + 1 << ":\n";

        cout << "Job ID: ";
        cin >> jobs[i].id;

        // Deadline validation
        do {
            cout << "Deadline (must be > 0): ";
            cin >> jobs[i].deadline;
            if (jobs[i].deadline <= 0) {
                cout << "Invalid deadline! Please enter a positive value.\n";
            }
        } while (jobs[i].deadline <= 0);

        // Profit validation
        do {
            cout << "Profit (must be > 0): ";
            cin >> jobs[i].profit;
            if (jobs[i].profit <= 0) {
                cout << "Invalid profit! Please enter a positive value.\n";
            }
        } while (jobs[i].profit <= 0);
    }

    // Display entered jobs
    cout << "\n\n===== Jobs Entered by User =====\n";
    printLine();
    cout << left << setw(10) << "Job ID" << setw(15) << "Deadline" << setw(10) << "Profit" << endl;
    printLine();
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << jobs[i].id << setw(15) << jobs[i].deadline << setw(10) << jobs[i].profit << endl;
    }
    printLine();

    // Call scheduling function
    jobSequencing(jobs, n);

    cout << "\nProgram Finished Successfully.\n";
    return 0;
}
