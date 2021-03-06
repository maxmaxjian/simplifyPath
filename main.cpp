#include <iostream>
#include <string>
#include <vector>
#include <numeric>

class solution {
public:
    std::string simplify(const std::string & path) {
	std::vector<std::string> vec = split(path);
	auto curr = vec.begin(), next = std::next(curr);
	while (next != vec.end()) {
	    while (next != vec.end() && (!next->compare(".") || !next->compare(".."))) {
		if (!next->compare("."))
		    next = vec.erase(next);
		else if (!next->compare("..")) {
		    curr = vec.erase(curr);
		    curr = vec.erase(curr);
		    if (!curr->compare("..")) {
			curr = std::prev(curr);
			next = std::next(curr);
		    }
		}
	    }
	    if (next != vec.end()) {
		if (next->compare(".") && next->compare("..")) {
		    curr = next;
		    next = std::next(curr);
		}
	    }
	}

	std::string result = std::accumulate(vec.begin(), vec.end(), std::string("/"),
					     [](const std::string & s1, const std::string & s2){
						 return !s1.compare("/") ? s1+s2 : s1+"/"+s2;
					     });
	return result;
    }

private:
    std::vector<std::string> split(const std::string & path) {
	std::vector<std::string> vec;
	size_t begin, end;
	begin = path.find_first_not_of("/");
	while (begin != std::string::npos) {
	    end = path.find_first_of("/", begin);
	    vec.push_back(path.substr(begin, end-begin));
	    begin = path.find_first_not_of("/", end);
	}
	return vec;
    }
};

int main() {
    // std::string path{"/home/"};
    std::string path{"/a/./b/../../c/"};

    solution soln;
    std::string simplified = soln.simplify(path);
    std::cout << "The simplified path is:\n"
	      << simplified << std::endl;
}
