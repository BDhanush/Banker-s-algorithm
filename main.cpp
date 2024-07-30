#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007
#define val 1000000001
#define debug(x) cout<< #x <<"="<<x<<endl
#define in(x) cin>>x
#define all(x) x.begin(),x.end()
#define PI 3.1415926535897932384626

long long int power();long long int powermod();

vector<vector<int>> order;

bool check(vector<int>& needed,vector<int>& available)
{
    for(int i=0;i<available.size();i++)
        if(needed[i]>available[i])
        {
            return false;
        }
    return true;
}

void nextprocess(vector<int>& allocated,vector<int>& available,vector<int>& needed)
{
    for(int i=0;i<available.size();i++)
    {
        available[i]+=allocated[i];
    }
}

void prevprocess(vector<int>& allocated,vector<int>& available,vector<int>& needed)
{
    for(int i=0;i<available.size();i++)
    {
        available[i]-=allocated[i];
    }
}

void bankers(vector<vector<int>>& maxi,vector<vector<int>>& allocated,vector<vector<int>>& need,vector<int>& available,vector<int>& processes,vector<bool>& visited)
{
    for(int i=0;i<maxi.size();i++)
    {
        if(!visited[i] && check(need[i],available))
        {
            visited[i]=true;
            nextprocess(allocated[i],available,need[i]);
            processes.push_back(i);
            bankers(maxi,allocated,need,available,processes,visited);
            processes.erase(processes.end()-1);
            prevprocess(allocated[i],available,need[i]);
            visited[i]=false;
        }
    }
    if(processes.size()!=maxi.size())
    {
        return;
    }
    order.push_back(processes);
}

void solution()
{
    int n,m;

    cin>>m>>n;
    vector<int> available(m);
    for(int i=0;i<m;i++)
    {
        cin>>available[i];
    }
    vector<vector<int>> maxi(n,vector<int> (m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>maxi[i][j];
        }
    }
    vector<vector<int>> allocated(n,vector<int> (m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>allocated[i][j];
            available[j]-=allocated[i][j];
        }
    }
    vector<vector<int>> need(n,vector<int> (m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j]=maxi[i][j]-allocated[i][j];
        }
    }
    vector<int> process;
    vector<bool> visited(n,false);
    bankers(maxi,allocated,need,available,process,visited);
    cout<<order.size()<<"\n";
    for(int i=0;i<order.size();i++)
    {
        for(int j=0;j<order[i].size();j++)
        {
            cout<<order[i][j]<<" ";
        }
        cout<<"\n";
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t=1;
    //cin>>t;

    while(t--)
    {
        solution();
    }
    return 0;
}

long long int power(long long int a,long long int n)
{
    long long int pow=1;
    for(long long int i=n;i>0;i>>=1)
    {
        if(i&1)
        {
            pow*=a;
        }
        a*=a;
        //a>>=1;
    }
    return pow;
}

long long int powermod(long long int a,long long int n,long long int m)
{
    long long int pow=1;
    a%=m;
    for(long long int i=n;i>0;i>>=1)
    {
        if(i&1)
        {
            pow=pow*a%m;
        }
        a=a*a%m;
    }
    return pow;
}
