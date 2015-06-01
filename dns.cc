#include "lib.h"
#include "dns.h"
Dns::Dns(const string& hostname)
{
	struct hostent* dns=gethostbyname(hostname.c_str());
	if(!dns){
		string wrong("DNS Parse Wrong: ");
		switch(h_errno){
			case HOST_NOT_FOUND:
				wrong=wrong+hostname.c_str()+" is unknown. ";
				errorExit(wrong.c_str());
				break;
			case NO_ADDRESS:
				wrong=wrong+hostname.c_str()+" is valid, but does not have IP address. ";
				errorExit(wrong.c_str());
				break;
			case NO_RECOVERY:
				wrong=wrong+hostname.c_str()+" Nonrecoverable name server error occurred. ";
				errorExit(wrong.c_str());
				break;
			case TRY_AGAIN:
				wrong=wrong+hostname.c_str()+" Try Again later. ";
				errorExit(wrong.c_str());
				break;
			default:
				wrong=wrong+hostname.c_str()+" Unkown reasion";
				errorExit(wrong.c_str());
				break;
		}
	}
	for(char** s=dns->h_addr_list;*s!=nullptr;++s){
		char*str=inet_ntoa(*(struct in_addr*)*s);
		ip4_list.push_back(str);
	}
}
const vector<string>& Dns::data()const
{
	return ip4_list;
}