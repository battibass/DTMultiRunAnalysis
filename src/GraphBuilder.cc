/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */

#include "DTDPGAnalysis/DTMultiRunAnalysis/src/GraphBuilder.h"

#include<array>
#include<iostream>

GraphBuilder::GraphBuilder(std::string name,
			   std::vector<RunProvider> & run_providers,
			   std::unique_ptr<BaseGetObs> x_obs,
			   std::unique_ptr<BaseGetObs> y_obs)
{

  m_graph = std::make_unique<TGraphErrors>(run_providers.size());
  m_graph->SetName(name.c_str());

  int i_point = 0;

  auto addPoint = [& i_point, 
		   & graph = this->m_graph,
		   & x_obs, & y_obs] (const auto & run_provider)
                  {

		    const auto [x, x_e] = x_obs->getObs(run_provider);
		    const auto [y, y_e] = y_obs->getObs(run_provider);

		    graph->SetPoint(i_point,x,y);
		    graph->SetPointError(i_point,x_e,y_e);

		    ++i_point;

		  };

  std::for_each(run_providers.begin(),run_providers.end(),addPoint);

}

void GraphBuilder::writeGraphToFile(std::shared_ptr<TFile> t_file, std::string folder)
{

  t_file->mkdir(folder.c_str());
  t_file->cd(folder.c_str());

  m_graph->Write();

}
  
		    
		    
  
