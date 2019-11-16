#include <iostream>
#include <vector>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Fh;
typedef K::Point_2 Point;

using namespace std;

void run(int n)
{
    vector<Point> infected(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        infected[i] = Point(x, y);
    }

    Triangulation t;
    t.insert(infected.begin(), infected.end());

    // Calculate for every face the max squared diameter of a disk that can escape and store it in the face info field
    // use a priority queue to always go from faces with biggest to faces with smallest escape values
    priority_queue<pair<K::FT, Fh>> q;

    // start with infinite faces and give them an escape value of infinity, and put them in queue
    for (auto fit = t.all_faces_begin(); fit != t.all_faces_end(); fit++)
    {
        if (t.is_infinite(fit))
        {
            fit->info() = INT64_MAX;
            q.emplace(INT64_MAX, fit);
        }
        else
        {
            fit->info() = 0;
        }
    }

    while (!q.empty())
    {
        Fh cur = q.top().second;
        q.pop();

        // update the three neighbours
        for (int i = 0; i < 3; i++)
        {
            Fh neighbor = cur->neighbor(i);
            K::FT dist = t.segment(cur, i).squared_length();
            K::FT max_val = max(neighbor->info(), min(cur->info(), dist));
            if (neighbor->info() < max_val)
            {
                neighbor->info() = max_val;
                q.emplace(neighbor->info(), neighbor);
            }
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long d;
        cin >> x >> y >> d;

        K::FT radius = d;

        Point person = Point(x, y);

        // is person already too close?
        if (CGAL::squared_distance(t.nearest_vertex(person)->point(), person) < radius)
        {
            cout << "n";
            continue;
        }

        // get face person is in
        Fh f = t.locate(person);
        if (f->info() >= 4 * radius)
            cout << "y";
        else
            cout << "n";
    }
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
