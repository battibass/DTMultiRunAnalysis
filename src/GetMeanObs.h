#ifndef DTMultiRunAnalysis_GetMeanObs_h
#define DTMultiRunAnalysis_GetMeanObs_h

/*
 *  
 * Helper class retrieve mean and mean-error of a TH1F
 *
 * \author C. Battilana (INFN BO)
 *
 */                                                                                                                                                                                                        

#include"DTDPGAnalysis/DTMultiRunAnalysis/src/BaseGetObs.h"

#include"TH1F.h"

class GetMeanObs : public BaseGetObs
{

 public:

  /// Constructor (refers to base class one)

 GetMeanObs(const RunProvider::tag tag_type, const std::string h_name = "") : BaseGetObs(tag_type, h_name) { };

  /// Destructor

  virtual ~GetMeanObs() {};

  /// Main function returning
  /// - mean of TH1F (pair.first)
  /// - error on the mean of TH1F (pair.second)

  virtual std::pair<double, double> getObs(const RunProvider & run_provider) const
  {

    auto histo = static_cast<TH1F*>(run_provider.getPlot(m_tag_type, m_h_name));
    auto result = std::make_pair<double,double>(histo->GetMean(), histo->GetMeanError());
    return result;

  };
  
};

#endif
