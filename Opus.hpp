#ifndef OPUS_HPP
#define OPUS_HPP

#include <sapi/sys/requests.h>
#include <sapi/var/Data.hpp>
#include <sapi/dsp/SignalData.hpp>
#include "opus_api.h"

namespace opus {


typedef var::Vector<unsigned char> OpusData;


class OpusObject : public api::WorkObject {
public:
    OpusObject();

protected:
    static const opus_api_t * api(){ return m_api; }

private:
    static const opus_api_t * m_api;

};

class Encoder : public OpusObject {
public:
    int create(s32 sampling_frequency, int channels, int application){
        int error_number;
        m_encoder = api()->encoder_create(sampling_frequency, channels, application, &error_number);
        if( m_encoder == 0 ){
            set_error_number(error_number);
            return -1;
        }
        return 0;
    }

    int encode(const dsp::SignalQ15 & input, OpusData & output){
        return api()->encode(m_encoder, input.vector_data_const(), input.count(), (u8*)output.cdata(), output.capacity());
    }

    int encode(const dsp::SignalF32 & input, OpusData & output){
        return api()->encode_float(m_encoder, input.vector_data_const(), input.count(), (u8*)output.cdata(), output.capacity());
    }

    int ctl(int request, void * args = 0){
        return api()->encoder_ctl(m_encoder, request, args);
    }

    static int get_size(int channels){
        return api()->encoder_get_size(channels);
    }

private:
    OpusEncoder * m_encoder;


};

class Decoder : public OpusObject {
public:

    static int get_size(int channels){
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

    int decode(const OpusData & input, dsp::SignalQ15 & output){
        return api()->decode(m_decoder, input.vector_data_const(), input.count(), output.vector_data(), output.capacity(), 0);
    }

    int decode(const OpusData & input, dsp::SignalF32 & output){
        return api()->decode_float(m_decoder, input.vector_data_const(), input.count(), output.vector_data(), output.capacity(), 0);
    }

    int ctl(int request, void * args = 0){
        return api()->decoder_ctl(m_decoder, request, args);
    }

    int get_nb_samples(const OpusData & data){
        return 0;
    }

private:
    OpusDecoder * m_decoder;


};

class Packet : public OpusObject {
public:

    static int get_bandwidth(const OpusData & data);
    static int get_samples_per_frame(const OpusData & data, s32 sampling_frequency);
    static int get_nb_samples(const OpusData & packet);
    static int pad(OpusData & data, u32 new_length);
    static int unpad(OpusData & data, u32 new_length);
    static int pad_multistrem(OpusData & data, u32 new_length);
    static int unpad_multistream(OpusData & data, u32 new_length);



};

class Repacketizer : public OpusObject {
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
