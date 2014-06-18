#include <fstream>
#include <boost/tokenizer.hpp>
#include "reader.h"


using namespace std;


ndvector CSVReader::read(string sFileName) {

    ndvector v;
    ifstream in(sFileName.c_str());
    if (!in.is_open()) return v;
    
    typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
    vector<string> vec;
    string line;

    while (getline(in,line))
    {
        vector<double> dLine;
        Tokenizer tok(line);
        for(Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
            double d = atof(it->c_str());
            dLine.push_back(d);
        }
        v.push_back(dLine);
    }

    return v;

}
