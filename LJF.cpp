#include <bits/stdc++.h>
using namespace std;
struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
} ps[100];
int main()
{
    int n;
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    ;
    cout << "Enter total number of processes: ";
    cin >> n;
    int sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i+1 << " Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i+1 << " Burst Time: ";
        cin >> ps[i].bt;
    }
    while (completed != n)
    {
        int max_index = -1;
        int maximum = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].bt > maximum)
                {
                    maximum = ps[i].bt;
                    max_index = i;
                }
                if (ps[i].bt == maximum)
                {
                    if (ps[i].at < ps[max_index].at)
                    {
                        maximum = ps[i].bt;
                        max_index = i;
                    }
                }
            }
        }
        if (max_index == -1)
        {
            current_time++;
        }
        else
        {
            ps[max_index].start_time = current_time;
            ps[max_index].ct = ps[max_index].start_time + ps[max_index].bt;
            ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
            ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
            ps[max_index].rt = ps[max_index].wt;
            sum_tat += ps[max_index].tat;
            sum_wt += ps[max_index].wt;
            sum_rt += ps[max_index].rt;
            total_idle_time += (is_first_process == true) ? 0 : (ps[max_index].start_time - prev);
            completed++;
            is_completed[max_index] = true;
            current_time = ps[max_index].ct;
            prev = current_time;
            is_first_process = false;
        }
    }
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i+1 << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t "<<ps[i].rt<<endl;
            cout
             << endl;
    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;
    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    return 0;
}