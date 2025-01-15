#ifndef BLOCKMATRIX_H_
#define BLOCKMATRIX_H_

#include <vector>

#include "block.hpp"

class BlockMatrix: public Matrix
{
    private:
        std::vector<Block> blocks;

        bool indexes_in_block (std::size_t i, std::size_t j, const Block & block) const;

    public:
        BlockMatrix();

        void add_block (const Block& block);

        virtual double& operator () (std::size_t i, std::size_t j) override;

        virtual double  operator () (std::size_t i, std::size_t j) const override;

        virtual ~BlockMatrix() = default;
};

#endif /* BLOCKMATRIX_H_ */
