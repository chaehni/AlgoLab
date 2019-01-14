#include <iostream>
#include <vector>
#include <map>
#include <queue>

// CGAL includes
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator EdgeIt;
typedef Triangulation::All_faces_iterator FaceIt;
typedef Triangulation::Face_handle Face;
typedef K::Point_2 Point;

using namespace std;

void precompute(Triangulation &t)
{

    // for all faces update their info with the max balloon size that can start them and add faces to the queue
    priority_queue<pair<K::FT, Face>> q;
    for (FaceIt eit = t.all_faces_begin(); eit != t.all_faces_end(); ++eit)
    {
        if (t.is_infinite(eit))
        {
            q.push(make_pair(INT64_MAX, eit));
            eit->info() = INT64_MAX;
        }
        else
        {
            Point v = t.dual(eit);
            K::FT dist = CGAL::squared_distance(v, eit->vertex(0)->point());
            q.push(make_pair(dist, eit));
            eit->info() = dist;
        }
    }

    while (!q.empty())
    {
        Face curr_f = q.top().second;
        K::FT clearance = q.top().first;
        q.pop();

        if (clearance < curr_f->info())
            continue;

        // update all neighbours
        for (int i = 0; i < 3; i++)
        {
            Face nb = curr_f->neighbor(i);
            K::FT edge_length = t.segment(curr_f, i).squared_length();
            K::FT new_clearance = min(curr_f->info(), edge_length);
            if (nb->info() < new_clearance)
            {
                q.push(make_pair(new_clearance, nb));
                nb->info() = new_clearance;
            }
        }
    }
}

void run()
{
    int n, m;
    long r;
    cin >> n >> m >> r;

    Triangulation t;

    vector<Triangulation::Point> points(n);
    for (int i = 0; i < n; i++)
    {
        long x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }

    // create triangulation
    t.insert(points.begin(), points.end());

    precompute(t);

    // test balloons
    vector<bool> success(m, true);
    for (int i = 0; i < m; i++)
    {

        // read balloon center
        long x, y;
        cin >> x >> y;
        Point b(x, y);

        // read balloon radius
        long s;
        cin >> s;

        K::FT radii = r + s;

        // see if ballon can be inflated
        Point nearest = t.nearest_vertex(b)->point();
        if (CGAL::squared_distance(nearest, b) < radii * radii)
        {
            cout << "n";
            continue;
        }

        // locate balloon and check against max lift off value for the triangle it lies in
        Face f = t.locate(b);
        if (f->info() < CGAL::square(2 * radii))
            cout << "n";
        else
            cout << "y";
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