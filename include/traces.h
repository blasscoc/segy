

#ifndef TRACES_H
#define TRACES_H

#include <string>
#include <vector>
#include <fstream>

// Traces consist of a 240-byte header followed by binary data.
// The binary data is typically stores in a 32-bit ibm-float
// format.
struct TraceHeader
{
  // starts with at 1
  int seq_no_within_line;
  int seq_no_within_file;
  
  int original_field_record_no;
  int original_field_seq_no;

  int energy_source_point;
  // The binary header defines the number of ensembles,
  // defines a gather of some sort (cdp, cmp etc)
  int ensemble_number;
  // starts at 1
  unsigned short int seq_no_within_ensemble;


  // Trace identification code*
  // *probably redundant, why put different data in a single file.
  // -1 - Other
  //  0 - Unknown
  //  1 - Seismic data
  //  2 - Dead
  //  3 - Dummy
  //  4 - Time Break
  //  5 - Uphole
  //  6 - Sweep
  //  7 - Timing
  //  8 - Waterbreak
  //  9 - Near-field gun signature
  // 10 - Far-field gun signature
  // 11 - Seismic pressure sensor
  // 12 - Multicomponent seismic sensor (Vertical)
  // 13 - Multicomponent seismic sensor (Cross-line)
  // 14 - Multicomponent seismic sensor (Inline)
  // 15 - Rotated Multicomponent seismic sensor (Vertical)
  // 16 - Rotated Multicomponent seismic sensor (Transverse)
  // 17 - Rotated Multicomponent seismic sensor (Radial)
  // 18 - Vibrator reaction mass
  // 19 - Vibrator base plate
  // 20 - Vibrator estimated ground force
  // 21 - Vibrator reference
  // 22 - Time-velocity pairs
  // 23 .. N - Custom
  short int trace_id_code;

  // if a stack
  short int num_vertically_summed_traces;
  short int num_horizontally_summed_traces;

  // Data use
  // 0 - Production
  // 1 - Test
  short int data_use;

  // Distance from source point to center of receiver group
  // -ve is opposite direction
  short int dist_src_to_recvr;

  short int recvr_group_elevation;
  short int src_elevation;
  unsigned short int src_depth_below_surface;

  short int datum_elevation_rcvr_group;
  short int datum_elevation_src;

  short int water_depth_at_src;
  short int water_depth_at_group;

  // 10**value scales depths and elevations
  short int scalar_to_apply_elevation_depth;
  short int scalar_to_apply_coords;

  // source coordinate system should be defined in
  // extended header. X is "longitude", Y is "latitude".
  short int src_coord_x;
  short int src_coord_y;
  short int group_coord_x;
  short int group_coord_y;

  // Coordinate units
  // 1 - length (meters or feet)
  // 2 - seconds of arc
  // 3 - decimal degrees
  // 4 - degrees in minutes
  short int coord_units;

  short int weathering_velocity;
  short int subweathering_velocity;

  short int uphole_time_at_src_ms;
  short int uphole_time_at_group_ms;

  short int static_src_correction_ms;
  short int static_group_correction_ms;
  short int static_applied_ms;

  //Time ms between end of 240-byte trace header and
  //time break
  short int lag_time_A;
  // Time ms between time break and initiation time
  short int lag_time_B;

  // Delay between initiation of energy source and recording
  short int delay_recording_ms;

  short int start_mute_time_ms;
  short int end_mute_time_ms;

  // SUPER IMPORTANT
  // Hopefully common to file headers and constant
  // to all traces
  short int number_samples_in_trace;
  // If the trace length is defined in binary headers, sample
  // interval and num samples must be invariant.
  short int sample_interval_ms;

  // Gain of field intruments
  // 1 - fixed
  // 2 - binary
  // 3 - floating point
  // 4 ... N - anything really
  short int instrument_gain_type;
  short int instrument_gain_constant_db;
  short int instrument_intitial_gain_db;

  // is correlated (? probably the vibroseis)
  // 1 - no
  // 2 - yes
  short int correlated;

  short int start_sweep_freq_hz;
  short int end_sweep_freq_hz;
  short int sweep_length_ms;

  // sweep type
  // 1 - linear
  // 2 - parabolic
  // 3 - exponential
  // 4 - other
  short int sweep_type;

  short int start_trace_taper_length_ms;
  short int end_trace_taper_length_ms;

  // taper type
  // 1 - linear
  // 2 - cosine squared
  // 3 - other
  short int taper_type;
  
  short int alias_filter_hz;
  short int alias_slope_db_per_octave;
  short int notch_filter_freq_hz;
  short int notch_filter_slope_db_per_octave;
  short int low_cut_freq_hz;
  short int high_cut_freq_hz;
  short int low_cut_slope_db_per_octave;
  short int high_cut_slope_db_per_octave;

  short int year_record_date;
  short int day_of_year;
  short int hour_of_day;
  short int second_of_minute;

  // time basis
  // 1 - local
  // 2 - GMT
  // 3 - Other
  // 4 - 4 UTC
  short int time_basis;

  // defined as 2^-N volts
  short int trace_weighting_factor;

  short int geoph_group_num_of_roll_switch;
  short int geoph_group_num_of_first_trace;
  short int geoph_group_num_of_last_trace;

  // number of groups dropped
  short int gap_size;

  // travel associated with taper
  // 1 - down
  // 2 - up
  short int travel_taper;

  // x,y coords of cdp position.
  // Doesn't specify what x,y are, supposed to be defined in
  // Location Data stanza of extended header.
  // The ebcdic header might also say, teapot dome specifies
  // x as inline, y as xline.
  int x_coord;
  int y_coord;

  int inline_num;
  int xline_num;
  int shot_num;

  // Applied to get real number +ve is multiply,
  // -ve implies division.
  short int scalar_to_apply_to_shot_num;

  // Trace value measurement units
  // -1 - Other
  //  0 - Unknown
  //  1 - Pascals
  //  2 - Volts
  //  3 - MilliVolts
  //  4 - Amperes
  //  5 - Meters
  //  6 - Velocity (m/s)
  //  7 - Acceleration (m/s^2)
  //  8 - Newtons
  //  9 - Watts
  short int measurement_units;

  // transduction constant is a float
  // x4 bytes for the mantissa, x2 bytes power of
  // 10 exponent, (205-208) * 10 ** (209-210)
  int transduction_mantissa;
  short int transfuction_exponent;

  // Trace value measurement units
  // -1 - Other
  //  0 - Unknown
  //  1 - Pascals
  //  2 - Volts
  //  3 - MilliVolts
  //  4 - Amperes
  //  5 - Meters
  //  6 - Velocity (m/s)
  //  7 - Acceleration (m/s^2)
  //  8 - Newtons
  //  9 - Watts
  short int transduction_units;

  short int device_trace_id;

  // power of 10, +ve multiplu, -ve divide
  short int scalar_to_apply_to_times;

  // Source type/orientation
  // -1 - Other
  //  0 - Unknown
  //  1 - Vibrator Vertical orientation
  //  2 - Vibrator Cross-line orientation
  //  3 - Vibrator Inline orientation
  //  4 - Impulsive Vertical orientation
  //  5 - Impulsive Cross-line orientation
  //  6 - Impulsive Inline orientation
  //  7 - Distributed Impulsive Vertical orientation
  //  8 - Distributed Impulsive Cross-line orientation
  //  9 - Distributed Impulsive Inline orientation
  short int src_type_orientation;

  // Encoded in tenths of degrees 123.4 is 1234 
  // Guessing the 6-bytes is like the transduction
  int src_energy_dirn_mantissa;
  short int src_energy_dirn_exponent;

  int src_measurement_mantissa;
  short int src_measurement_exponent;

  // source measurement units
  // -1 - Other
  //  0 - Unknown
  //  1 - Joule
  //  2 - KiloWatt
  //  3 - Pascal
  //  4 - Bar or Bar-m?
  //  5 - Newton
  //  6 - Kilograms
  short int src_measurement_units;

  // wotever
  char unassigned[8];
};

typedef std::vector<float> TraceData;
typedef std::pair<TraceHeader, TraceData> Trace;

// opens at first trace in the file
int open_traces(const std::string filename, std::ifstream& segy);
// If you want to start reading from a specific trace of ensemble, specify the offsets.
// In each case this an offset from the first trace or ensemble.
// If you supply both a trace_offset and an ensemble_offset, the trace_offset will be
// offset the trace within the ensemble.
int rewind_trace(std::ifstream& segy, int trace_offset=0, int ensemble_offset=0);
// segy data is big-endian, pretty much everything now is little endian,
// supply a byteswap if you need to do that. If the trace data is in ibm float format,
// which is most likely, then the parameter 0 returns big endian, and 1 return little endian.
int read_trace_header(std::ifstream& segy, TraceHeader& hdr, bool byteswap=1);
int read_trace_data(std::ifstream& segy, TraceData& data, bool byteswap=1);
int read_trace(std::ifstream& segy, Trace& trace, bool byteswap=1);
// or read the whole ensemble, if the data is organized that way.
int read_ensemble_headers(std::ifstream& segy, std::vector<TraceHeader>& hdrs,
			  bool byteswap=1);
int read_ensemble_data(std::ifstream& segy, std::vector<TraceData>& data,
		       bool byteswap=1);
int read_ensemble(std::ifstream& segy, std::vector<Trace>& traces,
		  bool byteswap=1);

#endif
