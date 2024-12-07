#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pair1;
typedef pair<int,pair<int,int>>  pair2 ;
typedef map<int,int>  map1 ;
void testing(vector<pair2 >temp){
    for(int i=0;i<temp.size();i++){
        cout<<"P"<<temp[i].first<<"|"<<temp[i].second.first<<"  "<<temp[i].second.second<<"|| ";
    }
    cout<<endl;
}
vector<pair2 >gant_chart_compression(vector<pair2 >gantc, int process){
    vector<pair2 >find;
    pair2 p;
    vector<int> chck(process,0);
    int chk;
    for(int i = 0; i < gantc.size() ; i++){
        if(chck[gantc[i].first] == 0){
            p.first = gantc[i].first;
            p.second.first = gantc[i].second.first;
            chck[gantc[i].first]++;
        }
        int j;
        for( j = gantc.size() - 1; j >= 0; j--){
            if(chck[gantc[j].first] == 1){
                chck[gantc[j].first]++;
                p.second.second = gantc[j].second.second;
                find.push_back(p);

                break;
            }
        }
    }
    return find;
}
int process_of_shortest_burst_time(int &min_bt_process,map1 a_b,map1 a_p,int max_limit,int process,vector<int>&vis,vector<int>arrival_time){
      
    int min_burst_time=INT_MAX;
      
    for(int i=0;i<process;i++){
        if(vis[i]==0){
            if(arrival_time[i]<=max_limit){
                if(a_b[arrival_time[i]]<min_burst_time){
                    min_bt_process=i;
                    min_burst_time=a_b[arrival_time[i]];
                }
            }
        }
    }

    vis[min_bt_process]=1;
    return min_burst_time;
}
int process_best_set(vector<int>&arrival_time,vector<int>&burst_time,int time_instant){
    int min=INT_MAX;
    int min_process=-1;
    for(int i=0;i<arrival_time.size();i++){
        if(arrival_time[i] <= time_instant  && burst_time[i]!=0){
            if(burst_time[i]<min){
                min=burst_time[i];
                min_process=i; 
            }
        }
    }
    return min_process;
}
vector<pair<int,pair<int,int>>>srtf(vector<int>arrival_time,int &total_time,map<int,int>a_p,map<int,int>a_b,vector<int>&burst_time){
    vector<pair<int,pair<int,int>>>ans;
    int min_arrival_time=INT_MAX;
    int start=0;
    int value=-1;


    while(total_time !=0){
        pair<int,pair<int,int>>p;
        value=process_best_set(arrival_time,burst_time,start);
 
        if(value!=-1){
            burst_time[value]--;
            start++;
            total_time--;
        }

        if(value==-1){
            start++;
            continue;
        }

        p.first=value;
        p.second.first=start-1;
        p.second.second=start;
        ans.push_back(p);
     
    
    }

    return ans;
}
pair1 turnaround_time_and_waiting_time(vector< pair2> gantc, vector<int>burst_t, vector<int> arrival_t){
    pair1 time;
    int turn_around_time = 0, waiting_time = 0;
    for(int i = 0;i < gantc.size();i++){
        turn_around_time += gantc[i].second.second - arrival_t[gantc[i].first];
    }
    waiting_time = turn_around_time - accumulate(burst_t.begin(),burst_t.end(),0);
    time.first = turn_around_time/(arrival_t.size());
    time.second = waiting_time/(arrival_t.size());
    return time;
}
void input(int &process,vector<int>&arrival_time,vector<int>&burst_time,vector<int> &burst_time2,map1 &arrival_burst,map1 &arrival_process,int &total_time){
    int add;
    int a,b;
    cout<<"enter arrival time  ";
    cin>>a;
    arrival_time.push_back(a);
    cout<<"enter burst time  ";
    cin>>b;
    burst_time.push_back(b);
    burst_time2.push_back(b);
    total_time+=b;
    arrival_burst[a]=b;
    arrival_process[a]=process;
    cout<<"enter add=1 for add one more process and add=0 to find the best process scheduliing algorithm ";
    cin>>add;
    cout<<endl;
    process++;
    if(add==1){
        input(process,arrival_time,burst_time,burst_time2,arrival_burst,arrival_process,total_time);
    }
    return;
}
vector<pair2 >fcfs(vector<int>arrival,vector<int>burst,map1 a_p,map1 a_b){
    sort(arrival.begin(),arrival.end());
    vector<pair2 >ans;
    int start=0;
    int end=0;
    for(int i=0;i<arrival.size();i++){
        pair2 p;
        start = (start<=arrival[i]? arrival[i]:start);
        end=start+a_b[arrival[i]];
        p.first=a_p[arrival[i]];
        p.second.first=start;
        p.second.second=end;
        ans.push_back(p);
        start=end;
    } 
    return ans;
}
vector<pair2 >sjf(int processes,map1 a_p,map1 a_b,vector<int>&visited,vector<int>arrival_time){ 
    int min_arrival_time=INT_MAX;
    int min_arrival_time_process=0;
    for(int i=0;i<arrival_time.size();i++){
        if(min_arrival_time>arrival_time[i]){
            min_arrival_time=arrival_time[i];
            min_arrival_time_process=i;
        }
    }
    int start=min_arrival_time;
    int end=0;
    vector<pair2 >ans;
    for(int i=0;i<processes;i++){
        pair2 sjf_pair;
        end=start+process_of_shortest_burst_time(min_arrival_time_process,a_b,a_p,start,processes,visited,arrival_time);;
        sjf_pair.first=min_arrival_time_process; 
        sjf_pair.second.first=start;
        sjf_pair.second.second=end;
        ans.push_back(sjf_pair);
        start=end;
    }
    return ans;
}
vector<pair2> rr(vector<int>arrival,vector<int>burst_time,map1 a_p,map1 &a_b,int time_quanta,int &total_time){
    sort(arrival.begin(),arrival.end());
    int start=0;
    vector<pair2> ans;
    while(total_time!=0){
        for(int i=0;i<arrival.size();i++){
            if(start >= arrival[i]){
                if(a_b[arrival[i]]!=0){ 
                    pair2 p; 
                    int initial=start;  
                    if(a_b[arrival[i]]>time_quanta){
                        int c=a_b[arrival[i]]-time_quanta;
                        a_b[arrival[i]]=c;
                        start+=time_quanta;
                        total_time-=time_quanta;         
                    }

                    else if(a_b[arrival[i]]<=time_quanta){
                        start+=a_b[arrival[i]];
                        total_time-=a_b[arrival[i]];
                        a_b[arrival[i]]=0;
                    }
                    p.first=a_p[arrival[i]];
                    p.second.first=initial;
                    p.second.second=start; 
                    ans.push_back(p);
                }
            }
            else{
                start++;
            }
            //cout<<"total_time"<<total_time<<endl;
        }
        // cout<<"total _ time after while loop"<<total_time<<endl;
        //break;   
    }
    return ans;
}

int main(){

    //INITS
    int total_time = 0, Maximum_process = 0;
    map1 arrival_burst, arrival_process;
    vector<int>arrival_time, burst_time,burst_time2;
    pair1     FCFS_TIME,SJF_TIME, SRTF_TIME, RR_TIME;
    vector<pair2>   fcfs_gantchart, sjf_gantchart, srtf_gantchart, srtf_gantchart_compressed, rr_gantchart, rr_gantchart_compressed;

    //INPUTS    
    input(Maximum_process,arrival_time,burst_time,burst_time2,arrival_burst,arrival_process,total_time);
    int total_time2 = total_time;

    //FCFS
    
    fcfs_gantchart=fcfs(arrival_time,burst_time,arrival_process,arrival_burst);
    FCFS_TIME=turnaround_time_and_waiting_time(fcfs_gantchart,burst_time,arrival_time);
    cout<<"\nFirst Come First Serve"<<endl;
    cout<<FCFS_TIME.first<<"  "<<FCFS_TIME.second<<endl;
    testing(fcfs_gantchart);

    
    //SJF
    vector<int>visited(Maximum_process,0);
    sjf_gantchart=sjf(Maximum_process,arrival_process,arrival_burst,visited,arrival_time);
    SJF_TIME=turnaround_time_and_waiting_time(sjf_gantchart,burst_time,arrival_time);
    cout<<"\nSJF"<<endl;
    cout<<SJF_TIME.first<<"   "<<SJF_TIME.second<<endl;
    testing(sjf_gantchart);


    //SRTF;    
    srtf_gantchart=srtf(arrival_time,total_time2,arrival_process,arrival_burst,burst_time2);
    srtf_gantchart_compressed = gant_chart_compression(srtf_gantchart, Maximum_process); 
    cout<<"\nSRTF"<<endl; 
    testing(srtf_gantchart);
    testing(srtf_gantchart_compressed);
    SRTF_TIME=turnaround_time_and_waiting_time(srtf_gantchart_compressed,burst_time,arrival_time);
    cout<<SRTF_TIME.first<<"  "<<SRTF_TIME.second<<endl;

    //RR
    int time_quanta=2;
    
    rr_gantchart = rr(arrival_time,burst_time,arrival_process,arrival_burst,time_quanta,total_time);
    rr_gantchart_compressed = gant_chart_compression(rr_gantchart, Maximum_process);
    cout<<"Round Robin( with tq = "<<time_quanta<<") "<<endl;
    testing(rr_gantchart);
    RR_TIME = turnaround_time_and_waiting_time(rr_gantchart_compressed,burst_time,arrival_time);
    cout<<RR_TIME.first<<"  "<<RR_TIME.second<<endl;

    int minTT=INT_MAX;
    int minWT=INT_MAX;
    int index=-1;
    vector<pair1> compare(4);
    compare[0] = FCFS_TIME;
    compare[1] = SJF_TIME;
    compare[2] = SRTF_TIME;
    compare[3] = RR_TIME;
    for(int i =0; i<compare.size();i++){
    if(minTT>compare[i].first){
        minTT=compare[i].first;
        minWT=compare[i].second;
        index=i;
    }

    else if(minTT == compare[i].first){
       if(minWT > compare[i].second){
        minWT=compare[i].second;
        index=i;
       }
    }
   }

   if(index==0){
    cout<<"FCFS is best algorithm"<<endl;
   }

   
 else if(index==1){
    cout<<"SJF is best algorithm"<<endl;
   }

   
 else if(index==2){
    cout<<"SRTF is best algorithm"<<endl;
   }

  
   else{
    cout<<"RR is best algorithm"<<endl;
   }

    
}