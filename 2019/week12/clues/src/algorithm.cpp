#include <iostream>
#include <vector>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
enum Color
{
    Undf = 0,
    Red = 1,
    Blue = 2
};
typedef std::pair<Color, int> info_t;
typedef CGAL::Triangulation_vertex_base_with_info_2<info_t, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 Point;
typedef Triangulation::Vertex_handle Vh;

using namespace std;

bool color(Triangulation &t, long r)
{
    // Find a two-coloring via BFS on Delauney graph: ignore edges longer or equal to r
    // at the same time keep track of connected components (by not considering all edges we create a forest)
    vector<Point> blue;
    vector<Point> red;

    // initialize all vertices to color 0 and component 0
    for (auto it = t.finite_vertices_begin(); it != t.finite_vertices_end(); ++it)
        it->info() = {Undf, 0};

    int comp = 0;
    // we possibly need to start a new BFS from every node since it could be in a new component
    for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v)
    {
        // maybe this node was visited before
        if (v->info().first != Undf)
            continue;

        // this is a new component; start BFS with Red as color and assign it a new component identifier
        v->info() = {Red, comp++};
        red.push_back(v->point());
        queue<Vh> q;
        q.push(v);

        do
        {
            // go trough all neighbouring vertices and if distance is small enough:
            // - color them if uncolored or verify color if colored
            // - assign same component id
            // - push them to queue

            Vh cur = q.front();
            q.pop();
            Triangulation::Vertex_circulator c = t.incident_vertices(cur);
            do
            {
                if (!t.is_infinite(c) && CGAL::squared_distance(cur->point(), c->point()) <= r * r)
                {
                    if (c->info().first == Undf)
                    {
                        c->info() = {cur->info().first == Red ? Blue : Red, cur->info().second};
                        q.push(c);
                        if (c->info().first == Red)
                            red.push_back(c->point());
                        else
                            blue.push_back(c->point());
                    }
                    if (c->info().first == cur->info().first)
                        return false;
                }
            } while (++c != t.incident_vertices(cur));
        } while (!q.empty());
    }

    // the sub graph is colorable; we need to validate that no two same colored points are to close to be sure the original graph is two colorable as well
    Triangulation tr;
    tr.insert(red.begin(), red.end());
    Triangulation tb;
    tb.insert(blue.begin(), blue.end());

    for (auto it = tr.finite_edges_begin(); it != tr.finite_edges_end(); ++it)
        if (tr.segment(*it).squared_length() <= r * r)
            return false;
    for (auto it = tb.finite_edges_begin(); it != tb.finite_edges_end(); ++it)
        if (tb.segment(*it).squared_length() <= r * r)
            return false;

    return true;
}

void run()
{
    int n, m;
    long r;
    cin >> n >> m >> r;

    vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    Triangulation t;
    t.insert(points.begin(), points.end());

    bool interference = !color(t, r);

    // answer clues
    for (int i = 0; i < m; i++)
    {
        int x, y, u, v;
        cin >> x >> y >> u >> v;

        // if there is interference, communication fails immediately
        if (interference)
        {
            cout << "n";
            continue;
        }

        Point holmes = Point(x, y);
        Point watson = Point(u, v);
        Vh n_holmes = t.nearest_vertex(holmes);
        Vh n_watson = t.nearest_vertex(watson);

        // holmes and watson can communicate directly
        if (CGAL::squared_distance(holmes, watson) <= r * r)
        {
            cout << "y";
            continue;
        }

        // holmes or watson are out of range of closest station
        if (CGAL::squared_distance(holmes, n_holmes->point()) > r * r || CGAL::squared_distance(watson, n_watson->point()) > r * r)
        {
            cout << "n";
            continue;
        }

        // they are in range of stations; check if they are in the same component
        if (n_holmes->info().second == n_watson->info().second)
            cout << "y";
        else
            cout << "n";
    }
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}