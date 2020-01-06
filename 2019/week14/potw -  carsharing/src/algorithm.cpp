#include <iostream>
#include <set>

// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
							  boost::property<boost::edge_capacity_t, long,
											  boost::property<boost::edge_residual_capacity_t, long,
															  boost::property<boost::edge_reverse_t, traits::edge_descriptor,
																			  boost::property<boost::edge_weight_t, long>>>>>
	graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; // Iterator

// Custom edge adder class
class edge_adder
{
	graph &G;

public:
	explicit edge_adder(graph &G) : G(G) {}
	void add_edge(int from, int to, long capacity, long cost)
	{
		auto c_map = boost::get(boost::edge_capacity, G);
		auto r_map = boost::get(boost::edge_reverse, G);
		auto w_map = boost::get(boost::edge_weight, G); // new!
		const edge_desc e = boost::add_edge(from, to, G).first;
		const edge_desc rev_e = boost::add_edge(to, from, G).first;
		c_map[e] = capacity;
		c_map[rev_e] = 0; // reverse edge has no capacity!
		r_map[e] = rev_e;
		r_map[rev_e] = e;
		w_map[e] = cost;	  // new assign cost
		w_map[rev_e] = -cost; // new negative cost
	}
};

struct req
{
	int s, t, d, a, p;
};

using namespace std;

void testcase()
{
	int n, s;
	cin >> n >> s;

	vector<req> reqs(n);
	vector<int> cars(s);
	vector<set<int>> times(s); // keep tracks of all relevant times per station
	map<pair<int, int>, int> index;

	for (int i = 0; i < s; i++)
		cin >> cars[i];

	int max_time = 0;
	for (int i = 0; i < n; i++)
	{
		req r;
		int s, t, d, a, p;
		cin >> s >> t >> d >> a >> p;
		r.s = --s; // fucking 1-indexing
		r.t = --t; // fucking 1-indexing
		r.d = d;
		r.a = a;
		r.p = p;
		times[s].insert(d);
		times[t].insert(a);
		reqs[i] = r;
		max_time = max(max_time, a);
	}

	int cnt = 0;
	// create a zero and max_stime node for every station and give all station-times an index
	for (int i = 0; i < s; i++)
	{
		times[i].insert(0);
		times[i].insert(max_time);
		for (auto it = times[i].begin(); it != times[i].end(); ++it)
			index[{i, *it}] = cnt++;
	}

	// create space-time graph
	graph G(cnt);
	int src = add_vertex(G);
	int dst = add_vertex(G);
	edge_adder eag(G);
	auto c_map = boost::get(boost::edge_capacity, G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	// connect the cars to the starting points (station at time 0)
	for (int i = 0; i < s; i++)
		eag.add_edge(src, index[{i, 0}], cars[i], 0);

	// connect last time point for each station to sink
	for (int i = 0; i < s; i++)
		eag.add_edge(index[{i, max_time}], dst, INT64_MAX, 0);

	// add edges between points in time for same station (car is parked)
	for (int i = 0; i < s; i++)
		for (auto it = times[i].begin(); it != prev(times[i].end()); ++it)
			eag.add_edge(index[{i, *it}], index[{i, *next(it)}], INT64_MAX, 100 * (*next(it) - *it));

	// add edges for rentals
	for (int i = 0; i < n; i++)
	{
		int from = index[{reqs[i].s, reqs[i].d}];
		int to = index[{reqs[i].t, reqs[i].a}];
		int travel_time = reqs[i].a - reqs[i].d;
		eag.add_edge(from, to, 1, travel_time * 100 - reqs[i].p);
	}

	// calculate min cost
	boost::successive_shortest_path_nonnegative_weights(G, src, dst);
	long cost = boost::find_flow_cost(G);
	long flow = 0;
	out_edge_it e, eend;
	for (boost::tie(e, eend) = boost::out_edges(boost::vertex(src, G), G); e != eend; ++e)
	{

		flow += c_map[*e] - rc_map[*e];
	}
	cout << max_time * flow * 100 - cost << "\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
