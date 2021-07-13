#include "DTDPGAnalysis/DTMultiRunAnalysis/src/RunProvider.h"
#include "DTDPGAnalysis/DTMultiRunAnalysis/src/TH1FBuilder.h"
#include "DTDPGAnalysis/DTMultiRunAnalysis/src/GraphBuilder.h"

#include "DTDPGAnalysis/DTMultiRunAnalysis/src/BaseGetObs.h"
#include "DTDPGAnalysis/DTMultiRunAnalysis/src/GetRunObs.h"
#include "DTDPGAnalysis/DTMultiRunAnalysis/src/GetMeanObs.h"

#include<memory>
#include<vector>
#include<algorithm>
#include<iostream>

#include "TFile.h"

int main(int argc, char *argv[])
{

  // The TFile storing the analysis output
  auto t_file = std::make_shared<TFile>("averages_by_run.root","recreate");

  // Get links to the DTNtuple and DTSliceTestOfflineAnalyses
  // rootfiles for the listed runs
  std::vector<RunProvider> run_providers = {341758, 341795, 341891, 342088, 342094, 342189, 342218, 342221};

  // The list of TH1F to be created
  std::vector<TH1FBuilder> histos = {
    TH1FBuilder("avg_segments_vs_run_ph1", run_providers,                // Name of the TGraph and list of runs to be processed
		std::make_unique<GetRunObs>(RunProvider::tag::DUMMY,""), // x axis: GetRunObs retrieves the run number (DUMMY means
                                                                         //         information does not come from DTNtuple of from 
                                                                         //         DTSliceTestOfflineAnalyses)
		std::make_unique<GetMeanObs>(RunProvider::tag::SEGM,"Ph1nSegments") // y axis: GetMeanObs gets the average value out of a TH1F
                                                                                    //         (SEGM means that this information is retrieved
                                                                                    //         from the results of the segment analysis by
                                                                                    //         DTSliceTestOfflineAnalyses - Ph1nSegments is the
                                                                                    //         name of the plot to be retrieved)
		),
    TH1FBuilder("avg_segments_vs_run_ph2", run_providers,
		std::make_unique<GetRunObs>(RunProvider::tag::DUMMY,""),
		std::make_unique<GetMeanObs>(RunProvider::tag::SEGM,"Ph2nSegments")
		)
  };

  // Loop on all TH1F that were created to store them in the output TFile
  std::for_each(histos.begin(), histos.end(), 
                [& t_file](auto & histo){ histo.writeTH1FToFile(t_file,""); });

  // The list of TGraphs to be created
  std::vector<GraphBuilder> graphs = {
    GraphBuilder("avg_segments_ph1_vs_ph2", run_providers,
		 std::make_unique<GetMeanObs>(RunProvider::tag::SEGM,"Ph1nSegments"),
		 std::make_unique<GetMeanObs>(RunProvider::tag::SEGM,"Ph2nSegments")
		 )
  };

  // Loop on all TGraphs that were created to store them in the output TFile
  std::for_each(graphs.begin(), graphs.end(), 
                [& t_file](auto & graph){ graph.writeGraphToFile(t_file,""); });

  t_file->Close();

  return 0;

}
    
