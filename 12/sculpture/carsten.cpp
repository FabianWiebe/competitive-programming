#include <algorithm>
#include <array>
#include <iostream>
#include <list>

class Sculptor
{
public:
	Sculptor(uint16_t log_count) : log_count{log_count} {};

	void insert(uint8_t colorA, uint8_t colorB)
	{
		log_matrix[colorA][colorB] += 1;
		log_matrix[colorB][colorA] += 1;
		color_count[colorA] += 1;
		color_count[colorB] += 1;
	}

	bool contains_odd_color()
	{
		for (uint8_t i = 0; i < color_count.size(); ++i)
		{
			if (color_count[i] % 2 != 0) return true;
		}
		return false;
	}

	std::list<std::pair<uint8_t,uint8_t>> get_sculpture()
	{
		std::list<std::pair<uint8_t,uint8_t>> logs;

		while (logs.size() < log_count)
		{
			uint8_t next_color;
			uint8_t end_color;
			auto insert_pos = logs.end();
			if (logs.empty())
			{
				logs.emplace_back(remove_any_log());
				next_color = logs.back().second;			
				end_color = logs.front().first;	
				insert_pos = logs.end();
			}
			else
			{
				std::pair<uint8_t, uint8_t> log;
				insert_pos = logs.begin();
				do
				{
					// no sculpture possible, cannot connect anything to existing ring
					if (insert_pos == logs.end()) return std::list<std::pair<uint8_t,uint8_t>>();
					log = remove_log(insert_pos->second);
					++insert_pos;
				} while (log.first == 0);

				logs.insert(insert_pos, log);
				// end_color = insert_pos == logs.end() ? logs.front().first : insert_pos->first;
				end_color = log.first;
				next_color = log.second;
			}

			while (next_color != end_color)
			{
				auto log = remove_log(next_color);
				// no sculpture possible if we get an invalid log
				if (log.first == 0)
				{
					return std::list<std::pair<uint8_t,uint8_t>>();
				}
				next_color = log.second;
				logs.insert(insert_pos, log);
			}
		}

		return logs;
	}

	std::pair<uint8_t, uint8_t> remove_log(uint8_t start_color)
	{
		for (uint8_t end_color = 1; end_color <= max_color; ++end_color)
		{
			if (log_matrix[start_color][end_color] > 0)
			{
				log_matrix[start_color][end_color] -= 1;
				log_matrix[end_color][start_color] -= 1;
				return {start_color, end_color};
			}
		}
		return {0, 0};
	}

	std::pair<uint8_t, uint8_t> remove_any_log()
	{
		for (uint8_t colorA = 1; colorA <= max_color; ++colorA)
			for (uint8_t colorB = colorA; colorB <= max_color; ++colorB)
			{
				if (log_matrix[colorA][colorB] > 0)
				{
					log_matrix[colorA][colorB] -= 1;
					log_matrix[colorB][colorA] -= 1;
					return {colorA, colorB};
				}
			}
		return {0, 0};
	}

private:
	static constexpr uint8_t max_color = 50;
	uint16_t log_count;
	std::array<uint16_t, max_color+1> color_count{};
	std::array<std::array<uint16_t, max_color+1>, max_color+1> log_matrix{};
};

int main(int argc, char ** argv)
{
	std::ios::sync_with_stdio(false);

	uint16_t case_count;
	std::cin >> case_count;

	for (uint16_t i = 1; i <= case_count; ++i)
	{
		uint16_t log_count;
		std::cin >> log_count;
		Sculptor sculptor(log_count);

		for (uint16_t j = 0; j < log_count; ++j)
		{
			uint16_t colorA;
			uint16_t colorB;
			std::cin >> colorA >> colorB;
			sculptor.insert(colorA, colorB);
		}


		std::cout << "Case #" << i << '\n';
		if (sculptor.contains_odd_color())
		{
			std::cout << "some trusses may be lost\n";
		}
		else
		{
			auto result = sculptor.get_sculpture();
			if (result.empty())
			{
				std::cout << "some trusses may be lost\n";
			}
			else
			{
				for (auto && log : result)
				{
					std::cout << static_cast<uint16_t>(log.first) << ' ' << static_cast<uint16_t>(log.second) << '\n';
				}
			}
		}
		if (i != case_count) std::cout << '\n';
	}
}

