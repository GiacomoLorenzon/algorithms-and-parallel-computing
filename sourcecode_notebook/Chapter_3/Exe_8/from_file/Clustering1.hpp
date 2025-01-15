#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include <vector>
#include <fstream>
#include <sstream>

#include "Centroid.hpp"
#include "Point.hpp"

class Clustering
{
  typedef  std::vector<unsigned int> f_labels_type ;
  typedef  std::vector<Centroid> centers_type;
  typedef std::vector<std::vector<Point *>> clusters_type;

  static constexpr double MAX_COORD=1000.0;

  std::vector<Point> points;
  f_labels_type labels; //label function
  unsigned int p; //number of dimensions
  unsigned int n; //number of points
  unsigned int k; //number of clusters

  centers_type centers;
  clusters_type clusters;

  unsigned int max_it; //maximum number of iterations

  unsigned int
  min_dist_index (Point const & point) const; //returns the index of the centroid
                                                        //closest to point
  void
  print_labels (void) const;
  void
  print_centers (void) const;
  void
  print_clusters (void) const;
  
  std::string name;

public:
  Clustering (unsigned int dimensions, unsigned int n_points,
              unsigned int k_cluster, unsigned int max_iterations, const std::string &nomefile);
  
  void
  print (void) const;
  void
  calc_cluster (void);
  
  bool checkfile (void) const;
  std::vector<Point> readfile (void) const;
  
};

#endif /* CLUSTERING_H_ */
