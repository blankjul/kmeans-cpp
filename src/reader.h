#include <vector>
#include <string>

typedef std::vector< std::vector<double> > ndvector;	

class CSVReader {
public:

    ndvector read(std::string sFileName);

};


