
#pragma once

#include <limits>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "Artus/Filter/interface/CutFilterBase.h"
#include "Artus/Utility/interface/Utility.h"
#include "Artus/KappaAnalysis/interface/KappaTypes.h"


/** Abstract Lepton Eta Filter
 */
template<class TLepton>
class LeptonUpperAbsEtaCutsFilter: public CutRangeFilterBase<KappaTypes> {
public:
	
	typedef typename std::function<double(KappaEvent const&, KappaProduct const&)> double_extractor_lambda;
	
	LeptonUpperAbsEtaCutsFilter(std::vector<TLepton*> KappaProduct::*validLeptons) :
		CutRangeFilterBase<KappaTypes>(),
		m_validLeptonsMember(validLeptons)
	{
	}


protected:

	void Initialise(std::vector<std::string> const& leptonUpperAbsEtaCutsVector) {
		std::map<std::string, std::vector<std::string> > leptonUpperAbsEtaCuts = Utility::ParseVectorToMap(leptonUpperAbsEtaCutsVector);
	
		std::vector<int> defaultIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
		for (std::map<std::string, std::vector<std::string> >::const_iterator leptonUpperAbsEtaCut = leptonUpperAbsEtaCuts.begin();
		     leptonUpperAbsEtaCut != leptonUpperAbsEtaCuts.end(); ++leptonUpperAbsEtaCut)
		{
			std::vector<int> indices;
			std::vector<std::string> hltNames;
			if (leptonUpperAbsEtaCut->first == "default") {
				indices = defaultIndices;
				LOG(WARNING) << "No lepton index for the Filter \"" << this->GetFilterId() << "\" specified. Check the possible 3 hardest leptons.";
			}
			else {
				try {
					indices.push_back(boost::lexical_cast<int>(leptonUpperAbsEtaCut->first));
				}
				catch (boost::bad_lexical_cast const& exception) {
					hltNames.push_back(leptonUpperAbsEtaCut->first);
				}
			}
			
			for (std::vector<std::string>::const_iterator absEtaCut = leptonUpperAbsEtaCut->second.begin();
			     absEtaCut != leptonUpperAbsEtaCut->second.end(); ++absEtaCut)
			{
				double absEtaCutValue = std::stod(*absEtaCut);
				
				for (std::vector<int>::iterator index = indices.begin(); index != indices.end(); ++index)
				{
					size_t tmpIndex(*index); // TODO
					this->m_cuts.push_back(std::pair<double_extractor_lambda, CutRange>(
							[this, tmpIndex](KappaEvent const& event, KappaProduct const& product) -> double {
								return (((product.*m_validLeptonsMember).size() > tmpIndex) ?
								        std::abs((product.*m_validLeptonsMember).at(tmpIndex)->p4.Eta()) :
								        -1.0);
							},
							CutRange::UpperThresholdCut(absEtaCutValue)
					));
				}
				
				for (std::vector<std::string>::iterator hltName = hltNames.begin(); hltName != hltNames.end(); ++hltName)
				{
					std::string tmpHltName(*hltName); // TODO
					boost::regex pattern(tmpHltName, boost::regex::icase | boost::regex::extended);
					for (std::vector<int>::iterator index = defaultIndices.begin(); index != defaultIndices.end(); ++index)
					{
						size_t tmpIndex(*index);
						this->m_cuts.push_back(std::pair<double_extractor_lambda, CutRange>(
								[this, tmpHltName, pattern, tmpIndex](KappaEvent const& event, KappaProduct const& product) -> double {
									return (((product.*m_validLeptonsMember).size() > tmpIndex && boost::regex_search(product.m_selectedHltName, pattern)) ?
									        std::abs((product.*m_validLeptonsMember).at(tmpIndex)->p4.Eta()) :
									        -1.0);
								},
								CutRange::UpperThresholdCut(absEtaCutValue)
						));
					}
				}
			}
		}	
	}


private:
	std::vector<TLepton*> KappaProduct::*m_validLeptonsMember;
};


/** Electron Eta Filter
 */
class ElectronUpperAbsEtaCutsFilter: public LeptonUpperAbsEtaCutsFilter<KDataElectron> {
public:
	
	virtual std::string GetFilterId() const ARTUS_CPP11_OVERRIDE;
	
	ElectronUpperAbsEtaCutsFilter() : LeptonUpperAbsEtaCutsFilter<KDataElectron>(&KappaProduct::m_validElectrons) {}
	
	virtual void Init(KappaSettings const& settings) ARTUS_CPP11_OVERRIDE;
};


/** Muon Eta Filter
 */
class MuonUpperAbsEtaCutsFilter: public LeptonUpperAbsEtaCutsFilter<KDataMuon> {
public:
	
	virtual std::string GetFilterId() const ARTUS_CPP11_OVERRIDE;
	
	MuonUpperAbsEtaCutsFilter() : LeptonUpperAbsEtaCutsFilter<KDataMuon>(&KappaProduct::m_validMuons) {}
	
	virtual void Init(KappaSettings const& settings) ARTUS_CPP11_OVERRIDE;
};


/** Tau Eta Filter
 */
class TauUpperAbsEtaCutsFilter: public LeptonUpperAbsEtaCutsFilter<KDataPFTau> {
public:
	
	virtual std::string GetFilterId() const ARTUS_CPP11_OVERRIDE;
	
	TauUpperAbsEtaCutsFilter() : LeptonUpperAbsEtaCutsFilter<KDataPFTau>(&KappaProduct::m_validTaus) {}
	
	virtual void Init(KappaSettings const& settings) ARTUS_CPP11_OVERRIDE;
};


/** Jet Eta Filter
 */
class JetUpperAbsEtaCutsFilter: public LeptonUpperAbsEtaCutsFilter<KDataPFJet> {
public:
	
	virtual std::string GetFilterId() const ARTUS_CPP11_OVERRIDE;
	
	JetUpperAbsEtaCutsFilter() : LeptonUpperAbsEtaCutsFilter<KDataPFJet>(&KappaProduct::m_validJets) {}
	
	virtual void Init(KappaSettings const& settings) ARTUS_CPP11_OVERRIDE;
};

