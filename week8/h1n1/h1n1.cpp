#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;
typedef Triangulation::Face_handle Face;

struct Edge
{
    Edge(Face _from, Face _to, K::FT _dist) : from(_from), to(_to), dist(_dist) {}
    Face from;
    Face to;
    K::FT dist;

    bool operator<(const Edge &e) const
    {
        return dist > e.dist;
    }
};

using namespace std;

map<Face, K::FT> precompute(Triangulation &t)
{

    // create a multiset that puts longest edges first
    // because of the "<" operator defined above and because multiple edges can have the same length,
    // a regular set would not insert all of them
    multiset<Edge> q;
    map<Face, K::FT> m;

    // start from infinite faces and add all edges to non-infinite faces into queue
    for (auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it)
    {
        if (t.is_infinite(it))
        {
            m[it] = INT64_MAX;
            for (int i = 0; i < 3; i++)
            {
                Face nb = it->neighbor(i);
                if (!t.is_infinite(nb))
                {
                    K::FT dist = t.segment(it, i).squared_length();
                    q.insert(Edge(it, nb, dist));
                }
            }
        }
    }

    // deque edges and update face escape values
    while (!q.empty())
    {
        auto edge = *q.begin();
        q.erase(q.find(edge)); // erase would delete all edges of same length
        Face to = edge.to;
        if (m[to] != 0)
            continue;
        K::FT distance = edge.dist;
        m[to] = min(m[edge.from], distance);

        // add edges of found face to queue
        for (int i = 0; i < 3; i++)
        {
            Face nb = to->neighbor(i);
            if (m[nb] == 0)
            {
                K::FT dist = t.segment(to, i).squared_length();
                q.insert(Edge(to, nb, dist));
            }
        }
    }
    return m;
}

void run(int n)
{
    Triangulation t;
    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }
    t.insert(points.begin(), points.end());

    int m;
    cin >> m;
    map<Face, K::FT> max_escape = precompute(t);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        Point start(x, y);
        long d;
        cin >> d;

        Point nearest = t.nearest_vertex(start)->point();

        // check if condition is already violated
        if (CGAL::squared_distance(start, nearest) < d)
        {
            cout << "n";
            continue;
        }

        // find the delauny face which `start` lies in
        Face fh = t.locate(start);

        if (4 * d <= max_escape[fh])
            cout << "y";
        else
            cout << "n";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        else
            run(n);
    }
}