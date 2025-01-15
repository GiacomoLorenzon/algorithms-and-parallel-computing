#include <iostream>
#include <sstream>
#include <string>
#include <mpi.h>

int main (int argc, char *argv[]) {

    MPI_Init(&argc,&argv);
    
    int rank, size;
    
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    std::ostringstream builder;
    builder << "Hello, world, from " << rank << " of " << size;
    
    std::string message(builder.str());
    unsigned length = message.size();
    
    if (rank > 0) 
        {
        MPI_Send (&length,1,MPI_UNSIGNED,0,0,MPI_COMM_WORLD);
        MPI_Send (&message[0],length,MPI_CHAR,0,1,MPI_COMM_WORLD);
        }
    else
        {
        std::cout << message << std::endl;  
        for (int r=1; r<size; r++)
            {
            MPI_Recv (&length,1,MPI_UNSIGNED,r,0,MPI_COMM_WORLD,
                                                       MPI_STATUS_IGNORE);
            message.resize(length);
            MPI_Recv (&message[0],length,MPI_CHAR,r,1,MPI_COMM_WORLD,
                                                       MPI_STATUS_IGNORE);
            std::cout << message << std::endl;
            }
        }
    
    MPI_Finalize(); 
    
    return 0;     

}
