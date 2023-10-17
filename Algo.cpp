class disjointset{
	vector<int> rank , parent , size;
public:
	disjointset(int n){
		rank.resize(n+1 , 0);
		size.resize(n+1 , 0);
		parent.resize(n+1);
		for(int i=0;i<=n;i++) parent[i] = i;
	}

	int findUparent(int node){
		if(node == parent[node]) return node;
		return parent[node] = findUparent(parent[node]);
	}

	void UnionByRank(int u , int v){
		int ultimateparent_u = findUparent(u);
		int ultimateparent_v = findUparent(v);

		if(ultimateparent_u == ultimateparent_v) return;
		
		if(rank[ultimateparent_u] < rank[ultimateparent_v]){
			parent[ultimateparent_v] = ultimateparent_u;
		}
		else if(rank[ultimateparent_u] > rank[ultimateparent_v]){
			parent[ultimateparent_u] = ultimateparent_v;
		}
		else{
			rank[ultimateparent_u]++;
			parent[ultimateparent_v] = ultimateparent_u;
		}
	}
	
	void UnionBySize(int u , int v){
		int ultimateparent_u = findUparent(u);
		int ultimateparent_v = findUparent(v);

		if(ultimateparent_u == ultimateparent_v) return;

		if(size[ultimateparent_u] < size[ultimateparent_v]){
			parent[ultimateparent_u] = ultimateparent_v;
			size[ultimateparent_v] += size[ultimateparent_u];
		}
		else{
			parent[ultimateparent_v] = ultimateparent_u;
			size[ultimateparent_u] += size[ultimateparent_v];
		}
	}
};


class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        vector<pair<int , pair<int , int>>> edges;
        for(int i=0;i<V;i++){
            for(auto it : adj[i]){
                int adjnode = it[0];
                int wt = it[1];
                int node = i;
                
                
                edges.push_back({wt , {node , adjnode}});
            }
        }
        
        disjointset ds(V);
        sort(edges.begin() , edges.end());
        int mstwt = 0;
        
        for(auto it : edges){
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            
            if(ds.findUparent(u) != ds.findUparent(v)){
                mstwt += wt;
                ds.UnionBySize(u , v);
            }
        }
        
        return mstwt;
    }
};
