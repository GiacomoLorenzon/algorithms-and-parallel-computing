#include <limits>
#include <iostream>

#include "block_matrix.hpp"

BlockMatrix::BlockMatrix()
  : Matrix (0, 0) {}

bool BlockMatrix::indexes_in_range (std::size_t i, std::size_t j) const
{
  return (i < n_rows) && (j < n_cols);
}

bool BlockMatrix::indexes_in_block (std::size_t i, std::size_t j,
                                    const Block & block) const
{
  return (i >= block.get_top_left_row()) && (i <= block.get_bottom_right_row()) &&
    (j >= block.get_top_left_col()) && (j <= block.get_bottom_right_col());
}

double BlockMatrix::operator()(std::size_t i, std::size_t j) const
{
   if (!indexes_in_range (i, j))
   {
      std::cerr << "indexes out of range!" << std::endl;
      return std::numeric_limits<double>::quiet_NaN();
   }
   for (const Block & block : blocks)
   {
      // if i, j in block coordinates
      if (indexes_in_block (i, j, block))
         // access proper indexes element and return
         return block(i - block.get_top_left_row(), j - block.get_top_left_col());
   }

   return 0;
}

double & BlockMatrix::operator() (std::size_t i, std::size_t j)
{
   for (Block & block : blocks)
   {
      // if i, j in block coordinates
      if (indexes_in_block (i, j, block))
      {
         // change proper indexes element and return
         return block(i - block.get_top_left_row(), j - block.get_top_left_col());
      }
   }
   // Create a single element block
   Block block (i, j, i, j, {0});
   add_block (block);
   return blocks.back()(0, 0);
}

void BlockMatrix::add_block (const Block & block)
{
   blocks.push_back (block);
   // Update matrix size
   n_rows = std::max (n_rows, block.get_bottom_right_row() + 1);
   n_cols = std::max (n_cols, block.get_bottom_right_col() + 1);
}
