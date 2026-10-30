

#ifndef UALINK_BLOCK_ENCODING_H
#define UALINK_BLOCK_ENCODING_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace ualink {

static constexpr uint8_t BLOCK_CMD_INVOKE     = 0x20;
static constexpr uint8_t BLOCK_CMD_ALLOCATE   = 0x21;
static constexpr uint8_t BLOCK_CMD_DEALLOCATE = 0x22;

struct block_ctrl {
  uint8_t  btype = 0;      
  uint8_t  ctype = 0;      
  uint32_t len = 0;        
  uint8_t  ropdt = 0;      
  uint8_t  rmode = 0;      
  uint64_t i_off = 0;      
  uint64_t o_off = 0;      
  uint64_t s_off = 0;      
  uint32_t xsize = 0;      
  uint32_t ysize = 0;      
  uint32_t ssize = 0;      
  uint32_t ssize2 = 0;     
  uint32_t sseed = 0;      
};

struct block_req {
  uint8_t  cmd = BLOCK_CMD_INVOKE;
  uint8_t  sq = 0;              
  uint8_t  entries_minus1 = 0;  
  bool     drain_only = false;  
  uint64_t base_addr = 0;       
  uint64_t status_addr = 0;     
  block_ctrl ctrl;
};

std::array<uint8_t, 64> encode_block_ctrl(const block_ctrl& c);
bool decode_block_ctrl(const std::array<uint8_t, 64>& p, block_ctrl& c,
                       std::string* err = nullptr);

uint64_t encode_allocate_req_addr(uint8_t sq, uint8_t entries_minus1);
uint64_t encode_deallocate_req_addr(uint8_t sq, bool drain_only);
uint64_t encode_invoke_req_addr(uint8_t sq, uint64_t base_addr);
bool decode_block_req_addr(uint8_t cmd, uint64_t req_addr, block_req& r,
                           std::string* err = nullptr);

std::array<uint8_t, 64> encode_block_req_payload(const block_req& r);
bool decode_block_req_payload(uint8_t cmd, uint64_t req_addr,
                              const std::array<uint8_t, 64>& payload,
                              block_req& r, std::string* err = nullptr);

uint8_t encode_block_status_byte(bool valid, uint8_t status);
bool decode_block_status_byte(uint8_t b, bool& valid, uint8_t& status);

std::array<uint8_t, 16> encode_invoke_status(bool v0, bool v1,
                                             uint8_t istatus, bool w,
                                             uint16_t bstatus, uint16_t accid,
                                             uint64_t fail_addr);
bool decode_invoke_status(const std::array<uint8_t, 16>& b, bool& v0,
                          bool& v1, uint8_t& istatus, bool& w,
                          uint16_t& bstatus, uint16_t& accid,
                          uint64_t& fail_addr);

}  

#endif
