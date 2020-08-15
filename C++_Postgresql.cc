#include<iostream>
#include<fstream>
#include<ostream>
#include<algorithm>
#include<string>
#include<postgresql/libpq-fe.h>
using namespace std;


bool has_only_spaces(const string& str)
{
	return str.find_first_not_of(' ') == str.npos;
}

int main()
{
	string file,input,s;
	fstream ifile;

	PGconn *PQConnectdb(const char * conninfo);
	PGconn *db = PQconnectdb("host = 'courses' dbname = 'z1851660' password ='1994Oct29'");			        
	if(!(CONNECTION_OK == PQstatus(db)))				        
	{			
		cout<<"error"<<endl;		
		return -1;				
	}			
	else	
	{		
		cout<<"connected";


		cout<<"Do you want to input RTC file:"<<endl;
		cin>>input;

		while(input == "y")
		{

			cout<<"Enter name of file:"<<endl;
			cin>>file;

			ifile.open(file);

			if(ifile.is_open())
			{
				while(getline(ifile,s))
				{

					string year,code,region_type,region_name;
					string _code;

					year = s.substr(10,4);


					if(year != "1990")
					{
						region_name  = s.substr(52,60);
						region_type = s.substr(24,1);
						if(region_type == "S" || region_type == "C" ||region_type == "M" || region_type == "P")
						{
							if(region_type == "S")
							{
								string v = s.substr(5,2);
								if(v.length() == 0)
								{
								}
								else
								{
									code = v;
								}
							}
							else if(region_type == "C")
							{
								string v = s.substr(7,3);
								if(v.length() == 0)
								{
								}
								else
								{
									code = v;
								}
							}
							else if(region_type == "M"|| region_type == "P")
							{
								string v = s.substr(5,2) +""+ s.substr(14,5);

								if(v.length() == 0)
								{
								}
								else
								{
									code = v;
								}
							}


							if(!has_only_spaces(code))
							{
								_code = code;
							}
							string id = _code;

							string query;
							query = "insert into z1851660.Region(id,iname,region_type) values('"+ id +"','"+ region_name +"','"+ region_type +"');";
							PQexec(db,query.c_str());

						}
					}
				}
			}
			else
			{
				cerr<<"file can't be opened";
				exit(EXIT_FAILURE);
			}

			ifile.close();

			cout<<"Do you want to input file(y/n)"<<endl;

			cin>>input;
		}

		cout<<"do you want to input bound files:(y/n)"<<endl;
		cin>>input;

		while(input == "y")
		{
			cout<<"Enter name of bound file:"<<endl;
			cin>>file;

			ifile.open(file);
			if(ifile.is_open())
			{
				while(getline(ifile,s))
				{
					string bnd_code,min_lat,min_lon,max_lat,max_lon;
					
					bnd_code = s.substr(0,7);
					min_lon = s.substr(7,10);
					min_lat = s.substr(17,9);
					max_lon = s.substr(26,10);
					max_lat = s.substr(36,9);

					string query1;
					PGresult * result = nullptr;

					query1 = "UPDATE Region set min_latitute ='"+ min_lat +"',max_latitude = '"+ max_lat +"',min_longitude = '"+ min_lon +"',max_longitude='"+ max_lon +"' where id ="+ bnd_code +";";

					result = PQexec(db,query1.c_str());
					PQclear(result);
				}


			}
			else
			{
				cerr<<"file can't be opened";
				exit(EXIT_FAILURE);
			}

			ifile.close();

			cout<<"Do you want to input bound file(y/n)"<<endl;

			cin>>input;


		}
	}

	PQfinish(db);

	return 0;

}



