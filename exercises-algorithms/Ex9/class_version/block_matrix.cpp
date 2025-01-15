#include <limits>
#include <iostream>

#include "block_matrix.hpp"

BlockMatrix::BlockMatrix(): Matrix (0, 0)
{}

bool
BlockMatrix::indexes_in_block (std::size_t i, std::size_t j, const Block & block) const
{
    return (i >= block.get_top_left_row()) && (i <= block.get_bottom_right_row())
           &&
           (j >= block.get_top_left_col()) && (j <= block.get_bottom_right_col());
}

double&
BlockMatrix::operator () (std::size_t i, std::size_t j)
{
    // if (i,j) inside a block, A(i,j)
    for (Block& block : blocks)
    {
        if (indexes_in_block(i,j,block))
        {
            std::size_t b_i = i - block.get_top_left_row();
            std::size_t b_j = j - block.get_top_left_col();
            return block(b_i, b_j);
        }
    }

    // else, add new block with one elem
    Block block(i,j,i,j, {0});
    add_block(block);
    return blocks.back()(0,0);
}

double
BlockMatrix::operator () (std::size_t i, std::size_t j) const
{
    double elem = 0.;

    // if (i,j) outside the matrix, error message
    if (i >= n_rows || j >= n_cols)
    {
        std::cerr << "idx out of range!" << std::endl;
        elem = std::numeric_limits<double>::quiet_NaN();
    }
    else {
        // if (i,j) outside a block, 0
        // else, A(i,j)
        for (const Block& block : blocks)
        {
            //if ((i >= block.get_top_left_row() && i <= block.get_bottom_right_row()) &&
            //    (j >= block.get_top_left_col() && j <= block.get_bottom_right_col()))
            if (indexes_in_block(i,j,block))
            {
                std::size_t b_i = i - block.get_top_left_row();
                std::size_t b_j = j - block.get_top_left_col();
                elem = block(b_i, b_j);
            }
        }
    }

    return elem;
}

void
BlockMatrix::add_block(const Block &block)
{
    blocks.push_back(block);

    n_rows = std::max(block.get_bottom_right_row() + 1, n_rows);
    n_cols = std::max(block.get_bottom_right_col() + 1, n_cols);
}
