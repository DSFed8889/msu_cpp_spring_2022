#include "ExtSort.hpp"


namespace customExtSort {
	void separate(const std::string & input_file, const std::string & output_file1, const std::string & output_file2, size_t series_size) {
		uint64_t num;
		size_t series_count = 0;
		bool eof = false;
		std::ifstream input(input_file);
		std::ofstream output1(output_file1);
		std::ofstream output2(output_file2);
		while(!eof) {
			if((series_count++) % 2) {
				for (size_t i = 0; i < series_size; ++i) {
					eof = !(input.read((char*)&num, sizeof(num)));
					if (eof)
						break;
					output2.write((char *) &num, sizeof(num));
				}
			}
			else {
				for (size_t i = 0; i < series_size; ++i) {
					eof = !(input.read((char*)&num, sizeof(num)));
					if (eof)
						break;
					output1.write((char *) &num, sizeof(num));
				}
			}
		}
		input.close();
		output1.close();
		output2.close();
	}
	
	void merge(const std::string & input_file1, const std::string & input_file2, const std::string & output_file, size_t series_size) {
		uint64_t n1;
		uint64_t n2;
		bool eof1;
		bool eof2;
		std::ifstream input1(input_file1);
		std::ifstream input2(input_file2);
		std::ofstream output(output_file);
		
		eof1 = !(input1.read((char*)&n1, sizeof(n1)));
		eof2 = !(input2.read((char*)&n2, sizeof(n2)));
		
		while(!eof1 && !eof2) {
			size_t i1 = 0;
			size_t i2 = 0;
			
			while (i1 < series_size && i2 < series_size) {
				if (n1 <= n2) {
					output.write((char *) &n1, sizeof(n1));
					++i1;
					eof1 = !(input1.read((char*)&n1, sizeof(n1)));
					if (eof1)
						break;
				}
				else {
					output.write((char *) &n2, sizeof(n2));
					++i2;
					eof2 = !(input2.read((char*)&n2, sizeof(n2)));
					if (eof2)
						break;
				}
			}
			
			if (!eof1) {
				for (; i1 < series_size; ++i1) {
					output.write((char *) &n1, sizeof(n1));
					eof1 = !(input1.read((char *) &n1, sizeof(n1)));
					if (eof1)
						break;
				}
			}
			
			if (!eof2) {
				for (; i2 < series_size; ++i2) {
					output.write((char *) &n2, sizeof(n2));
					eof2 = !(input2.read((char *) &n2, sizeof(n2)));
					if (eof2)
						break;
				}
			}
		}
		
		if (!eof1) {
			output.write((char *) &n1, sizeof(n1));
			while(input1.read((char*)&n1, sizeof(n1)))
				output.write((char *) &n1, sizeof(n1));
		}
		if (!eof2) {
			output.write((char *) &n2, sizeof(n2));
			while(input2.read((char*)&n2, sizeof(n2)))
				output.write((char *) &n2, sizeof(n2));
		}
		
		input1.close();
		input2.close();
		output.close();
	}
	
	void SortFile(const std::string & input_file, size_t size) {
		std::string output_file1;
		std::string output_file2;
		if (input_file[input_file.size() - 1] == '1') {
			output_file1 = "./output11";
			output_file2 = "./output12";
		}
		else {
			output_file1 = "./output21";
			output_file2 = "./output22";
		}
		
		size_t series_size = 1;
		while (series_size < size) {
			separate(input_file, output_file1, output_file2, series_size);
			merge(output_file1, output_file2, input_file, series_size);
			series_size <<= 1;
		}
		
		std::remove(output_file1.c_str());
		std::remove(output_file2.c_str());
	}

	void ExtSort(const std::string & input_file, const std::string & output_file) {
		uint64_t num;
		size_t size = 0;
		std::string input_file1 = "./input1";
		std::string input_file2 = "./input2";
		std::ifstream input(input_file);
		while(input.read((char*)&num, sizeof(num)))
			size++;
		input.close();

		separate(input_file, input_file1, input_file2, 1);

		std::thread thread1(SortFile, input_file1, (size >> 1) + (size & 1));
		std::thread thread2(SortFile, input_file2, (size >> 1));
		thread1.join();
		thread2.join();

		merge(input_file1, input_file2, output_file, size);

		std::remove(input_file1.c_str());
		std::remove(input_file2.c_str());
	}
}