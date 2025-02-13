//Job Scheduler

#include <bits/stdc++.h>
using namespace std;


class job{
public:
    char id;
    int dead;
    int profit;

    job(){

    }

    job(char i, int d, int p){
        this->id = i;
        this->dead = d;
        this->profit = p;
    }

};

bool comparator (job a, job b){
    return a.profit > b.profit;
}

void JobSchedular(job arr[], int n){

    sort(arr,arr+n,comparator);

    bool slots[n] = {false};

    int ans[n] ;
    fill(ans, ans + n, -1);  // -1 means no job scheduled for that slot


    for(int i=0;i<n;i++)
    {
        for(int j=min(n,arr[i].dead) -1; j>=0; j--){
            if(!slots[j]){
                ans[j] = i;
                slots[j] = true;
                break;
            }
        }
        
    }
    int total_profit = 0;
    for (int i = 0; i < n; i++)
    {
        if(ans[i] == -1)break;
        cout << arr[ans[i]].id << " " << arr[ans[i]].dead << " " << arr[ans[i]].profit <<endl ;
        total_profit += arr[ans[i]].profit;
        
    }
    cout<<"Total Profits: "<<total_profit<<endl;

}

int main(){
    int x;cout<<"Enter number of jobs: ";cin>>x;
    job arr[x];
    for(int i=0;i<x;i++){
        cout<<"Enter id: ";cin>>arr[i].id;
        cout<<"Enter deadline: ";cin>>arr[i].dead;
        cout<<"Enter profit: ";cin>>arr[i].profit;
    }

    // job arr[] = { {'a', 2, 100}, 
    //               {'b', 1, 19}, 
    //               {'c', 2, 27}, 
    //               {'d', 3, 15}, 
    //               {'e', 3, 125} };
                                       

    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Sequence of jobs:\n";
    JobSchedular(arr, n);

    return 0;

}