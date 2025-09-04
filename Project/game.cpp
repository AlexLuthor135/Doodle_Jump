#include "./inc/AllHeaders.hpp"
#include "./inc/GameEngine.hpp"

void ft_error(std::string error)
{
	std::cerr << error << std::endl;
	exit(1);
}

void set_window(char **argv, int &height, int &width)
{
	std::string arg = argv[1];
	std::string value = argv[2];

	if (arg == "-window")
	{
		std::regex pattern(R"(^(\d{2,4})x(\d{2,4})$)");
		std::smatch matches;
		if (std::regex_match(value, matches, pattern))
		{
			width = std::stoi(matches[1].str());
			height = std::stoi(matches[2].str());

			if (width < 400 || height < 600)
				ft_error("Window size too small. Minimum recommended size is 400x600.");
		}
		else
			ft_error("Invalid window size format. Use WIDTHxHEIGHT (e.g., 800x800).");
	}
	else
		ft_error("Unknown argument: " + arg);
}

int main(int argc, char **argv)
{
	int height = 0;
	int width = 0;
	bool fullscreen = false;
	if (argc == 1)
		ft_error(std::string("Usage:\n") + "  " + argv[0] + " -fullscreen\n" + "  " + argv[0] + " -window WIDTHxHEIGHT\n");
	else if (argc == 3)
		set_window(argv, height, width);
	else
		ft_error("Wrong amount of arguments");
	try {
        std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>(height, width, fullscreen);
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
