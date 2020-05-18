//submit this file ONLY
//if you need to write your own helper functions, write the functions in this file
//again, do NOT include additional libraries and make sure this todo.cpp can be compiled with the unmodified versions of the other given files in our official compilation environment

#include "todo.h"
using namespace std;

//******** IMPLEMENTATION OF DayStat *******

DayStat::DayStat(){
}

DayStat::DayStat(int _cases, int _deaths){
    cases = _cases;
    deaths = _deaths;
}

DayStat::DayStat(const DayStat &d, double denominator){
// d: another DayStat that stores the raw data.
// denominator: It should be area or population.
}

double DayStat::mortalityRate() const {
// retured value: mortality (percentage of cases that resulted in death).
}

double DayStat::getcases() const {
// retured value: cases.
}

double DayStat::getdeaths() const {
// retured value: deaths
}

//******** IMPLEMENTATION OF Region *******
Region::Region(){
}

void Region::readline(char *line){
// line: char array. A single line read from the csv file.
}

Region::~Region(){
}

void Region::normalizeByPopulation(){
}

void Region::normalizeByArea(){
}

void Region::computeMortalityRate(){
}

void Region::write(Stat stat) const {
// stat: one element of the Enum Stat and indicates which kind of data need to be stored in csv files. See definition of Stat. As you need to generate 7 csv files, this function will be called 7 times for each region in writecsvs().
}

//******** IMPLEMENTATION OF FILE I/O FUNCTIONS *******

int readcsv(Region*& region, const char* csvFileName){
//  region: an array of Region. Each element stores the information of one country (or region).
//  csvFileName: path to the csv file.
//  retured value: the length of the region array.

//  1. Load the CSV file
    ifstream ifs(csvFileName);
    if (!ifs)
    {
        return -1;
    }
    int csvLineCount = 0;
    char line[2048];
    while (ifs.getline(line,2048))
    {
        csvLineCount++;
    }
//  2. Allocate for an array of region;
    char **lines = new char*[csvLineCount];
    ifs.clear();
    ifs.seekg(0, ios::beg);
//  3. for each line in CSV filr: readline;
    for (int i = 0; i < csvLineCount; i++)
    {
        ifs.getline(line,2048);
        lines[i] = new char[strlen(line)+1];
        strcpy(lines[i],line);
    }
    ifs.close();

    return csvLineCount;
}

void writecsvs(const Region* region, int nRegions){
//  region: an array of Region. Each element stores the information of one country (or region).
//  nRegions: the length of the region array.
}
