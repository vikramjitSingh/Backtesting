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
	};

	class CSVReader
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
					std::cout<<"Failed to open file: " << si_fileName<<std::endl;
				}

				return (!l_bFileMisformed);
			}
	};
}

int main()
{
	BTF::SecurityInfo l_PriceInfo;
	const char* l_sfileName {"Nifty500.csv"};

	std::cout<<l_sfileName<<std::endl;
	if(BTF::CSVReader::ParseData(l_sfileName, l_PriceInfo))
	{
		std::cout<<"Stored value ------>>"<<std::endl;
		/*for(int i= 0; i<l_PriceInfo.open.size(); i++)
		{
			std::cout<<l_PriceInfo.date[i]<<", "
					<<l_PriceInfo.open[i]<<", "
					<<l_PriceInfo.high[i]<<", "
					<<l_PriceInfo.low[i]<<", "
					<<l_PriceInfo.close<<", "
					<<l_PriceInfo.volume[i]<<std::endl;
		}*/
		for(const auto& val: l_PriceInfo.date)
		{
			std::cout<<val<<std::endl;
		}
	}
	else
	{
		std::cout<<"main - failed to parse: "<<l_sfileName<<std::endl;
	}

	return 0;
}

