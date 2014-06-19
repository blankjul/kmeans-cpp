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
    int k;
    int iMaxIteration;

    try {  
        CmdLine cmd("Command description message", ' ', "0.9");

        SwitchArg cmdHard("","hard","hardClustering",false);
        SwitchArg cmdVerbose("","verbose","verbose",false);
        SwitchArg cmdInteractive("","interactive","interactive",false);
        UnlabeledValueArg<string> cmdFile( "data","unlabeled test",true,"","csv file" );
        UnlabeledValueArg<int> cmdK( "cluster","number of cluster",true,3,"" );
        ValueArg<int> cmdMaxIteration("i", "iteration","maximal iteration",false,numeric_limits<int>::max(),"" );
        UnlabeledValueArg<string> cmdCentroids( "centroids","",false,"","csv file centroids" );

        cmd.add(cmdFile);
        cmd.add(cmdK);
        cmd.add(cmdMaxIteration);
        cmd.add(cmdCentroids);
        cmd.add(cmdHard);
        cmd.add(cmdVerbose);
        cmd.add(cmdInteractive);

        cmd.parse(argc, argv);

        bHardClustering = cmdHard.getValue();
        bVerbose = cmdVerbose.getValue();
        bInteractive = cmdInteractive.getValue();
        k = cmdK.getValue();
        iMaxIteration = cmdMaxIteration.getValue();
        sFileName= cmdFile.getValue();
        sCentroidFile = cmdCentroids.getValue();

    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }

    CSVReader r;
    
    ndvector v = r.read(sFileName);
    ndvector centroids = (sCentroidFile != "") ? r.read(sCentroidFile) : ndvector();

    kmeans c = kmeans(v,k,centroids);
    c.HARD_CLUSTERING = bHardClustering;
    c.MAX_ITERATION = iMaxIteration;
    
    if (bInteractive) {
        bool bContinue = true;
        while (bContinue) {
            c.print();
        bContinue = c.next();
        cin.ignore();
        }
    } else c.learn();

    if (bVerbose) c.print();
    else c.print(false,true);

    return EXIT_SUCCESS;

}







