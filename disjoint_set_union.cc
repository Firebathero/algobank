#include <utility>
#define N 1000

/*
enum {
    UNION_BY_TREE_SIZE =  (1 << 0),
    UNION_BY_TREE_DEPTH = (1 << 1),
}
*/

int parent[N];
int tree_size[N];

void make_set(int v) {
    parent[v] = v;
    tree_size[v] = 1;
}

//with path compression
//this allows us to recursively connect all children to the root
//as we search
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}


void union_sets(int a, int b) {
    int root_a = find_set(a);
    int root_b = find_set(b);
    if (root_a != root_b) {
        //optimization: merge the smaller tree to the bigger
        if (tree_size[root_a] < tree_size[root_b])
            std::swap(root_a, root_b);
        parent[root_b] = root_a;   
        tree_size[root_a] += tree_size[root_b];
    }
}


int main() {
    //Some interesting applications of DSU
    /*
    can iteratively alter and query groupings in near constant time
    this allows us to do many interesting things 

    1) Connected components: respond to a mix of are_connected queries and graph updates 

    2) Search for connected components in an image: say we've got a mostly white chunk of pixels
        with black pixels too, and we want to put connected whtie pixels into groups
        we can linearly iterate all pixels and simply call union_sets on them and their 4 orthogonal 
        neighbors!  bfs/dfs work too, but with this DSU method we only need one row at a time!
    
    3) Store additional information for each set: 
        similar to how we store tree_size[], we could store data about each group
        in an aux strucutre or even at the root node very easily!  this is becuase as we
        perform finds operations, we traverse to the representative node
        and gather info that can be cached!

    4) Support distances up to representative:
        Maintain the distance between a vertex and the representative of its set
        Store distance to parent as additional info for each node

    */
}
