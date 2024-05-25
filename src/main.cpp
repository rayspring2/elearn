#include "System.hpp"
#include "io.hpp"

int main(int argc , char* argv[]){
    //ifstream outfile("out.txt");
    // cout.rdbuf(outfile.rdbuf());
    IO elearn(argv);
    elearn.run();
}