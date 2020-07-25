#include "Opus.hpp"

using namespace opus;

OpusApi OpusWorkObject::m_api;

int Encoder::create(
		const CodecAttributes& attributes
		){

	int error_number;
	m_encoder = api()->encoder_create(
				attributes.sampling_frequency(),
				attributes.channel_count(),
				attributes.type(),
				&error_number
				);

	if( m_encoder == 0 ){
		set_error_number(error_number);
		return -1;
	}
	m_channels = attributes.channel_count();
	return 0;
}

void Encoder::destroy(){
	if( m_encoder ){
		api()->encoder_destroy(m_encoder);
		m_encoder = nullptr;
	}
}

int Encoder::encode(SourceData input,
		DestinationData output
		){
	int result = api()->encode(
				m_encoder,
				input.argument().to<const opus_int16>(),
				input.argument().count<opus_int16>()/(m_channels),
				output.argument().to_u8(),
				output.argument().size()
				);
	return result;
}

int Encoder::encode_float(SourceData input,
		DestinationData output
		){
	int result = api()->encode_float(
				m_encoder,
				input.argument().to<const float>(),
				input.argument().count<float>()/(m_channels),
				output.argument().to_u8(),
				output.argument().size()
				);
	return result;
}

int Encoder::ctl(
		arg::OpusControlRequest request,
		arg::OpusControlArgument args
		){
	return api()->encoder_ctl(
				m_encoder,
				request.argument(),
				args.argument()
				);
}

int Encoder::get_size(
		arg::OpusChannelCount channel_count
		){
	return api()->encoder_get_size(
				channel_count.argument()
				);
}

int Decoder::get_size(
		arg::OpusChannelCount channel_count
		){
	return api()->decoder_get_size(
				channel_count.argument()
				);
}

int Decoder::create(
		const CodecAttributes& attributes
		){
	int error_number;
	m_decoder = api()->decoder_create(
				attributes.sampling_frequency(),
				attributes.channel_count(),
				&error_number
				);
	if( m_decoder == nullptr ){
		set_error_number(error_number);
		return -1;
	}
	return 0;
}

void Decoder::destroy(){
	if( m_decoder ){
		api()->decoder_destroy(m_decoder);
		m_decoder = nullptr;
	}
}

int Decoder::decode(
		SourceData input,
		DestinationData output
		){

	return api()->decode(
				m_decoder,
				input.argument().to<const unsigned char>(),
				input.argument().size(),
				output.argument().to<opus_int16>(),
				output.argument().count<opus_int16>(),
				0
				);
}

int Decoder::decode_float(
		SourceData input,
		DestinationData output
		){

	return api()->decode_float(
				m_decoder,
				input.argument().to<const unsigned char>(),
				input.argument().size(),
				output.argument().to_float(),
				output.argument().count<float>(),
				0
				);
}

int Decoder::ctl(
		arg::OpusControlRequest request,
		arg::OpusControlArgument args
		){
	return api()->decoder_ctl(
				m_decoder,
				request.argument(),
				args.argument()
				);
}

int Decoder::get_sample_count(const var::Data& input
		){
	return 0;
}
