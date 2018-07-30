#ifndef OPUS_HPP
#define OPUS_HPP

#include <sapi/sys/Sys.hpp>
#include <sapi/var/Data.hpp>
#include <sapi/dsp/SignalData.hpp>
#include "opus_api.h"

namespace opus {


typedef var::Vector<unsigned char> EncodedData;


class OpusWorkObject : public api::WorkObject {
public:
    OpusWorkObject(){
        if( sys::Sys::request(OPUS_API_REQUEST, &m_api) < 0 ){
            set_error_number(ENOENT);
        }
    }

protected:
    const opus_api_t * api(){ return m_api; }

private:
    const opus_api_t * m_api;

};

class Encoder : public OpusWorkObject {
public:

    Encoder(){
        m_encoder = 0;
    }

    ~Encoder(){
        destroy();
    }

    enum {
        APPLICATION_VOIP = OPUS_APPLICATION_VOIP,
        APPLICATION_AUDIO = OPUS_APPLICATION_AUDIO,
        APPLICATION_RESTRICTED_LOWDELAY = OPUS_APPLICATION_RESTRICTED_LOWDELAY
    };

    int create(s32 sampling_frequency, int channels, int application = APPLICATION_VOIP){
        int error_number;
        m_encoder = api()->encoder_create(sampling_frequency, channels, application, &error_number);
        if( m_encoder == 0 ){
            set_error_number(error_number);
            return -1;
        }
        m_channels = channels;
        return 0;
    }

    void destroy(){
        if( m_encoder ){
            api()->encoder_destroy(m_encoder);
            m_encoder = 0;
        }
    }

    int encode(const dsp::SignalQ15 & input, EncodedData & output){
        return api()->encode(m_encoder,
                             input.vector_data_const(), input.size()*m_channels,
                             (u8*)output.cdata(), output.capacity());
    }

    int encode(const dsp::SignalF32 & input, EncodedData & output){
        return api()->encode_float(m_encoder,
                                   input.vector_data_const(), input.size()*m_channels,
                                   (u8*)output.cdata(), output.capacity());
    }

    int ctl(int request, void * args = 0){
        return api()->encoder_ctl(m_encoder, request, args);
    }

    int get_size(int channels){
        return api()->encoder_get_size(channels);
    }

private:
    OpusEncoder * m_encoder;
    u8 m_channels;


};

class Decoder : public OpusWorkObject {
public:

    int get_size(int channels){
        return api()->decoder_get_size(channels);
    }

    int create(s32 sampling_frequency, int channels){
        int error_number;
        m_decoder = api()->decoder_create(sampling_frequency, channels, &error_number);
        if( m_decoder == 0 ){
            set_error_number(error_number);
            return -1;
        }
        return 0;
    }

    void destroy(){
        if( m_decoder ){
            api()->decoder_destroy(m_decoder);
            m_decoder = 0;
        }
    }

    int decode(const EncodedData & input, dsp::SignalQ15 & output){
        return api()->decode(m_decoder, input.vector_data_const(), input.count(), output.vector_data(), output.capacity(), 0);
    }

    int decode(const EncodedData & input, dsp::SignalF32 & output){
        return api()->decode_float(m_decoder, input.vector_data_const(), input.count(), output.vector_data(), output.capacity(), 0);
    }

    int ctl(int request, void * args = 0){
        return api()->decoder_ctl(m_decoder, request, args);
    }

    int get_nb_samples(const EncodedData & data){
        return 0;
    }

private:
    OpusDecoder * m_decoder;


};

class Packet : public OpusWorkObject {
public:

    int get_bandwidth(const EncodedData & data);
    int get_samples_per_frame(const EncodedData & data, s32 sampling_frequency);
    int get_nb_samples(const EncodedData & packet);
    int pad(EncodedData & data, u32 new_length);
    int unpad(EncodedData & data, u32 new_length);
    int pad_multistrem(EncodedData & data, u32 new_length);
    int unpad_multistream(EncodedData & data, u32 new_length);



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
