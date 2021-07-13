#ifndef DTMultiRunAnalysis_RunProvider_h
#define DTMultiRunAnalysis_RunProvider_h

/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include <map>
#include <memory>
#include <string>

#include "TObject.h"
#include "TFile.h"

class RunProvider
{

 public:

  enum class tag { DUMMY = 0, NTUP, DIGI, SEGM, TRIG };
    
  /// Constructor, looks for paths from a given run to exist and opens TFiles

  RunProvider(const int run_number);

  /// Destructor

  ~RunProvider() {};

  /// Returns path to ntuple file

  inline std::string ntuplePath() const { return m_file_paths.at(tag::NTUP); };

  /// Returns run number
  inline int runNumber() const { return m_run_number; };

  /// Returns plot from digi/segment/trigger TFiles
  /// accessed using DIGI/SEGM/TRIG tags and given
  /// plot name

  TObject * getPlot(const tag tag_type, const std::string h_name) const;

 private:

  /// Helper function: checks that a TFile exists
  /// and appends it to m_file_paths

  void condAppendToMap(const tag tag_type, const std::string path);

  /// Base folders where ntuple and results TFiles are stored

  static constexpr char BASE_RESULT_PATH[] = "/eos/project/c/cmsweb/www/MUON/dpgdt/sx5/Results/SliceTest/";
  static constexpr char BASE_NTUPLE_PATH[] = "/eos/cms/store/group/dpg_dt/comm_dt/commissioning_2021_data/ntuples/ST/";
  
  int m_run_number;
  std::map<tag, std::string> m_file_paths;
  std::map<tag, std::shared_ptr<TFile>> m_tfiles;
  
};

#endif
