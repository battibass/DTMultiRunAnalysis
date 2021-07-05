#ifndef DTMultiRunAnalysis_GetMeanObs_h
#define DTMultiRunAnalysis_GetMeanObs_h

/*
 *  
 * Helper class retrieve mean and mean-error of a TH1F
 *
 * \author C. Battilana (INFN BO)
 *
 */                                                                                                                                                                                                        

#include"GetBaseObs.h"

#include"TH1F.h"

class GetMeanObs : public GetBaseObs
{

 public:

  /// Constructor (refers to base class one)

  GetRunObs(const RunProvider::tag tag_type, const std::string h_name = "") { GetBaseObs::GetBaseObs(tag_type, h_name); };

  /// Destructor

  virtual GetRunObs() {};

  /// Main function returning
  /// - mean of TH1F (pair.first)
  /// - error on the mean of TH1F (pair.second)

  virtual std::pair<double, double> getObs(const RunProvider & run_provider) const
  {

    auto histo = static_cast<TH1F*>(run_provider.getPlot(m_tag_type, m_h_name));
    auto result = std::make_pair<double,double>(histo.GetMean(), histo.GetMeanError());
    return result;

  };
  
};

#endif
