#include "cantcoap.h"
#include <string>
#include <cstring>
#include <cstdlib>

struct Options {
    CoapPDU::Code code;
    const char * hostname;
    const char * path;
    const char * data;
    bool confirmable;
};

class CoapRequest : public CoapPDU {
    public:
        CoapRequest(const Options & opt) : CoapPDU() {
	        setVersion(1);
	        if (!opt.confirmable) {
	            setType(CoapPDU::COAP_CONFIRMABLE);
            } else {
                setType(CoapPDU::COAP_NON_CONFIRMABLE);
            }
            setCode(opt.code);
            std::string token = generateToken(4);
            unsigned int token_len = std::strlen(token.c_str());
            if (token_len) {
                setToken((uint8_t*)token.c_str(), token_len);
            }
	        setMessageID(generateID());
	        unsigned int uri_len = std::strlen(opt.path);
	        setURI((char *)opt.path, uri_len);
	        remote_addr = std::string(opt.hostname);

            unsigned int payload_len = std::strlen(opt.data);
            if (payload_len) {
		        setContentFormat(CoapPDU::COAP_CONTENT_FORMAT_TEXT_PLAIN);
		        setPayload((uint8_t *)opt.data, payload_len);
            }

        }
        std::string generateToken(unsigned int size) {
            return std::string(std::to_string(rand() % size));
        }

        int generateID() {
            return rand();
        }

        std::string remote_addr;
};

int main(int argc, char **argv) {
    Options opt1 = {CoapPDU::COAP_PUT, "hostname", "/gateways/1/config", "127.0.0.1", true};
    Options opt2 = {CoapPDU::COAP_GET, "127.0.0.1", "/nodes/1/temperature", "hahaha"};
    CoapRequest r1(opt1);
    CoapRequest r2(opt2);
    r1.printHuman();
    r2.printHuman();
}
