#include <bits/stdc++.h>
using namespace std;

struct process
{
    int a_time;         // Arrival time
    int c_time;         // CPU burst time
    int id;             // Process ID for reference
    int w_time;         // Waiting time
    int t_time;         // Turnaround time
    int priority = 0;   // initialised to zero by default
    int remaining_time; // Remaining burst time for preemptive scheduling
    int completiontime;
};

bool compareArrivalTimes(process x, process y)
{
    return (x.a_time < y.a_time);
}

bool compareID(process x, process y)
{
    return (x.id < y.id);
}
bool comparePriority(const process &x, const process &y)
{
    return x.priority < y.priority;
}
void FCFS(process a[], int n)
{
    // Sort processes based on arrival time
    sort(a, a + n, compareArrivalTimes);

    // Calculate waiting time for the first process
    a[0].w_time = 0;

    // Calculate waiting time for the rest of the processes
    for (int i = 1; i < n; i++)
    {
        a[i].w_time = a[i - 1].c_time + a[i - 1].w_time - (a[i].a_time - a[i - 1].a_time);
        if (a[i].w_time < 0)
            a[i].w_time = 0;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        a[i].t_time = a[i].c_time + a[i].w_time;
    }

    // Sort back based on the original process ID to preserve input order
    sort(a, a + n, compareID);

    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += a[i].w_time;
        total_turnaround_time += a[i].t_time;
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

void SJFNP(process a[], int n)
{
    // Sort processes based on arrival time
    sort(a, a + n, compareArrivalTimes);

    bool completed[n] = {false}; // To keep track of completed processes
    int current_time = 0, completed_count = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    while (completed_count < n)
    {
        int idx = -1;
        int min_burst_time = INT_MAX;

        // Find the process with the shortest burst time among the processes that have arrived
        for (int i = 0; i < n; i++)
        {
            if (a[i].a_time <= current_time && !completed[i] && a[i].c_time < min_burst_time)
            {
                min_burst_time = a[i].c_time;
                idx = i;
            }
        }

        if (idx != -1)
        {
            a[idx].w_time = current_time - a[idx].a_time;
            a[idx].t_time = a[idx].w_time + a[idx].c_time;

            current_time += a[idx].c_time;
            completed[idx] = true;
            completed_count++;

            total_waiting_time += a[idx].w_time;
            total_turnaround_time += a[idx].t_time;
        }
        else
        {
            current_time++;
        }
    }

    // Sort back based on the original process ID to preserve input order
    sort(a, a + n, compareID);

    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

void SJFP(process a[], int n)
{
    // Sort processes based on arrival time
    sort(a, a + n, compareArrivalTimes);

    int remaining_time[n];
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = a[i].c_time;
    }

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    int total_waiting_time = 0, total_turnaround_time = 0;

    while (complete != n)
    {
        // Find the process with the minimum remaining time among the processes that have arrived
        for (int j = 0; j < n; j++)
        {
            if ((a[j].a_time <= t) && (remaining_time[j] < minm) && remaining_time[j] > 0)
            {
                minm = remaining_time[j];
                shortest = j;
                check = true;
            }
        }

        if (!check)
        {
            t++;
            continue;
        }

        // Reduce the remaining time by one
        remaining_time[shortest]--;

        // Update minimum
        minm = remaining_time[shortest];
        if (minm == 0)
        {
            minm = INT_MAX;
        }

        // If a process gets completely executed
        if (remaining_time[shortest] == 0)
        {
            complete++;
            check = false;

            finish_time = t + 1;

            // Calculate waiting time
            a[shortest].w_time = finish_time - a[shortest].c_time - a[shortest].a_time;

            if (a[shortest].w_time < 0)
            {
                a[shortest].w_time = 0;
            }

            // Calculate turnaround time
            a[shortest].t_time = a[shortest].c_time + a[shortest].w_time;

            total_waiting_time += a[shortest].w_time;
            total_turnaround_time += a[shortest].t_time;
        }
        t++;
    }

    // Sort back based on the original process ID to preserve input order
    sort(a, a + n, compareID);

    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}
void PriorityNP(process a[], int n)
{
    // Sort processes based on arrival time
    for (int i = 0; i < n; i++)
        a[i].id = i + 1;
    sort(a, a + n, compareArrivalTimes);

    bool completed[n] = {false}; // To keep track of completed processes

    int current_time = 0, completed_count = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    while (completed_count < n)
    {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find the process with the highest priority (lowest priority number) among the processes that have arrived
        for (int i = 0; i < n; i++)
        {
            if (a[i].a_time <= current_time && !completed[i] && a[i].priority < highest_priority)
            {
                highest_priority = a[i].priority;
                idx = i;
            }
        }

        if (idx != -1)
        {
            // Calculate waiting and turnaround times
            a[idx].w_time = current_time - a[idx].a_time;
            a[idx].t_time = a[idx].w_time + a[idx].c_time;

            // Move current time forward
            current_time += a[idx].c_time;

            // Mark the process as completed
            completed[idx] = true;
            completed_count++;

            // Accumulate waiting and turnaround times for averages
            total_waiting_time += a[idx].w_time;
            total_turnaround_time += a[idx].t_time;
        }
        else
        {
            // If no process is available, move time forward
            current_time++;
        }
    }

    // Sort back based on the original process ID to preserve input order
    sort(a, a + n, compareID);

    // Output results
    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

void PriorityP(process a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i].id = i + 1;
        a[i].remaining_time = a[i].c_time;
    }
    sort(a, a + n, compareArrivalTimes);
    int currenttime = 0, completed = 0;
    int idx = -1, maxpriority = INT_MAX;
    while (completed != n)
    {
        idx = -1;
        maxpriority = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (a[i].a_time <= currenttime && a[i].remaining_time > 0 && a[i].priority < maxpriority)
            {
                maxpriority = a[i].priority;
                idx = i;
            }
        }

        if (idx != -1)
        {
            a[idx].remaining_time--;
            currenttime++;
            if (a[idx].remaining_time == 0)
            {
                a[idx].completiontime = currenttime;
                a[idx].t_time = a[idx].completiontime - a[idx].a_time;
                a[idx].w_time = a[idx].t_time - a[idx].c_time;
                completed++;
            }
        }
        else
        {
            currenttime++;
        }
    }

    sort(a, a + n, compareID);

    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
        total_waiting_time += a[i].w_time;
        total_turnaround_time += a[i].t_time;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}
void RoundRobin(process a[], int n, int quantum)
{
    for (int i = 0; i < n; i++)
    {
        a[i].id = i + 1;
        a[i].remaining_time = a[i].c_time;
    }
    sort(a, a + n, compareArrivalTimes);
    int currenttime = 0, completed = 0;
    queue<int> q;
    bool visited[n] = {false};
    q.push(0);
    visited[0] = true;
    while (!q.empty())
    {
        int idx = q.front();
        q.pop();
        if (a[idx].remaining_time > quantum)
        {
            currenttime += quantum;
            a[idx].remaining_time -= quantum;
        }
        else
        {
            currenttime += a[idx].remaining_time;
            a[idx].remaining_time = 0;
            a[idx].t_time = currenttime - a[idx].a_time;
            a[idx].w_time = a[idx].t_time - a[idx].c_time;
            completed++;
        }
        for (int i = 0; i < n; i++)
        {
            if (a[i].a_time <= currenttime && a[i].remaining_time > 0 && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
        if (a[idx].remaining_time > 0)
        {
            q.push(idx);
        }
    }
    sort(a, a + n, compareID);
    int total_waiting_time = 0, total_turnaround_time = 0;
    cout << "Waiting Time and Turnaround Time of processes are: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << a[i].id << ": Waiting Time = " << a[i].w_time << ", Turnaround Time = " << a[i].t_time << endl;
        total_waiting_time += a[i].w_time;
        total_turnaround_time += a[i].t_time;
    }

    cout << "Average Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    process a[n];
    cout << "Enter arrival time and CPU burst time respectively:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].a_time >> a[i].c_time;
        a[i].id = i + 1; // Assign process ID
    }
    int x;
    cout << "Choose type of CPU Scheduling:\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (preemptive)\n";
    cout << "3. Shortest Job First (non-preemptive)\n";
    cout << "4. Priority Scheduling (preemptive)\n";
    cout << "5. Priority Scheduling (non-preemptive)\n";
    cout << "6. Round Robin Scheduling\n";
    cin >> x;
    if (x == 1)
    {
        FCFS(a, n);
    }
    else if (x == 2)
    {
        SJFP(a, n);
    }
    else if (x == 3)
    {
        SJFNP(a, n);
    }
    else if (x == 4)
    {
        cout << "Enter priorities\n";

        for (int i = 0; i < n; i++)
        {
            cout << "process " << i + 1 << " : ";
            cin >> a[i].priority;
        }
        PriorityP(a, n);
    }
    else if (x == 5)
    {
        cout << "Enter priorities\n";

        for (int i = 0; i < n; i++)
        {
            cout << "process " << i + 1 << " : ";
            cin >> a[i].priority;
        }
        PriorityNP(a, n);
    }
    else if (x == 6)
    {
        int q;
        cout << "Enter quantam time : ";
        cin >> q;
        RoundRobin(a, n, q);
    }
    return 0;
}
