/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include "DTDPGAnalysis/DTMultiRunAnalysis/src/TH1FBuilder.h"

#include<iostream>

TH1FBuilder::TH1FBuilder(std::string name,
			 std::vector<RunProvider> run_providers,
			 std::unique_ptr<BaseGetObs> x_obs,
			 std::unique_ptr<BaseGetObs> y_obs)
{

  std::sort(run_providers.begin(),run_providers.end(),
	    [](auto & a, auto & b){ return a.runNumber() < b.runNumber(); });

  m_histo = std::make_unique<TH1F>(name.c_str(),
				   name.c_str(),
				   run_providers.size(),
				   0.5, 0.5 + run_providers.size());
  int i_bin = 1;

  auto addPoint = [& i_bin, 
		   & histo = this->m_histo,
		   & x_obs, & y_obs] (const auto & run_provider)
                  {

		    const auto [x, x_e] = x_obs->getObs(run_provider);
		    const auto [y, y_e] = y_obs->getObs(run_provider);

		    histo->SetBinContent(i_bin,y);
		    histo->SetBinError(i_bin,y_e);
		    histo->GetXaxis()->SetBinLabel(i_bin,std::to_string(x).c_str());

		    ++i_bin;

		  };

  std::for_each(run_providers.begin(),run_providers.end(),addPoint);

}

void TH1FBuilder::writeTH1FToFile(std::shared_ptr<TFile> t_file, std::string folder)
{

  t_file->mkdir(folder.c_str());
  t_file->cd(folder.c_str());

  m_histo->Write();

}

