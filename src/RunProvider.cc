/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include "DTDPGAnalysis/DTMultiRunAnalysis/src/RunProvider.h"

#include <filesystem>
#include <algorithm>
#include <iostream>

RunProvider::RunProvider(int run_number) : m_run_number(run_number)
{

  auto ntuple_path = std::string(BASE_NTUPLE_PATH) + "/DTDPGNtuple_run" + std::to_string(run_number) + ".root";
  condAppendToMap(tag::NTUP, ntuple_path);

  std::map<tag, std::string> result_files = {
    {tag::DIGI, "/digi/results_digi.root"},
    {tag::SEGM, "/segment/results_segment.root"},
    {tag::TRIG, "/trigger/results_trigger.root"}
  };

  auto condAppendResults = [this, & run_number](const auto & map_entry)
                            {

			      const auto & [tag_type, file] = map_entry;
			      auto result_path = std::string(BASE_RESULT_PATH) + "/run" + std::to_string(run_number) + file;
			      condAppendToMap(tag_type, result_path);

			    };

  auto openTFiles = [& tfiles = this->m_tfiles](const auto & map_entry)
                    {

		      const auto & [tag_type, file_path] = map_entry;
		      tfiles[tag_type] = std::shared_ptr<TFile>(new TFile(file_path.c_str(),"read"),
								[](const auto & tfile){ if (tfile->IsOpen()) tfile->Close(); });

		    };
    
  std::for_each(result_files.begin(), result_files.end(), condAppendResults);
  std::for_each(m_file_paths.begin(), m_file_paths.end(), openTFiles);
  
}

void RunProvider::condAppendToMap(const tag tag_type, const std::string ntuple_path)
{
  
  if (! std::filesystem::exists(ntuple_path))
    {
      std::cout <<"[RunProvide]: File " << ntuple_path << " does not exist. Quitting\n";
      exit(100);
    }
  
  m_file_paths[tag_type] = ntuple_path;

  return;
  
}

TObject * RunProvider::getPlot(const tag tag_type, const std::string h_name) const
{
  
  TObject* obj = m_tfiles.at(tag_type)->Get(h_name.c_str());
  return obj;

}
