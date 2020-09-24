#include <iostream>
#include <ctime>
#include <cstdlib>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m" 

time_t now = time(0);
char* date_time = ctime(&now);	

struct bench_formater{
	std::string bench_fun_name;
	std::chrono::duration<double> chrono_diff;
	std::string full_time;
};

class Timer{
	private:
		std::chrono::time_point<std::chrono::steady_clock> _start_timepoint;
		inline static std::vector<bench_formater> _benchmark_call_tracker;
		std::size_t _call_count = 0;
		inline static std::chrono::time_point<std::chrono::steady_clock> _start;
		inline static std::chrono::time_point<std::chrono::steady_clock> _end;
		inline static std::vector<std::string> _bench_time_line;
		inline static ::bench_formater* _format_container;
		inline static std::string _final_console_print;
	public:
		static void timer_start(std::string&& bench_function) noexcept;
		static void timer_stop() noexcept;
		static void end_of_file() noexcept;
		Timer()=default;
		~Timer()=default;
};

void Timer::timer_start(std::string &&bench_function) noexcept {
	 _start = std::chrono::steady_clock::now();	
	 _format_container = new bench_formater; // object creation
	 _format_container->bench_fun_name = std::move(bench_function);
}

void Timer::timer_stop() noexcept {
	_end = std::chrono::steady_clock::now();
	_format_container->chrono_diff = _end - _start;
	_format_container->full_time = std::to_string(_format_container->chrono_diff.count()) + " secs";
	_benchmark_call_tracker.emplace_back(std::move(*_format_container));
	delete _format_container;
}

void Timer::end_of_file() noexcept {
	_final_console_print = std::string(GREEN) + "Benchmark Function\t\t\tTime\n" + std::string(RESET) + std::string(RED) + "------------------------------------------------------\n" + std::string(RESET);
	for(const bench_formater& bench : _benchmark_call_tracker){
		_final_console_print += bench.bench_fun_name + "            " + bench.full_time + "\n";
	}
	std::cout << _final_console_print << std::endl;
}
// Todo: Implementation of dumping a date_time.json file as a log for performance benchmark



