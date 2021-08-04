/*
 *this class i meant to read the csv files containing securities data and parse it to SecurityInfo data structure.
 *
 * */

#include <vector>
#include<fstream>
#include<iostream>
#include<string>
#include <bits/stdc++.h>
#include <cmath>
#include <filesystem>

namespace BTF
{
	class SecurityInfo
	{
		public:
			std::vector<std::string> date;
			std::vector<float> open;
			std::vector<float> high;
			std::vector<float> low;
			std::vector<float> close;
			std::vector<float> volume;
			unsigned int m_uSize {0};
			
			void Clear()
			{
				date.clear();
				open.clear();
				high.clear();
	         	low.clear();
                close.clear();
				m_uSize = 0;
			}
	};
	
	class CSVReader //:IDataExtractor
	{
		public:
			static bool ParseData(const char* si_fileName, SecurityInfo& o_PriceInfo)
			{
				std::cout<<"CSVReader::ParseData"<<std::endl;

				bool l_bFileMisformed {false};
				std::ifstream l_file(si_fileName);
				std::string l_line;
				std::string l_delimiter { ","};
				if(l_file.is_open())
				{
					size_t l_pos {0};
					unsigned int l_uLineCount {0};
					while((!l_bFileMisformed) && (getline (l_file, l_line)))
					{
						o_PriceInfo.m_uSize++;
						l_uLineCount++;

						size_t l_columnCount{0};
						std::string l_token;

						while ( !l_line.empty() )
						{
							if (l_columnCount < 6)
							{
								l_pos = l_line.find(l_delimiter);
							}

							l_token = l_line.substr(0, l_pos);
							std::cout << l_token << std::endl;

							if(l_columnCount == 0)
							{
								if((l_uLineCount == 1) && "Date" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Date"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.date.push_back((l_token));
								}
							}
							else if(l_columnCount == 1)
							{

								if((l_uLineCount == 1) && "Open" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Open"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.open.push_back(std::stof(l_token));
								}
							}
							else if(l_columnCount == 2)
							{
								if((l_uLineCount == 1) && "High" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: High"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.high.push_back(std::stof(l_token));
								}
							}
							else if(l_columnCount == 3)
							{

								if((l_uLineCount == 1) && "Low" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Low"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.low.push_back(std::stof(l_token));
								}
							}
							else if(l_columnCount == 4)
							{

								if((l_uLineCount == 1) && "Close" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Close"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.close.push_back(std::stof(l_token));
								}
							}
							else if(l_columnCount == 5)
							{

								if((l_uLineCount == 1) && "Adj Close" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Adj Close"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									//o_PriceInfo.open.push_back(l_token)
									/* do nothing */
								}
							}
							else if(l_columnCount == 6)
							{

								if((l_uLineCount == 1) && "Volume" != l_token)
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Volume"<<std::endl;
								}
								else if (!(l_uLineCount == 1))
								{
									o_PriceInfo.volume.push_back(std::stof(l_token));
								}
								//std::cout<<"value of line after last column: "<<l_line<<std::endl;
							}
							else
							{
								l_columnCount++;
								l_bFileMisformed = true;
								std::cout<<"Unexpeced column size: "<< l_columnCount<<std::endl;
								break;
							}
							l_line.erase(0, l_pos + l_delimiter.length());
							l_columnCount++;
						}						
					}

					std::cout<<"Total lines parsed: "<<l_uLineCount<<std::endl;
					l_file.close();
				}
				else
				{
					l_bFileMisformed = true;
					o_PriceInfo.Clear();
					std::cout<<"Failed to open file: " << si_fileName<<std::endl;
				}

				return (!l_bFileMisformed);
			}
	};
	enum eTradeDirection
	{
		NOT_SET = -2,
		SHORT = -1,
		INDECISION = 0,
		LONG = 1,
		CLOSED,
		STOPPED
	};
	enum eSource
	{
		OPEN = 0,
		HIGH,
		LOW,
		CLOSE,
		VOLUME,
		HL2,
		OHLC4
	};
	
	class Strategy
	{
		public:
		int m_nPositionSize {0};
		
	};
	
	class TradeDirectionInfo
	{
		public:
		eTradeDirection m_eC1{eTradeDirection::NOT_SET};
		eTradeDirection m_eV1{eTradeDirection::NOT_SET};
		eTradeDirection m_eB {eTradeDirection::NOT_SET};
		eTradeDirection m_eC2{eTradeDirection::NOT_SET};
		eTradeDirection m_eV2{eTradeDirection::NOT_SET};
		eTradeDirection m_eE {eTradeDirection::NOT_SET};
		eTradeDirection m_eCombined {eTradeDirection::NOT_SET};

		bool m_bUsable { false };
	};

	class RunningTradeInfo
	{
	public:
		int		m_nPositionSize 				{ 0 };

		float	m_fEntryCloseOrig				{0.f};
		float	m_fEntryClose					{0.f};
		float	m_fTakeProfitOrig				{0.f};
		float	m_fStopLossOrig					{0.f};
		float	m_fTrailingStopLoss				{0.f};
		float 	m_fAtr_TakeProfitFactor 		{1.0f};
		float 	m_fAtr_InitialStopLossFactor 	{1.0f};
		float 	m_fAtr_TrailingStopLossFactor 	{1.0f};

		bool 	m_bTakeProfit 					{ false };
		bool 	m_bLongEntry 					{ false };
		bool 	m_bLongClose 					{ false };
	};

	class TradesResultInfo
	{
	public:
		unsigned int	m_uTotalTrades				{ 0U };
		unsigned int	m_uTotalClosedTrades		{ 0U };
		unsigned int	m_uTotalProfitableTrades	{ 0U };
		unsigned int	m_uTotalNonProfitableTrades	{ 0U };
		unsigned int	m_uStoppedTradesCount		{ 0U };
		unsigned int	m_uClosedTradesCount		{ 0U };
		unsigned int	m_uTakeProfitTradesCount	{ 0U };

		float m_fActualGrossProfit 		{0.f};
		float m_fActualGrossLoss		{0.f};
		float m_fMaxDrawDown			{0.f};
		float m_fProfitFactor			{0.f};
		float 	m_fPercentageProfitable	{1.0f};
	};

	typedef std::vector<TradeDirectionInfo> vTradeDirectionInfo;

	namespace Helpers
	{
		float PartialCalculateAbssio(const float& ci_fCurrentSourceLevel, 
										const float& ci_fPreviousSourceLevel, const unsigned int& ci_cosl,
										float& io_fA1, float& io_fM1, float& io_fD1
									)
		{
			auto l_fA { io_fA1 };						
			io_fA1 = ( ci_fCurrentSourceLevel>ci_fPreviousSourceLevel) ? 
						( (l_fA) + (ci_fCurrentSourceLevel/ci_fPreviousSourceLevel) - 1) : l_fA;
			
			auto l_fM { io_fM1 };
			io_fM1 = ( ci_fCurrentSourceLevel==ci_fPreviousSourceLevel) ? (l_fM + 1.0 / ci_cosl) : l_fM;
			
			auto l_fD { io_fD1 };
			io_fD1 = ( ci_fCurrentSourceLevel<ci_fPreviousSourceLevel) ? l_fD + (ci_fPreviousSourceLevel/ci_fCurrentSourceLevel)-1 : l_fD;
			
			return ( io_fD1 + io_fM1 / 2 == 0) ?  1 :  1 - (1 / ( 1+ ( io_fA1 + io_fM1 / 2 ) / ( io_fD1 + io_fM1 / 2 ) ) );
		}
		
		//does not support date or string
		float GetSourceValue(const SecurityInfo& ci_PriceInfo, const unsigned int ci_index, const eSource& ci_eSource)
		{
			float l_fVal {0.0f};
			
			switch (ci_eSource)
			{
				case eSource::OPEN:
					l_fVal = ci_PriceInfo.open[ci_index];
					break;
				case eSource::HIGH:
					l_fVal = ci_PriceInfo.high[ci_index];
					break;
				case eSource::LOW:
					l_fVal = ci_PriceInfo.low[ci_index];
					break;
				case eSource::CLOSE:
					l_fVal = ci_PriceInfo.close[ci_index];
					break;
				case eSource::VOLUME:
					l_fVal = ci_PriceInfo.volume[ci_index];
					break;
				case eSource::HL2:
					l_fVal = (ci_PriceInfo.high[ci_index] + ci_PriceInfo.low[ci_index])/2;
					break;
				case eSource::OHLC4:
					l_fVal = (ci_PriceInfo.open[ci_index] + ci_PriceInfo.high[ci_index] +
							ci_PriceInfo.low[ci_index] + ci_PriceInfo.close[ci_index])/4;
					break;
				default:
					l_fVal = 0.0f;
					std::cout<<std::endl<<"unknown source type"<<std::endl;
			}
			return l_fVal;
		}

		//Populate TradeDirectionInfo::m_eCombined based on individual indicator setup (initial).
		void DetermineTradeDirectionBasedOnIndicatorSetup(BTF::TradeDirectionInfo& io_eTradeInfo)
		{
			if( (io_eTradeInfo.m_bUsable) &&(
					( (io_eTradeInfo.m_eB == eTradeDirection::LONG) || (io_eTradeInfo.m_eB == eTradeDirection::NOT_SET) ) &&
						((io_eTradeInfo.m_eC1 == eTradeDirection::LONG) || (io_eTradeInfo.m_eC1 == eTradeDirection::NOT_SET))  &&
						((io_eTradeInfo.m_eV1 == eTradeDirection::LONG) || (io_eTradeInfo.m_eV1 == eTradeDirection::NOT_SET)) &&
						((io_eTradeInfo.m_eC2 == eTradeDirection::LONG) || (io_eTradeInfo.m_eC2 == eTradeDirection::NOT_SET)) &&
						((io_eTradeInfo.m_eV2 == eTradeDirection::LONG) || (io_eTradeInfo.m_eV2 == eTradeDirection::NOT_SET)) &&
						((io_eTradeInfo.m_eE == eTradeDirection::LONG) || (io_eTradeInfo.m_eE == eTradeDirection::NOT_SET))
					)
			  )
			{
				io_eTradeInfo.m_eCombined = eTradeDirection::LONG;
			}
			else if ( (io_eTradeInfo.m_bUsable) &&(
						( (io_eTradeInfo.m_eB == eTradeDirection::SHORT) || (io_eTradeInfo.m_eB == eTradeDirection::NOT_SET) ) &&
							((io_eTradeInfo.m_eC1 == eTradeDirection::SHORT) || (io_eTradeInfo.m_eC1 == eTradeDirection::NOT_SET))  &&
							((io_eTradeInfo.m_eV1 == eTradeDirection::SHORT) || (io_eTradeInfo.m_eV1 == eTradeDirection::NOT_SET)) &&
							((io_eTradeInfo.m_eC2 == eTradeDirection::SHORT) || (io_eTradeInfo.m_eC2 == eTradeDirection::NOT_SET)) &&
							((io_eTradeInfo.m_eV2 == eTradeDirection::SHORT) || (io_eTradeInfo.m_eV2 == eTradeDirection::NOT_SET)) &&
							((io_eTradeInfo.m_eE == eTradeDirection::SHORT) || (io_eTradeInfo.m_eE == eTradeDirection::NOT_SET))
						)
			  	  )
			{
				io_eTradeInfo.m_eCombined = eTradeDirection::SHORT;
			}
			else
			{
				io_eTradeInfo.m_eCombined = eTradeDirection::INDECISION;
			}
		}

		//update TradeDirectionInfo::m_eCombined based on rules -
		//TODO: Ideally this should come from .ini or .XML file.
		void DetermineTradeDirectionBasedOnUserDefinedRules(BTF::TradeDirectionInfo& io_eTradeInfo)
		{


			/*
			 *determine the first occurrence of LONG trade
			 *determine if the next candle flip the LONG to SHORT -
			 *		1. yes - update the  m_eCombined to CLOSED
			 *		2. no - determine whether the LOW crossed the Atr_InitialStopLoss
			 */
		}
	}
	namespace Indicators
	{
		class IMovingAverage
		{
			public:
			virtual ~IMovingAverage() = 0;
			virtual float Execute() = 0;
		};

		class JurichMovingAverage //:IMovingAverage
		{
			public:
			float m_fJMA {0.0f};
			float m_fE0 {0.0f};
			float m_fE1 {0.0f};
			float m_fE2 {0.0};
			
			float Execute (const float& ci_source,
							const unsigned int ci_baseLength,
							const unsigned int ci_basepower,
							int i_uPhase)
			{
				auto length = ci_baseLength;
				auto phase = i_uPhase;
				auto power = ci_basepower;
				
				auto phaseRatio = (phase < -100) ? 0.5 : (phase > 100) ? 2.5 : (phase / 100 + 1.5);
				auto jbeta = 0.45 * (length - 1) / (0.45 * (length - 1) + 2);
				auto jalpha = std::pow(jbeta, power);
				
				auto jma = m_fJMA;
				
				auto e0 = m_fE0;
				m_fE0 = (1 - jalpha) * ci_source + jalpha * e0;
				
				auto e1 = m_fE1;
				m_fE1 = (ci_source - m_fE0) * (1 - jbeta) + jbeta * e1;
				
				auto e2 = m_fE2;
				m_fE2 = (m_fE0 + phaseRatio * m_fE1 - jma) * std::pow(1 - jalpha, 2) + std::pow(jalpha, 2) * e2;
				
				m_fJMA = m_fE2 + jma;

				return m_fJMA;
			}
		};
		
		class AbsoluteStrength //:IIndicators
		{
			private:
			//the data members will store the previous values respectively
			float m_fA1  {0.0f};
			float m_fM1  {0.0f};
			float m_fD1  {0.0f};
			float m_fMT1 {0.0f};
			float m_fUT1 {0.0f};
			float m_fPrevPriceLevel {0.0f};
			eSource m_eSource;
			
			JurichMovingAverage m_JMA;
			
			public: //add get methods for the following.
			unsigned int 	m_uStartBaseLength	{0U};
			unsigned int 	m_uStartBasepower	{0U};
			unsigned int 	m_uStartSignalLength{0U};
			int 			m_nStartPhase 		{0};
			
			unsigned int 	m_uEndBaseLength	{0U};
			unsigned int 	m_uEndBasepower		{0U};
			unsigned int 	m_uEndSignalLength	{0U};
			int 			m_nEndPhase 		{0};
			
			public:
			//ctor
			AbsoluteStrength(const eSource 		l_eSource,
							const unsigned int 	l_uStartBaseLength,
							const unsigned int 	l_uStartBasepower,
							const unsigned int 	l_uStartSignalLength,
							const int 		   	l_nStartPhase,
							const unsigned int 	l_uEndBaseLength,
							const unsigned int 	l_uEndBasepower,
							const unsigned int 	l_uEndSignalLength,
							const int 		   	l_nEndPhase) :
			m_eSource 			{l_eSource},
			m_uStartBaseLength	{l_uStartBaseLength},
			m_uStartBasepower	{l_uStartBasepower},
			m_uStartSignalLength{l_uStartSignalLength},
			m_nStartPhase 		{l_nStartPhase},
			m_uEndBaseLength	{l_uEndBaseLength},
			m_uEndBasepower		{l_uEndBasepower},
			m_uEndSignalLength	{l_uEndSignalLength},
			m_nEndPhase			{l_nEndPhase}
			{}
			
			//dtor
			~AbsoluteStrength() {}
		
			eSource GetSource () const { return m_eSource;}
			eTradeDirection Execute(const float& ci_fCurrentPriceLevel, 
									const unsigned int ci_uBaseLength,
									const unsigned int ci_uBasepower,
									const unsigned int ci_uSignalLength,
									int i_nPhase)
			{
				//there are no changes in results because of this so, we will keep it as defined constant.
				const unsigned int cosl { 10 };
				
				auto abssi {Helpers::PartialCalculateAbssio(ci_fCurrentPriceLevel, m_fPrevPriceLevel, cosl,
													m_fA1, m_fM1, m_fD1) };
													
				auto abssio { abssi - m_JMA.Execute(abssi, ci_uBaseLength, ci_uBasepower, i_nPhase) };
				
				auto alp { 2.0/(ci_uSignalLength+1) };

				auto mt { m_fMT1 };
				m_fMT1 = alp * abssio + (1-alp) * mt;

				auto ut { m_fUT1 };
				m_fUT1 = alp * m_fMT1 + (1-alp) * ut;
				
				auto s { ( ( 2 - alp ) * m_fMT1 - m_fUT1 ) / (1-alp) };
#ifdef DEBUG
				auto d { abssio-s };
#endif
				m_fPrevPriceLevel = ci_fCurrentPriceLevel;
				
				return ( abssio > 0 ? abssio >= s ? LONG : INDECISION : abssio <=s ? SHORT : INDECISION);
			}
		};	
	}
}

namespace BTFI = BTF::Indicators;
namespace BTFH = BTF::Helpers;

int main()
{
#ifdef DEBUG
	std::cout<<std::filesystem::current_path()<<std::endl;
#endif

	//read the price info file.
	BTF::SecurityInfo l_PriceInfo;
	const char* l_sfileName {"Nifty500.csv"};

	std::cout<<l_sfileName<<std::endl;
	if(BTF::CSVReader::ParseData(l_sfileName, l_PriceInfo))
	{
#ifdef DEBUG
		//For Debug - Print individual values
		/*
		std::cout<<"Stored value ------>>"<<std::endl;
		
		for(const auto& val: l_PriceInfo.date)
		{			
			std::cout<<"Date: "<<val<<std::endl;
		}
		for(const auto& val: l_PriceInfo.open)
		{			
			std::cout<<"Open: "<<val<<std::endl;
		}
		for(const auto& val: l_PriceInfo.high)
		{			
			std::cout<<"High: "<<val<<std::endl;
		}
		for(const auto& val: l_PriceInfo.low)
		{			
			std::cout<<"Low: "<<val<<std::endl;
		}
		for(const auto& val: l_PriceInfo.close)
		{			
			std::cout<<"Close: "<<val<<std::endl;
		}
		for(const auto& val: l_PriceInfo.volume)
		{			
			std::cout<<"Volume: "<<val<<std::endl;
		}
		*/
#endif
		assert(l_PriceInfo.m_uSize > 0);

		
		//TODO: INIT: set config values for the indicators. Ideally, this should be provided in some .ini or xml file
		BTFI::AbsoluteStrength l_Abs{BTF::eSource::CLOSE, 2U, 2U, 2U, -101, 52U, 52U, 52U, 101};
		//Volume (eSource::VOLUME);
		//BaseLine (eSource::OHLC4);

		//TODO: At the end of parsing we will loop over the l_lTradeDirectionInfo to figure out at what price levels we are entering / exiting the trade
		//We will also calculate the other parameters like - gross profit / loss, win%, win count, total count, max draw-down, total bars in winning / loosing trade and what not.
		std::list<BTF::TradeDirectionInfo> l_lTradeDirectionInfo;
			
		//for each of the setting variable, we will calculate the performance of the indicator on particular setting
		//then use those settings in decreasing order of performance to figure out the performance of next indicator
		//and so on till we find the optimal setting for the trading.
		for (unsigned int baseLength = l_Abs.m_uStartBaseLength; baseLength < l_Abs.m_uEndBaseLength; baseLength++)
		{
			for (unsigned int basePower = l_Abs.m_uStartBasepower; basePower < l_Abs.m_uEndBasepower; basePower++)
			{
				for (unsigned int signalLength = l_Abs.m_uStartSignalLength; signalLength < l_Abs.m_uEndSignalLength; signalLength++)
				{
					for (int startPhase = l_Abs.m_nStartPhase; startPhase < l_Abs.m_nEndPhase; startPhase++)
					{
						//TODO: add further indicators LIKE BASELINE, C2, V1, V2.
						/*
						for (unsigned int cyclePeriod = KAMA.m_uStartCyclePeriod; cyclePeriod < KAMA.m_uEndCyclePeriod; cyclePeriod++)
						{
							for (unsigned int fastEnd = KAMA.m_uStartFastEnd; baseLength < KAMA.m_uEndBaseLength; baseLength++)
							{					
								*/

								for (unsigned int i = 0U; i<l_PriceInfo.m_uSize; i++)
								{
									BTF::TradeDirectionInfo l_TradeDirectionInfo;
									
									l_TradeDirectionInfo.m_bUsable = true;

									float l_fC1SrcVal = BTFH::GetSourceValue(l_PriceInfo, i, l_Abs.GetSource());
									l_TradeDirectionInfo.m_eC1 = l_Abs.Execute(l_fC1SrcVal,
																				baseLength,
																				basePower,
																				signalLength,
																				startPhase);
									/*
									float l_fV1SrcVal = GetSourceValue(l_PriceInfo, i, Volume1Indicator.GetSource());
									l_TradeDirectionInfo.m_eV1 = Volume1Indicator.Execute(l_fC1SrcVal
									
									and other like baseline, c2, e.
									*/

									BTFH::DetermineTradeDirectionBasedOnIndicatorSetup(l_TradeDirectionInfo);

									l_lTradeDirectionInfo.push_back(l_TradeDirectionInfo);
								}
							//}
						//}
					}
				}
			}		
		}

		if(!l_lTradeDirectionInfo.empty())
		{
			for(auto val : l_lTradeDirectionInfo)
			{
				BTFH::DetermineTradeDirectionBasedOnUserDefinedRules(val);
			}
		}
	}
	else
	{
		std::cout<<"main - failed to parse: "<<l_sfileName<<std::endl;
	}

	return 0;
}

