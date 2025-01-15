#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include <vector>

#include "Centroid.hpp"
#include "Point.hpp"

class Clustering
{
  typedef  std::vector<unsigned> f_labels_type ;
  typedef  std::vector<Centroid> centers_type;
  typedef std::vector<std::vector<Point *>> clusters_type;

  static constexpr double MAX_COORD=1000.0;

  std::vector<Point> points;
  f_labels_type labels; //label function
  unsigned p; //number of dimensions
  unsigned n; //number of points
  unsigned k; //number of clusters

  centers_type centers;
  clusters_type clusters;

  unsigned max_it; //maximum number of iterations

  unsigned
  min_dist_index (const Point& point) const; //returns the index of the centroid
                                                        //closest to point
  void
  print_labels (void) const;
  void
  print_centers (void) const;
  void
  print_clusters (void) const;

public:
  Clustering (unsigned dimensions, unsigned n_points,
              unsigned k_cluster, unsigned max_iterations);
  
  void
  print (void) const;
  void
  calc_cluster (void);
};

#endif /* CLUSTERING_H_ */
