#ifndef DTMultiRunAnalysis_BaseGetObs_h
#define DTMultiRunAnalysis_BaseGetObs_h

/*
 *  
 * Helper class defining base interface to retrieve
 * a quantity and its error from a plot (e.g. mean and mean error)
 *
 * \author C. Battilana (INFN BO)
 *
 */

#include<string>
#include<utility>

#include"RunProvider.h"

class GetBaseObs
{

 public:

  /// Constructor, wants to know:
  /// - type of input file (e.g. digi/segment/trigger results file)
  /// - plot name (e.g. Ph1nSegments from results_segments.root)

  GetBaseObs(const RunProvider::tag tag_type, const std::string h_name = "") :
    m_tag_type(tag_type), m_h_name(h_name) {};

  /// Destructor

  virtual GetBaseObs() {};
  
  /// Main function (virtual in base class) to retrieve a std::pair
  /// consisting of an observable (e.g. an histo mean - pair.first)
  /// and its error (e.g. the error on the mean - pair.second)

  virtual std::pair<double, double> getObs(const RunProvider & run_provider) = 0 const;

 private:

  RunProvider::tag m_tag_type;
  std::string m_h_name;

};

#endif
