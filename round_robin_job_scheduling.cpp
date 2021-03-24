#include <bits/stdc++.h>
using namespace std;

class Job{
public:
    int job_id;
    int arrivalTime;
    int burstTime;
    int tempBurstTime;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

bool compareWithArrivalTime(Job j1, Job j2){
    return j1.arrivalTime < j2.arrivalTime;
}


int main()
{
    int totalJobs;
    cout<<"How many jobs: ";
    cin>>totalJobs;

    Job job[totalJobs];

    for(int i=0;i<totalJobs;i++){
        job[i].job_id = i+1;
        cout<<"Enter arrival time & burst time for job "<<i+1<<": ";
        cin>>job[i].arrivalTime>>job[i].burstTime;
        job[i].tempBurstTime = job[i].burstTime;
    }

    int quantumSize;
    cout<<"Quantum Size: ";
    cin>>quantumSize;

    sort(job, job+totalJobs, compareWithArrivalTime);

    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    double averageWaitingTime;
    double averageTurnAroundTime;

    queue<int> readyQueue;
    int current_job = 0;
    readyQueue.push(current_job);
    job[current_job].startTime = 0;

    int jobDone = 0;
    int time = 0;

    bool vis[totalJobs] = {false};
    vis[current_job] = true;

    while(jobDone != totalJobs){
        current_job = readyQueue.front();
        readyQueue.pop();

        if(job[current_job].tempBurstTime == job[current_job].burstTime){
            time = max(time, job[current_job].arrivalTime);
            job[current_job].startTime = time;
        }

        if(job[current_job].tempBurstTime > quantumSize){
            job[current_job].tempBurstTime -= quantumSize;
            time += quantumSize;
        }
        else {
            time += job[current_job].tempBurstTime;
            job[current_job].tempBurstTime = 0;
            jobDone++;

            job[current_job].completionTime = time;

            job[current_job].turnAroundTime = job[current_job].completionTime - job[current_job].arrivalTime;
            totalTurnAroundTime += job[current_job].turnAroundTime;

            job[current_job].waitingTime = job[current_job].turnAroundTime - job[current_job].burstTime;
            totalWaitingTime += job[current_job].waitingTime;
        }

        if(jobDone == totalJobs)break;

        for(int i=0; i<totalJobs; i++){
            if(job[i].arrivalTime <= time && job[i].tempBurstTime>0 && !vis[i]){
                readyQueue.push(i);
                vis[i] = true;
            }
        }

        if(job[current_job].tempBurstTime > 0)
            readyQueue.push(current_job);

        if(readyQueue.empty()){
            for(int i=0;i<totalJobs;i++){
                if(job[i].tempBurstTime > 0){
                    readyQueue.push(i);
                    vis[i] = true;
                    break;
                }
            }
        }
    }


    cout<<endl<<endl;
    cout<<"Total Jobs: "<<totalJobs<<endl;
    cout<<"Jobs   Arrival Time   Burst Time   Start Time   Completion Time   Waiting Time   Turnaround Time"<<endl;
    for(int i=0;i<totalJobs;i++)
        cout<<job[i].job_id<<"\t   "<<job[i].arrivalTime<<"\t\t"<<job[i].burstTime<<"\t\t"<<job[i].startTime<<"\t\t"
        <<job[i].completionTime<<"\t\t"<<job[i].waitingTime<<"\t\t"<<job[i].turnAroundTime<<endl;

    cout<<endl<<endl;

    averageWaitingTime = (double)totalWaitingTime / (double)totalJobs;
    averageTurnAroundTime = (double)totalTurnAroundTime / (double)totalJobs;

    cout<<"Average Waiting Time: "<<averageWaitingTime<<endl;
    cout<<"Average Turnaround Time: "<<averageTurnAroundTime<<endl;

    return 0;
}
