#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include <string>
#include <vector>

#include "Centroid.hh"
#include "Point.hh"

class Clustering
{
  typedef std::vector<unsigned int> f_labels_type;
  typedef std::vector<Centroid> centers_type;
  typedef std::vector<std::vector<Point *>> clusters_type;
  typedef std::vector<Point> points_type;

  static constexpr double MAX_COORD = 1000.0;

  points_type points;
  f_labels_type labels; //label function
  unsigned int p; //number of dimensions
  unsigned int n; //number of points
  unsigned int k; //number of clusters

  unsigned int local_n;

  centers_type centers;
  clusters_type clusters;

  unsigned int max_it; //maximum number of iterations

  unsigned int
  min_dist_index (Point const & point) const; //returns the index of the centroid closest to point

public:
  Clustering (unsigned int dimensions, unsigned int n_points,
              unsigned int k_cluster, unsigned int max_iterations);

  std::string
  print (void) const;
  std::string
  print_labels (void) const;
  std::string
  print_centers (void) const;
  std::string
  print_clusters (void) const;
  unsigned
  calc_cluster (void);
};

#endif /* CLUSTERING_H_ */
