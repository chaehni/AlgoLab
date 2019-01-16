#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 Point;
typedef Triangulation::Face_handle Face;

using namespace std;

void precompute(Triangulation &t)
{

    // for every face precompute the maximal distance for which one can still escape
    // start with biggest values (infinite faces) and update all neighbours until nothing changes anymore
    priority_queue<pair<K::FT, Face>> q;

    for (auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it)
    {
        if (t.is_infinite(it))
        {
            it->info() = INT64_MAX;
            q.push(make_pair(INT64_MAX, it));
        }
        else
        {
            it->info() = -1;
            q.push(make_pair(0, it));
        }
    }

    while (!q.empty())
    {
        Face curr_f = q.top().second;
        K::FT escape_val = q.top().first;
        q.pop();

        if (escape_val < curr_f->info())
            continue;

        // update all neighbours
        for (int i = 0; i < 3; i++)
        {
            Face nb = curr_f->neighbor(i);
            K::FT edge_length = t.segment(curr_f, i).squared_length();
            K::FT new_val = min(curr_f->info(), edge_length);
            if (nb->info() < new_val)
            {
                q.push(make_pair(new_val, nb));
                nb->info() = new_val;
            }
        }
    }
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
    precompute(t);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        Point start(x, y);
        long d_in;
        cin >> d_in;
        K::FT d = d_in;

        Point nearest = t.nearest_vertex(start)->point();

        // check if condition is already violated
        if (CGAL::squared_distance(start, nearest) < d)
        {
            cout << "n";
            continue;
        }

        // find the delauny face which `start` lies in
        Face fh = t.locate(start);
        if (4 * d <= fh->info())
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