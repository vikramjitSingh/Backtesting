/*
 *this class i meant to read the csv files containing securities data and parse it to SecurityInfo data structure.
 *
 * */

#include <vector>
#include<fstream>
#include<iostream>
#include<string>
#include <bits/stdc++.h>

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
	
	class TradeDirectionInfo
	{
		public:
		eTradeDirection m_eC1{eTradeDirection::INDECISION};
		eTradeDirection m_eV1{eTradeDirection::INDECISION};
		eTradeDirection m_eB {eTradeDirection::INDECISION};
		eTradeDirection m_eC2{eTradeDirection::INDECISION};
		eTradeDirection m_eV2{eTradeDirection::INDECISION};
		eTradeDirection m_eE {eTradeDirection::INDECISION};		
	};
	
	typedef std::vector<TradeDirectionInfo> vTradeDirectionInfo;
	
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
		SHORT = -1;
		INDECISION = 0,
		LONG = 1
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
	
	namespace Helpers
	{
		float PartialCalculateAbssio(const float& ci_fCurrentSourceLevel, 
										const float& ci_fPreviousSourceLevel, const unsigned int& ci_cosl
										float& io_fA1, float& io_fM1, float& io_fD1
									)
		{
			auto l_fA { io_fA1 };						
			io_fA1 = ( ci_fCurrentSourceLevel>ci_fPreviousSourceLevel) ? 
						( (l_fA1) + (ci_fCurrentSourceLevel/ci_fPreviousSourceLevel) - 1) : l_fA;
			
			auto l_fM { io_fM1 };
			io_fM1 = ( ci_fCurrentSourceLevel==ci_fPreviousSourceLevel) ? (l_fM + 1.0 / ci_cosl) : l_fM;
			
			auto l_fD { io_fD1 };
			io_fD1 = ( ci_fCurrentSourceLevel<ci_fPreviousSourceLevel) ? l_fD + (ci_fPreviousSourceLevel/ci_fCurrentSourceLevel)-1 : l_fD;
			
			return ( io_fD1 + io_fM1 / 2 == 0) ?  1 :  1 - (1 / ( 1+ ( io_fA1 + io_fM1 / 2 ) / ( io_fD1 + io_fM1 / 2 ) ) )
		}
		
		//does not support date or string
		float GetSourceValue(const SecurityInfo& ci_PriceInfo, const unsigned int ci_index, const eSource& ci_eSource)
		{
			float l_fVal {0.0f};
			
			switch (ci_eSource)
			{
				case eSource::OPEN:
					l_fVal = l_PriceInfo.open[ci_index];					
				case eSource::HIGH:
					l_fVal = l_PriceInfo.high[ci_index];
				case eSource::LOW:
					l_fVal = l_PriceInfo.low[ci_index];
				case eSource::CLOSE:
					l_fVal = l_PriceInfo.close[ci_index];
				case eSource::VOLUME:
					l_fVal = l_PriceInfo.volume[ci_index];
				case eSource::HL2:
					l_fVal = (l_PriceInfo.high[ci_index] + l_PriceInfo.low[ci_index])/2;
				case eSource::OHLC4:
					l_fVal = (l_PriceInfo.open[ci_index] + l_PriceInfo.high[ci_index] + 
								l_PriceInfo.low[ci_index] + l_PriceInfo.close[ci_index])/4;
				default:
					l_fVal = 0.0f;
					std::cout<<std::endl<<"unknown source type"<<std::endl;
			}
			return l_fVal;
		}
	}
	namespace Indicators
	{
		class JurichMovingAverage //:IMovingAverage
		{
			public:
			float m_fJMA {0.0f};
			float m_fE0 {0.0f};
			float m_fE1 {0.0f};
			float m_fE2 {0.0};
			
			float Execute (const eSource& ci_source, 
							const unsigned int ci_baseLength,
							const unsigned int ci_basepower
							int i_uPhase)
			{
				length = ci_baseLength;
				phase = i_uPhase;
				power = ci_basepower;
				
				phaseRatio = (phase < -100) ? 0.5 : (phase > 100) ? 2.5 : (phase / 100 + 1.5);
				jbeta = 0.45 * (length - 1) / (0.45 * (length - 1) + 2);
				jalpha = pow(jbeta, power);
				
				auto jma = m_fJMA;
				
				auto e0 = m_fE0;
				m_fE0 = (1 - jalpha) * src + jalpha * e0);
				
				auto e1 = m_fE1;
				m_fE1 = (src - m_fE0) * (1 - jbeta) + jbeta * e1);
				
				auto e2 = m_fE2;
				e2 = (m_fE0 + phaseRatio * m_fE1 - jma) * pow(1 - jalpha, 2) + pow(jalpha, 2) * e2);
				
				m_fJMA = e2 + jma;
			}
		};
		
		class AbsoluteStrength //:IIndicators
		{
			private:
			//the data members will store the previous values respctively
			float m_fA1  {0.0f};
			float m_fM1  {0.0f};
			float m_fD1  {0.0f};
			float m_fMT1 {0.0f};
			float m_fUT1 {0.0f};
			float m_fPrevPriceLevel {0.0f};
			eSource m_eSource {eSource::INDECISION};
			
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
			m_uStartBaseLength	{l_uStartBaseLength};
			m_uStartBasepower	{l_uStartBasepower};
			m_uStartSignalLength{l_uStartSignalLength};
			m_nStartPhase 		{l_nStartPhase};
			m_uEndBaseLength	{l_uEndBaseLength};
			m_uEndBasepower		{l_uEndBasepower};
			m_uEndSignalLength	{l_uEndSignalLength};
			m_nEndPhase			{l_nEndPhase}
			
			//dtor
			~AbsoluteStrength() {}
		
			eSource GetSource () const { return m_eSource;}
			eTradeDirection Execute(const float& ci_fCurrentPriceLevel, 
									const unsigned int ci_uBaseLength,
									const unsigned int ci_uBasepower,
									const unsigned int ci_uSignalLength,
									int i_nPhase)
			{
				//there are no changes in results beause of this so, we will keep it as defined constant.
				const unsigned int cosl { 10 };
				
				auto abssi {PartialCalculateAbssio(ci_fCurrentPriceLevel, m_fPrevPriceLevel, cosl, 
													m_fA1, m_fM1, m_fD1) };
													
				auto abssio = { abssi - m_JMA.Execute(abssi, ci_uBaseLength, ci_uBasepower, i_nPhase) };
				
				alp { 2.0/(ci_uSignalLength+1) };

				auto mt { m_fMT1 };
				m_fMT1 = alp * abssio + (1-alp) * mt;

				auto ut { m_fUT1 };
				m_fUT1 = alp * m_fMT1 + (1-alp) * ut;
				
				auto s { ( ( 2 - alp ) * m_fMT1 - m_fUT1 ) / (1-alp) };
				
				auto d { abssio-s };
				
				m_fPrevPriceLevel = ci_fCurrentPriceLevel;
				
				return { abssio > 0 ? abssio >= s ? LONG : INDECISION : abssio <=s ? SHORT : INDECISION};
			}
		};	
	}
}


int main()
{
	//read the price info file.
	BTF::SecurityInfo l_PriceInfo;
	const char* l_sfileName {"Nifty500.csv"};

	std::cout<<l_sfileName<<std::endl;
	if(BTF::CSVReader::ParseData(l_sfileName, l_PriceInfo))
	{
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
		assert(l_PriceInfo.m_uSize > 0);
		
		//INIT: set config values for the indicators. Ideally, this should be provided in some .ini or xml file
		AbsoluteStrength (eSource::CLOSE, 2, 2, 2, -101, 52, 52, 52, 101);
		//Volume (eSource::VOLUME);
		//BaseLine (eSource::OHLC4);		
			
		//for each of the setting variable, we will calculate the performance of the indicatoron particular setting
		//then use those settings in decreasing order of performance to figure out the performance of next indicator
		//and so on till we find the optimal setting for the trading.
		for (unsigned int baseLength = AbsoluteStrength.m_uStartBaseLength; baseLength < AbsoluteStrength.m_uEndBaseLength; baseLength++)
		{
			for (unsigned int basePower = AbsoluteStrength.m_uStartBasepower; basePower < AbsoluteStrength.m_uEndBasepower; basePower++)
			{
				for (unsigned int signalLength = AbsoluteStrength.m_uStartSignalLength; signalLength < AbsoluteStrength.m_uEndSignalLength; signalLength++)
				{
					for (int startPhase = AbsoluteStrength.m_nStartPhase; startPhase < AbsoluteStrength.m_nEndPhase; startPhase++)
					{
						//TODO: add further indicators LIKE BASELINE, C2, V1, V2.
						/*
						for (unsigned int cyclePeriod = KAMA.m_uStartCyclePeriod; cyclePeriod < KAMA.m_uEndCyclePeriod; cyclePeriod++)
						{
							for (unsigned int fastEnd = KAMA.m_uStartFastEnd; baseLength < KAMA.m_uEndBaseLength; baseLength++)
							{					
								*/
								//TODO: If entry then calculate the trading info like - profit, loss, drawdown, etc.
								//int l_nPositionSize {0};
								//eTradeDirection l_eLongEntry {eTradeDirection::INDECISION};
								//eTradeDirection l_eLongClose {eTradeDirection::INDECISION};
								
								for (unsigned int i = 0U; i<l_PriceInfo.m_uSize; i++)
								{
									TradeDirectionInfo l_TradeDirectionInfo;
									
									float l_fC1SrcVal = GetSourceValue(l_PriceInfo, i, AbsoluteStrength.GetSource());
									l_TradeDirectionInfo.m_eC1 = AbsoluteStrength.Execute(l_fC1SrcVal, 
																						l_uBaseLength,
																						l_uBasepower,
																						l_uSignalLength,
																						i_nPhase);
									/*
									float l_fV1SrcVal = GetSourceValue(l_PriceInfo, i, Volume1Indicator.GetSource());
									l_TradeDirectionInfo.m_eV1 = Volume1Indicator.Execute(l_fC1SrcVal
									
									and other like baseline, c2, e.
									*/
									vTradeDirectionInfo.pushback(l_TradeDirectionInfo);
								}
							//}
						//}
					}
				}
			}		
		}
	}
	else
	{
		std::cout<<"main - failed to parse: "<<l_sfileName<<std::endl;
	}

	return 0;
}

