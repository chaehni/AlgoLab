#include <iostream>
#include <vector>
#include <stack>

// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

enum Color
{
    red,
    blue,
    none
};
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int, Color>, K> Vb; // vertex info for storing the component to which the vertex belongs and its coloring
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex;
typedef K::Point_2 Point;

using namespace std;

bool color_graph(Triangulation &t, K::FT rr)
{

    // iterate over all points in triangulation and initialize their color to 'none'
    for (auto it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++)
        it->info() = make_pair(0, none);

    // iterate over all nodes again, this time for every uncolored node we start a DFS to find all the other nodes in the same component
    // at the same time we assign alternating colors
    int components = 0;
    for (auto it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++)
    {

        //if node is already colored we must not start a new DFS with this node
        if (it->info().second != none)
            continue;

        stack<Vertex> s;
        s.push(it);
        it->info() = make_pair(++components, red);

        while (!s.empty())
        {
            Vertex current = s.top();
            s.pop();

            // find all the neighbours and add them to same component but opposite color
            Triangulation::Vertex_circulator c = t.incident_vertices(current);
            do
            {
                K::FT dist = CGAL::squared_distance(current->point(), c->point());
                if (dist > rr || t.is_infinite(c)) // this neighbour is out of transmission range
                    continue;

                if (c->info().second == current->info().second)
                    return false;

                if (c->info().second == none)
                {
                    c->info() = make_pair(components, current->info().second == red ? blue : red);
                    s.push(c);
                }

            } while (++c != t.incident_vertices(current));
        }
    }

    // So far the spanning tree is colorable but this doesn't mean the original, full conflict graph is colorable since we
    // didn't use all the edges from the full conflict graph
    // check that shortes distance between two red points is more than rr, same for blue points by computing two additional triangulations
    // for the two colors
    Triangulation t_red, t_blue;
    vector<Point> rPoints;
    vector<Point> bPoints;

    // create two triangulations from the two point sets
    for (auto it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++)
        if (it->info().second == red)
            rPoints.push_back(it->point());
        else
            bPoints.push_back(it->point());

    t_red.insert(rPoints.begin(), rPoints.end());
    t_blue.insert(bPoints.begin(), bPoints.end());

    // check if closest distance is big enough (we test all edges since we don't know which one is the shortest)
    for (auto it = t_red.finite_edges_begin(); it != t_red.finite_edges_end(); it++)
        if (t.segment(*it).squared_length() <= rr)
            return false;

    for (auto it = t_blue.finite_edges_begin(); it != t_blue.finite_edges_end(); it++)
        if (t.segment(*it).squared_length() <= rr)
            return false;

    return true;
}

void run()
{
    int n, m, r;
    cin >> n >> m >> r;
    K::FT radius = r;

    // read stations
    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }

    // create triangulation from stations, we need it to efficiently get a MST
    Triangulation t;
    t.insert(points.begin(), points.end());

    bool possible = color_graph(t, radius * radius);

    for (int i = 0; i < m; i++)
    {
        int x, y, u, v;
        cin >> x >> y >> u >> v;

        // is no interference even possible?
        if (!possible)
        {
            cout << "n";
            continue;
        }

        Point holmes(x, y);
        Point watson(u, v);

        // can they communicate directly?
        if (CGAL::squared_distance(holmes, watson) <= radius * radius)
        {
            cout << "y";
            continue;
        }

        // are their two closest senders in the same component and within reach?
        Vertex vh = t.nearest_vertex(holmes);
        Vertex vw = t.nearest_vertex(watson);
        if (vh->info().first == vw->info().first &&
            CGAL::squared_distance(vh->point(), holmes) <= radius * radius &&
            CGAL::squared_distance(vw->point(), watson) <= radius * radius)
            cout << "y";
        else
            cout << "n";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}
