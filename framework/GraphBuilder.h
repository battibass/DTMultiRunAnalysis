#ifndef DTMultiRunAnalysis_GraphBuilder_h
#define DTMultiRunAnalysis_GraphBuilder_h

/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include<memory>
#include<string>

#include"TFile.h"
#include"TGraphErrors.h"

#include"RunProvider.h"
#include"GetBaseObs.h"

class GraphBuilder
{

 public:

  /// Constructor, gets as input:
  /// - the name of the TGraph to be created to store results
  /// - the list of RunProviders (i.e. the runs) to be processed
  /// - the GetBaseObs (i.e. the functions used to gather information 
  ///   from existing plots) that define the x and y axes of the graph
  /// ** Upon construction the graph is created and filled **

  GraphBuilder(std::string name,
	       std::vector<RunProvider> & run_providers,
	       std::unique_ptr<GetBaseObs> x,
	       std::unique_ptr<GetBaseObs> y);

  /// Destructor

  ~GraphBuilder() {};
  
  /// Writes the TGraph that was built at construction
  /// stage into a root TFile

  writeGraphToFile(std::shared_ptr<TFile> t_file, std::string folder);

 private:

  std::unique_ptr<TGraphErrors> m_graph;

};

#endif
