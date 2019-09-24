#ifndef OPUS_HPP
#define OPUS_HPP

#include <sapi/sys/Sys.hpp>
#include <sapi/var/Data.hpp>
#include <sapi/arg/Argument.hpp>
#include <sapi/dsp/SignalData.hpp>
#include "opus_api.h"

namespace arg {

using OpusSampleFrequency = Argument<s32, struct OpusSampleFrequencyTag>;
using OpusChannelCount = Argument<u32, struct OpusChannelCountTag>;
using OpusControlRequest = Argument<int, struct OpusControlRequestTag>;
using OpusControlArgument = Argument<void*, struct OpusControlArgumentTag>;

}

namespace opus {

using OpusApi = api::Api<opus_api_t, OPUS_API_REQUEST>;


class OpusWorkObject : public api::WorkObject {
public:

	 OpusWorkObject(){}

	 static OpusApi & api(){ return m_api; }

protected:


private:
	 static OpusApi m_api;

};

class Encoder : public OpusWorkObject {
public:

    Encoder(){
        m_encoder = 0;
    }

    ~Encoder(){
        destroy();
    }

	 enum application_type {
        APPLICATION_VOIP = OPUS_APPLICATION_VOIP,
        APPLICATION_AUDIO = OPUS_APPLICATION_AUDIO,
        APPLICATION_RESTRICTED_LOWDELAY = OPUS_APPLICATION_RESTRICTED_LOWDELAY
    };

	 int create(
			 arg::OpusSampleFrequency sampling_frequency,
			 arg::OpusChannelCount channel_count,
			 enum application_type application = APPLICATION_VOIP
			 );

	 void destroy();

	 int encode(
			 const arg::SourceData input,
			 arg::DestinationData output
			 );

	 int encode_float(
			 const arg::SourceData input,
			 arg::DestinationData output
			 );

	 int ctl(
			 arg::OpusControlRequest request,
			 arg::OpusControlArgument args = arg::OpusControlArgument(nullptr)
			 );

	 int get_size(
			 arg::OpusChannelCount channel_count
			 );

private:
    OpusEncoder * m_encoder;
    u8 m_channels;


};

class Decoder : public OpusWorkObject {
public:

	 int get_size(
			 arg::OpusChannelCount channel_count
			 );

	 int create(
			 arg::OpusSampleFrequency sampling_frequency,
			 arg::OpusChannelCount channel_count
			 );

	 void destroy();

	 int decode(
			 const arg::SourceData input,
			 arg::DestinationData output
			 );

	 int decode_float(
			 const arg::SourceData input,
			 arg::DestinationData output
			 );

	 int ctl(
			 arg::OpusControlRequest request,
			 arg::OpusControlArgument args = arg::OpusControlArgument(nullptr)
			 );

	 int get_sample_count(
			 const arg::SourceData input
			 );

private:
    OpusDecoder * m_decoder;


};

class Packet : public OpusWorkObject {
public:

	 int get_bandwidth(
			 const arg::SourceData data
			 );

	 int get_samples_per_frame(
			 const arg::SourceData data,
			 arg::OpusSampleFrequency
			 );

	 int get_sample_count(
			 const arg::SourceData data
			 );

	 int pad(
			 arg::DestinationData data,
			 arg::Length length
			 );

	 int unpad(
			 arg::DestinationData data,
			 arg::Length length
			 );

	 int pad_multistrem(
			 arg::DestinationData data,
			 arg::Length length
			 );

	 int unpad_multistream(
			 arg::DestinationData data,
			 arg::Length length
			 );



};

class Repacketizer : public OpusWorkObject {
public:

    //get size
    //create
    //destroy
    //cat
    //out range
    //get nb frames
    //out

private:
    OpusRepacketizer * m_repacketizer;


};

}



#endif // OPUS_HPP
