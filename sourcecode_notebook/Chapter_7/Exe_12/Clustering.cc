#include <iostream>
#include <random>
#include <sstream>

#include "Clustering.hh"
#include "MPI.hh"

Clustering::Clustering (unsigned int dimensions, unsigned int n_points,
                        unsigned int k_cluster, unsigned int max_iterations)
  : p (dimensions), n (n_points), k (k_cluster), max_it (max_iterations)
{
  const unsigned rank = mpi::rank (MPI_COMM_WORLD);
  const unsigned size = mpi::size (MPI_COMM_WORLD);

  MPI_Bcast (&p, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast (&k, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast (&max_it, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  local_n = n / size;
  if (rank < n % size) ++local_n;

  std::default_random_engine generator (rank * size * local_n);
  std::cerr << "Process " << mpi::rank (MPI_COMM_WORLD)
            << " value: " << generator () << std::endl;
  std::uniform_real_distribution<double> distribution (0.0, MAX_COORD);

  for (unsigned i = 0; i < local_n; ++i)
    {
      std::vector<double> coords (p);
      for (double & value : coords)
        {
          value = distribution (generator);
        }
      points.push_back (coords);
    }

  labels.assign (local_n, 0);
  centers.assign (k, std::vector<double> (p, 0.));
  clusters.assign (k, {nullptr});
}

std::string
Clustering::print (void) const
{
  std::ostringstream buffer;
  // Print points and labels
  for (std::size_t i = 0; i < points.size (); ++i)
    {
      buffer << points[i].print ();
      buffer << " : " << labels[i] << std::endl;
    }
  return buffer.str ();
}

unsigned
Clustering::calc_cluster (void)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<unsigned> distribution (0, k - 1);

  //Randomly initialize labels
  for (unsigned & label : labels)
    {
      label = distribution (generator);
    }

  // MPI is C, unfortunately
  int term_cond = false;
  unsigned i;

  for (i = 0; i < max_it and not term_cond; ++i)
    {
      f_labels_type old_labels (labels);
      clusters_type new_clusters (k);

      // update clusters according to the labels
      for (std::size_t j = 0; j < points.size (); ++j)
        {
          new_clusters[labels[j]].push_back (&points[j]);
        }
      clusters.swap (new_clusters);

      // update centroids
      for (std::size_t j = 0; j < centers.size (); ++j)
        {
          centers[j].update_coords (clusters[j]);
        }

      // assign points to new centroids
      for (std::size_t j = 0; j < points.size (); ++j)
        {
          const unsigned int min_dist_idx = min_dist_index (points[j]);
          labels[j] = min_dist_idx;
        }

      term_cond = (old_labels == labels);
      MPI_Allreduce (MPI_IN_PLACE, &term_cond, 1,
                     MPI_INT, MPI_LAND, MPI_COMM_WORLD);
    }

  return i;
}

unsigned int
Clustering::min_dist_index (const Point & point) const
{
  int min_dist_ind = 0;
  double min_dist = point.distance (centers[0]);

  for (centers_type::size_type i = 1; i < centers.size (); ++i)
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

std::string
Clustering::print_labels (void) const
{
  std::ostringstream buffer;
  auto it = labels.cbegin ();
  if (it != labels.cend ())
    {
      buffer << *it++;
    }
  while (it != labels.cend ())
    {
      buffer << " " << *it++;
    }
  buffer << std::endl;
  return buffer.str ();
}

std::string
Clustering::print_centers (void) const
{
  std::ostringstream buffer;
  buffer << "Centers size: " << centers.size () << std::endl;
  for (Centroid const& c: centers)
    {
      buffer << c.print ();
    }
  return buffer.str ();
}

std::string
Clustering::print_clusters (void) const
{
  std::ostringstream buffer;
  for (unsigned i = 0; i < k; ++i)
    {
      buffer << "Cluster: " << i << std::endl;
      for (Point* c: clusters[i])
        {
          buffer << c -> print () << std::endl;
        }
    }
  return buffer.str ();
}
