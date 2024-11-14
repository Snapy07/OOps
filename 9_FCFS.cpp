#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Function to find the index of a process in the process list
int getProcessIndex(const vector<string>& procs, const string& proc) {
    for (int i = 0; i < procs.size(); i++) {
        if (procs[i] == proc) {
            return i;
        }
    }
    return -1;
}

// Scheduling function
void solve(vector<string>& procs, vector<string>& rq, vector<int>& at, vector<int>& bt, vector<int>& ct) {
    int time = 0;  // Current time in the simulation
    int i = 0;  // Index for processes arriving in the ready queue
    int n = procs.size();  // Number of processes
    vector<int> tat(n), wt(n);  // Vectors to store Turnaround Time and Waiting Time for each process

    // Table header for process scheduling
    cout << "Time\tReady Queue\tRunning Process\tStatus" << endl;

    while (i < n || !rq.empty()) {  // Loop until all processes are completed
        // Check for processes that have arrived and add them to the ready queue
        while (i < n && at[i] <= time) {
            int index = -1;  // Insertion index in the ready queue for SJF order
            for (int j = 0; j < rq.size(); j++) {
                // Insert process in the ready queue based on arrival time or burst time
                if (at[i] < at[getProcessIndex(procs, rq[j])] || 
                   (at[i] == at[getProcessIndex(procs, rq[j])] && bt[i] < bt[getProcessIndex(procs, rq[j])])) {
                    index = j;
                    break;
                }
            }
            // Insert the process into the ready queue in SJF order
            if (index == -1) {
                rq.push_back(procs[i]);
            } else {
                rq.insert(rq.begin() + index, procs[i]);
            }
            i++;
        }

        // Display ready queue and process status
        cout << time << "\t";
        for (const auto& p : rq) cout << p << " ";
        cout << "\t\t";

        // Process the first process in the ready queue
        if (!rq.empty()) {
            string current_process = rq.front();  // Get the process at the front of the queue
            int index = getProcessIndex(procs, current_process);
            cout << current_process << "\t\t";

            time += bt[index];  // Increment time by the burst time of the current process
            ct[index] = time;  // Set the completion time for the process
            tat[index] = ct[index] - at[index];  // Calculate turnaround time
            wt[index] = tat[index] - bt[index];  // Calculate waiting time
            cout << current_process << " completed" << endl;

            rq.erase(rq.begin());  // Remove the completed process from the ready queue
        } else {
            cout << "Idle" << "\t\tNo process completed" << endl;
            time++;  // If no process is ready, increment time
        }
    }

    // Display the final table of AT, BT, CT, TAT, WT
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int j = 0; j < n; ++j) {
        cout << procs[j] << "\t" << at[j] << "\t" << bt[j] << "\t" << ct[j] << "\t" << tat[j] << "\t" << wt[j] << endl;
    }
}

int main() {
    vector<string> rq, procs;  // Ready queue and process names
    vector<int> at, bt, ct;  // Arrival times, burst times, and completion times
    int num;

    // User input for number of processes and process details
    cout << "Enter the total number of processes: ";  // Example: 3 or 4 
    cin >> num;

    // Input for process names
    cout << "Enter process names: ";  // Example: P1 P2 P3 OR P1 P2 P3 P4
    for (int i = 0; i < num; i++) {
        string str;
        cin >> str;
        procs.push_back(str);
    }

    // Input for arrival times of each process
    cout << "Enter arrival times: ";  // Example: 0 1 2 (for each process)
    for (int i = 0; i < num; i++) {
        int ele;
        cin >> ele;
        at.push_back(ele);
    }

    // Input for burst times of each process
    cout << "Enter burst times: ";  // Example: 5 3 1 (for each process)
    for (int i = 0; i < num; i++) {
        int ele;
        cin >> ele;
        bt.push_back(ele);
    }

    // Initialize completion times to zero for each process
    ct.resize(num, 0);

    // Call the scheduling function to process the tasks
    solve(procs, rq, at, bt, ct);
    return 0;
}
