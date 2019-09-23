#ifndef __MEMMAP_DEVICE__

// we'll ASSUME a device is mapped to a single contiguous 64k block of memory...

class memmap_device {
 public:
  memmap_device() : base_address(0), extent(0), is_implemented(false) { };
  virtual ~memmap_device() { };

  // map device to some contiguous block of memory...
  
  virtual void MapDevice(unsigned long long _base_address,unsigned long long _extent=0xffff) {
    base_address = _base_address;
    extent = _extent;
    is_implemented = true;
    Reset();
  };
  
  virtual std::string Name() { return std::string("?"); };
  virtual std::string RegisterName(unsigned long long PA) { return std::string("?"); };
  
  // reset device...

  virtual void Reset() {};

  // returns true once device has been mapped to some physical address range...

  virtual bool IsImplemented() { return is_implemented; };

  // return true if physical address falls within memory-mapped device address range...
  
  virtual bool InRange(unsigned long long PA) { return (PA >= base_address) && (PA <= (base_address + 0xffc)); };

  // return true if physical address maps to a defined device register...

  virtual bool IsMapped(unsigned long long PA) { return register_index(PA) != -1; };

  // will ASSUME memory-mapped devices are little-endian...
  
  virtual bool BigEndian() { return false; };
  
  // translate physical address into device register index...

  virtual int register_index(unsigned long long PA) { return -1; };

  // read or write to device register(s) - we'll let the device figure out how to map access size to device register(s)

  virtual int Read(unsigned long long PA,unsigned char *buffer,int access_size) { return -1; };
  virtual int Write(unsigned long long PA,unsigned char *buffer,int access_size)  { return -1; };

  // device memory endianness matches 'host' endianness...

  virtual bool Endianness() {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return false;
#else
    return true;
#endif
  }

  virtual int RegisterSize() { return 4; };  // default memory-mapped register size is 32 bits (4 bytes)
  
 protected:
  unsigned long long base_address;   // device (physical) base address,
  unsigned long long extent;         //   block size
  bool               is_implemented; // a device is implemented if it has been mapped to some memory range
};

#define __MEMMAP_DEVICE__
#endif
