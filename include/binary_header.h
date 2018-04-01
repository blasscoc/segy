
#ifndef BINARY_HEADER_H
#define BINARY_HEADER_H

#include <string>

// The REV 1 definitions of the file binary header
struct BinaryHeader
{
  int jobid;
  int line_number;
  int reel_number;

  short int number_traces_per_ensemble;
  short int number_aux_traces_per_ensemble;
  short int sample_interval_micro_sec;
  short int original_sample_interval_micro_sec;
  
  short int num_of_samples_per_trace;
  short int origial_num_of_samples_per_trace;

  // This is where the wheels fall off (almost always ibm float in practice)
  unsigned short int data_sample_format;
  // 1 - IBM float (default)
  // 2 - 4-byte two's complement int
  // 3 - 2-byte two's complement int
  // 4 - 4-byte fixed point with gain
  // 5 - 4-byte IEEE float (single precision)
  // 6 - N/A
  // 7 - N/A
  // 8 - 1-byte two's complement int

  short int ensemble_fold;
  
  // -1 - Other detailed in extended header
  // 0 - Unknown
  // 1 - As recording (no sorting)
  // 2 - CDP ensemble
  // 3 - Single fold continuous profile
  // 4 - Horizontally stacked
  // 5 - Common source point
  // 6 - Common receiver point
  // 7 - Common offset point
  // 8 - Common mid-point
  // 9 - Common conversion point
  short int trace_sorting;

  short int vertical_sum_code;

  short int min_sweep_freq_hz;
  short int max_sweep_freq_hz;
  short int sweep_length_ms;

  // 1 - linear
  // 2 - parabolic
  // 3 - exponential
  // 4 - other
  short int sweep_type_code;
  short int trace_number_sweep_channel;
  short int min_sweep_trace_taper_length_hz;
  short int max_sweep_trace_taper_length_hz;

  // 1 - linear
  // 2 - cosine squared
  // 3 - other
  short int sweep_taper_type;

  short int is_correlated_data_traces;
  short int is_binary_gain_recovered;

  // 1 - none
  // 2 - spherical divergence
  // 3 - AGC
  // 4 - other
  short int amplitude_recovery_method;

  // 1 - meters
  // 2 - feet
  short int units;

  // Seismic signal lags pilot signal by:
  // 1 - 337.5 to 22.5 degrees
  // 2 - 22.5 to 67.5 degrees
  // 3 - 67.5 to 112.5 degrees
  // 4 - 112.5 to 157.5 degrees
  // 5 - 157.5 to  202.5 degrees
  // 6 - 202.5 to 247.5 degrees
  // 7 - 247.5 to 292.5 degrees
  // 8 - 292.5 to 337.5 degrees
  short int impulse_signal_polarity;
  
  // Really gets messy here
  char unassigned1[240];

  // segy rev 1 manual says it's unsigned
  unsigned short int revision_number; // hopefully 0 or 1

  // 0 - no fixed length
  // trace length otherwise
  short int fixed_trace_length;

  // The segy format consists of an 3200-byte header (EBCDIC format),
  // followed by this 400-byte file header then 0 or more 3200-byte
  // headers in (EBCDIC format).
  // -1 - A variable number, terminated by a SEG:EndText on the first
  //      line of the last extended header.
  //  N - the number of extended headers
  short int num_extended_file_headers;

  //
  char unassigned2[94];
};

void print_bhdr(const BinaryHeader& bhdr);
// segy stores data that is in big-endian format.
// The Intel hegemony means everything is little endian now pretty much.
void byteswap(BinaryHeader& bhdr);
BinaryHeader read_binary_header(std::string filename,
				bool bswap=true);


#endif

