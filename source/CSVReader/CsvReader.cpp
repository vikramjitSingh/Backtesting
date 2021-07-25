/*
 *this class i meant to read the csv files containing securities data and parse it to SecurityInfo data structure.
 *
 * */

#include <vector>
#include<fstream>
#include<iostream>
#include<string>

namespace BTF
{
	class SecurityInfo
	{
		public:
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
						bool l_bParseHeader {false};

						while ( (!l_bFileMisformed) && (l_pos = l_line.find(l_delimiter)) != std::string::npos ) 
						{
							if(l_columnCount == 0)
							{
								l_token = l_line.substr(0, l_pos);
								std::cout << l_token << std::endl;
								if(l_bParseHeader && "Date" == l_token)
								{
									l_line.erase(0, l_pos + l_delimiter.length());
								}
								else
								{
									l_bFileMisformed = true;
									std::cout<<"first line of the file should contain the header: Date"<<std::endl;
								}

								l_columnCount++;
							}
							else if(l_columnCount == 1)
							{
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "Open" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }

								l_columnCount++;
							} 
							else if(l_columnCount == 2)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "High" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }

								l_columnCount++;
                                                        }
							else if(l_columnCount == 2)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "High" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }

								l_columnCount++;
                                                        }
							else if(l_columnCount == 3)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "Low" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }
						
								l_columnCount++;
                                                        }
							else if(l_columnCount == 4)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "Close" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }

								l_columnCount++;
                                                        }
							else if(l_columnCount == 5)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "Adj Close" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }

								l_columnCount++;
                                                        }
							else if(l_columnCount == 6)
                                                        {
                                                                l_token = l_line.substr(0, l_pos);
                                                                std::cout << l_token << std::endl;
                                                                if(l_bParseHeader && "High" == l_token)
                                                                {
                                                                        l_line.erase(0, l_pos + l_delimiter.length());
                                                                }
                                                                else
                                                                {
                                                                        l_bFileMisformed = true;
                                                                        std::cout<<"first line of the file should contain the header: Open"<<std::endl;
                                                                }
								
								l_columnCount = 0; //reset column count for next iteration
                                                        }
							else
                                                        {
								l_columnCount++;
                                                                l_bFileMisformed = true;
                                                                std::cout<<"Unexpeced column size: "<< l_columnCount<<std::endl;
                                                        }
						}

					}

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

