#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int priority;
    int arrival_time;
    int burst_time;
};

// Function to perform priority scheduling
void priority_scheduling(int num_processes, vector<Process>& processes) {
    // Sort processes based on arrival time and priority (lower priority value means higher priority)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrival_time != b.arrival_time) return a.arrival_time < b.arrival_time;
        return a.priority > b.priority;
    });
    
    vector<int> completion_time(num_processes);
    vector<int> turnaround_time(num_processes);
    vector<int> waiting_time(num_processes);
    
    int current_time = 0;
    
    for (int i = 0; i < num_processes; ++i) {
        // Process arrives after the current time, so move the current time forward
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Calculate completion time
        completion_time[i] = current_time + processes[i].burst_time;
        
        // Calculate turnaround time
        turnaround_time[i] = completion_time[i] - processes[i].arrival_time;
        
        // Calculate waiting time
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
        
        // Update current time
        current_time = completion_time[i];
    }
    
    // Output
    cout << "\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < num_processes; ++i) {
        cout << "P" << processes[i].id << "\t" << completion_time[i] << "\t\t" << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;
    }
    
    // Calculate average waiting time and turnaround time
    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / num_processes;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / num_processes;
    
    cout << "\nAverage Waiting Time: " << avg_waiting_time << " units\n";
    cout << "Average Turnaround Time: " << avg_turnaround_time << " units\n";
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    
    vector<Process> processes(num_processes);
    
    // Input
    cout << "Enter the priority for processes: ";
    for (int i = 0; i < num_processes; ++i) {
        cin >> processes[i].priority;
        processes[i].id = i + 1;
    }
    
    cout << "Enter the arrival time for processes: ";
    for (int i = 0; i < num_processes; ++i) {
        cin >> processes[i].arrival_time;
    }
    
    cout << "Enter the burst time for processes: ";
    for (int i = 0; i < num_processes; ++i) {
        cin >> processes[i].burst_time;
    }
    
    // Perform priority scheduling
    priority_scheduling(num_processes, processes);
    
    return 0;
}
