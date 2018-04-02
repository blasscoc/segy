
#include <traces.h>


int open_traces(const std::string filename, std::ifstream& segy)
{}

int rewind_trace(std::ifstream& segy, int trace_offset=0, int ensemble_offset=0)
{}

int read_trace_header(std::ifstream& segy, TraceHeader& hdr, bool byteswap=1)
{}

int read_trace_data(std::ifstream& segy, TraceData& data, bool byteswap=1)
{}

int read_trace(std::ifstream& segy, Trace& trace, bool byteswap=1)
{}

int read_ensemble_headers(std::ifstream& segy, std::vector<TraceHeader>& hdrs,
			  bool byteswap=1)
{}

int read_ensemble_data(std::ifstream& segy, std::vector<TraceData>& data,
		       bool byteswap=1)
{}

int read_ensemble(std::ifstream& segy, std::vector<Trace>& traces,
		  bool byteswap=1)
{}
 
