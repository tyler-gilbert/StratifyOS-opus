#include "Opus.hpp"

#include <sapi/sys.hpp>
#include <sapi/sys/requests.h>

using namespace opus;

const opus_api_t * OpusObject::m_api;


OpusObject::OpusObject(){
    if( m_api == 0 ){
        Sys::request(OPUS_API_REQUEST, &m_api);
    }
}
