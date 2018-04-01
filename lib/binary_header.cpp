
#include <binary_header.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <string.h>

static short int byteswap(short int big)
{
  // high byte / low byte
  return (big & 0xff00) >> 8 | (big & 0xff);
}

static unsigned short int byteswap(unsigned short int big)
{
  // high byte / low byte
  return (big & 0xff00) >> 8 | (big & 0xff);
}

static int byteswap(int big)
{
  return (big & 0x000000FF) << 24 | (big & 0x0000FF00) << 8 | (big & 0x00FF0000) >> 8 | (big & 0xFF000000) >> 24;
}

void byteswap(BinaryHeader& bhdr)
{
  bhdr.jobid = byteswap(bhdr.jobid);
  bhdr.line_number = byteswap(bhdr.line_number);
  bhdr.reel_number = byteswap(bhdr.reel_number);

  bhdr.number_traces_per_ensemble = byteswap(bhdr.number_traces_per_ensemble);
  bhdr.number_aux_traces_per_ensemble = byteswap(bhdr.number_aux_traces_per_ensemble);

  bhdr.sample_interval_micro_sec = byteswap(bhdr.sample_interval_micro_sec);
  bhdr.original_sample_interval_micro_sec = byteswap(bhdr.original_sample_interval_micro_sec);  

  bhdr.num_of_samples_per_trace = byteswap(bhdr.num_of_samples_per_trace);
  bhdr.origial_num_of_samples_per_trace = byteswap(bhdr.origial_num_of_samples_per_trace);

  bhdr.data_sample_format = byteswap(bhdr.data_sample_format);
  bhdr.ensemble_fold = byteswap(bhdr.ensemble_fold);
  bhdr.trace_sorting = byteswap(bhdr.trace_sorting);
  
  bhdr.vertical_sum_code = byteswap(bhdr.trace_sorting);
  bhdr.min_sweep_freq_hz = byteswap(bhdr.min_sweep_freq_hz);
  bhdr.max_sweep_freq_hz = byteswap(bhdr.max_sweep_freq_hz);
  
  bhdr.sweep_length_ms = byteswap(bhdr.sweep_length_ms);
  bhdr.sweep_type_code = byteswap(bhdr.sweep_type_code);
  
  bhdr.trace_number_sweep_channel = byteswap(bhdr.trace_number_sweep_channel);
  bhdr.min_sweep_trace_taper_length_hz = byteswap(bhdr.min_sweep_trace_taper_length_hz);
  bhdr.max_sweep_trace_taper_length_hz = byteswap(bhdr.max_sweep_trace_taper_length_hz);
  
  bhdr.sweep_taper_type = byteswap(bhdr.sweep_taper_type);
  bhdr.is_correlated_data_traces = byteswap(bhdr.is_correlated_data_traces);
  bhdr.is_binary_gain_recovered = byteswap(bhdr.is_binary_gain_recovered);
  bhdr.amplitude_recovery_method = byteswap(bhdr.amplitude_recovery_method);
  bhdr.units = byteswap(bhdr.units);
  bhdr.impulse_signal_polarity = byteswap(bhdr.impulse_signal_polarity);
  bhdr.revision_number = byteswap(bhdr.revision_number);
  bhdr.fixed_trace_length = byteswap(bhdr.fixed_trace_length);
  bhdr.num_extended_file_headers = byteswap(bhdr.num_extended_file_headers);
}


void print_bhdr(const BinaryHeader& bhdr)
{
  std::cout << "jobid : " << bhdr.jobid << std::endl;
  std::cout << "line_number : " << bhdr.line_number << std::endl;
  std::cout << "reel_number : " <<  bhdr.reel_number << std::endl;
  std::cout << "number_traces_per_ensemble : " <<  bhdr.number_traces_per_ensemble << std::endl;
  std::cout << "number_aux_traces_per_ensemble : " << bhdr.number_aux_traces_per_ensemble << std::endl;
  std::cout << "sample_interval_micro_sec : " << bhdr.sample_interval_micro_sec << std::endl;
  std::cout << "original_sample_interval_micro_sec : " << bhdr.original_sample_interval_micro_sec << std::endl;
  std::cout << "num_of_samples_per_trace : " << bhdr.num_of_samples_per_trace << std::endl;
  std::cout << "origial_num_of_samples_per_trace : " << bhdr.origial_num_of_samples_per_trace << std::endl;
  std::cout << "data_sample_format : " << bhdr.data_sample_format << std::endl;
  std::cout << "ensemble_fold : " << bhdr.ensemble_fold << std::endl;
  std::cout << "trace_sorting : " << bhdr.trace_sorting << std::endl;
  std::cout << "vertical_sum_code : " << bhdr.vertical_sum_code << std::endl;
  std::cout << "min_sweep_freq_hz : " << bhdr.min_sweep_freq_hz << std::endl;
  std::cout << "max_sweep_freq_hz : " << bhdr.max_sweep_freq_hz << std::endl;
  std::cout << "sweep_length_ms : " << bhdr.sweep_length_ms << std::endl;
  std::cout << "sweep_type_code : " << bhdr.sweep_type_code << std::endl;
  std::cout << "trace_number_sweep_channel : " << bhdr.trace_number_sweep_channel << std::endl;
  std::cout << "min_sweep_trace_taper_length_hz : " << bhdr.min_sweep_trace_taper_length_hz << std::endl;
  std::cout << "max_sweep_trace_taper_length_hz : " << bhdr.max_sweep_trace_taper_length_hz << std::endl;
  std::cout << "sweep_taper_type : " << bhdr.sweep_taper_type << std::endl;
  std::cout << "is_correlated_data_traces : " << bhdr.is_correlated_data_traces << std::endl;
  std::cout << "is_binary_gain_recovered : " << bhdr.is_binary_gain_recovered << std::endl;
  std::cout << "amplitude_recovery_method : " << bhdr.amplitude_recovery_method << std::endl;
  std::cout << "units : " << bhdr.units << std::endl;
  std::cout << "impulse_signal_polarity : " << bhdr.impulse_signal_polarity << std::endl;
  std::cout << "revision_number : " << bhdr.revision_number << std::endl; // hopefully 0 or 1
  std::cout << "fixed_trace_length : " << bhdr.fixed_trace_length << std::endl;
  std::cout << "num_extended_file_headers : " << bhdr.num_extended_file_headers << std::endl;
}

BinaryHeader read_binary_header(std::string filename, bool bswap)
{
  std::ifstream segy(filename, std::ifstream::in);
    
  if(!segy.good())
    {
      throw std::runtime_error("file " + filename + " does not exist\n");
    }

  segy.seekg(0, segy.end);
  int length = segy.tellg();
  segy.seekg(0, segy.beg);
  
  if(length < 3600)
    {
      throw std::runtime_error(
	"file " + filename + " does not contain at least 3600 "
	"bytes for the ebcdic and binary headers.");      
    }

  char bhdrp[400];
  BinaryHeader bhdr;

  segy.ignore(3200);
  segy.read(bhdrp, 400);
  
  memcpy(&bhdr, bhdrp, sizeof(bhdr));
  if(bswap)
    {
      byteswap(bhdr);
    }
  return bhdr;
}

