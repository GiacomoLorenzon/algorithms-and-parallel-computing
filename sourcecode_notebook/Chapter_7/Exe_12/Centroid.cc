#include <mpi.h>

#include "Centroid.hh"

void
Centroid::update_coords (std::vector<Point *> const & points)
{
  std::vector<double> new_coords (x.size (), 0);

  for (std::vector<Point *>::size_type i = 0; i < points.size (); ++i)
    {
      for (size_type j = 0; j < x.size (); ++j)
        {
          new_coords[j] += points[i] -> get_coord (j);
        }
    }

  MPI_Allreduce (MPI_IN_PLACE, new_coords.data (), new_coords.size (),
                 MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  unsigned cluster_size = points.size ();
  MPI_Allreduce (MPI_IN_PLACE, &cluster_size, 1,
                 MPI_UNSIGNED, MPI_SUM, MPI_COMM_WORLD);

  for (double & coord: new_coords)
    {
      coord /= cluster_size;
    }

  x.swap (new_coords);
}
