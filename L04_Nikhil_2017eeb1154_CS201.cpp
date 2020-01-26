#include <iostream>
#include<bits/stdc++.h>
#include<chrono>
using namespace std;
int find(int x,int in,vector<pair<int,int> >&edges)
{
    for(int i=in;i<edges.size();i++)
    {
        if(edges[i].second==x)
        return i;
    }
    return -1;
}
bool sortbysec(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second < b.second);
}
bool cycle(int u,int v,vector<pair<int,int> >&edges,vector<pair<int,int> >&temp)
{
    int index;
    pair<int,int>k=make_pair(u,v);
    index=find(k.first,0,edges);
    temp.push_back(make_pair(u,v));int l=0;
    while(index!=-1&&edges[index].first!=k.second&&l<edges.size())
    {
    temp.push_back(edges[index]);
    index=find(edges[index].first,0,edges);l++;
    }
    if(index==-1||l==edges.size())
    {
    temp.clear();return 0;
    }
    else
    {temp.push_back(edges[index]);
    return 1;
    }
}
vector<int>dis;
int zero(int root,int degree[],int N,set<int>&k)
{
    for(auto it=k.begin();it!=k.end();it++)
    {
        if(degree[*it]==0)
        {
            auto it1=it;
            k.erase(*it);
            return *it1;
        }
    }
    return -1;
}
int make_matrix(vector<pair<int,int> >A[],vector<pair<int,int> >B[],int N,int root,vector<pair<int,int> >&edges)
{
    int edg;cin>>edg;int degree[N]={0};set<int>k;vector<pair<int,int> >D[N];
    for(int i=0;i<edg;i++)
    {
        int x,y,z;cin>>x>>y>>z;
        D[x-1].push_back(make_pair(y-1,z));
        degree[y-1]++;
    }
        queue<int>q;
        q.push(root);int vis[N]={0};
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        if(vis[f]==0)
        for(int i=0;i<D[f].size();i++)
           {
               A[D[f][i].first].push_back(make_pair(f,D[f][i].second));
               q.push(D[f][i].first);
           }
           vis[f]=1;
    }
    for(int i=0;i<N;i++)
        B[i]=A[i];
    for(int i=0;i<N;i++)
    {
        if(i!=root)
        {
        pair<int,int> min;
           int saveIndex = 0;
           for(int j=0;j<A[i].size();j++)
           if(A[i][saveIndex].second > A[i][j].second)
             saveIndex = j;
             if(A[i].size()>0)
           min=A[i][saveIndex];
           for(int j=0;j<A[i].size();j++)
           {
            A[i][j].second=A[i][j].second-min.second;
           }
        for(int j=0;j<A[i].size();j++)
            if(A[i][j].second==0)
              {
                  edges.push_back(make_pair(A[i][j].first,i));
                  break;
              }
        }
    }if(edges.size()==0)return -1;
    return 1;
}
int Remove_cycle(vector<pair<int,int>>A[],vector<pair<int,int> >&temp,vector<pair<int,int> >&edges,int N)
{
    vector<int>in;vector<int>out;pair<int,int>min;
    vector<pair<int,int> >temp2;vector<pair<int,int> >temp3;
    int dis=2147483647;int u;
    for(int i=0;i<N;i++)
    {
        if(find(i,0,temp)==-1)
        out.push_back(i);
        else
        in.push_back(i);
    }
    for(int i=0;i<in.size();i++)
    {
        int v=in[i];
        for(int j=0;j<A[v].size();j++)
        {
             if(A[v][j].second<dis&&find(A[v][j].first,0,temp)==-1)
             {
                 dis=A[v][j].second;
                 min.first=A[v][j].first;
                 min.second=v;
             }
        }
    }
    for(int i=0;i<in.size();i++)
    {
        int v=in[i];
        for(int j=0;j<A[v].size();j++)
        {
            if(find(A[v][j].first,0,temp)==-1)
             A[v][j].second=A[v][j].second-dis;
        }
    }
    if(cycle(min.first,min.second,edges,temp2))
    {
        temp3=temp;
        for(int i=0;i<temp2.size();i++)
            if(find(temp.begin(),temp.end(),temp2[i])==temp.end())
            temp.push_back(temp2[i]);temp2.push_back(min);
            u= Remove_cycle(A,temp,edges,N);
    }
    else
    {
        edges.push_back(min);return min.second;
    }
     if(find(u,0,temp3)==-1)
     {
         edges.push_back(min);
         int ind=find(u,0,edges);
         edges.erase(edges.begin()+ind);
         return min.second;
     }
     return u;
}
void print_dis(vector<pair<int,int> >C[],int root,int N)
{
    int dis[N];
    for(int i=0;i<N;i++)
        dis[i]=INT_MAX;dis[root]=0;
        queue<int>q;
    q.push(root);
    while(!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=0;i<C[f].size();i++)
           {
               if(C[f][i].second+dis[f]<dis[C[f][i].first])
            {dis[C[f][i].first]=C[f][i].second+dis[f];q.push(C[f][i].first);}
           }
    }
    for(int i=0;i<N;i++)
        if(dis[i]!=INT_MAX)
        cout<<dis[i]<<" ";
        else cout<<"-1 ";
}
int main()
{
    int testcases;cin>>testcases;
    auto t1 = std::chrono::high_resolution_clock::now();
    while(testcases--)
    {
        pair<int,int>k;vector<pair<int,int> >edges;
        vector<pair<int,int> >temp;int index;
        int N,root;cin>>N>>root;
        vector<pair<int,int> >A[N];vector<pair<int,int> >B[N];vector<pair<int,int> >C[N];
        if(make_matrix(A,B,N,root-1,edges)==-1){cout<<"Not possible";continue;}
        for(int i=0;i<N;i++)
        {   k=edges[i];int l=0;
            index=find(k.first,0,edges);
            temp.push_back(edges[i]);
                while(index!=-1&&edges[index].first!=k.second&&l<edges.size())
               {
                temp.push_back(edges[index]);
                index=find(edges[index].first,0,edges);l++;
               }
              if(index==-1||l==edges.size())
               {
                temp.clear();
               }
              else
               {
                   temp.push_back(edges[index]);
                   vector<pair<int,int> >temp3=temp;
                   int u=Remove_cycle(A,temp,edges,N);
                   if(find(u,0,temp3)!=-1)
                    {
                     int ind=find(u,0,edges);
                     edges.erase(edges.begin()+ind);
                    }
               }
        }
        int total=0;
        for(int i=0;i<edges.size();i++)
        {
            int x;
            for(auto it=B[edges[i].second].begin();it!=B[edges[i].second].end();it++)
                if(it->first==edges[i].first)
                x=it->second;total+=x;
            C[edges[i].first].push_back(make_pair(edges[i].second,x));
        }
        edges.push_back(make_pair(-1,root-1));
        sort(edges.begin(),edges.end(),sortbysec);int j=0;
        for(int i=0;i<N;i++)
        {
            if(edges[j].second!=i)
            {
                edges.insert(edges.begin()+j,make_pair(-2,i));
            } j++;
        }
        cout<<total<<" ";
        print_dis(C,root-1,N);

        cout<<"# ";
        for(int i=0;i<edges.size();i++)
        {
            cout<<edges[i].first+1<<" ";
        }cout<<endl;
   }
           auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
          cout <<"Duration= "<<duration;
}
