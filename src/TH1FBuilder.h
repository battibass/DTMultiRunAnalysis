#ifndef DTMultiRunAnalysis_TH1FBuilder_h
#define DTMultiRunAnalysis_TH1FBuilder_h

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
#include"TH1F.h"

#include"DTDPGAnalysis/DTMultiRunAnalysis/src/RunProvider.h"
#include"DTDPGAnalysis/DTMultiRunAnalysis/src/BaseGetObs.h"

class TH1FBuilder
{

 public:

  /// Constructor, gets as input:
  /// - the name of the TH1F to be created to store results
  /// - the list of RunProviders (i.e. the runs) to be processed
  /// - the GetBaseObs (i.e. the functions used to gather information 
  ///   from existing plots) that define the x and y axes of the graph
  /// ** Upon construction the graph is created and filled **

  TH1FBuilder(std::string name,
	      std::vector<RunProvider> run_providers,
	      std::unique_ptr<BaseGetObs> x,
	      std::unique_ptr<BaseGetObs> y);

  /// Destructor

  ~TH1FBuilder() {};
  
  /// Writes the THisto that was built at construction
  /// stage into a root TFile

  void writeTH1FToFile(std::shared_ptr<TFile> t_file, std::string folder);

 private:

  std::shared_ptr<TH1F> m_histo;

};

#endif
