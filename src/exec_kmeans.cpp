#include <limits>
#include <string>
#include <iostream>
#include <tclap/CmdLine.h>
#include "reader.h"
#include "kmeans.h"

using namespace std;
using namespace TCLAP;

int main(int argc, char **argv){
    
    string sFileName;
    string sCentroidFile;
    bool bHardClustering;
    bool bVerbose;
    bool bInteractive;
    unsigned int k;
    int iFuzzifier;
    int iMaxIteration;

    try {  
        CmdLine cmd("Command description message", ' ', "0.9");

        SwitchArg cmdHard("","hard","hardClustering",false);
        SwitchArg cmdVerbose("","verbose","verbose",false);
        SwitchArg cmdInteractive("","interactive","interactive",false);
        UnlabeledValueArg<string> cmdFile( "data","unlabeled test",true,"","csv file" );
        UnlabeledValueArg<unsigned int> cmdK( "cluster","number of cluster",true,3,"#cluster" );
        ValueArg<int> cmdMaxIteration("i", "iteration","maximal iteration",false,numeric_limits<int>::max(),"max iteration" );
        ValueArg<int> cmdFuzzifier("f", "fuzzifier","fuzzifier",false,3,"fuzzifier" );
        ValueArg<string> cmdCentroids("c", "centroids","",false,"","csv file centroids" );

        cmd.add(cmdFile);
        cmd.add(cmdK);
        cmd.add(cmdMaxIteration);
        cmd.add(cmdFuzzifier);
        cmd.add(cmdCentroids);
        cmd.add(cmdHard);
        cmd.add(cmdVerbose);
        cmd.add(cmdInteractive);

        cmd.parse(argc, argv);

        bHardClustering = cmdHard.getValue();
        bVerbose = cmdVerbose.getValue();
        bInteractive = cmdInteractive.getValue();
        k = cmdK.getValue();
        iFuzzifier = cmdFuzzifier.getValue();
        iMaxIteration = cmdMaxIteration.getValue();
        sFileName= cmdFile.getValue();
        sCentroidFile = cmdCentroids.getValue();

    } catch (TCLAP::ArgException &e) { 
        cerr << "error: " << e.error() << " for arg " << e.argId() << endl; 
    }

    CSVReader r;
    
    ndvector v = r.read(sFileName);
    ndvector centroids = (sCentroidFile != "") ? r.read(sCentroidFile) : ndvector();

    if (k > v.size()) {
        cerr << "ERROR: k has to be equal or lower than " << v.size() << endl;
        return EXIT_FAILURE;
    }
    
    kmeans c = kmeans(v,k,centroids);
    c.bHardClustering = bHardClustering;
    c.iMaxIteration = iMaxIteration;
    c.iFuzzifier = iFuzzifier;
        
    if (bInteractive or bVerbose) {
        int counter = 0;
        cout << "---------------- Initial Means -------------------" << endl;
        c.printMeans();
        cout << "--------------------------------------------------" << endl;
        bool bContinue = true;
        while (bContinue) {
            cout << "----------------------" << ++counter <<  "-------------------------" << endl;
            c.printPartitionMatrix();
            c.printMeans();
        bContinue = c.next();
        if (bInteractive) cin.ignore();
        }
    } else c.learn();

    c.printMeans();
    return EXIT_SUCCESS;

}







