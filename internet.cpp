#include <bits/stdc++.h>
using namespace std;

/* 
   Combined solution for dynamic connectivity optimization
   using Min-Cost Max-Flow, Segment Tree, and Skip List
  
*/

// Edge for Min-Cost Max-Flow
struct Edge { int to, rev, capacity, cost; };

class MinCostMaxFlow {
    int N; vector<vector<Edge>> G;
public:
    MinCostMaxFlow(int N) : N(N) { G.resize(N); }

    void addEdge(int u,int v,int cap,int cost) {
        G[u].push_back({v,(int)G[v].size(),cap,cost});
        G[v].push_back({u,(int)G[u].size()-1,0,-cost});
    }

    // Finds max flow while minimizing total latency/congestion
    pair<int,int> getMaxFlow(int s,int t) {
        int flow=0,cost=0;
        vector<int> dist(N),prevv(N),preve(N);
        while(true) {
            fill(dist.begin(),dist.end(),INT_MAX); dist[s]=0;
            bool updated=true;
            while(updated) {
                updated=false;
                for(int v=0;v<N;v++) if(dist[v]!=INT_MAX)
                    for(int i=0;i<G[v].size();i++){
                        Edge &e=G[v][i];
                        if(e.capacity>0 && dist[e.to]>dist[v]+e.cost){
                            dist[e.to]=dist[v]+e.cost;
                            prevv[e.to]=v; preve[e.to]=i;
                            updated=true;
                        }
                    }
            }
            if(dist[t]==INT_MAX) break;
            int d=INT_MAX;
            for(int v=t;v!=s;v=prevv[v]) d=min(d,G[prevv[v]][preve[v]].capacity);
            flow+=d;
            for(int v=t;v!=s;v=prevv[v]){
                Edge &e=G[prevv[v]][preve[v]];
                e.capacity-=d;
                G[v][e.rev].capacity+=d;
                cost+=d*e.cost;
            }
        }
        return {flow,cost};
    }
};

// Segment Tree to enforce per-AP bandwidth quotas dynamically
class SegmentTree {
    int size; vector<int> tree,lazy;
public:
    SegmentTree(int n) { size=n; tree.assign(4*n,0); lazy.assign(4*n,0); }

    void push(int node,int l,int r){
        if(lazy[node]){
            tree[node]+=lazy[node];
            if(l!=r){ lazy[node*2]+=lazy[node]; lazy[node*2+1]+=lazy[node]; }
            lazy[node]=0;
        }
    }

    void update(int node,int l,int r,int ql,int qr,int val){
        push(node,l,r);
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ lazy[node]+=val; push(node,l,r); return; }
        int mid=(l+r)/2;
        update(node*2,l,mid,ql,qr,val);
        update(node*2+1,mid+1,r,ql,qr,val);
        tree[node]=max(tree[node*2],tree[node*2+1]);
    }

    int query(int node,int l,int r,int ql,int qr){
        push(node,l,r);
        if(qr<l||r<ql) return 0;
        if(ql<=l&&r<=qr) return tree[node];
        int mid=(l+r)/2;
        return max(query(node*2,l,mid,ql,qr),query(node*2+1,mid+1,r,ql,qr));
    }
};

// Skip List to manage active sessions by priority for quick reassignment
struct SkipNode{
    int sessionID,priority;
    vector<SkipNode*> forward;
    SkipNode(int id,int prio,int level):sessionID(id),priority(prio),forward(level+1,nullptr){}
};
class SkipList{
    int maxLevel; float prob;
    SkipNode* header;
public:
    SkipList(int maxLevel=6,float prob=0.5):maxLevel(maxLevel),prob(prob){
        header=new SkipNode(-1,INT_MAX,maxLevel);
    }
    int randomLevel(){ int lvl=0; while(((float)rand()/RAND_MAX)<prob && lvl<maxLevel) lvl++; return lvl; }

    void insert(int id,int prio){
        vector<SkipNode*> update(maxLevel+1);
        SkipNode* curr=header;
        for(int i=maxLevel;i>=0;i--){
            while(curr->forward[i] && curr->forward[i]->priority<prio) curr=curr->forward[i];
            update[i]=curr;
        }
        int lvl=randomLevel();
        SkipNode* node=new SkipNode(id,prio,lvl);
        for(int i=0;i<=lvl;i++){ node->forward[i]=update[i]->forward[i]; update[i]->forward[i]=node; }
    }

    void display(){
        SkipNode* curr=header->forward[0];
        cout<<"Active Sessions (Priority -> ID): ";
        while(curr){ cout<<"("<<curr->priority<<"->"<<curr->sessionID<<") "; curr=curr->forward[0]; }
        cout<<"\n";
    }
};

int main(){
    srand(time(0));
    cout<<"=== Digital Connectivity Optimization Simulation ===\n\n";

    // Model network as capacitated graph and optimize traffic (Min-Cost Max-Flow)
    MinCostMaxFlow network(4);
    network.addEdge(0,1,10,2);
    network.addEdge(0,2,5,4);
    network.addEdge(1,2,15,1);
    network.addEdge(1,3,10,3);
    network.addEdge(2,3,10,1);
    auto result=network.getMaxFlow(0,3);
    cout<<"Max Flow: "<<result.first<<", Min Cost: "<<result.second<<"\n\n";

    // Apply dynamic per-AP bandwidth limits (Segment Tree)
    SegmentTree quotas(10);
    quotas.update(1,0,9,2,5,5); // increase quota on APs 2-5
    cout<<"Max quota in APs 0-9: "<<quotas.query(1,0,9,0,9)<<"\n\n";

    // Track and reassign sessions based on priority (Skip List)
    SkipList sessions;
    sessions.insert(101,3);
    sessions.insert(102,1);
    sessions.insert(103,5);
    sessions.display();

    cout<<"\nAll three layers combined to simulate intelligent connectivity.\n";
    return 0;
}
