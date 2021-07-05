/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include "RunProvider.h"
#include <filesystem>
#include <algorithm>

RunProvider::RunProvider(int run_number)
{
  
  auto ntuple_path = BASE_NTUPLE_PATH + "/DTDPGNtuple_run" + run_number + ".root";
  condAppendToMap(tag::NTUP, ntuple_path);

  std::map<tag, std::string> result_files = {
    {tag::DIGI, "/digi/results_digi.root"},
    {tag::SEGM, "/segment/results_segment.root"},
    {tag::TRIG, "/trigger/results_trigger.root"}
  };

  auto condAppendResults = [const auto & BASE_RESULT_PATH, const auto & run_number](const auto & [tag_type, file])
                            {
                  			      auto result_path = BASE_RESULT_PATH + "/run" + run_number + file;
			                        condAppendToMap(tag_type, result_path);
  			                    };

  auto openTFiles = [auto & m_tfiles](const auto & [tag_type, file_path])
                    {
            		      m_tfiles[tag_type] = (new TFile(file_path.c_str(),"read"),
                                            [](const auto & [tfile]){ if (tfile->IsOpen()) tfile->Close(); });
		                }
    
  std::for_each(result_files.begin(), result_files.end(), condAppendResults);
  std::for_each(m_file_paths.begin(), m_file_paths.end(), openTFiles);
  
}

void RunProvider::condAppendToMap(const tag tag_type, const std::string path)
{
  
  if (! std::filesystem::exists(path))
    {
      std::cout <<"[RunProvide]: File " << ntuple_path << " does not exist. Quitting\n";
      exit(100);
    }
  
  m_file_paths[tag_type] = ntuple_path;

  return;
  
}

TObject * RunProvider::getPlot(const tag tag_type, const std::string h_name) const
{
  
  TObject* obj = m_tfiles[tag_type]->Get(hName.c_str());
  return obj;

}
