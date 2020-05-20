//submit this file ONLY
//if you need to write your own helper functions, write the functions in this file
//again, do NOT include additional libraries and make sure this todo.cpp can be compiled with the unmodified versions of the other given files in our official compilation environment

#include "todo.h"
using namespace std;

string filetype = ".csv";

char* substring(char* source, int startIndex, int endIndex)
{
    int size = endIndex - startIndex + 1;
    char* s = new char[size+1];
    strncpy(s, source + startIndex, size); //you can read the documentation of strncpy online
    s[size]  = '\0'; //make it null-terminated
    return s;
}

//******** IMPLEMENTATION OF DayStat *******

DayStat::DayStat(){
    cases = 0;
    deaths = 0;
}

DayStat::DayStat(int _cases, int _deaths){
    cases = _cases;
    deaths = _deaths;
}

DayStat::DayStat(const DayStat &d, double denominator){
// d: another DayStat that stores the raw data.
// denominator: It should be area or population.
    cases = d.cases/denominator;
    deaths = d.deaths/denominator;
}

double DayStat::mortalityRate() const {
// retured value: mortality (percentage of cases that resulted in death).
    if (getcases() != 0)
    {
        double mortality = deaths/cases;
        return mortality;
    }
    else
        return 0;
}

double DayStat::getcases() const {
// retured value: cases.
    return cases;
}

double DayStat::getdeaths() const {
// retured value: deaths
    return deaths;
}

//******** IMPLEMENTATION OF Region *******
Region::Region(){
}

void Region::readline(char *line){
// line: char array. A single line read from the csv file.
    int commaCount = 0;
    int curcases = 0;
    int curdeaths = 0;
    int lastCommaP = 0;
    char* substr;
    char* lsubstr;
    int dayCount = 0;
    raw = new DayStat[1024];
    for (int i = 0; line[i] ; i++)
    {
        
        if (line[i] == ',')
        {
            commaCount += 1;
            char * substr = substring(line,lastCommaP + 1,i-1);
            if (commaCount == 1)
            {
                substr = substring(line,lastCommaP,i-1);
                name = substr;
                //cout << substr << endl;
            }
            else if (commaCount == 2)
            {
                population = atoi(substr);
            }
            else if (commaCount == 3)
            {
                area = atoi(substr);
            }
            else if (commaCount >= 4 && commaCount % 2 != 0)
            {
                //cout << lsubstr << " "<< substr << endl;
                //cout << dayCount << " " << atoi(lsubstr) << " " <<  atoi(substr) << endl;
                raw[dayCount] = DayStat(atoi(lsubstr), atoi(substr));
                dayCount += 1;
            }
            else{}
            lastCommaP = i;
            lsubstr = substr;
        }
        else{}
    }
    nday = dayCount + 1;
    //cout << name << " " << population << " " << area << " " << nday << endl;
}

Region::~Region(){
}

void Region::normalizeByPopulation(){
    normPop = new DayStat[nday];
    for (int i = 0; i < nday; i++)
        normPop[i] = DayStat(raw[i], population);
}

void Region::normalizeByArea(){
    normArea = new DayStat[nday];
    for (int i = 0; i < nday; i++)
        normArea[i] = DayStat(raw[i], area);
}

void Region::computeMortalityRate(){
    mortality = new double[nday];
    for (int i = 0; i < nday; i++)
    {
        mortality[i] = raw[i].mortalityRate();
    }
}

void initialCSV (string name){
    ifstream ifs(name + filetype);
    if (ifs)
    {
        remove((name + filetype).c_str());
    }
    else{}
    ifs.close();
}

void Region::write(Stat stat) const {
// stat: one element of the Enum Stat and indicates which kind of data need to be stored in csv files. See definition of Stat. As you need to generate 7 csv files, this function will be called 7 times for each region in writecsvs().
    //ofs.setf(ios::fixed);
    //ofs.precision();
    if (stat == CASESRAW) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"CASESRAW.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision(0);
            ofs << name;
            for (int i = 0; i < nday; i++)
            {
                ofs << "," << raw[i].getcases();
            }
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed);
            ofs.precision(0);
            ofs << name;
            for (int i = 0; i < nday; i++)
            {
                ofs << "," << raw[i].getcases();
            }
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == DEATHSRAW) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"DEATHSRAW.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision(0);
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << raw[i].getdeaths();
            ofs << endl; ofs.close();
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed);
            ofs.precision(0);
            ofs << name;
            for (int i = 0; i < nday; i++)
            {
                ofs << "," << raw[i].getdeaths();
            }
            ofs << endl;
            ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == CASESPOP) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"CASESPOP.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normPop[i].getcases();
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normPop[i].getcases();
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == DEATHSPOP) ////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"DEATHSPOP.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normPop[i].getdeaths();
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normPop[i].getdeaths();
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == CASESAREA) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"CASESAREA.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normArea[i].getcases();
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normArea[i].getcases();
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == DEATHSAREA) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"DEATHSAREA.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normArea[i].getdeaths();
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << normArea[i].getdeaths();
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else if (stat == MORTALITY) /////////////////////////////////////////////////////////////
    {
        char* status = new char[16];
        strcpy(status,"MORTALITY.csv" );
        ifstream ifs(status);
        if (!ifs)
        {
            ofstream ofs(status);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << mortality[i];
            ofs << endl; ofs.close();  
        }
        else
        {
            ofstream ofs(status, fstream::app);
            ofs.setf(ios::fixed); ofs.precision();
            ofs << name;
            for (int i = 0; i < nday; i++)
                ofs << "," << mortality[i];
            ofs << endl; ofs.close();
        }
        ifs.close();
        delete [] status;
    }
    else{}
}

//******** IMPLEMENTATION OF FILE I/O FUNCTIONS *******

int readcsv(Region*& region, const char* csvFileName){
//  region: an array of Region. Each element stores the information of one country (or region).
//  csvFileName: path to the csv file.
//  retured value: the length of the region array.

//  1. Load the CSV file
    ifstream ifs(csvFileName);
    if (!ifs)
        return -1;

    int csvLineCount = 0;
    char line[2048];
    while (ifs.getline(line,2048)){
        csvLineCount++;
    }

//  2. Allocate for an array of region;
    ifs.clear();
    ifs.seekg(0, ios::beg);
    region = new Region[csvLineCount];
//  3. for each line in CSV filr: readline;
    for (int i = 0; i < csvLineCount ; i++)
    {
        ifs.getline(line,2048);
        if (i == 0)
            continue;
        region[i - 1].readline(line);
        
    }
    ifs.close();
    return csvLineCount - 1;
}

void writecsvs(const Region* region, int nRegions){
//  region: an array of Region. Each element stores the information of one country (or region).
//  nRegions: the length of the region array.

    //Initialize the folder, delete all existing file:

    initialCSV("CASESRAW");
    initialCSV("DEATHSRAW");
    initialCSV("CASESPOP");
    initialCSV("DEATHSPOP");
    initialCSV("CASESAREA");
    initialCSV("DEATHSAREA");
    initialCSV("MORTALITY");

    // Writer CSV files
    for (int i = 0; i < nRegions; i++){
        region[i].write(CASESRAW);
    }
    for (int i = 0; i < nRegions; i++)
        region[i].write(DEATHSRAW);
    for (int i = 0; i < nRegions; i++)
        region[i].write(CASESPOP);
    for (int i = 0; i < nRegions; i++)
        region[i].write(DEATHSPOP);
    for (int i = 0; i < nRegions; i++)
        region[i].write(CASESAREA);
    for (int i = 0; i < nRegions; i++)
        region[i].write(DEATHSAREA);
    for (int i = 0; i < nRegions; i++)
        region[i].write(MORTALITY);
}
