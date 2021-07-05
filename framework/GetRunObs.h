#ifndef DTMultiRunAnalysis_GetRunObs_h
#define DTMultiRunAnalysis_GetRunObs_h

/*
 *  
 * Helper class retrieve run number from RunProvider
 *
 * \author C. Battilana (INFN BO)
 *
 */ 

#include"GetBaseObs.h"

class GetRunObs : public GetBaseObs
{

 public:

  /// Constructor (refers to base class one)

  GetRunObs(const RunProvider::tag tag_type, const std::string h_name = "") { GetBaseObs::GetBaseObs(tag_type,h_name); };

  /// Destructor

  virtual GetRunObs() {};

  /// Main function returning
  /// - run number (pair.first)
  /// - 0.5 (pair.second)

  virtual std::pair<double, double> getObs(const RunProvider & run_provider) const
  { 

    auto result = std::make_pair<double,double>(run_provider.runNumber(),0.5);
    return result;

  };

};
#endif
