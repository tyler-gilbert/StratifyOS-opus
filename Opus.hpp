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

class OpusFlags {
public:
	enum application_type {
		application_type_voip = OPUS_APPLICATION_VOIP,
		application_type_audio = OPUS_APPLICATION_AUDIO,
		application_type_restricted_lowdelay = OPUS_APPLICATION_RESTRICTED_LOWDELAY
	};
};

class OpusWorkObject : public api::WorkObject {
public:

	using SourceData = arg::Argument<const var::Data &, struct OpusWorkObjectSourceDataTag>;
	using DestinationData = arg::Argument<var::Data &, struct OpusWorkObjectSourceDataTag>;
	using Length = arg::Argument<u32, struct OpusWorkObjectLengthTag>;

	OpusWorkObject(){}

	static OpusApi & api(){ return m_api; }

protected:


private:
	static OpusApi m_api;

};

class CodecAttributes : public OpusFlags {
public:
	CodecAttributes(){}

	CodecAttributes& set_sampling_frequency(
			u32 value
			){
		m_sampling_frequency = value;
		return *this;
	}

	CodecAttributes& set_channel_count(
			u32 value
			){
		m_channel_count = value;
		return *this;
	}

	CodecAttributes& set_application_type(
			enum application_type value
			){
		m_application_type = value;
		return *this;
	}

	u32 sampling_frequency() const {
		return m_sampling_frequency;
	}

	u32 channel_count() const {
		return m_channel_count;
	}

	enum application_type type() const {
		return m_application_type;
	}

private:
	u32 m_sampling_frequency = 16000;
	u32 m_channel_count = 2;
	enum application_type m_application_type = application_type_voip;
};

class Encoder : public OpusWorkObject, public OpusFlags {
public:


	Encoder(){
		m_encoder = 0;
	}

	~Encoder(){
		destroy();
	}

	int create(const CodecAttributes& attributes);

	void destroy();

	int encode(
			SourceData input,
			DestinationData output
			);

	int encode_float(
			SourceData input,
			DestinationData output
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

class Decoder : public OpusWorkObject, public OpusFlags {
public:

	int get_size(
			arg::OpusChannelCount channel_count
			);

	int create(const CodecAttributes& attributes);

	void destroy();

	int decode(
			SourceData input,
			DestinationData output
			);

	int decode_float(
			SourceData input,
			DestinationData output
			);

	int ctl(
			arg::OpusControlRequest request,
			arg::OpusControlArgument args = arg::OpusControlArgument(nullptr)
			);

	int get_sample_count(
			const var::Data & input
			);

private:
	OpusDecoder * m_decoder;


};

class Packet : public OpusWorkObject, public OpusFlags {
public:

	int get_bandwidth(
			const var::Data & data
			);

	int get_samples_per_frame(
			const var::Data & data,
			arg::OpusSampleFrequency
			);

	int get_sample_count(
			const var::Data & data
			);

	int pad(
			var::Data & data,
			Length length
			);

	int unpad(
			var::Data & data,
			Length length
			);

	int pad_multistrem(
			var::Data & data,
			Length length
			);

	int unpad_multistream(
			var::Data & data,
			Length length
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
