#include <string>
#include <vector>

class Memory;

class ELFIO {
 public:
  ELFIO() {};
  
  int Load(Memory &mem, string &elf_file, bool verbose);
  int Load(Memory &mem, string &elf_file, unsigned long long load_address, bool verbose);
  int Save(Memory &mem, string &elf_file, unsigned long long entry_point, bool compress, bool verbose);

 protected:
  int SaveToELF(Memory &mem, string &elf_file, vector<unsigned long long> &file_block_addresses, int file_block_size, unsigned long long entry_point, bool verbose);
  unsigned long long estimateELFFileSize(unsigned int &resulting_block_count,vector<unsigned long long> &program_block_addresses,
					 int desired_block_size, bool verbose);
  bool ChooseFileBlockSize(int &block_size_in_bits, unsigned int &resulting_block_count,vector<unsigned long long> &test_block_addresses,
			   bool verbose);
};
