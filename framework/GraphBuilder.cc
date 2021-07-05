/*
 *  
 * Helper class handling all that is related with
 * a run (root result files, ntuples, ...)
 *
 * \author C. Battilana (INFN BO)
 *
 *
 */


GraphBuilder::GraphBuilder(std::string name,
			   std::vector<RunProvider> & run_providers,
			   std::unique_ptr<GetBaseObs> x,
			   std::unique_ptr<GetBaseObs> y)
{

  m_graph = std::make_unique<TGraphErrors>();
  m_graph->SetName(name.c_str());

  auto addPoint = [auto & m_graph, auto & x, auto & y] (const auto & run_provider)
                  {

		    const auto & [x, x_err] = x->getObs(run_provider);
		    const auto & [y, y_err] = y->getObs(run_provider);

		    m_graph->AddPoint(x, y);

		    int n = m_graph->getN();

		    m_graph->SetPointError(n, x_err, y_err);

		  }

    std::for_each(run_providers.begin(),run_providers.end(),addPoint);

}

void GraphBuilder::writeGraphToFile(std::shared_ptr<TFile> t_file, std::string folder)
{

  t_file->mkdir(folder.c_str());
  t_file->cd(folder.c_str());

  m_graph->Write();

}
  
		    
		    
  
