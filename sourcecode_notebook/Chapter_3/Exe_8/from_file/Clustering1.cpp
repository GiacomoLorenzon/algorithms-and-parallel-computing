#include <iostream>
#include <random>

#include "Clustering1.hpp"

Clustering::Clustering (unsigned dimensions, unsigned n_points,
                        unsigned k_cluster, unsigned max_iterations, const std::string &nomefile)
  : p (dimensions), n (n_points), k (k_cluster), max_it (max_iterations), name(nomefile)
{
  if(!checkfile()) std::cerr << "Try to check if the file is correct" << std::endl;

  std::vector<Point *> all_pointers_points;

  points = readfile();

  for (unsigned i = 0; i < n; ++i)
    {
      labels.push_back (0); // assign every point to class 0
      all_pointers_points.push_back(& points[i]);  // store current point address
    }
    
  // Assign all points to cluster 0
  //clusters.push_back(all_pointers_points);  

  std::vector<double> origin (p, 0);

  // Create and intialize centroids to origin
  for (unsigned i = 0; i < k; ++i)
    centers.push_back (origin);

  // Create and initialize clusters to nulls
  for (unsigned i = 0; i < k; ++i)
    clusters.push_back ({nullptr});
}

//checkfile function
bool Clustering::checkfile (void) const
{
  int n_points(n);
  bool is_correct = true;
  std::ifstream ist(name);
  if (!ist)
  {
    std::cerr << "Problem with file opening" << std::endl;
    is_correct = false;
  }
 
  {//new block
    std::string aux; 
    int i(0); 
    std::string number;                     
    while(getline(ist,aux))
    {  
      ++i;
      int j = 0; 
      std::istringstream temp(aux); // I want to read the single line
      while(temp >> number)      // I count the distinct entries on a line
        ++j;
      if (j != p) 
        std::cerr << "Wrong dimension on a line" << std::endl;
    }
    
    if (i != n_points)
    {
      std::cerr << "The file contains too many or too few elements" << std::endl;
      is_correct = false;
    }
  }
  return is_correct;
}

//Readfile function
std::vector<Point> Clustering::readfile (void) const
{
  std::ifstream ist(name);
  std::vector<Point> ret;
  double val;

  for(int i=0; i<n; i++) 
  {
    std::vector<double> coords;
    for(int i=0; i<p; i++)
    { 
      ist >> val;
      coords.push_back(val);
    }
  Point P(coords);
  ret.push_back(P);
  }
  return ret;
}

void
Clustering::print (void) const
{
  // Print points and labels
  for (std::size_t i = 0; i < points.size (); ++i)
    {
      points[i].print ();
      std::cout << " : ";
      std::cout << labels[i];
      std::cout << std::endl;
    }
}

void
Clustering::calc_cluster (void)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution (0, k - 1);

  //Randomly initialize labels
  for (auto it = labels.begin (); it != labels.end (); ++it)
    *it = distribution (generator);

  bool term_cond = false;
  unsigned i;

  for (i = 0; i < max_it && ! term_cond; ++i)
    {
      f_labels_type old_labels (labels);

      clusters_type new_clusters (k);

      // update clusters according to new labels
      for (std::size_t j = 0; j < points.size (); ++j)
        new_clusters[labels[j]].push_back (&points[j]);

      clusters.swap (new_clusters);

      // update centroids
      for (std::size_t j = 0; j < centers.size (); ++j)
        centers[j].update_coords (clusters[j]);

      // assign points to new centroids
      for (std::size_t j = 0; j < points.size (); ++j)
        {
          const unsigned min_dist_ind = min_dist_index (points[j]);
          labels[j] = min_dist_ind;
        }

      term_cond = (old_labels == labels);
    }
        
  std::cout << "Number of iterations: " << i << std::endl;
  std::cout << "Final result!" << std::endl;
  print_labels ();
  std::cout << std::endl;
}

unsigned
Clustering::min_dist_index (const Point & point) const
{
  int min_dist_ind = 0;
  double min_dist = point.distance (centers[0]);

  for (std::size_t i = 1; i < centers.size (); ++i)
    {
      const double dist = point.distance (centers[i]);
      if (dist < min_dist)
        {
          min_dist = dist;
          min_dist_ind = i;
        }
    }

  return min_dist_ind;
}

void
Clustering::print_labels (void) const
{
  for (auto it = labels.begin (); it != labels.end (); ++it)
    {
      std::cout << *it << " ";
    }
}

void
Clustering::print_centers (void) const
{
  std::cout << "Centers size: ";
  std::cout << centers.size ();
  std::cout << std::endl;

  for (std::size_t i = 0; i < centers.size (); ++i)
    centers[i].print ();
}

void
Clustering::print_clusters (void) const
{
  for (unsigned i = 0; i < k; ++i)
    {
      std::cout << "Cluster: " <<  i << std::endl;
      for (Point* c: clusters[i])
        {
          c -> print ();
          std::cout << std::endl;
        }
    }
}
