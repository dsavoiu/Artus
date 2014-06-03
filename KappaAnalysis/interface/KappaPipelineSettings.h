
#pragma once

#include "Artus/Configuration/interface/SettingsBase.h"
#include "Artus/Configuration/interface/SettingMacros.h"
#include "Artus/Configuration/interface/PropertyTreeSupport.h"

/**
   \brief Reads settings for local parts of KappaPipelineRunner from a prepared json configuration 
   file. 

   Defines local settings that can be obtained from the json configuration file. These settings are
   then available as key value pairs of type:

   KappaGlobalSetting mysetting;
   mysetting.key = value

   for an implementation of type:

   IMPL_SETTING_DEFAULT(type_of_value, key, default_value);

   You can define the readout of new global settings here or in a derived class.
*/

class KappaPipelineSettings: public SettingsBase {
public:

	VarCache<stringvector> quantities;
	stringvector GetQuantities() const
	{
		RETURN_CACHED(quantities, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".Quantities"))
	}

	VarCache<std::vector<std::string>> jsonFiles;
	stringvector GetJsonFiles() const
	{
		RETURN_CACHED(jsonFiles, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".JsonFiles"))
	}
	IMPL_SETTING_DEFAULT(int, PassRunLow, 1);
	IMPL_SETTING_DEFAULT(int, PassRunHigh, 0);
	
	VarCache<std::vector<int> > runWhitelist;
	std::vector<int> GetRunWhitelist() const
	{
		RETURN_CACHED(runWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".RunWhitelist"))
	}
	VarCache<std::vector<int> > runBlacklist;
	std::vector<int> GetRunBlacklist() const
	{
		RETURN_CACHED(runBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".RunBlacklist"))
	}
	VarCache<std::vector<int> > lumiWhitelist;
	std::vector<int> GetLumiWhitelist() const
	{
		RETURN_CACHED(lumiWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".LumiWhitelist"))
	}
	VarCache<std::vector<int> > lumiBlacklist;
	std::vector<int> GetLumiBlacklist() const
	{
		RETURN_CACHED(lumiBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".LumiBlacklist"))
	}
	VarCache<std::vector<int> > eventWhitelist;
	std::vector<int> GetEventWhitelist() const
	{
		RETURN_CACHED(eventWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".EventWhitelist"))
	}
	VarCache<std::vector<int> > eventBlacklist;
	std::vector<int> GetEventBlacklist() const
	{
		RETURN_CACHED(eventBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "Pipelines." + GetName() + ".EventBlacklist"))
	}
	
	VarCache<std::vector<std::string>> hltPaths;
	stringvector GetHltPaths() const
	{
		RETURN_CACHED(hltPaths, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".HltPaths"))
	}
	IMPL_SETTING_DEFAULT(bool, AllowPrescaledTrigger, true);
	
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingElectron, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingMuon, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingTau, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingJet, 0.5);
	
	IMPL_SETTING(int, Year);
	
	IMPL_SETTING(std::string, MuonID);
	IMPL_SETTING(std::string, MuonIsoType);
	IMPL_SETTING(std::string, MuonIso);
	
	IMPL_SETTING(std::string, ElectronID);
	IMPL_SETTING(std::string, ElectronIsoType);
	IMPL_SETTING(std::string, ElectronIso);
	IMPL_SETTING(std::string, ElectronReco);
	
	VarCache<std::vector<std::string>> tauDiscriminators;
	stringvector GetTauDiscriminators() const
	{
		RETURN_CACHED(tauDiscriminators, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".TauDiscriminators"))
	}

	IMPL_SETTING(std::string, JetID);
	
	IMPL_SETTING(int, NElectrons);
	IMPL_SETTING(int, NMuons);
	IMPL_SETTING(int, NTaus);
	IMPL_SETTING(int, NJets);
	
	VarCache<std::vector<std::string>> electronLowerPtCuts;
	stringvector GetElectronLowerPtCuts() const
	{
		RETURN_CACHED(electronLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".ElectronLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> muonLowerPtCuts;
	stringvector GetMuonLowerPtCuts() const
	{
		RETURN_CACHED(muonLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".MuonLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> tauLowerPtCuts;
	stringvector GetTauLowerPtCuts() const
	{
		RETURN_CACHED(tauLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".TauLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> jetLowerPtCuts;
	stringvector GetJetLowerPtCuts() const
	{
		RETURN_CACHED(jetLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".JetLowerPtCuts"))
	}
	
	VarCache<std::vector<std::string>> electronUpperAbsEtaCuts;
	stringvector GetElectronUpperAbsEtaCuts() const
	{
		RETURN_CACHED(electronUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".ElectronUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> muonUpperAbsEtaCuts;
	stringvector GetMuonUpperAbsEtaCuts() const
	{
		RETURN_CACHED(muonUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".MuonUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> tauUpperAbsEtaCuts;
	stringvector GetTauUpperAbsEtaCuts() const
	{
		RETURN_CACHED(tauUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".TauUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> jetUpperAbsEtaCuts;
	stringvector GetJetUpperAbsEtaCuts() const
	{
		RETURN_CACHED(jetUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "Pipelines." + GetName() + ".JetUpperAbsEtaCuts"))
	}

	IMPL_SETTING(std::string, PileupWeightFile);
	
	IMPL_SETTING(std::string, EventWeight);

};

/**
   \brief Reads settings for global parts of KappaPipelineRunner from a prepared json configuration 
   file. 

   Defines global settings that can be obtained from the json configuration file. These settings are
   then available as key value pairs of type:

   KappaGlobalSetting mysetting;
   mysetting.key = value

   for an implementation of type:

   IMPL_SETTING_DEFAULT(type_of_value, key, default_value);

   You can define the readout of new global settings here or in a derived class.
*/

class KappaGlobalSettings: public GlobalSettingsBase {

public:

	/// name of electron collection in kappa tuple	
	IMPL_SETTING_DEFAULT(std::string, Electrons, "");

	/// name of muon collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, Muons, "");

	/// name of tau collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, Taus, "");
	IMPL_SETTING_DEFAULT(std::string, TauDiscriminatorMetadata, "");

	/// name of jet collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, Jets, "");

	/// name of tagged jet collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, TaggedJets, "");

	/// name of jet area collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, JetArea, "");

	/// name of MET collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, Met, "");
	
	/// name of GenMET collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, GenMet, "");

	/// names of PF candidate collections in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, PFChargedHadronsPileUp, "");
	IMPL_SETTING_DEFAULT(std::string, PFChargedHadronsNoPileUp, "");
	IMPL_SETTING_DEFAULT(std::string, PFNeutralHadronsNoPileUp, "");
	IMPL_SETTING_DEFAULT(std::string, PFPhotonsNoPileUp, "");

	/// name of beamspot collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, BeamSpot, "");

	/// name of vertexSummary collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, VertexSummary, "");

	/// name of genParticle collection in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, GenParticles, "");

	/// name of lumiMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, LumiMetadata, ""); // TODO: Default value, move to Artus/Provider

	/// name of genLumiMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, GenLumiMetadata, ""); // TODO: Default value, move to Artus/Provider

	/// name of eventMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, EventMetadata, ""); // TODO: Default value, move to Artus/Provider

	/// name of genEventMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, GenEventMetadata, ""); // TODO: Default value, move to Artus/Provider

	/// name of filterMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, FilterMetadata, ""); // TODO: Default value, move to Artus/Provider

	/// name of filterSummary in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, FilterSummary, ""); // TODO: Default value, move to Artus/Provider

	/// name of TaggerMetaData in kappa tuple
	IMPL_SETTING_DEFAULT(std::string, TaggerMetadata, ""); // TODO: Default value, move to Artus/Provider
	IMPL_SETTING_DEFAULT(std::string, TriggerObjects, "")

	VarCache<std::vector<std::string>> jsonFiles;
	stringvector GetJsonFiles() const
	{
		RETURN_CACHED(jsonFiles, PropertyTreeSupport::GetAsStringList(GetPropTree(), "JsonFiles"))
	}
	IMPL_SETTING_DEFAULT(int, PassRunLow, 0);
	IMPL_SETTING_DEFAULT(int, PassRunHigh, 0);
	
	VarCache<std::vector<int> > runWhitelist;
	std::vector<int> GetRunWhitelist() const
	{
		RETURN_CACHED(runWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "RunWhitelist"))
	}
	VarCache<std::vector<int> > runBlacklist;
	std::vector<int> GetRunBlacklist() const
	{
		RETURN_CACHED(runBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "RunBlacklist"))
	}
	VarCache<std::vector<int> > lumiWhitelist;
	std::vector<int> GetLumiWhitelist() const
	{
		RETURN_CACHED(lumiWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "LumiWhitelist"))
	}
	VarCache<std::vector<int> > lumiBlacklist;
	std::vector<int> GetLumiBlacklist() const
	{
		RETURN_CACHED(lumiBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "LumiBlacklist"))
	}
	VarCache<std::vector<int> > eventWhitelist;
	std::vector<int> GetEventWhitelist() const
	{
		RETURN_CACHED(eventWhitelist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "EventWhitelist"))
	}
	VarCache<std::vector<int> > eventBlacklist;
	std::vector<int> GetEventBlacklist() const
	{
		RETURN_CACHED(eventBlacklist, PropertyTreeSupport::GetAsIntList(GetPropTree(), "EventBlacklist"))
	}
	
	VarCache<std::vector<std::string>> hltPaths;
	stringvector GetHltPaths() const
	{
		RETURN_CACHED(hltPaths, PropertyTreeSupport::GetAsStringList(GetPropTree(), "HltPaths"))
	}
	IMPL_SETTING_DEFAULT(bool, AllowPrescaledTrigger, true);
	
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingElectron, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingMuon, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingTau, 0.5);
	IMPL_SETTING_DEFAULT(float, DeltaRTriggerMatchingJet, 0.5);
	
	//Reading Boson PdgId for GenTauDecayProducer studies.
	VarCache<stringvector> BosonPdgId;
	stringvector GetBosonPdgId() const
	{
		RETURN_CACHED(BosonPdgId, PropertyTreeSupport::GetAsStringList(GetPropTree(), "BosonPdgId"))
	}
	
	IMPL_SETTING(int, Year);
	
	IMPL_SETTING(std::string, MuonID);
	IMPL_SETTING(std::string, MuonIsoType);
	IMPL_SETTING(std::string, MuonIso);
	
	IMPL_SETTING(std::string, ElectronID);
	IMPL_SETTING(std::string, ElectronIsoType);
	IMPL_SETTING(std::string, ElectronIso);
	IMPL_SETTING(std::string, ElectronReco);
	
	VarCache<std::vector<std::string>> tauDiscriminators;
	stringvector GetTauDiscriminators() const
	{
		RETURN_CACHED(tauDiscriminators, PropertyTreeSupport::GetAsStringList(GetPropTree(), "TauDiscriminators"))
	}

	IMPL_SETTING(std::string, JetID);
	
	IMPL_SETTING(int, NElectrons);
	IMPL_SETTING(int, NMuons);
	IMPL_SETTING(int, NTaus);
	IMPL_SETTING(int, NJets);
	
	VarCache<std::vector<std::string>> electronLowerPtCuts;
	stringvector GetElectronLowerPtCuts() const
	{
		RETURN_CACHED(electronLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "ElectronLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> muonLowerPtCuts;
	stringvector GetMuonLowerPtCuts() const
	{
		RETURN_CACHED(muonLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "MuonLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> tauLowerPtCuts;
	stringvector GetTauLowerPtCuts() const
	{
		RETURN_CACHED(tauLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "TauLowerPtCuts"))
	}
	VarCache<std::vector<std::string>> jetLowerPtCuts;
	stringvector GetJetLowerPtCuts() const
	{
		RETURN_CACHED(jetLowerPtCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "JetLowerPtCuts"))
	}
	
	VarCache<std::vector<std::string>> electronUpperAbsEtaCuts;
	stringvector GetElectronUpperAbsEtaCuts() const
	{
		RETURN_CACHED(electronUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "ElectronUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> muonUpperAbsEtaCuts;
	stringvector GetMuonUpperAbsEtaCuts() const
	{
		RETURN_CACHED(muonUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "MuonUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> tauUpperAbsEtaCuts;
	stringvector GetTauUpperAbsEtaCuts() const
	{
		RETURN_CACHED(tauUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "TauUpperAbsEtaCuts"))
	}
	VarCache<std::vector<std::string>> jetUpperAbsEtaCuts;
	stringvector GetJetUpperAbsEtaCuts() const
	{
		RETURN_CACHED(jetUpperAbsEtaCuts, PropertyTreeSupport::GetAsStringList(GetPropTree(), "JetUpperAbsEtaCuts"))
	}

	IMPL_SETTING(std::string, PileupWeightFile);
	
	IMPL_SETTING(std::string, EventWeight);

};
