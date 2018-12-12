#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2 <K> Triangulation;
typedef K::Point_2 P;

using namespace std;

struct Edge {
	Edge(int u_, int v_, K::FT d2_) : u(u_), v(v_), d2(d2_) {}
	int u, v;
	K::FT d2;
};

void run(){
    int n, m; cin >> n >> m;
    double p; cin >> p;

    // read jammers
    vector<P> jammers;
    map<P, int> jammers_i;
    for (int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        P jammer = P(x, y);
        jammers.push_back(jammer);
        jammers_i[jammer] = i;
    }

    Triangulation t;
    t.insert(jammers.begin(), jammers.end());

    // extract edges and sort by length
    vector<Edge> edges;
}


int main() {
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	size_t t;
	cin >> t;
	while (t--) { run(); }
}