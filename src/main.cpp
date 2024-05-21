#include "System.hpp"

#define MAJORSPATH argv[1]
#define COURSESPATH argv[2]
#define PROFESSORPATH argv[3]
#define STUDENTPATH argv[4]

int main(int argc , char* argv[]){
    System elearn;
    ifstream majors_file(MAJORSPATH);
    ifstream courses_file(COURSESPATH);
    ifstream professors_file(PROFESSORPATH);
    ifstream students_file(STUDENTPATH);
    string x;
    getline( majors_file , x );
    elearn.readData( majors_file, courses_file, professors_file, students_file);
    elearn.run();
}