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
    //bool bHardClustering;
    int k;

    try {  
        CmdLine cmd("Command description message", ' ', "0.9");

        //SwitchArg cmdHard("h","hard","Hard_",false);
        UnlabeledValueArg<string> cmdFile( "data","unlabeled test",true,"","csv file" );
        UnlabeledValueArg<int> cmdK( "cluster","number of cluster",true,3,"" );
        UnlabeledValueArg<string> cmdCentroids( "centroids","",false,"","csv file centroids" );

        //cmd.add(cmdHard);
        cmd.add(cmdFile);
        cmd.add(cmdK);
        cmd.add(cmdCentroids);

        cmd.parse(argc, argv);

        //bHardClustering = cmdHard.getValue();
        k = cmdK.getValue();
        sFileName= cmdFile.getValue();
        sCentroidFile = cmdCentroids.getValue();

    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }

    CSVReader r;
    
    ndvector v = r.read(sFileName);
    ndvector centroids = (sCentroidFile != "") ? r.read(sCentroidFile) : ndvector();

    kmeans c =kmeans(v,k);
    c.M = centroids;
    c.HARD_CLUSTERING = true;
    c.learn();
    c.print();
    return EXIT_SUCCESS;

}







