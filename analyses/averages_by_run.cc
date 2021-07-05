#include "../framework/RunProvider.h"
#include "../framework/GraphBuilder.h"

#include "../framework/BaseGetObs.h"
#include "../framework/GetRunObs.h"
#include "../framework/GetMeanObs.h"

#include<memory>
#include<vector>
#include<algorithm>

#include "TFile.h"

int main()
{

  // The TFile storing the analysis output
  auto t_file = std::make_shared<TFile>("averages_by_run.root","recreate");

  // Get links to the DTNtuple and DTSliceTestOfflineAnalyses
  // rootfiles for the listed runs
  std::vector<RunProvider> run_providers = {342189, 342218, 342221};

  // The list of TGraphs to be created
  std::vector<GraphBuilder> graphs = {
    GraphBuilder("avg_segments_vs_run_ph1", run_providers,                        // Name of the TGraph and list of runs to be processed
		 std::make_unique<BaseGetObs>(GetRunObs(RunProvider::DUMMY,"")),              // x axis: GetRunObs retrieves the run number (DUMMY means
                                                                                  //         information does not come from DTNtuple of from 
                                                                                  //         DTSliceTestOfflineAnalyses)
		 std::make_unique<BaseGetObs>(GetMeanObs(RunProvider::SEGM,"Ph1nSegments"))   // y axis: GetMeanObs gets the average value out of a TH1F
                                                                                  //         (SEGM means that this information is retrieved
                                                                                  //         from the results of the segment analysis by
                                                                                  //         DTSliceTestOfflineAnalyses - Ph1nSegments is the
                                                                                  //         name of the plot to be retrieved)
		 ),
    GraphBuilder("avg_segments_vs_run_ph2", run_providers,
		 std::make_unique<BaseGetObs>(GetRunObs(RunProvider::DUMMY,"")),
		 std::make_unique<BaseGetObs>(GetMeanObs(RunProvider::SEGM,"Ph1nSegments"))
		 )
  };

  // Loop on all TGraphs that were created to store them in the output TFile
  std::for_each(graphs.begin(), graphs.end(), 
                [auto & t_file](auto & graph){ graph.writeGraphToFile(t_file,""); });

  t_file->Close();

  return 0;

}
    
